#pragma once
#include "IVGA.hpp"
#include "RP_GUI.hpp"

namespace Pong
{
    enum Buttons
    {
        PaddleOneUp = 0,
        PaddleOneDown,
        PaddleTwoUp,
        PaddleTwoDown,
    };
    enum class CollisionType
    {
        None,
        Top,
        Middle,
        Bottom,
        Left,
        Right,
    };

    bool buttons[4] = {};

    const int BALL_RADIUS = 6;
    const int PADDLE_WIDTH = 8;
    const int PADDLE_HEIGHT = 60;
    const float PADDLE_SPEED = 1.8;
    const float BALL_SPEED = 1.3;
    const float BALL_ACCEL = 0.1;
// QVGA display resolution
#define WINDOW_WIDTH 320  // display width
#define WINDOW_HEIGHT 240 // display height

    template <typename T>
    int sgn(T val)
    {
        return (T(0) < val) - (val < T(0));
    }

    struct Contact
    {
        CollisionType type;
        float penetration;
    };

    class Vec2
    {
    public:
        float x, y;

        Vec2()
            : x(0.0f), y(0.0f)
        {
        }

        Vec2(float x, float y)
            : x(x), y(y)
        {
        }

        Vec2 operator+(Vec2 const &rhs)
        {
            return Vec2(x + rhs.x, y + rhs.y);
        }

        Vec2 &operator+=(Vec2 const &rhs)
        {
            x += rhs.x;
            y += rhs.y;

            return *this;
        }

        Vec2 operator*(float rhs)
        {
            return Vec2(x * rhs, y * rhs);
        }
    };

    class PlayerScore
    {
    public:
        UI::Label *label;

        PlayerScore() = default;
        PlayerScore(UI::Label *label, UI::View &view)
            : label(label)
        {
            view.AddElement(label);
        }
    };

    class Ball
    {
        UI::Circle *circle = new UI::Circle();

    public:
        Vec2 position;
        Vec2 velocity;

        Ball() = default;
        Ball(Vec2 position, Vec2 velocity, UI::View &view)
            : position(position), velocity(velocity)
        {
            circle->center.x = static_cast<int>(position.x);
            circle->center.y = static_cast<int>(position.y);
            circle->radius.v = BALL_RADIUS;
            circle->color = VColors::Color::White;

            view.AddElement(circle);
        }

        void Update()
        {
            position += velocity;
            circle->center.x = position.x;
            circle->center.y = position.y;
        }

        void CollideWithPaddle(Contact const &contact);

        void CollideWithWall(Contact const &contact);
    };

    class Paddle
    {
        UI::Rectangle *circle = new UI::Rectangle();

    public:
        Vec2 position;
        Vec2 velocity;

        Paddle() = default;
        Paddle(Vec2 position, Vec2 velocity, UI::View &view)
            : position(position), velocity(velocity)
        {
            circle->coords.start.x = static_cast<int>(position.x);
            circle->coords.start.y = static_cast<int>(position.y);
            circle->coords.width.v = PADDLE_WIDTH;
            circle->coords.height.v = PADDLE_HEIGHT;
            circle->color = VColors::Color::White;

            view.AddElement(circle);
        }

        void Update()
        {
            position += velocity;

            if (position.y < 0)
            {
                // Restrict to top of the screen
                position.y = 0.0f;
            }
            else if (position.y > (WINDOW_HEIGHT - PADDLE_HEIGHT))
            {
                // Restrict to bottom of the screen
                position.y = WINDOW_HEIGHT - PADDLE_HEIGHT;
            }

            circle->coords.start.x = position.x;
            circle->coords.start.y = position.y;
        }
    };

    class PongGame
    {
        UI::View view;

    public:
        int playerOneScore = 0, playerTwoScore = 0;
        PlayerScore playerOneScoreText, playerTwoScoreText;
        Ball ball;
        Paddle paddleOne, paddleTwo;

        PongGame()
            : view(UI::View())
        {
        }

        UI::View &GetView() { return view; }

        void Init()
        {
            // Create the player score text fields
            this->playerOneScoreText = PlayerScore(new UI::Label("0", IVGA::Point(WINDOW_WIDTH / 4, 20)), view);
            this->playerTwoScoreText = PlayerScore(new UI::Label("0", IVGA::Point(3 * WINDOW_WIDTH / 4, 20)), view);

            // Create the ball
            this->ball = Ball(
                Vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2),
                Vec2(1.0f, 0.0f),
                view);

            // Create the paddles
            this->paddleOne = Paddle(
                Vec2(20.0f, (WINDOW_HEIGHT / 2) - (PADDLE_HEIGHT / 2)),
                Vec2(),
                view);

            this->paddleTwo = Paddle(
                Vec2(WINDOW_WIDTH - 20.0f, (WINDOW_HEIGHT / 2) - (PADDLE_HEIGHT / 2)),
                Vec2(),
                view);
        }

        void Update();

    private:
        Contact CheckPaddleCollision(Ball const &ball, Paddle const &paddle);

        Contact CheckWallCollision(Ball const &ball);

        void ProcessButtons();
    };

}