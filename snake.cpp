#include "snake.h"
#include "globals.h"
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

enum class DIRECTION {
	UP
	, DOWN
	, LEFT
	, RIGHT
};

struct Snake {
	int hor_bound;
	int ver_bound;

	int x, y;
	DIRECTION current_dir;
};


Snake* createSnake(size_t _hor_bound, size_t _ver_bound)
{
	Snake* object = (Snake*)malloc(sizeof(Snake));
	if (!object) {
		fprintf(stderr, "Bad snake allocation");
		abort();
	}
	object->hor_bound = _hor_bound;
	object->ver_bound = _ver_bound;

	object->x = 5;
	object->y = 3;
	object->current_dir = DIRECTION::DOWN;

	return object;
}

void destroySnake(Snake* self)
{
	free(self);
}

void changeDirection(Snake* self, SNAKE_COMMAND command)
{
	switch (self->current_dir)
	{
	case DIRECTION::UP:
	case DIRECTION::DOWN:
		if (SNAKE_COMMAND::LEFT == command) {
			self->current_dir = DIRECTION::LEFT;
		} else if (SNAKE_COMMAND::RIGHT == command) {
			self->current_dir = DIRECTION::RIGHT;
		}
		break;
	case DIRECTION::LEFT:
	case DIRECTION::RIGHT:
		if (SNAKE_COMMAND::UP == command) {
			self->current_dir = DIRECTION::UP;
		} else if (SNAKE_COMMAND::DOWN == command) {
			self->current_dir = DIRECTION::DOWN;
		}
		break;
	default:
		fprintf(stderr, "Bad snake direction (change)");
		abort();
		break;
	}
}

void makeStep(Snake* self)
{
	switch (self->current_dir)
	{
	case DIRECTION::UP:
		self->y--;
		if (self->y < 0) self->y = self->ver_bound - 1;
		break;
	case DIRECTION::DOWN:
		self->y++;
		if (self->y >= self->ver_bound) self->y = 0;
		break;
	case DIRECTION::LEFT:
		self->x--;
		if (self->x < 0) self->x = self->hor_bound - 1;
		break;
	case DIRECTION::RIGHT:
		self->x++;
		if (self->x >= self->hor_bound) self->x = 0;
		break;
	default:
		fprintf(stderr, "Bad snake direction");
		abort();
		break;
	}
}

bool snakeIn(Snake* self, size_t x, size_t y) {
	return (self->x == x) && (self->y == y);
}

void getSnakeRow(Snake* self, char* buffer, size_t row)
{
	for (int i = 0; i < self->hor_bound; ++i) {
		if ((self->y == row) && (self->x == i)) {
			buffer[i] = '@';
		}
	}
}