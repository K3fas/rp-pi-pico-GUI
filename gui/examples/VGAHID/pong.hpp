#pragma once
#include "IVGA.hpp"
#include "RpiUI.hpp"

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

    const int BALL_WIDTH = 8;
    const int BALL_HEIGHT = 8;
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
        UI::Rectangle *rect = new UI::Rectangle();

    public:
        Vec2 position;
        Vec2 velocity;

        Ball() = default;
        Ball(Vec2 position, Vec2 velocity, UI::View &view)
            : position(position), velocity(velocity)
        {
            rect->coords.start.x = static_cast<int>(position.x);
            rect->coords.start.y = static_cast<int>(position.y);
            rect->coords.width.v = BALL_WIDTH;
            rect->coords.height.v = BALL_HEIGHT;
            rect->color = VColors::Color::White;

            view.AddElement(rect);
        }

        void Update(float dt)
        {
            position += velocity * dt;
            rect->coords.start.x = position.x;
            rect->coords.start.y = position.y;
        }

        void CollideWithPaddle(Contact const &contact)
        {
            position.x += contact.penetration;
            velocity.x = -velocity.x;

            if (contact.type == CollisionType::Top)
            {
                velocity.y = -0.75f * BALL_SPEED;
            }
            else if (contact.type == CollisionType::Bottom)
            {
                velocity.y = 0.75f * BALL_SPEED + BALL_ACCEL;
            }
            velocity.y += sgn(velocity.y) * BALL_ACCEL * BALL_SPEED * 0.75;
            velocity.x += sgn(velocity.x) * BALL_ACCEL * BALL_SPEED;
        }

        void CollideWithWall(Contact const &contact)
        {
            if ((contact.type == CollisionType::Top) || (contact.type == CollisionType::Bottom))
            {
                position.y += contact.penetration;
                velocity.y = -velocity.y;
            }
            else if (contact.type == CollisionType::Left)
            {
                position.x = WINDOW_WIDTH / 2.0f;
                position.y = WINDOW_HEIGHT / 2.0f;
                velocity.x = BALL_SPEED;
                velocity.y = 0.75f * BALL_SPEED;
            }
            else if (contact.type == CollisionType::Right)
            {
                position.x = WINDOW_WIDTH / 2.0f;
                position.y = WINDOW_HEIGHT / 2.0f;
                velocity.x = -BALL_SPEED;
                velocity.y = 0.75f * BALL_SPEED;
            }
        }
    };

    class Paddle
    {
        UI::Rectangle *rect = new UI::Rectangle();

    public:
        Vec2 position;
        Vec2 velocity;

        Paddle() = default;
        Paddle(Vec2 position, Vec2 velocity, UI::View &view)
            : position(position), velocity(velocity)
        {
            rect->coords.start.x = static_cast<int>(position.x);
            rect->coords.start.y = static_cast<int>(position.y);
            rect->coords.width.v = PADDLE_WIDTH;
            rect->coords.height.v = PADDLE_HEIGHT;
            rect->color = VColors::Color::White;

            view.AddElement(rect);
        }

        void Update(float dt)
        {
            position += velocity * dt;

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

            rect->coords.start.x = position.x;
            rect->coords.start.y = position.y;
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

        void Update(uint32_t dt)
        {
            if (Pong::buttons[Buttons::PaddleOneUp])
            {
                paddleOne.velocity.y = -PADDLE_SPEED;
            }
            else if (Pong::buttons[Buttons::PaddleOneDown])
            {
                paddleOne.velocity.y = PADDLE_SPEED;
            }
            else
            {
                paddleOne.velocity.y = 0.0f;
            }

            if (Pong::buttons[Buttons::PaddleTwoUp])
            {
                paddleTwo.velocity.y = -PADDLE_SPEED;
            }
            else if (Pong::buttons[Buttons::PaddleTwoDown])
            {
                paddleTwo.velocity.y = PADDLE_SPEED;
            }
            else
            {
                paddleTwo.velocity.y = 0.0f;
            }

            ball.Update(dt);
            paddleOne.Update(dt);
            paddleTwo.Update(dt);

            // Check collisions
            if (Contact contact = CheckPaddleCollision(ball, paddleOne);
                contact.type != CollisionType::None)
            {
                ball.CollideWithPaddle(contact);
            }
            else if (contact = CheckPaddleCollision(ball, paddleTwo);
                     contact.type != CollisionType::None)
            {
                ball.CollideWithPaddle(contact);
            }
            else if (contact = CheckWallCollision(ball);
                     contact.type != CollisionType::None)
            {
                ball.CollideWithWall(contact);
                if (contact.type == CollisionType::Left)
                {
                    playerTwoScoreText.label->text = std::to_string(++playerTwoScore);
                }
                else if (contact.type == CollisionType::Right)
                {
                    playerOneScoreText.label->text = std::to_string(++playerOneScore);
                }
            }
        }

    private:
        Contact CheckPaddleCollision(Ball const &ball, Paddle const &paddle)
        {
            float ballLeft = ball.position.x;
            float ballRight = ball.position.x + BALL_WIDTH;
            float ballTop = ball.position.y;
            float ballBottom = ball.position.y + BALL_HEIGHT;

            float paddleLeft = paddle.position.x;
            float paddleRight = paddle.position.x + PADDLE_WIDTH;
            float paddleTop = paddle.position.y;
            float paddleBottom = paddle.position.y + PADDLE_HEIGHT;

            Contact contact{};

            if (ballLeft >= paddleRight)
            {
                return contact;
            }

            if (ballRight <= paddleLeft)
            {
                return contact;
            }

            if (ballTop >= paddleBottom)
            {
                return contact;
            }

            if (ballBottom <= paddleTop)
            {
                return contact;
            }

            float paddleRangeUpper = paddleBottom - (2.0f * PADDLE_HEIGHT / 3.0f);
            float paddleRangeMiddle = paddleBottom - (PADDLE_HEIGHT / 3.0f);

            if (ball.velocity.x < 0)
            {
                // Left paddle
                contact.penetration = paddleRight - ballLeft;
            }
            else if (ball.velocity.x > 0)
            {
                // Right paddle
                contact.penetration = paddleLeft - ballRight;
            }

            if ((ballBottom > paddleTop) && (ballBottom < paddleRangeUpper))
            {
                contact.type = CollisionType::Top;
            }
            else if ((ballBottom > paddleRangeUpper) && (ballBottom < paddleRangeMiddle))
            {
                contact.type = CollisionType::Middle;
            }
            else
            {
                contact.type = CollisionType::Bottom;
            }

            return contact;
        }

        Contact CheckWallCollision(Ball const &ball)
        {
            float ballLeft = ball.position.x;
            float ballRight = ball.position.x + BALL_WIDTH;
            float ballTop = ball.position.y;
            float ballBottom = ball.position.y + BALL_HEIGHT;

            Contact contact{};

            if (ballLeft < 0.0f)
            {
                contact.type = CollisionType::Left;
            }
            else if (ballRight > WINDOW_WIDTH)
            {
                contact.type = CollisionType::Right;
            }
            else if (ballTop < 0.0f)
            {
                contact.type = CollisionType::Top;
                contact.penetration = -ballTop;
            }
            else if (ballBottom > WINDOW_HEIGHT)
            {
                contact.type = CollisionType::Bottom;
                contact.penetration = WINDOW_HEIGHT - ballBottom;
            }

            return contact;
        }
    };

}