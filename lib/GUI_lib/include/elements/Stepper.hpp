//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_STEPPER_HPP
#define PICO_KIT_FRAMEWORK_STEPPER_HPP

#include "include.hpp"
#include "Button.hpp"
#include "IVGA.hpp"
#include "MouseDispatcher.hpp"

namespace rpgui::ui
{
    class Button;
}

using namespace rpgui::common;
using namespace rpgui::type;

namespace rpgui::ui
{
    template <typename T>
    concept Incrementable = requires(T x){
        {++x} -> std::same_as<T&>;
        {--x} -> std::same_as<T&>;
    };

    template <Incrementable T>
    class Stepper : public View, public Clickable
    {
    private:
        Button *_bAdd;
        Button *_bSub;

    public:
        Color backgroundColor;
        uint8_t frameWidth = 2;
        T counter;

    public:
        Stepper() = delete;
        Stepper(const Stepper &) = default;
        ~Stepper();

        Stepper(const Width &w, const Height &h, Color color, Color backgroundColor, uint8_t frameWidth);

        void Draw() const final;

        void SetBounds(const Bounds &bounds) override;

    private:
        static void add(rpgui::event::MouseEvent<MouseEventType> &event, Clickable *sender);
        static void sub(rpgui::event::MouseEvent<MouseEventType> &event, Clickable *sender);
    };

    template <Incrementable T>
    inline Stepper<T>::~Stepper()
    {
        delete _bAdd;
        delete _bSub;
    }

    template <Incrementable T>
    inline Stepper<T>::Stepper(const Width &w, const Height &h, Color color, Color backgroundColor, uint8_t frameWidth)
        : rpgui::common::View(Bounds(0, 0, w.v, h.v), color), backgroundColor(backgroundColor), frameWidth(frameWidth)
    {
        auto bound = this->GetBounds();
        auto adjBounds = bound - frameWidth;
        adjBounds.w = adjBounds.w / 2;
        _bAdd = new Button(Bounds(adjBounds.x + frameWidth / 2 + adjBounds.w, adjBounds.y, adjBounds.w, adjBounds.h),
            color,
            "+",
            backgroundColor);

        _bSub = new Button(Bounds(adjBounds.x + frameWidth / 2 + adjBounds.w, adjBounds.y, adjBounds.w, adjBounds.h),
            color,
            "-",
            backgroundColor);

        _bAdd->SetOnClickHandler(MouseEventType::Clicked, add);
        _bSub->SetOnClickHandler(MouseEventType::Clicked, sub);
    }

    template <Incrementable T>
    inline void Stepper<T>::Draw() const
    {
        for (uint8_t i = 0; i < frameWidth; i++)
        {
            IVGA::IDrawFrame(this->GetBounds() - i, this->backgroundColor);
        }
        auto b = _bSub->GetBounds();
        IVGA::IDrawRectangle(Bounds(b.x + b.w, b.y, frameWidth, b.h), backgroundColor);
        _bAdd->Draw();
        _bSub->Draw();
    }

    template <Incrementable T>
    inline void Stepper<T>::SetBounds(const Bounds &bounds)
    {
        this->rpgui::common::View::SetBounds(bounds);
        auto adjBounds = bounds - frameWidth;
        adjBounds.w = adjBounds.w / 2;
        _bAdd->SetBounds(Bounds(adjBounds.x + frameWidth / 2 + adjBounds.w, adjBounds.y, adjBounds.w, adjBounds.h));
        _bSub->SetBounds(Bounds(adjBounds.x, adjBounds.y, adjBounds.w - frameWidth / 2, adjBounds.h));
    }

    template <Incrementable T>
    inline void Stepper<T>::add(rpgui::event::MouseEvent<MouseEventType> &event, Clickable *sender)
    {
        rpgui::ui::Stepper<T> *sw = (rpgui::ui::Stepper<T> *)sender;
        ++(sw->counter);
    }

    template <Incrementable T>
    void rpgui::ui::Stepper<T>::sub(rpgui::event::MouseEvent<MouseEventType> &event, Clickable *sender)
    {
        rpgui::ui::Stepper<T> *sw = (rpgui::ui::Stepper<T> *)sender;
        --(sw->counter);
    }

} // namespace rpgui::ui

#endif // PICO_KIT_FRAMEWORK_STEPPER_HPP
