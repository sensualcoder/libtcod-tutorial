#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include <memory>
#include <vector>

namespace tcodtutorial
{
    class Observer;

    class Entity;
    struct Event;

    class Subject
    {
        public:
            void AddObserver(Observer* observer);
            void RemoveObserver(Observer* observer);
            void Clear();

            void Notify(const Entity& entity, Event event);

        private:
            std::vector<Observer*> observers_;
    };
}

#endif
