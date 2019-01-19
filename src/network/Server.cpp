#include "network/Server.h"
#include "network/Protocol.h"

Server::Server() : thread(&Server::executionThread, this) {
}

Server::~Server() {
    waitThreadEnd = true;
    thread.wait();
}

void Server::handleIncomingConnections() {
    if (!listening) {
        return;
    }

    if (listenerSocket.accept(peers[connectedPlayers]->socket) == sf::TcpListener::Done) {
        playersInfo[idCounter].position = sf::Vector2f(2.f, 2.f);

        sf::Packet packet;
        packet << static_cast<sf::Int32>(Packet::Server::SpawnSelf);
        packet << idCounter;
        packet << playersInfo[idCounter].position.x;
        packet << playersInfo[idCounter].position.y;

        peers[connectedPlayers]->playerID.push_back(idCounter);

        broadcastMessage("Player joined");
        notifyPlayerSpawn(idCounter++);
        //

        peers[connectedPlayers]->socket.send(packet);
        peers[connectedPlayers]->ready = true;
        peers[connectedPlayers]->lastPacket = now();
        entityCount++;
        connectedPlayers++;

        // Update socket listening state
        if (connectedPlayers >= MAX_PLAYERS) {
            listening = false;
        } else {  // add a new waiting peer
            peers.push_back(PeerPtr(new RemotePeer()));
        }
    }
}

// RemotePeer constructor
Server::RemotePeer::RemotePeer() : ready(false), timedout(false) {
    socket.setBlocking(false);
}

void Server::broadcastMessage(const std::string& message) {
    for (std::size_t i = 0; i < connectedPlayers; ++i) {
        if (peers[i]->ready) {
            sf::Packet packet;
            packet << static_cast<sf::Int32>(Packet::Server::BroadcastMessage);
            packet << message;

            peers[i]->socket.send(packet);
        }
    }
}

sf::Time Server::now() const {
    return clock.getElapsedTime();
}
