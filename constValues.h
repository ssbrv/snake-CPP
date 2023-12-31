#pragma once

/* system */

const int FPS = 6;

/* window */

const char WINDOW_NAME[] = "SNAKE";
const Size WINDOW_SIZE{800, 800};
const Position WINDOW_POSITION{550, 150};
const Color WINDOW_COLOR{0.012, 0.09, 0.09};

/* grid */

const int GRID_WIDTH = 10;
const int GRID_HEIGHT = 10;
const float GRID_THICKNESS = 1.0;
const float BOUNDARY_THICKNESS = 1.0;
const Size GRID_SIZE{(float)GRID_WIDTH, (float)GRID_HEIGHT};

/* standard boxes */

const Size STANDARD_BOX_SIZE{1.0, 1.0};
const Box GRID_BOX{BEGIN_COORDINATES, GREY, GRID_THICKNESS, STANDARD_BOX_SIZE};
const Box BOUNDARY_BOX{BEGIN_COORDINATES, GREY, BOUNDARY_THICKNESS, STANDARD_BOX_SIZE};

/* snake */

const Position SNAKE_INIT_POSITION{4, 4};
const Color SNAKE_HEAD_COLOR = DARK_GREEN;
const Color SNAKE_BODY_COLOR = LIGHT_GREEN;
const float SNAKE_HEAD_THICKNESS = 3.0;
const float SNAKE_BODY_THICKNESS = 2.0;
const Rectangle SNAKE_HEAD_RECTANGLE{BEGIN_COORDINATES, SNAKE_HEAD_COLOR, SNAKE_HEAD_THICKNESS, STANDARD_BOX_SIZE};
const Rectangle SNAKE_BODY_RECTANGLE{BEGIN_COORDINATES, SNAKE_BODY_COLOR, SNAKE_BODY_THICKNESS, STANDARD_BOX_SIZE};

const Vector ONE_RIGHT = VECTOR_I;
const Vector ONE_LEFT = VECTOR_NEGATIVE_I;
const Vector ONE_UP = VECTOR_J;
const Vector ONE_DOWN = VECTOR_NEGATIVE_J;

/* apple */
const Position APPLE_INIT_POSITION{GRID_WIDTH / 2 + 2, GRID_HEIGHT / 2};
const Color APPLE_COLOR = DARK_RED;
const float APPLE_THICKNESS = 2.0;
const Rectangle APPLE_RECTANGLE{BEGIN_COORDINATES, APPLE_COLOR, APPLE_THICKNESS, STANDARD_BOX_SIZE};

/* genereator */
const int MIN_X_RANDOM = 0;
const int MAX_X_RANDOM = GRID_WIDTH - 1;
const int MIN_Y_RANDOM = 0;
const int MAX_Y_RANDOM = GRID_HEIGHT - 1;