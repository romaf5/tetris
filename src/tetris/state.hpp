#ifndef TETRIS_STATE_HPP
#define TETRIS_STATE_HPP

#include <iostream>
#include <vector>
#include <unordered_set>

#include "figures.hpp"

namespace tetris {

class State {
public:
  State();

  void update();

  int findFigureDistance(std::shared_ptr<FigureWorld> figure);
  void checkIfFigureStopped(std::shared_ptr<FigureWorld>& figure);

  bool checkAction(std::shared_ptr<FigureWorld> figure);
  void step(std::shared_ptr<FigureWorld>& figure, const GameAction action);

  bool gameFinished = false;
  static constexpr int m_width = 10;
  static constexpr int m_height = 20;
  std::vector<std::vector<uint8_t>> m_buffer;
  std::vector<std::vector<ColorVec3>> m_bufferColor;
};
}

#endif
