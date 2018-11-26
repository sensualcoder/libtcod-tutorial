#ifndef AI_COMPONENT_HPP
#define AI_COMPONENT_HPP

namespace tcodtutorial
{
    class Entity;
    class World;

    class AiComponent
    {
        public:
            virtual ~AiComponent() {}
            virtual void Update(Entity* owner, World& world) {}
    };

    class NpcAi : public AiComponent
    {
        public:
            void Update(Entity* owner, World& world);
    };
}

#endif
