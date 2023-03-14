//
// Created by kefas on 27.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_EVENT_HPP
#define PICO_KIT_FRAMEWORK_EVENT_HPP

#include <string>

namespace rpgui::event
{
    template <typename T>
    class Event
    {
    private:
        T _type;
        std::string _name;
        bool _handled = false;

    public:
        Event() = default;
        Event(T type, const std::string &name) : _type(type), _name(name){};
        virtual ~Event() = default;

        inline const T Type() const { return _type; }
        inline const std::string &Name() const { return _name; }
        virtual bool IsHandled() { return _handled; }
    };

} // namespace rpgui::evnt

#endif // PICO_KIT_FRAMEWORK_EVENT_HPP
