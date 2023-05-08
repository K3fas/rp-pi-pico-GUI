//
// Created by kefas on 26.2.23.
//
#include "Stepper.hpp"

// rpgui::ui::Stepper::~Stepper()
// {
//     delete _bAdd;
//     delete _bSub;
// }

// rpgui::ui::Stepper::Stepper(const Width &width, const Height &height, Color color, Color backgroundColor, uint8_t frameWidth)
//     : rpgui::common::VisualElement(Bounds(0, 0, width.v, height.v), color),
//       backgroundColor(backgroundColor),
//       frameWidth(frameWidth),
//       counter(0)
// {
//     prepareButtons();
// }

// rpgui::ui::Stepper::Stepper(const Width &width, const Height &height, int &counter, Color color, Color backgroundColor, uint8_t frameWidth)
//     : rpgui::common::VisualElement(Bounds(0, 0, width.v, height.v), color),
//       backgroundColor(backgroundColor),
//       frameWidth(frameWidth),
//       counter(counter)
// {
//     prepareButtons();
// }

// void rpgui::ui::Stepper::Draw() const
// {
//     for (uint8_t i = 0; i < frameWidth; i++)
//     {
//         IVGA::IDrawFrame(this->GetBounds() - i, this->backgroundColor);
//     }
//     auto b = _bSub->GetBounds();
//     IVGA::IDrawRectangle(Bounds(b.x + b.w, b.y, frameWidth, b.h), backgroundColor);
//     _bAdd->Draw();
//     _bSub->Draw();
// }
// void rpgui::ui::Stepper::SetBounds(const Bounds &bounds)
// {
//     this->rpgui::common::VisualElement::SetBounds(bounds);
//     auto adjBounds = bounds - frameWidth;
//     adjBounds.w = adjBounds.w / 2;
//     _bAdd->SetBounds(Bounds(adjBounds.x + frameWidth / 2 + adjBounds.w, adjBounds.y, adjBounds.w, adjBounds.h));
//     _bSub->SetBounds(Bounds(adjBounds.x, adjBounds.y, adjBounds.w - frameWidth / 2, adjBounds.h));
// }
// void rpgui::ui::Stepper::add(rpgui::event::MouseEvent<MouseEventType> &event, Clickable *sender)
// {
//     auto btn = (rpgui::ui::Button *)sender;
//     auto stepper = (ui::Stepper*)btn->GetParrent();
//     int& val = stepper->counter.GetValueRef();
//     ++val;
// }

// void rpgui::ui::Stepper::sub(rpgui::event::MouseEvent<MouseEventType> &event, Clickable *sender)
// {
//     auto btn = (rpgui::ui::Button *)sender;
//     auto stepper = (ui::Stepper*)btn->GetParrent();
//     int& val = stepper->counter.GetValueRef();
//     --val;
// }

// void rpgui::ui::Stepper::prepareButtons()
// {
//     auto bound = this->GetBounds();
//     auto adjBounds = bound - frameWidth;
//     adjBounds.w = adjBounds.w / 2;
//     _bAdd = new Button(Bounds(adjBounds.x + frameWidth / 2 + adjBounds.w, adjBounds.y, adjBounds.w, adjBounds.h),
//                        color,
//                        "+",
//                        backgroundColor);

//     _bSub = new Button(Bounds(adjBounds.x + frameWidth / 2 + adjBounds.w, adjBounds.y, adjBounds.w, adjBounds.h),
//                        color,
//                        "-",
//                        backgroundColor);
//     _bAdd->SetParrent(this);
//     _bSub->SetParrent(this);
//     _bAdd->SetOnClickHandler(MouseEventType::Clicked, add, 1);
//     _bSub->SetOnClickHandler(MouseEventType::Clicked, sub, 1);
// }
