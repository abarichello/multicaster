#pragma once

#include <SFML/Config.hpp>
#include <SFML/System/Vector2.hpp>

const unsigned short SERVER_PORT = 5000;

namespace Packet {
    enum class Server {
        BroadcastMessage,
        SpawnSelf,
        PlayerConnect,
        PlayerDisconnect,
        SpawnEnemy,
        MissionSuccess
    };

    enum class Client { PlayerEvent, PositionUpdate, Quit };
};  // namespace Packet

namespace PlayerAction {
    enum { MoveForward, MoveBackward, MoveLeft, MoveRight, TurnLeft, TurnRight };
};
