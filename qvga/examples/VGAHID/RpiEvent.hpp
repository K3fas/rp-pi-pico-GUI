#pragma once

#include <functional>
#include <map>

namespace Events
{
    class Event
    {
    public:
        virtual ~Event();
        using DescriptorType = const char *;
        virtual DescriptorType Type() const = 0;
    };

    class Clicked : public Event
    {
    public:
        Clicked();
        virtual ~Clicked();

        static constexpr DescriptorType descriptor = "Clicked";

        virtual DescriptorType Type() const
        {
            return descriptor;
        }
    };

    class Dispatcher
    {
    public:
        using SlotType = std::function<void(const Event &)>;

        void Subscribe(const Event::DescriptorType &descriptor, SlotType &&slot);

        void Post(const Event &event) const;

    private:
        // lookup map for events
        std::map<Event::DescriptorType, std::vector<SlotType>> _observers;
    };

    class ClassObserver
    {
    public:
        void handle(const Event &e)
        {
            if (e.Type() == Clicked::descriptor)
            {
                // This demonstrates how to obtain the underlying event type in case a
                // slot is set up to handle multiple events of different types.
                const Clicked &demoEvent = static_cast<const Event &>(e);
                printf("Event fired: %s\n", demoEvent.Type());
            }
        }
    };

} // namespace Events
