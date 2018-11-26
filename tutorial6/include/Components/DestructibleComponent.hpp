#ifndef DESTRUCTIBLE_COMPONENT_HPP
#define DESTRUCTIBLE_COMPONENT_HPP

namespace tcodtutorial
{
    class DestructibleComponent
    {
        public:
            virtual ~DestructibleComponent() {}
    };

    class BasicDestructible : public DestructibleComponent
    {
    };
}

#endif
