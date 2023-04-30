#include "pong.hpp"

using namespace Pong;

void Ball::CollideWithPaddle(Contact const &contact)
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

void Ball::CollideWithWall(Contact const &contact)
{
    if ((contact.type == CollisionType::Top) || (contact.type == CollisionType::Bottom))
    {
        position.y += contact.penetration;
        velocity.y = -velocity.y;
    }
    else if (contact.type == CollisionType::Left)
    {
        position.x = WIDTH / 2.0f;
        position.y = HEIGHT / 2.0f;
        velocity.x = BALL_SPEED;
        velocity.y = 0;
    }
    else if (contact.type == CollisionType::Right)
    {
        position.x = WIDTH / 2.0f;
        position.y = HEIGHT / 2.0f;
        velocity.x = -BALL_SPEED;
        velocity.y = 0;
    }
}
void PongGame::Update()
{
    ProcessButtons();

    ball.Update();
    paddleOne.Update();
    paddleTwo.Update();

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
            playerTwoScore.label->SetText(std::to_string(++playerTwoScoreVal));
        }
        else if (contact.type == CollisionType::Right)
        {
            playerOneScore.label->SetText(std::to_string(++playerOneScoreVal));
        }
    }
}

Contact PongGame::CheckPaddleCollision(Ball const &ball, Paddle const &paddle)
{
    float ballLeft = ball.position.x;
    float ballRight = ball.position.x + BALL_RADIUS;
    float ballTop = ball.position.y;
    float ballBottom = ball.position.y + BALL_RADIUS;

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

Contact PongGame::CheckWallCollision(Ball const &ball)
{
    float ballLeft = ball.position.x;
    float ballRight = ball.position.x + BALL_RADIUS;
    float ballTop = ball.position.y;
    float ballBottom = ball.position.y + BALL_RADIUS;

    Contact contact{};

    if (ballLeft < 0.0f)
    {
        contact.type = CollisionType::Left;
    }
    else if (ballRight > WIDTH)
    {
        contact.type = CollisionType::Right;
    }
    else if (ballTop < 0.0f)
    {
        contact.type = CollisionType::Top;
        contact.penetration = -ballTop;
    }
    else if (ballBottom > HEIGHT)
    {
        contact.type = CollisionType::Bottom;
        contact.penetration = HEIGHT - ballBottom;
    }

    return contact;
}

void PongGame::ProcessButtons()
{
    buttons[0] = false;
    buttons[1] = false;
    buttons[2] = false;
    buttons[3] = false;
    for (size_t i = 0; i < 6; i++)
    {
        if (HID::kbd::pressedKeys[i] == 'w')
        {
            buttons[0] = true;
        }
        if (HID::kbd::pressedKeys[i]  == 's')
        {
            buttons[1] = true;
        }
        if (HID::kbd::pressedKeys[i]  == 'i')
        {
            buttons[2] = true;
        }
        if (HID::kbd::pressedKeys[i]  == 'k')
        {
            buttons[3] = true;
        }
    }

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
}
