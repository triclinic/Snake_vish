// snake.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <conio.h>
#include <stdlib.h>

#include "field.h"
#include "globals.h"
#include "windows.h"


#define	  stop __asm nop

SNAKE_COMMAND getDirection() {
    if (!_kbhit()) {
        return SNAKE_COMMAND::NOPE;
    }
    for (;;) {                      // TODO: make via FSM
        int key = _getch();
        switch (key)
        {
        case 'w':
        case 72:
            return SNAKE_COMMAND::UP;
        case 's':
        case 80:
            return SNAKE_COMMAND::DOWN;
        case 'a':
        case 75:
            return SNAKE_COMMAND::LEFT;
        case 'd':
        case 77:
            return SNAKE_COMMAND::RIGHT;
        case 27:
            return SNAKE_COMMAND::EXIT;
        case 0xe0:
        case 0:
            continue;
        default:
            return SNAKE_COMMAND::UNKNOWN;
        }
        fprintf(stderr, "Bad command");
        abort();
    }
}

int main()
{
    stop
    int score = 0;
    Field* f = createField(COLS, ROWS);
    Snake* s = createSnake(COLS, ROWS);
    Food* food = createFood(COLS, ROWS);
    emplaceSnake(f, s);
    emplaceFood(f, food);
    generateFood(food);
    
    for (;;) {
        SNAKE_COMMAND command = getDirection();
        if (SNAKE_COMMAND::EXIT == command) break;
        if (SNAKE_COMMAND::NOPE != command) {
            changeDirection(s, command);
        }
        
        makeStep(s);
        if (isFoodCollision(f)) {
            generateFood(food);
            score++;
        }

        paintField(f);
        printf("Score: %d\n", score);
        Sleep(500);
    }
        
    destroyFood(food);
    destroySnake(s);
    destroyField(f);
    stop

}
