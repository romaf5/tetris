#ifndef TETRIS_UTILS_HPP
#define TETRIS_UTILS_HPP

#include <stdexcept>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>


typedef glm::i8vec3 ColorVec3;

namespace tetris {

constexpr uint8_t CELL_EMPTY = 0;
constexpr uint8_t CELL_OCCUPIED = 1;

enum class FigureType : uint8_t {
  I,
  Sq,
  T,
  S,
  SI,
  P,
  PI,
  Count
};

FigureType getRandomFigureType();

enum class GameAction : uint8_t {
  Nothing = 0,
  Rotate,
  RotateInv, 
  MoveLeft,
  MoveRight,
  SpeedUp,
  Quit,
  Count,
};

void printAction(GameAction action);

enum class Color : uint8_t {
  Yellow,
  Blue,
  Red,
  Green,
  Count
};

ColorVec3 getColor(Color color);

ColorVec3 getRandomColor();

}

#endif