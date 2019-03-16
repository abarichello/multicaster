#include <iostream>

#include "network/Protocol.h"
#include "network/Server.h"

Server::Server() : thread(&Server::executionThread, this), peers(1) {
    listenerSocket.setBlocking(false);
    peers[0].reset(new RemotePeer());
    std::cout << "Lauching server" << std::endl;
    thread.launch();
}

Server::~Server() {
    waitThreadEnd = true;
    thread.wait();
}

void Server::notifyPlayerSpawn(sf::Int32 playerID) {
    for (std::size_t i = 0; i < connectedPlayers; ++i) {
        if (peers[i]->ready) {
            sf::Packet packet;
            packet << static_cast<sf::Int32>(Packet::Server::PlayerConnect);
            packet << playerID;
            packet << playersInfo[playerID].position.x << playersInfo[playerID].position.y;
            peers[i]->socket.send(packet);
        }
    }
}

void Server::notifyPlayerEvent(sf::Int32 playerID, sf::Int32 action) {
    for (std::size_t i = 0; i < connectedPlayers; ++i) {
        if (peers[i]->ready) {
            sf::Packet packet;
            packet << static_cast<sf::Int32>(Packet::Server::PlayerEvent);
            packet << playerID;
            packet << action;
            peers[i]->socket.send(packet);
        }
    }
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
    setListening(true);

    sf::Time stepInterval = sf::seconds(1.0f / 60.0f);  // 60 Hz
    sf::Time tickInterval = sf::seconds(1.0f / 30.0f);  // 30 Hz
    sf::Time stepTime = sf::Time::Zero;
    sf::Time tickTime = sf::Time::Zero;

    sf::Clock stepClock, tickClock;
    while (!waitThreadEnd) {
        handleIncomingPackets();
        handleIncomingConnections();

        stepTime = stepClock.restart();
        tickTime = tickClock.restart();

        // Fixed update step
        while (stepTime >= stepInterval) {
        }

        // Server update capped to 30 Hz
        while (tickTime >= tickInterval) {
            serverTick();
        }

        sf::sleep(sf::milliseconds(100));  // sleep the remaining frame time
    }
}

void Server::serverTick() {
    updateClientState();

    // TODO: Check for win condition
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
    bool playerTimedout = false;

    for (PeerPtr& peer : peers) {
        if (peer->ready) {
            sf::Packet packet;
            while (peer->socket.receive(packet) == sf::Socket::Done) {
                handlePacket(packet, *peer, playerTimedout);
                peer->lastPacket = now();
                packet.clear();
            }

            if (peer->lastPacket + timedoutThreshold <= now()) {
                peer->timedout = true;
                playerTimedout = true;
            }
        }
    }

    if (playerTimedout) {
        handleDisconnections();
    }
}

void Server::handlePacket(sf::Packet& packet, RemotePeer& receivingPeer, bool& timedout) {
    sf::Int32 packetHeader;
    packet >> packetHeader;

    switch (packetHeader) {
        // TODO: Handle Packages::Client packages
    }
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

void Server::updateClientState() {
    sf::Packet packet;
    packet << static_cast<sf::Int32>(Packet::Server::UpdateClientState);
    packet << static_cast<sf::Int32>(playersInfo.size());

    // Send each playerID and position
    for (auto info : playersInfo) {
        packet << info.first << info.second.position.x << info.second.position.x;
    }
    sendToAll(packet);
}

void Server::sendToAll(sf::Packet& packet) {
    for (PeerPtr& peer : peers) {
        if (peer->ready) {
            peer->socket.send(packet);
        }
    }
}
