#include "headers/snake.h"
#include <algorithm>
#include <utility>
Snake::Snake() : moveDirection(NoMove) {
  asnake.push_back(std::make_pair(15, 2));
  asnake.push_back(std::make_pair(14, 2));
}
Snake::~Snake() {}
void Snake::setMoveDirection(Direction direction) {
  if (not_confused(direction, moveDirection))
    moveDirection = direction;
}

void Snake::run() {
  switch (moveDirection) {
  case NoMove:
    break;
  case MoveLeft:
    asnake.pop_back();
    if (asnake.front().first > 0)
      asnake.push_front(
          std::make_pair(asnake.front().first - 1, asnake.front().second));
    else
      asnake.push_front(std::make_pair(15, asnake.front().second));
    break;
  case MoveRight:
    asnake.pop_back();
    if (asnake.front().first < 15)
      asnake.push_front(
          std::make_pair(asnake.front().first + 1, asnake.front().second));
    else
      asnake.push_front(std::make_pair(0, asnake.front().second));
    break;
  case MoveUp:
    asnake.pop_back();
    if (asnake.front().second > 0)
      asnake.push_front(
          std::make_pair(asnake.front().first, asnake.front().second - 1));
    else
      asnake.push_front(std::make_pair(asnake.front().first, 15));
    break;
  case MoveDown:
    asnake.pop_back();
    if (asnake.front().second < 15)
      asnake.push_front(
          std::make_pair(asnake.front().first, asnake.front().second + 1));
    else
      asnake.push_front(std::make_pair(asnake.front().first, 0));
    break;
  }
}
Snake::Direction Snake::currentDirection() { return moveDirection; }
bool Snake::not_confused(Direction A, Direction B) {
  if (A == B)
    return false;
  else if ((A == MoveUp && B == MoveDown) || (A == MoveDown && B == MoveUp))
    return false;
  else if ((A == MoveLeft && B == MoveRight) ||
           (A == MoveRight && B == MoveLeft))
    return false;
  else
    return true;
}
void Snake::longer() {
  std::cout << "hello" << std::endl;
  switch (moveDirection) {
  case NoMove:
    break;
  case MoveLeft:
    if (asnake.front().first > 0)
      asnake.push_front(
          std::make_pair(asnake.front().first - 1, asnake.front().second));
    else
      asnake.push_front(std::make_pair(15, asnake.front().second));
    break;
  case MoveRight:
    if (asnake.front().first < 15)
      asnake.push_front(
          std::make_pair(asnake.front().first + 1, asnake.front().second));
    else
      asnake.push_front(std::make_pair(0, asnake.front().second));
    break;
  case MoveUp:
    if (asnake.front().second > 0)
      asnake.push_front(
          std::make_pair(asnake.front().first, asnake.front().second - 1));
    else
      asnake.push_front(std::make_pair(asnake.front().first, 15));
    break;
  case MoveDown:
    if (asnake.front().second < 15)
      asnake.push_front(
          std::make_pair(asnake.front().first, asnake.front().second + 1));
    else
      asnake.push_front(std::make_pair(asnake.front().first, 0));
    break;
  }
}
