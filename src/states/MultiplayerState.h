#pragma once

#include <SFML/Network.hpp>
#include <map>
#include <memory>
#include <string>

#include "State.h"
#include "game/Map.h"
#include "game/Player.h"
#include "network/Server.h"
#include "util/ResourceHolder.h"

class MultiplayerState : public State {
public:
    MultiplayerState(StateManager& stateManager, State::SharedContext context, bool host);

    virtual void draw();
    virtual void handleEvent(const sf::Event& event);
    virtual void update(float delta);

private:
    void handlePacket(sf::Int32 packetType, sf::Packet& packet);
    void updateBroadcastMessage(sf::Time elapsedTime);

    sf::IpAddress getIPFromFile();

    using PlayerPtr = std::unique_ptr<Player>;

    TextureHolder textureHolder;
    Map map;

    std::unique_ptr<Server> server;
    std::map<int, PlayerPtr> playerList;
    sf::Int32 playerID;
    sf::TcpSocket socket;

    std::vector<std::string> broadcasts;
    sf::Text broadcastText;
    sf::Time broadcastElapsedTime;

    bool host = true;
    bool connected = false;
    bool gameStarted = false;

    const sf::Time CONNECTION_TIMEOUT = sf::seconds(5.0f);
    sf::Clock tickClock;
    sf::Clock failedConnection;
    sf::Time lastPacketReceived = sf::Time::Zero;
};
