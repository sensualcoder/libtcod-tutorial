#ifndef EVENT_HPP
#define EVENT_HPP

namespace tcodtutorial
{
    enum EventType_t
    {
        NONE,
        MOVE
    };

    enum Direction_t
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    struct Event
    {
        EventType_t type_;
        Direction_t movedir_;
    };
}

#endif
