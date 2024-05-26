#pragma once

enum class SNAKE_COMMAND {
    NOPE
    , UNKNOWN
    , EXIT
    , UP
    , DOWN
    , LEFT
    , RIGHT
};

struct Snake;

Snake* createSnake(size_t hor_bound, size_t ver_bound);
void destroySnake(Snake*);

void changeDirection(Snake*, SNAKE_COMMAND);
void makeStep(Snake*);
bool snakeIn(Snake*, size_t x, size_t y);
void getSnakeRow(Snake*, char * buffer, size_t row);