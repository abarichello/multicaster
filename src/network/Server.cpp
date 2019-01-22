#include "network/Server.h"
#include "network/Protocol.h"

Server::Server() : thread(&Server::executionThread, this) {
}

Server::~Server() {
    waitThreadEnd = true;
    thread.wait();
}

void Server::notifyPlayerSpawn(sf::Int32 playerID) {
}

void Server::notifyPlayerEvent(sf::Int32 playerID, sf::Int32 action) {
}

// RemotePeer constructor
Server::RemotePeer::RemotePeer() : ready(false), timedout(false) {
    socket.setBlocking(false);
}

void Server::setListening(bool enable) {
    if (enable) {
        if (!listening) {
            listening = (listenerSocket.listen(SERVER_PORT) == sf::TcpListener::Done);
        }
    } else {
        listenerSocket.close();
        listening = false;
    }
}

void Server::executionThread() {
}

void Server::serverTick() {
}

sf::Time Server::now() const {
    return clock.getElapsedTime();
}

void Server::handleIncomingConnections() {
    if (!listening) {
        return;
    }

    if (listenerSocket.accept(peers[connectedPlayers]->socket) == sf::TcpListener::Done) {
        playersInfo[idCounter].position = sf::Vector2f(2.5f, 2.5f);  // starting position

        sf::Packet packet;
        packet << static_cast<sf::Int32>(Packet::Server::SpawnSelf);
        packet << idCounter;
        packet << playersInfo[idCounter].position.x;
        packet << playersInfo[idCounter].position.y;

        peers[connectedPlayers]->playerIDs.push_back(idCounter);

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
            setListening(false);
        } else {  // add a new waiting peer
            peers.push_back(PeerPtr(new RemotePeer()));
        }
    }
}

void Server::handleDisconnections() {
    for (auto itr = peers.begin(); itr != peers.end(); ++itr) {
        if ((*itr)->timedout) {
            for (auto id : (*itr)->playerIDs) {
                sf::Packet packet;
                packet << static_cast<sf::Int32>(Packet::Server::PlayerDisconnect) << id;
                sendToAll(packet);
                playersInfo.erase(id);
            }

            connectedPlayers--;
            entityCount--;
            peers.erase(itr);

            if (connectedPlayers < MAX_PLAYERS) {
                peers.push_back(PeerPtr(new RemotePeer()));
                setListening(true);
            }
            broadcastMessage("A player has disconnected");
        }
    }
}

void Server::handleIncomingPackets() {
}

void Server::handleIncomingPacket(sf::Packet& packet, RemotePeer& receivingPeer, bool& timedout) {
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

void Server::sendToAll(sf::Packet& packet) {
}
