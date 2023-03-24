#include "RpiEvent.hpp"

using namespace Events;

void Dispatcher::Subscribe(const MouseEvent::DescriptorType &descriptor, SlotType &&slot)
{
    _observers[descriptor].push_back(slot);
}

void Dispatcher::Post(const MouseEvent &event) const
{
    auto type = event.Type();

    // Ignore events for which we do not have an observer (yet).
    if (_observers.find(type) == _observers.end())
        return;

    auto &&observers = _observers.at(type);

    for (auto &&observer : observers)
        observer(event);
}