#include "field.h"
#include "globals.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>


struct Field {
	int cols;
	int rows;
	Snake* snake;
	Food* food;
};

Field* createField(size_t cols, size_t rows)
{
	if ((cols >= MAX_COLS) || (rows >= MAX_ROWS)) {
		fprintf(stderr, "Bad field size %d X %d", cols, rows);
		abort();
	}

	Field *object = (Field*)malloc(sizeof(Field));
	if (!object) {
		fprintf(stderr, "Bad field allocation");
		abort();
	}
	object->cols = cols;
	object->rows = rows;
	object->snake = NULL;
	return object;
}

void paintField(Field* self)
{
	char line[MAX_COLS + 1];
	memset(line, '\0', MAX_COLS + 1);

	system("cls");
	for (int i = -1; i < self->rows + 1; i++) {
		if ((-1 == i) || (i == self->rows)) {
			memset(line, '*', self->cols);
		} else {
			memset(line, ' ', self->cols);
			if (self->food) {
				getFoodRow(self->food, line, i);
			}
			if (self->snake) {
				getSnakeRow(self->snake, line, i);
			}
		}
		printf("*%s*\n", line);
	}
}

bool isFoodCollision(Field* self) {
	return snakeIn(self->snake, getX(self->food), getY(self->food));
}

void emplaceSnake(Field* self, Snake* _snake)
{
	self->snake = _snake;
}

void emplaceFood(Field* self, Food* _food) 
{
	self->food = _food;
}

void destroyField(Field* self)
{
	free(self);
}