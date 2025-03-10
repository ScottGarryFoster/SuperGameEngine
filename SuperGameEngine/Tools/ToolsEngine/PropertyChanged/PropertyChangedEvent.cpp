#include "PropertyChangedEvent.h"
#include "PropertyChangedObserver.h"

using namespace SuperGameTools;

PropertyChangedEvent::PropertyChangedEvent()
{
    m_observers = std::vector<std::weak_ptr<PropertyChangedObserver>>();
}

void PropertyChangedEvent::Subscribe(std::weak_ptr<PropertyChangedObserver> observer)
{
    m_observers.push_back(observer);
}

void PropertyChangedEvent::Unsubscribe(std::weak_ptr<PropertyChangedObserver> observer)
{
    // Copied from bool RemoveValue(std::vector<std::weak_ptr<T>>& vector, const std::weak_ptr <T>& valueToRemove)
    // To keep references separate.

    // Find the value we are looking for as a shared pointer
    // Remove if will return a pointer to the elements to remove (after moving them to end)
    // or just return the end of the vector.
    auto it = std::remove_if(
        m_observers.begin(), m_observers.end(), [&observer](const std::weak_ptr<PropertyChangedObserver>& weakPointer)
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

void PropertyChangedEvent::PropertyChanged(const std::string& name)
{
    for (const std::weak_ptr<PropertyChangedObserver>& observer : m_observers)
    {
        if (auto const shared = observer.lock())
        {
            shared->OnPropertyChanged(name);
        }
    }

    // TODO: Consider only removing these after so many dead pointers so that we do not get spikes.
    std::erase_if(m_observers, [](const std::weak_ptr<PropertyChangedObserver>& observer)
        {
            return observer.expired();
        });
}
