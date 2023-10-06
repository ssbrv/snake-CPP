#pragma once

#include <vector>
#include "helpers.h"
#include "staticObjects.h"
#include "constValues.h"

class Apple
{
    Position m_initPosition;
    Size m_size;
    Rectangle m_rectangle;

    // void setPosition(const Position position) { m_position = position; }

public:
    Apple(const Position initPosition, const Size &size, const Rectangle &rectangle) : m_initPosition{initPosition}, m_size{size}, m_rectangle{rectangle}
    {
        m_rectangle.setPosition(m_initPosition);
    }
    Apple() {}

    Position getPosition() const { return m_rectangle.getPosition(); }
    void draw() { m_rectangle.draw(); }

    void respawn(const Position position)
    {
        m_rectangle.setPosition(position);
    }
    // void blink() {}
};

class Snake
{
    Position m_initPosition;
    Vector m_velocity;
    std::vector<Rectangle> m_snake;
    Size m_sizeRectangle;
    Rectangle m_headRectangle;
    Rectangle m_bodyRectangle;

    bool m_moved = false;
    Position m_tailPrevPosition;

    void addBody()
    {
        Rectangle body = m_bodyRectangle;
        body.setPosition(m_tailPrevPosition);
        m_snake.push_back(body);
    }

    void adjust() 
    {
        Position headPosition = m_snake[0].getPosition();

        if (headPosition.m_x < 0)
            headPosition.m_x = GRID_WIDTH - 1;
        else if (headPosition.m_x >= GRID_WIDTH)
            headPosition.m_x = 0;
        if (headPosition.m_y < 0)
            headPosition.m_y = GRID_HEIGHT - 1;
        else if (headPosition.m_y >= GRID_HEIGHT)
            headPosition.m_y = 0;

        m_snake[0].setPosition(headPosition);
    }
 
public:
    Snake(const Position &initPosition, const Vector &velocity, const Size &sizeRectangle, const Rectangle &headRectangle, const Rectangle &bodyRectangle) : m_initPosition{initPosition}, m_velocity{velocity}, m_sizeRectangle{sizeRectangle}, m_headRectangle{headRectangle}, m_bodyRectangle{bodyRectangle}
    {
        m_headRectangle.setSize(m_sizeRectangle);
        m_bodyRectangle.setSize(m_sizeRectangle);
        Rectangle head = m_headRectangle;
        head.setPosition(m_initPosition);
        m_snake.push_back(head);
        m_tailPrevPosition = Position{m_initPosition.m_x - velocity.m_x, m_initPosition.m_y - velocity.m_y};
        addBody();
        m_tailPrevPosition = Position{m_tailPrevPosition.m_x - velocity.m_x, m_tailPrevPosition.m_y - velocity.m_y};
        addBody();
    }
    Snake() {}

    int m_score = 3;

    Position getHeadPosition() { return m_snake[0].getPosition(); }

    void setVelosity(const Vector &velocity)
    {
        if (m_moved == false || velocity == -1 * m_velocity)
            return;
        m_velocity = velocity;
        m_moved = false;
    }

    void move() 
    {
        m_tailPrevPosition = m_snake.back().getPosition();

        for (size_t i = m_snake.size() - 1; i > 0;)
            m_snake[i].setPosition(m_snake[--i].getPosition());

        m_snake[0].move(m_velocity);
        m_moved = true;
        adjust();
    }

    void draw()
    {
        for (const Rectangle &rectangle : m_snake)
            rectangle.draw();
        m_snake[0].draw();
    }

    bool attemptEat(const Apple &apple) const 
    { 
        for (const Rectangle &rectangle : m_snake)
            if (rectangle.getPosition() == apple.getPosition())
                return true;
        return false;
    }

    void eat()
    {
        addBody();
        m_score++;
    }

    bool inCollision() const 
    {
        for (size_t i = 1; i < m_snake.size(); i++) 
            if (m_snake[i].getPosition() == m_snake[0].getPosition())
                return true;
        return false;
    }
};