#include <fstream>

#include "MultiplayerState.h"
#include "network/Protocol.h"
#include "util/Savefile.h"

MultiplayerState::MultiplayerState(StateManager& stateManager, State::SharedContext context, bool host)
    : State(stateManager, context), host(host), gui(*context.window) {
    setupGUI();

    if (host) {
        server.reset(new Server());
        currentIp = LOCALHOST;
    } else {
        Savefile save;
        auto lastIp = save.getSaveData<std::string>("last_ip");
        currentIp = sf::IpAddress(lastIp);
    }

    connect(currentIp);
    socket.setBlocking(false);
}

void MultiplayerState::setupGUI() {
    gui.add(chatBox, "chatBox");
    gui.add(chatInput, "chatInput");

    chatBox->setPosition("7%", "70%");
    chatBox->setSize("25%", "20%");
    chatBox->setInheritedOpacity(chatOpacity);
    chatBox->addLine("--- CHAT START ---");

    chatInput->setPosition("chatBox.left", "chatBox.bottom + height / 4");
    chatInput->setSize("chatBox.width", "chatBox.height / 5");
    chatInput->setInheritedOpacity(chatOpacity);
    chatInput->setVisible(false);
}

void MultiplayerState::draw() {
    if (currPlayerID != sf::Int32(-1)) {
        players[currPlayerID]->draw(*context.window);
    }
    gui.draw();
}

void MultiplayerState::handleEvent(const sf::Event& event) {
    gui.handleEvent(event);
    handleChatEvent(event);
}

void MultiplayerState::update(float delta) {
    if (chatInput->getText().isEmpty() && currPlayerID != sf::Int32(-1)) {
        players[currPlayerID]->update(delta);
    }

    // Handle messages from server
    if (connected) {
        sf::Packet packet;
        if (socket.receive(packet) == sf::Socket::Done) {
            sf::Int32 packetHeader;
            packet >> packetHeader;
            handlePacket(packetHeader, packet);
        } else {
            if (lastPacketReceived > CONNECTION_TIMEOUT) {
                connected = false;
                failedConnection.restart();
                chatBox->addLine("You got disconnected");
                return;
            }
        }

        // Position update package
        if (tickClock.getElapsedTime() > sf::seconds(1.0f / 30.0f)) {
            sf::Packet positionUpdate;
            positionUpdate << static_cast<sf::Int32>(Packet::Client::PositionUpdate);
            positionUpdate << playerID;
            auto localPlayer = players.find(currPlayerID);
            if (localPlayer == players.end()) {
                return;
            }
            auto playerPos = localPlayer->second->position;
            positionUpdate << playerPos.x;
            positionUpdate << playerPos.y;
            positionUpdate << socket.send(positionUpdate);
            tickClock.restart();
        }
    }

    if (!connected && failedConnection.getElapsedTime() >= CONNECTION_TIMEOUT) {
        requestClear();
        requestPush(StateType::MainMenu);
    }
}

void MultiplayerState::connect(const sf::IpAddress ip) {
    auto connectionStatus = socket.connect(ip, SERVER_PORT, CONNECTION_TIMEOUT);
    if (connectionStatus == sf::TcpSocket::Done) {
        connected = true;
    } else {
        failedConnection.restart();
        chatBox->addLine("Connection error, going back to main menu.");
    }
}

void MultiplayerState::handlePacket(sf::Int32 packetHeader, sf::Packet& packet) {
    switch (packetHeader) {
        case Packet::Server::BroadcastMessage: {
            std::string message;
            packet >> message;
            chatBox->addLine(message);
        } break;

        case Packet::Server::SpawnSelf: {
            sf::Vector2f spawnPos;
            packet >> currPlayerID >> spawnPos.x >> spawnPos.y;

            Player* player = new Player(currPlayerID, &socket);
            player->position = spawnPos;
            players[currPlayerID].reset(player);
            gameStarted = true;

            std::stringstream s;
            s << "Player " << currPlayerID << ": Joined game at position: (" << spawnPos.x << " , "
              << spawnPos.y << ")";
            chatBox->addLine(s.str());
        } break;

        case Packet::Server::InitialState: {
            sf::Int32 playerCount;
            packet >> playerCount;
            for (sf::Int32 i = 0; i < playerCount; ++i) {
                sf::Int32 playerID;
                sf::Vector2f pos;
                packet >> playerID >> pos.x >> pos.y;

                players[playerID].reset(new Player(playerID, &socket));
            }
        } break;

        case Packet::Server::PlayerConnect: {
            sf::Int32 playerID;
            sf::Vector2f playerPos;
            packet >> playerID >> playerPos.x >> playerPos.y;
            players[playerID].reset(new Player(playerID, &socket));
            players[playerID]->position = playerPos;
        } break;

        case Packet::Server::UpdateClientState: {
            sf::Int32 playerCount;
            packet >> playerCount;
            std::cout << "pcount: " << playerCount << "\n";
            for (sf::Int32 i = 0; i < playerCount; ++i) {
                sf::Int32 playerID;
                float x, y;
                packet >> playerID >> x >> y;

                std::stringstream dbg;
                dbg << "player " << playerID << " pos " << x << " " << y;
                std::cout << dbg.str() << "\n";

                auto player = players.find(playerID);
                if (player != players.end() && playerID != currPlayerID) {
                    player->second->position.x = x;
                    player->second->position.y = y;
                    std::stringstream s;
                    s << "Player " << player->first << " X: " << x << " Y: " << y;
                    std::string msg = s.str();
                    std::cout << "Up:" << msg << "\n";
                }
            }
        } break;
    }
}

void MultiplayerState::updateBroadcastMessage(sf::Time elapsedTime) {
}

void MultiplayerState::handleChatEvent(const sf::Event& event) {
    if (chatInput->isFocused() && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        chatInput->setVisible(false);
        chatInput->setText("");
    }
    if (!chatInput->isVisible() && sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
        chatInput->setFocused(true);
        chatInput->setVisible(true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        sendChatMessage();
        chatInput->setText("");
        chatInput->setVisible(false);
    }
}

void MultiplayerState::sendChatMessage() {
    auto txt = chatInput->getText();
    if (!txt.isEmpty()) {
        std::string message = std::to_string(currPlayerID) + ": " + txt;
        sf::Packet packet;
        packet << static_cast<sf::Int32>(Packet::Client::ChatMessage);
        packet << message;
        socket.send(packet);
    }
}
