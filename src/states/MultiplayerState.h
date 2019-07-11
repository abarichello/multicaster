#pragma once

#include <SFML/Network.hpp>
#include <TGUI/TGUI.hpp>
#include <memory>
#include <string>
#include <unordered_map>

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

    void connect(const sf::IpAddress ip);

private:
    void handlePacket(sf::Int32 packetType, sf::Packet& packet);
    void updateBroadcastMessage(sf::Time elapsedTime);

    void handleChatEvent(const sf::Event& event);
    void sendChatMessage();

    sf::TcpSocket socket;
    sf::IpAddress currentIp;

    using PlayerPtr = std::unique_ptr<Player>;
    TextureHolder textureHolder;
    Map map;

    std::unique_ptr<Server> server;
    std::unordered_map<int, PlayerPtr> players;
    sf::Int32 playerID = sf::Int32(-1);

    // TODO: Implement fadeout
    sf::Clock fadeChatClock;
    sf::Time fadeChatTime = sf::seconds(5.0f);

    bool host = true;
    bool connected = false;
    bool gameStarted = false;

    const sf::Time CONNECTION_TIMEOUT = sf::seconds(2.0f);
    sf::Clock tickClock;
    sf::Clock failedConnection;
    sf::Time lastPacketReceived = sf::Time::Zero;

    tgui::Gui gui;
    tgui::ChatBox::Ptr chatBox = tgui::ChatBox::create();
    tgui::EditBox::Ptr chatInput = tgui::EditBox::create();

    const float chatOpacity = 0.55f;
};
