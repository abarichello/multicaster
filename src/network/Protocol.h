#pragma once

#include <SFML/Config.hpp>
#include <SFML/System/Vector2.hpp>

const unsigned short SERVER_PORT = 5000;
const sf::IpAddress LOCALHOST = "127.0.0.1";

namespace Packet {
    enum Server {
        BroadcastMessage,   // broadcast to all clients chat - (std::string)
        SpawnSelf,          // used to spawn host's aircraft, start position - (float. float)
        PlayerConnect,      // different client connected, id and start position - (sf::Int32, float, float)
        PlayerEvent,        // notifies of a player Action, id and action id - (sf::Int32, sf::int32)
        PlayerDisconnect,   // aircraft id to be destroyed - (sf::Int32)
        SpawnEnemy,         // id and position of enemy spawn - (sf::Int32, float, float)
        UpdateClientState,  // aircraft count and each player's id and position -
                            // (sf::Int32, (sf::Int32, float, float), ...)
        MissionSuccess      // end of mission, no body
    };

    enum Client { EventPlayer, PositionUpdate, Quit };
};  // namespace Packet

namespace PlayerAction {
    enum { MoveForward, MoveBackward, MoveLeft, MoveRight, TurnLeft, TurnRight };
};
