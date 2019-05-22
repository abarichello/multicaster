#pragma once

#include <SFML/Network.hpp>
#include <TGUI/TGUI.hpp>
#include <map>
#include <memory>
#include <string>

#include "State.h"
#include "game/Map.h"
#include "game/Player.h"
#include "network/Server.h"

class MultiplayerState : public State {
public:
    MultiplayerState(StateManager& stateManager, State::SharedContext context, bool host);
    void setupGUI();

    virtual void draw();
    virtual void handleEvent(const sf::Event& event);
    virtual void update(float delta);

private:
    void handlePacket(sf::Int32 packetType, sf::Packet& packet);
    void updateBroadcastMessage(sf::Time elapsedTime);

    void handleChatEvent(const sf::Event& event);
    void sendChatMessage();

    sf::IpAddress getIPFromFile();

    using PlayerPtr = std::unique_ptr<Player>;
    sf::Int32 currPlayerID = sf::Int32(-1);

    TextureHolder textureHolder;
    Map map;

    std::unique_ptr<Server> server;
    std::map<int, PlayerPtr> players;
    sf::Int32 playerID;
    sf::TcpSocket socket;

    sf::Clock fadeChatClock;
    sf::Time fadeChatTime = sf::seconds(5.0f);

    bool host = true;
    bool connected = false;
    bool gameStarted = false;

    const sf::Time CONNECTION_TIMEOUT = sf::seconds(5.0f);
    sf::Clock tickClock;
    sf::Clock failedConnection;
    sf::Time lastPacketReceived = sf::Time::Zero;

    tgui::Gui gui;
    tgui::ChatBox::Ptr chatBox = tgui::ChatBox::create();
    tgui::EditBox::Ptr chatInput = tgui::EditBox::create();

    const float chatOpacity = 0.55f;
};
