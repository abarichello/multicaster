#pragma once

#include <SFML/Config.hpp>
#include <SFML/Network.hpp>

const unsigned short SERVER_PORT = 5000;
const sf::IpAddress LOCALHOST = "127.0.0.1";

namespace Packet {
    enum Server {
        BroadcastMessage,  // broadcast to all clients chat - (std::string)
        SpawnSelf,         // used to spawn host's player, id and start position - (sf::Int32, float, float)
        InitialState,  // initial state when connected, player count, playerid, position - sf::Int32 x (sf::Int32, float, float)
        PlayerConnect,      // different client connected, id and start position - (sf::Int32, float, float)
        PlayerEvent,        // notifies of a player Action, id and action id - (sf::Int32, sf::int32)
        PlayerDisconnect,   // player id to be destroyed - (sf::Int32)
        SpawnEnemy,         // id and position of enemy spawn - (sf::Int32, float, float)
        UpdateClientState,  // player count and each player's id and position -
                            // (sf::Int32, (sf::Int32, float, float), ...)
        MissionSuccess      // end of mission, no body
    };

    enum Client {
        ChatMessage,     // chat message - (std::string)
        EventPlayer,     //
        PositionUpdate,  // player id, x pos and y pos- (sf::Int32, float, float)
        Quit             //
    };
};  // namespace Packet

namespace PlayerAction {
    enum { MoveForward, MoveBackward, MoveLeft, MoveRight, TurnLeft, TurnRight };
};
