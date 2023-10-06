#pragma once

#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>
#include "helpers.h"

class Box
{
protected:
    Position m_position;
    Color m_color;
    float m_thinkness;
    Size m_size;
    
    void draw(GLenum mode) const
    {
        glLineWidth(m_thinkness);
        glColor3f(m_color.m_R, m_color.m_G, m_color.m_B);

        glBegin(mode);
        glVertex2f(m_position.m_x, m_position.m_y);
        glVertex2f(m_position.m_x + m_size.m_x, m_position.m_y);
        glVertex2f(m_position.m_x + m_size.m_x, m_position.m_y + m_size.m_y);
        glVertex2f(m_position.m_x, m_position.m_y + m_size.m_y);
        glEnd();
    }

public:
    Box(const Position &position, const Color &color, const float &thickness, const Size &size) : m_position{position}, m_color{color}, m_thinkness{thickness}, m_size{size} {}
    Box() {}

    void move(const Coordinates2D &delta) { m_position += delta; }

    Position getPosition() const { return m_position; }
    Size getSize() { return m_size; }

    void setPosition(const Position &position) { m_position = position; }
    void setSize(const Size &size) { m_size = size; }

    virtual void draw() const { draw(GL_LINE_LOOP); }
};

class Rectangle : public Box 
{
public:
    Rectangle(const Position &position, const Color &color, const float &thickness, const Size &size) : Box{position, color, thickness, size} {}
    Rectangle() {}
    void draw() const override { Box::draw(GL_QUADS); }
};

/* const */

class Grid
{
    Size m_size;
    std::vector<std::vector<Box>> m_grid;
    Size m_sizeBox;
    Box m_gridBox;
    Box m_boundaryBox;

    void add(const Box &box, const Position &position) { m_grid[position.m_y][position.m_x] = box; }

public:
    Grid(const Size &size, const Size &sizeBox, const Box &gridBox, const Box &boundaryBox) : m_size{size}, m_grid{(size_t)m_size.m_y, std::vector<Box>((size_t)m_size.m_x)}, m_sizeBox{sizeBox}, m_gridBox{gridBox}, m_boundaryBox{boundaryBox}
    {
        m_gridBox.setSize(m_sizeBox);
        m_boundaryBox.setSize(m_sizeBox);
        for (int x = 0; x < m_size.m_x; x++)
            for (int y = 0; y < m_size.m_y; y++)
            {
                Position position{(float)x, (float)y};
                Box box = (position.m_x == 0 || position.m_y == 0 || position.m_x == m_size.m_x - 1 || position.m_y == m_size.m_y - 1) ? m_boundaryBox : m_gridBox;
                box.setPosition(position);
                add(box, position);
            }
    }
    Grid() {}

    void draw() const
    {
        for (const auto &vectorOfBoxes : m_grid)
            for (const auto &box : vectorOfBoxes)
                box.draw();
    }
};