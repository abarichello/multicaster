#pragma once

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <memory>
#include <vector>

class Server {
public:
    explicit Server();
    ~Server();

    void notifyPlayerSpawn(sf::Int32 playerID);
    // void notifyPlayerRealtimeChange(sf::Int32 playerID, )
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
    void handleIncomingPacket(sf::Packet& packet, RemotePeer& receivingPeer, bool& timedout);

    void broadcastMessage(const std::string& message);
    void sendToAll(sf::Packet& packet);

    sf::Thread thread;
    sf::TcpListener listenerSocket;
    sf::Clock clock;
    bool waitThreadEnd = false;
    bool listening = false;

    std::map<sf::Int32, PlayerInfo> playersInfo;
    std::vector<PeerPtr> peers;  // size = connected players +1

    const std::size_t MAX_PLAYERS = 4;
    std::size_t connectedPlayers = 0;  // unique peers connected

    sf::Int32 idCounter = 1;  // identifier counter representing nº of player instances
    std::size_t entityCount = 0;
};
