#pragma once

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <memory>
#include <unordered_map>
#include <vector>

class Server {
public:
    Server();
    ~Server();

    void transmitInitialState(sf::TcpSocket& socket);
    void notifyPlayerSpawn(sf::Int32 playerID);
    void notifyPlayerEvent(sf::Int32 playerID, sf::Int32 action);

private:
    struct RemotePeer {
        RemotePeer();
        sf::TcpSocket socket;
        sf::Time lastPacket;
        std::vector<sf::Int32> playerIDs;
        bool ready;
        bool timedout;
    };

    struct PlayerInfo {
        sf::Vector2f position;
        std::map<sf::Int32, bool> realtimeActions;
    };

    using PeerPtr = std::unique_ptr<RemotePeer>;

private:
    void setListening(bool enable);
    void executionThread();
    void serverTick();
    sf::Time now() const;

    void handleIncomingConnections();
    void handleDisconnections();

    void handleIncomingPackets();
    void handlePacket(sf::Packet& packet, RemotePeer& receivingPeer, bool& timedout);

    void broadcastMessage(const std::string& message);
    void updateClientState();
    void sendToAll(sf::Packet& packet);

    sf::Thread thread;
    sf::TcpListener listenerSocket;
    sf::Clock clock;
    sf::Time timedoutThreshold = sf::Time(sf::seconds(3.0f));
    bool waitThreadEnd = false;
    bool listening = false;

    std::unordered_map<sf::Int32, PlayerInfo> playersInfo;
    std::vector<PeerPtr> peers;  // size = connected players +1

    const std::size_t MAX_PLAYERS = 4;
    const sf::Vector2f playerStartPos = sf::Vector2f(5.f, 5.f);
    std::size_t connectedPlayers = 0;  // unique peers connected

    sf::Int32 idCounter = 1;  // identifier counter representing nº of player instances
    std::size_t entityCount = 0;
};
