#include "snake.h"
#include "globals.h"
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

static void step(Snake*, int x, int y);

enum class DIRECTION {
	UP
	, DOWN
	, LEFT
	, RIGHT
};

struct Point {
	int x;
	int y;
};

struct Snake {
	int hor_bound;
	int ver_bound;

	struct Point *body;
	int head;
	size_t size;
	bool grow;
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

	object->body = (Point*)malloc(_hor_bound * _ver_bound * sizeof(Point));
	if (!object->body) {
		fprintf(stderr, "Bad snake allocation");
		abort();
	}
	object->size = 1;
	object->body[0] = { 3, 5 };
	//object->body[1] = { 3, 6 };
	//object->body[2] = { 4, 6 };
	object->head = 0;
	object->grow = false;


	object->current_dir = DIRECTION::DOWN;

	return object;
}

void destroySnake(Snake* self)
{
	free(self->body);
	free(self);
}

void grow(Snake* self) {
	self->grow = true;
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
		step(self, 0, -1);
		break;
	case DIRECTION::DOWN:
		step(self, 0, 1);
		break;
	case DIRECTION::LEFT:
		step(self, -1, 0);
		break;
	case DIRECTION::RIGHT:
		step(self, 1, 0);
		break;
	default:
		fprintf(stderr, "Bad snake direction");
		abort();
		break;
	}
}

bool snakeIn(Snake* self, size_t x, size_t y) {
	for (int i = 0; i < self->size; i++) {
		if ((self->body[i].x == x) && (self->body[i].y == y)) return true;
	}
	return false;
}

void getSnakeRow(Snake* self, char* buffer, size_t row)
{
	for (int i = 0; i < self->size; i++) {
		if (self->body[i].y == row) {
			buffer[self->body[i].x] = (self->head == i) ? '@': 'x';
		}
	}
	
}

void step(Snake* self, int x, int y) {
	int idx = self->head;
	Point head = self->body[idx];
	
	if (self->grow) {
		self->size++;
		for (int i = self->size - 1; i > idx ; i--) {
			self->body[i] = self->body[i - 1];
		}
		self->grow = false;
	}

	head.x += x;
	head.y += y;
	if (head.x >= self->hor_bound)
		head.x = 0;
	else if (head.x < 0)
		head.x = self->hor_bound - 1;
	if (head.y >= self->ver_bound)
		head.y = 0;
	else if (head.y < 0)
		head.y = self->ver_bound - 1;

	if (++idx == self->size) idx = 0;
	self->head = idx;
	self->body[idx] = head;
}

bool isSelfCollision(Snake* self) {
	for (int i = 0; i < self->size; i++) {
		if (i == self->head) continue;
		if ((self->body[i].x == self->body[self->head].x)
			&& (self->body[i].y == self->body[self->head].y))
			return true;
	}
	return false;
}