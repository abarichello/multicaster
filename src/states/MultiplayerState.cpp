#include <fstream>

#include "MultiplayerState.h"
#include "network/Protocol.h"

MultiplayerState::MultiplayerState(StateManager& stateManager, State::SharedContext context, bool host)
    : State(stateManager, context), host(host), gui(*context.window) {
    setupGUI();

    sf::IpAddress ip;
    if (host) {
        server.reset(new Server());
        ip = LOCALHOST;
    } else {
        ip = getIPFromFile();
    }

    if (socket.connect(ip, SERVER_PORT, CONNECTION_TIMEOUT) == sf::TcpSocket::Done) {
        connected = true;
    } else {
        failedConnection.restart();
        chatBox->addLine("Failed connection");
    }
    socket.setBlocking(false);
}

void MultiplayerState::setupGUI() {
    gui.add(chatBox);
    chatBox->setPosition(100, 800);
    chatBox->setSize(500, 300);
    chatBox->setInheritedOpacity(0.8f);
    chatBox->addLine("--- CHAT START ---");
}

void MultiplayerState::draw() {
    if (currPlayerID != sf::Int32(-1)) {
        players[currPlayerID]->draw(*context.window);
    }
    gui.draw();
}

void MultiplayerState::handleEvent(const sf::Event& event) {
    gui.handleEvent(event);
}

void MultiplayerState::update(float delta) {
    if (currPlayerID != sf::Int32(-1)) {
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
            // positionUpdate << TODO: Position

            socket.send(positionUpdate);
            tickClock.restart();
        }
    }
}

void MultiplayerState::handlePacket(sf::Int32 packetHeader, sf::Packet& packet) {
    switch (packetHeader) {
        case Packet::Server::BroadcastMessage: {
            std::string message;
            packet >> message;
            chatBox->addLine(message);
            break;
        }
        case Packet::Server::SpawnSelf: {
            sf::Int32 id;
            sf::Vector2f spawnPos;
            packet >> id >> spawnPos.x >> spawnPos.y;

            currPlayerID = id;
            Player* player = new Player(id, &socket);
            player->position = spawnPos;
            players[id].reset(player);
            gameStarted = true;
            chatBox->addLine(std::to_string(id) + ": Joined game at position: " + std::to_string(spawnPos.x) +
                             ":" + std::to_string(spawnPos.y));
            break;
        }
    }
}

void MultiplayerState::updateBroadcastMessage(sf::Time elapsedTime) {
}

// TODO: placeholder until a save file is implemented for last visited server
sf::IpAddress MultiplayerState::getIPFromFile() {
    std::ifstream file("ip.txt");
    std::string ipString;
    file >> ipString;
    return sf::IpAddress(ipString);
}
