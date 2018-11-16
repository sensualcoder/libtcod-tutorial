#ifndef OBSERVER_HPP
#define OBSERVER_HPP

namespace tcodtutorial
{
    class Entity;
    struct Event;

    class Observer
    {
        public:
            virtual ~Observer() {}
            virtual void OnNotify(const Entity& entity, Event event) = 0;
    };
}

#endif
