#include "figures.hpp"

namespace tetris {

void Figure::print() {
	std::cout << "***" << '\n';
	
  for (int r = 0; r < N; ++r) {
    for (int c = 0; c < N; ++c) {
      std::cout << m_data[r][c];
    }
    std::cout << '\n';
  }

	std::cout << "***" << '\n';
}

void Figure::rotate(GameAction action) {
  if (action == GameAction::Rotate) {
    rotateRight();
  } else if (action == GameAction::RotateInv) {
    rotateLeft();
  } else {
    throw std::logic_error("action is not suitable for rotate");
  }
}

void Figure::rotateLeft() {
  for (int r = 0; r < N; ++r) {
    for (int c = 0; c < r; ++c) {
      std::swap(m_data[r][c], m_data[c][r]);
    }
  }

  for (int c = 0; c < N; ++c) {
    for (int r = 0; r < N / 2; ++r) {
      std::swap(m_data[r][c], m_data[N - r - 1][c]);
    }
  }
}

void Figure::rotateRight() {
  for (int c = 0; c < N; ++c) {
    for (int r = 0; r < N / 2; ++r) {
      std::swap(m_data[r][c], m_data[N - r - 1][c]);
    }
  }

  for (int r = 0; r < N; ++r) {
    for (int c = 0; c < r; ++c) {
      std::swap(m_data[r][c], m_data[c][r]);
    }
  }
}
   
FigureI::FigureI() {
	m_type = FigureType::I;
  N = 4;
	m_data.resize(N);
  for (int r = 0; r < N; ++r) {
    m_data[r].resize(N);
    m_data[r][1] = 1;
  }
}

FigureSq::FigureSq() {
	m_type = FigureType::Sq;
	N = 2;
  m_data.resize(N);
  for (int r = 0; r < N; ++r) {
    m_data[r].resize(N);
    for (int c = 0; c < N; ++c) {
      m_data[r][c] = 1;
    }
  }
}

FigureT::FigureT() {
  m_type = FigureType::T;
  N = 3;
  m_data.resize(N);
  for (int r = 0; r < N; ++r) {
    m_data[r].resize(N);
  }
  m_data[0][0] = m_data[0][1] = m_data[0][2] = 1;
  m_data[1][1] = 1;
}

FigureP::FigureP() {
  m_type = FigureType::P;
  N = 3;
  m_data.resize(N);
  for (int r = 0; r < N; ++r) {
    m_data[r].resize(N);
  }

  m_data[0][1] = m_data[1][1] = m_data[2][1] = 1;
  m_data[0][2] = 1;
}

FigurePI::FigurePI() {
  m_type = FigureType::PI;
  N = 3;
  m_data.resize(N);
  for (int r = 0; r < N; ++r) {
    m_data[r].resize(N);
  }

  m_data[0][1] = m_data[1][1] = m_data[2][1] = 1;
  m_data[0][0] = 1;
}

FigureS::FigureS() {
  m_type = FigureType::S;
  N = 3;
  m_data.resize(N);
  for (int r = 0; r < N; ++r) {
    m_data[r].resize(N);
  }

  m_data[0][0] = m_data[0][1] = 1;
  m_data[1][1] = m_data[1][2] = 1;
}

FigureSI::FigureSI() {
  m_type = FigureType::S;
  N = 3;
  m_data.resize(N);
  for (int r = 0; r < N; ++r) {
    m_data[r].resize(N);
  }

  m_data[0][1] = m_data[0][2] = 1;
  m_data[1][0] = m_data[1][1] = 1;
}

std::shared_ptr<FigureWorld> FigureWorld::create(int boardWidth) {
	auto figure = std::make_shared<FigureWorld>();

	figure->m_position = {boardWidth / 2, 0};
	figure->m_color = getRandomColor();
	figure->m_figure = Figure::build(getRandomFigureType());
	return figure;
}

std::shared_ptr<Figure> Figure::build(FigureType type) {
  std::shared_ptr<Figure> figure {nullptr};
  switch (type) {
    case FigureType::I:
      figure = std::make_shared<FigureI>();
      break;
    case FigureType::Sq:
      figure = std::make_shared<FigureSq>();
      break;
    case FigureType::T:
      figure = std::make_shared<FigureT>();
      break;
    case FigureType::P:
      figure = std::make_shared<FigureP>();
      break;
    case FigureType::PI:
      figure = std::make_shared<FigurePI>();
      break;
    case FigureType::S:
      figure = std::make_shared<FigureS>();
      break;
    case FigureType::SI:
      figure = std::make_shared<FigureSI>();
      break;
    case FigureType::Count:
      throw std::logic_error("None figure type"); 
  }
  assert (figure != nullptr);
  return figure;
}

}