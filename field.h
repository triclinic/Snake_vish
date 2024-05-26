#pragma once
#include "snake.h"
#include "food.h"

struct Field;

Field * createField(size_t cols, size_t rows);
void destroyField(Field*);

void paintField(Field*);

void emplaceSnake(Field*, Snake*);
void emplaceFood(Field*, Food*);
bool isFoodCollision(Field*);