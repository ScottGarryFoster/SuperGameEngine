#include "FEvent.h"

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
    // Copied from bool RemoveValue(std::vector<std::weak_ptr<T>>& vector, const std::weak_ptr <T>& valueToRemove)
    // To keep references separate.

    // Find the value we are looking for as a shared pointer
    // Remove if will return a pointer to the elements to remove (after moving them to end)
    // or just return the end of the vector.
    auto it = std::remove_if(
        m_observers.begin(), m_observers.end(), [&observer](const std::weak_ptr<FEventObserver>& weakPointer)
        {
            if (auto sharedPointer = weakPointer.lock())
            {
                auto sharedPointerToRemove = observer.lock();
                if (sharedPointer && sharedPointerToRemove)
                {
                    return sharedPointer == sharedPointerToRemove;
                }
            }

            return false;
        });

    // Actually remove it provided that is possible.
    if (it != m_observers.end())
    {
        m_observers.erase(it, m_observers.end());
    }
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