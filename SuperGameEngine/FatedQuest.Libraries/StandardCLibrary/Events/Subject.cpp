#include "Subject.h"
#include "../Collection/Vector/VectorHelpers.h"

using namespace StandardCLibrary;

Subject::Subject()
{
    m_observers = std::vector<Observer*>();
}

Subject::~Subject()
{

}

void Subject::AddObserver(Observer* observer)
{
    m_observers.push_back(observer);
}

void Subject::RemoveObserver(Observer* observer)
{
    VectorHelpers::RemoveValue(m_observers, observer);
}

void Subject::Notify()
{
    for (Observer* observer : m_observers)
    {
        if (observer != nullptr)
        {
            observer->Notify();
        }
    }
}