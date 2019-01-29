#include "MultiplayerState.h"
#include "network/Protocol.h"

MultiplayerState::MultiplayerState(StateManager& manager, State::SharedContext context, bool host)
    : window(*context.window), host(host) {
    sf::IpAddress ip;
    if (host) {
        server.reset(new Server());
        ip = LOCALHOST;
    } else {
        // TODO: Handle user-inserted IP using tgui
        // ip =
    }

    if (socket.connect(ip, SERVER_PORT, CONNECTION_TIMEOUT) == sf::TcpSocket::Done) {
        connected = true;
    } else {
        failedConnection.restart();
    }

    socket.setBlocking(false);
}

void MultiplayerState::draw() {
}

bool MultiplayerState::event(const sf::Event& event) {
    return true;
}

bool MultiplayerState::update(float delta) {
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
                return false;
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
    return true;
}

void MultiplayerState::handlePacket(sf::Int32 packetHeader, sf::Packet& packet) {
    switch (packetHeader) {
        case Packet::Server::BroadcastMessage:
            std::string message;
            packet >> message;
            broadcasts.push_back(message);
            break;
    }
}

void MultiplayerState::updateBroadcastMessage(sf::Time elapsedTime) {
}
