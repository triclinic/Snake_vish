#pragma once

struct Food;

Food* createFood(size_t hor_bound, size_t ver_bound);
void destroyFood(Food*);

void generateFood(Food*);
size_t getX(Food*);
size_t getY(Food*);
void getFoodRow(Food*, char* buffer, size_t row);