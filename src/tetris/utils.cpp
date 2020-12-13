#include <iostream>

#include "utils.hpp"

namespace tetris {


FigureType getRandomFigureType() {
  auto figuresNumber = (int)FigureType::Count;
  return static_cast<FigureType>(rand() % figuresNumber);
}

void printAction(GameAction action) {
  std::cerr << "print action: ";
  switch (action) {
    case GameAction::Nothing:
      std::cerr << "Nothing\n";
      break;
    case GameAction::Rotate:
      std::cerr << "Rotate\n";
      break;
    case GameAction::RotateInv:
      std::cerr << "RotateInv\n";
      break;
    case GameAction::MoveLeft:
      std::cerr << "Move left\n";
      break;
    case GameAction::MoveRight:
      std::cerr << "Move right\n";
      break;
    case GameAction::SpeedUp:
      std::cerr << "Speed up\n";
      break;
    case GameAction::Quit:
      std::cerr << "Quit\n";
      break;
    case GameAction::Count:
      std::cerr << "Count " << static_cast<int>(action) << '\n';
      break;
  }
}

ColorVec3 getColor(Color color) {
  switch (color) {
    case Color::Yellow:
      return ColorVec3(0, 255, 255);
    case Color::Red:
      return ColorVec3(255, 0, 0);
    case Color::Green:
      return ColorVec3(0, 255, 0);
    case Color::Blue:
      return ColorVec3(0, 0, 255);
    default:
      throw std::invalid_argument("Invalid color code");
  }
}

ColorVec3 getRandomColor() {
  auto numberOfColors = static_cast<int>(Color::Count);
  auto colorIndex = rand() % numberOfColors;
  return getColor(static_cast<Color>(colorIndex));
}

}
