#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <list>
#include <utility>

class Snake {

public:
    enum Direction {
        NoMove,
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown
    };
    Snake();
    ~Snake();
    std::list<std::pair<int, int>> asnake;
    void setMoveDirection(Direction direction);
    void run();
    void longer();
    Direction currentDirection();
    bool not_confused(Direction A,Direction B);
private:
    Direction moveDirection;
};


#endif // SNAKE_H
