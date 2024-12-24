#include "FEvent.h"
#include "../../StandardOperations/AllReferences.h"

using namespace FatedQuestLibraries;

FEvent::FEvent()
{
    m_observers = std::vector<std::weak_ptr<FEventObserver>>();
}

void FEvent::Subscribe(std::weak_ptr<FEventObserver> observer)
{
    m_observers.push_back(observer);
}

void FEvent::Unsubscribe(std::weak_ptr<FEventObserver> observer)
{
    VectorHelpers::RemoveValue(m_observers, observer);
}

void FEvent::Invoke(std::shared_ptr<FEventArguments> arguments)
{
    for (const std::weak_ptr<FEventObserver>& observer : m_observers)
    {
        if (auto const shared = observer.lock())
        {
            shared->Invoke(arguments);
        }
    }

    // TODO: Consider only removing these after so many dead pointers so that we do not get spikes.
    std::erase_if(m_observers, [](const std::weak_ptr<FEventObserver>& observer)
    {
        return observer.expired();
    });
}
