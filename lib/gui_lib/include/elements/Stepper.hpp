//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_STEPPER_HPP
#define PICO_KIT_FRAMEWORK_STEPPER_HPP

#include "include.hpp"
#include "Button.hpp"
#include "IVGA.hpp"
#include "MouseDispatcher.hpp"
#include "BindableProperty.hpp"

namespace rpgui::ui
{
    class Button;
}

using namespace rpgui::common;
using namespace rpgui::type;

namespace rpgui::ui
{
    template <typename T>
    concept Stepable = requires(T x) {
        {
            ++x
        } -> std::same_as<T &>;
        {
            --x
        } -> std::same_as<T &>;
    };

    template <typename T>
    concept Constructible = requires {
        typename std::enable_if<std::is_default_constructible_v<T>>::type;
    };

    template <typename T>
    concept StepableAndConstructible = requires {
        Stepable<T> &&Constructible<T>;
    };

    template <Stepable T>
    class Stepper : public VisualElement, public Clickable
    {
    private:
        Button *_bAdd;
        Button *_bSub;

    public:
        Color backgroundColor;
        uint8_t frameWidth;
        BindableProperty<T> counter;

    public:
        Stepper() = delete;
        Stepper(const Stepper &) = default;
        ~Stepper();

        Stepper(const Width &width, const Height &height, Color color = Color::White, Color backgroundColor = Color::SemiGray, uint8_t frameWidth = 2);
        Stepper(const Width &width, const Height &height, T &counter, Color color = Color::White, Color backgroundColor = Color::SemiGray, uint8_t frameWidth = 2);

        void Draw() const final;

        void SetBounds(const Bounds &bounds) override;

    private:
        static void add(rpgui::event::MouseEvent<MouseEventType> &event, Clickable *sender);
        static void sub(rpgui::event::MouseEvent<MouseEventType> &event, Clickable *sender);

        void prepareButtons();
    };

    template <Stepable T>
    inline Stepper<T>::~Stepper()
    {
        delete _bAdd;
        delete _bSub;
    }

    template <StepableAndConstructible T>
    inline Stepper<T>::Stepper(const Width &width, const Height &height, Color color, Color backgroundColor, uint8_t frameWidth)
        : rpgui::common::VisualElement(Bounds(0, 0, width.v, height.v), color),
          backgroundColor(backgroundColor),
          frameWidth(frameWidth),
          counter(T())
    {
        prepareButtons();
    }

    template <Stepable T>
    inline Stepper<T>::Stepper(const Width &width, const Height &height, T &counter, Color color, Color backgroundColor, uint8_t frameWidth)
        : rpgui::common::VisualElement(Bounds(0, 0, width.v, height.v), color),
          backgroundColor(backgroundColor),
          frameWidth(frameWidth),
          counter(counter)
    {
        prepareButtons();
    }

    template <Stepable T>
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

    template <Stepable T>
    inline void Stepper<T>::SetBounds(const Bounds &bounds)
    {
        this->rpgui::common::VisualElement::SetBounds(bounds);
        auto adjBounds = bounds - frameWidth;
        adjBounds.w = adjBounds.w / 2;
        _bAdd->SetBounds(Bounds(adjBounds.x + frameWidth / 2 + adjBounds.w, adjBounds.y, adjBounds.w, adjBounds.h));
        _bSub->SetBounds(Bounds(adjBounds.x, adjBounds.y, adjBounds.w - frameWidth / 2, adjBounds.h));
    }

    template <Stepable T>
    inline void Stepper<T>::add(rpgui::event::MouseEvent<MouseEventType> &event, Clickable *sender)
    {
        auto btn = (rpgui::ui::Button *)sender;
        auto stepper = (ui::Stepper<T> *)btn->GetParrent();
        T &val = stepper->counter.GetValueRef();
        ++val;
    }

    template <Stepable T>
    void rpgui::ui::Stepper<T>::sub(rpgui::event::MouseEvent<MouseEventType> &event, Clickable *sender)
    {
        auto btn = (rpgui::ui::Button *)sender;
        auto stepper = (ui::Stepper<T> *)btn->GetParrent();
        T &val = stepper->counter.GetValueRef();
        --val;
    }

    template <Stepable T>
    inline void Stepper<T>::prepareButtons()
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
        _bAdd->SetParrent(this);
        _bSub->SetParrent(this);
        _bAdd->SetOnClickHandler(MouseEventType::Clicked, add, 1);
        _bSub->SetOnClickHandler(MouseEventType::Clicked, sub, 1);
    }

} // namespace rpgui::ui

#endif // PICO_KIT_FRAMEWORK_STEPPER_HPP
