#pragma once

#include <SFML/Config.hpp>
#include <SFML/System/Vector2.hpp>

const unsigned short SERVER_PORT = 5000;

namespace Server {
    enum class PacketType {
        BroadcastMessage,
        SpawnSelf,
        PlayerConnect,
        PlayerDisconnected,
        SpawnEnemy,
        MissionSuccess
    };
};

namespace Client {
    enum class PacketType { PlayerEvent, PositionUpdate, Quit };
};

namespace PlayerAction {
    enum class Action { MoveForward, MoveBackward, MoveLeft, MoveRight, TurnLeft, TurnRight };
};
