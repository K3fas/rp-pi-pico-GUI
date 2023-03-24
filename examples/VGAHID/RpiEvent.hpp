#pragma once

#include <functional>
#include <map>

namespace Events
{
    class MouseEvent
    {
    public:
        virtual ~MouseEvent();
        using DescriptorType = const char *;
        virtual DescriptorType Type() const = 0;
    };

    class Clicked : public MouseEvent
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
        using SlotType = std::function<void(const MouseEvent &)>;

        void Subscribe(const MouseEvent::DescriptorType &descriptor, SlotType &&slot);

        void Post(const MouseEvent &event) const;

    private:
        // lookup map for events
        std::map<MouseEvent::DescriptorType, std::vector<SlotType>> _observers;
    };

    class ClassObserver
    {
    public:
        void handle(const MouseEvent &e)
        {
            if (e.Type() == Clicked::descriptor)
            {
                // This demonstrates how to obtain the underlying event type in case a
                // slot is set up to handle multiple events of different type.
                const Clicked &demoEvent = static_cast<const MouseEvent &>(e);
                printf("MouseEvent fired: %s\n", demoEvent.Type());
            }
        }
    };

} // namespace Events
