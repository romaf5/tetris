#ifndef TETRIS_FIGURES_HPP
#define TETRIS_FIGURES_HPP

#include <vector>
#include <iostream>

#include "utils.hpp"

namespace tetris {

class Figure {
public:
  static std::shared_ptr<Figure> build(FigureType type);
  virtual void rotate(GameAction action);
  void print();
  
  int N = 2;
  std::vector<std::vector<uint8_t>> m_data;
  FigureType m_type { FigureType::I };
private:
  virtual void rotateLeft();
  virtual void rotateRight();
  
};

class FigureI : public Figure {
public:
  FigureI();
};

class FigureSq : public Figure {
public:
  FigureSq();
};

class FigureT : public Figure {
public:
  FigureT();
};

class FigureP : public Figure {
public:
  FigureP();
};

class FigurePI : public Figure {
public:
  FigurePI();
};

class FigureS : public Figure {
public:
  FigureS();
};

class FigureSI : public Figure {
public:
  FigureSI();
};

class FigureWorld {
public:
  static std::shared_ptr<FigureWorld> create(int boardWidth);
  
  glm::i8vec2 m_position;
  ColorVec3 m_color;
  std::shared_ptr<Figure> m_figure;
};

}

#endif