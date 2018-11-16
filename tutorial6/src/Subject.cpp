#include "Subject.hpp"

#include "Entity.hpp"
#include "Event.hpp"
#include "Observer.hpp"

namespace tcodtutorial
{
    void Subject::AddObserver(Observer* observer)
    {
        observers_.push_back(observer);
    }
    
    void Subject::RemoveObserver(Observer* observer)
    {
        for(auto item = observers_.begin(); item != observers_.end();  )
        {
            if(*item == observer)
            {
                observers_.erase(item);
            }
        }
    }

    void Subject::Clear()
    {
        observers_.clear();
    }
    
    void Subject::Notify(const Entity& entity, Event event)
    {
        for(auto obs : observers_)
        {
            obs->OnNotify(entity, event);
        }
    }
}
