#include "food.h"
#include "globals.h"
#include <stdlib.h>
#include <stdio.h>

struct Food
{
	int hor_bound;
	int ver_bound;

	int x, y;
};

Food* createFood(size_t _hor_bound, size_t _ver_bound) {
	Food* object = (Food*)malloc(sizeof(Food));
	if (!object) {
		fprintf(stderr, "Bad food allocation");
		abort();
	}
	object->hor_bound = _hor_bound;
	object->ver_bound = _ver_bound;
	
	object->x = 0;
	object->y = 0;

	return object;
}


void destroyFood(Food* self) {
	free(self);
}

void generateFood(Food* self) {
	self->x = rand() % self->hor_bound;
	self->y = rand() % self->ver_bound;
}

void getFoodRow(Food* self, char* buffer, size_t row) {
	for (int i = 0; i < self->hor_bound; ++i) {
		if ((self->y == row) && (self->x == i)) {
			buffer[i] = '#';
		}
	}
}

size_t getX(Food* self) { return self->x; }

size_t getY(Food* self) { return self->y; }