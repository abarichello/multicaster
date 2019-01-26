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

class MultiplayerState {
public:
    MultiplayerState(StateManager& manager, State::SharedContext context, bool isHost);

    virtual void draw();
    virtual bool event(const sf::Event& event);
    virtual bool update(float delta);

private:
    void updateBroadcastMessage(sf::Time elapsedTime);
    void handlePacket(sf::Int32 packetType, sf::Packet& packet);

    using PlayerPtr = std::unique_ptr<Player>;

    sf::RenderWindow& window;
    TextureHolder textureHolder;
    Map map;

    std::unique_ptr<Server> server;
    std::map<int, PlayerPtr> playerList;
    std::vector<sf::Int32> playerIDs;
    sf::TcpSocket socket;
    sf::Clock tickClock;
    bool conected = false;

    std::vector<std::string> broadcasts;
    sf::Text broadcastText;
    sf::Time broadcastElapsedTime;
};
