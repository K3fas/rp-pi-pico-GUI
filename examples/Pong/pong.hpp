#pragma once

#include <rpgui.hpp>

using namespace rpgui::type;
using namespace rpgui::common;
using namespace rpgui::colors;
using namespace rpgui::ui;
using namespace rpgui::layout;

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

    static bool buttons[4] = {};

    const int BALL_RADIUS = 6;
    const int PADDLE_WIDTH = 8;
    const int PADDLE_HEIGHT = 60;
    const float PADDLE_SPEED = 1.8;
    const float BALL_SPEED = 1.3;
    const float BALL_ACCEL = 0.1;

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
        Label *label;

        PlayerScore() = default;
        PlayerScore(Label *label, Vec2 position, AbsoluteLayout &view)
            : label(label)
        {
            view.AddElement(Point(position.x, position.y), label);
        }
    };

    class Ball
    {
        rpgui::ui::Circle *circle = new rpgui::ui::Circle(Radius(BALL_RADIUS), Color::White);

    public:
        Vec2 position;
        Vec2 velocity;

        Ball() = default;
        Ball(Vec2 position, Vec2 velocity, AbsoluteLayout &view)
            : position(position), velocity(velocity)
        {
            circle->SetCenter(Point(position.x, position.y));
            circle->radius.v = BALL_RADIUS;

            view.AddElement(Point(position.x, position.y), circle);
        }

        void Update()
        {
            position += velocity;
            circle->SetCenter(Point(position.x, position.y));
        }

        void CollideWithPaddle(Contact const &contact);

        void CollideWithWall(Contact const &contact);
    };

    class Paddle
    {
        Rectangle *paddle = new Rectangle(Bounds(0, 0, 0, 0), Color::White);

    public:
        Vec2 position;
        Vec2 velocity;

        Paddle() = default;
        Paddle(Vec2 position, Vec2 velocity, AbsoluteLayout &view)
            : position(position), velocity(velocity)
        {
            paddle->SetBounds(Bounds(position.x, position.y, PADDLE_WIDTH, PADDLE_HEIGHT));
            view.AddElement(Point(position.x, position.y), paddle);
        }

        void Update()
        {
            position += velocity;

            if (position.y < 0)
            {
                // Restrict to top of the screen
                position.y = 0.0f;
            }
            else if (position.y > (WIDTH - PADDLE_HEIGHT))
            {
                // Restrict to bottom of the screen
                position.y = WIDTH - PADDLE_HEIGHT;
            }

            auto b = paddle->GetBounds();
            b.x = position.x;
            b.y = position.y;
            paddle->SetBounds(b);
        }
    };

    class PongGame
    {
        AbsoluteLayout view;

    public:
        uint8_t playerOneScoreVal = 0, playerTwoScoreVal = 0;
        PlayerScore playerOneScore, playerTwoScore;
        Ball ball;
        Paddle paddleOne, paddleTwo;

        PongGame()
            : view(AbsoluteLayout())
        {
        }

        AbsoluteLayout *GetView() { return &view; }

        void Init()
        {
            // Create the player score text fields
            this->playerOneScore = PlayerScore(new Label("0"), Vec2(10, 10), view);
            this->playerTwoScore = PlayerScore(new Label("0"), Vec2(140, 10), view);

            // Create the ball
            this->ball = Ball(
                Vec2(WIDTH / 2, HEIGHT / 2),
                Vec2(1.0f, 0.0f),
                view);

            // Create the paddles
            this->paddleOne = Paddle(
                Vec2(20.0f, (HEIGHT / 2) - (PADDLE_HEIGHT / 2)),
                Vec2(),
                view);

            this->paddleTwo = Paddle(
                Vec2(WIDTH - 20.0f, (HEIGHT / 2) - (PADDLE_HEIGHT / 2)),
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