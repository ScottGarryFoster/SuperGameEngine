#include "FEvent.h"
#include "../Collection/Vector/VectorHelpers.hpp"

using namespace StandardCLibrary;

FEvent::FEvent()
{
    m_observers = std::vector<FEventObserver*>();
}

void FEvent::Subscribe(FEventObserver* observer)
{
    m_observers.push_back(observer);
}

void FEvent::Unsubscribe(FEventObserver* observer)
{
    VectorHelpers::RemoveValue(m_observers, observer);
}

void FEvent::Invoke(FEventArguments* arguments) 
{
    for (FEventObserver* observer : m_observers)
    {
        if (observer != nullptr)
        {
            observer->Invoke(arguments);
        }
    }
}
