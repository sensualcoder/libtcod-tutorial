#ifndef AI_HPP
#define AI_HPP

namespace tcodtutorial
{
    class Entity;

    class AI
    {
        public:
            virtual void Update(Entity* owner) {}
    };

    class EnemyAI : public AI
    {
        public:
            void Update(Entity* owner);
    };
}

#endif
