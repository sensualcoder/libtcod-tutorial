#ifndef DESTRUCTIBLE_HPP
#define DESTRUCTIBLE_HPP

namespace tcodtutorial
{
    class Destructible
    {
        public:
            virtual ~Destructible() {}
    };

    class BasicDestructible : public Destructible
    {
    };
}

#endif
