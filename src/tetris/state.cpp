#include "state.hpp"

namespace tetris {

State::State() {
  m_buffer.resize(m_height);
  m_bufferColor.resize(m_height);
  for (int row = 0; row < m_height; ++row) {
    m_buffer[row].resize(m_width);
    m_bufferColor[row].resize(m_width);

    std::fill(m_buffer[row].begin(), m_buffer[row].end(), CELL_EMPTY);
    std::fill(
      m_bufferColor[row].begin(),
      m_bufferColor[row].end(),
      ColorVec3(0, 0, 0)
    );
  }
}

void State::occupy_random() {
  const int fillRows = 15;
  for (int i = 0; i < fillRows; ++i) {
    int row = rand() % m_height;
    std::fill(m_buffer[row].begin(), m_buffer[row].end(), CELL_OCCUPIED);
    std::fill(m_bufferColor[row].begin(), m_bufferColor[row].end(), getRandomColor());
    if (rand() % 2 == 0) {
      auto randCol = rand() % m_width;
      m_buffer[row][randCol] = CELL_EMPTY;
      m_bufferColor[row][randCol] = ColorVec3(0, 0, 0);
    }
  }
}
  
void State::update() {
  std::unordered_set<int> fullRows;
  for (int row = 0; row < m_height; ++row) {
    bool hasEmptyCell = false;
    for (int col = 0; col < m_width && !hasEmptyCell; ++col) {
      hasEmptyCell |= (m_buffer[row][col] == CELL_EMPTY);
    }
    if (!hasEmptyCell) {
      fullRows.insert(row);
    }
  }

  int rowId = 0;
  for (int row = 0; row < m_height; ++row) {
    if (fullRows.find(row) == fullRows.end()) {
      m_buffer[rowId] = m_buffer[row];
      m_bufferColor[rowId++] = m_bufferColor[row];
    }
  }
    
  for (int row = 0; row < fullRows.size(); ++row) {
    int rowIndex = m_height - row - 1;
    std::fill(m_buffer[rowIndex].begin(), m_buffer[rowIndex].end(), CELL_EMPTY);
    std::fill(
      m_bufferColor[rowIndex].begin(),
      m_bufferColor[rowIndex].end(),
      ColorVec3(0, 0, 0)
    );
  }
}

bool State::checkAction(std::shared_ptr<FigureWorld> figure) {
  const auto& figureBlock = figure->m_figure;
  const auto& position = figure->m_position;

  for (int r = 0; r < figureBlock->N; ++r) {
    for (int c = 0; c < figureBlock->N; ++c) {
      if (figureBlock->m_data[r][c] == 1) {
        int pr = r + position.y;
        int pc = c + position.x;
        if (pr >= m_height || pc >= m_width || m_buffer[pr][pc] == CELL_OCCUPIED) {
          return false;
        }
      }
    }
  }

  return true;
}

int State::findFigureDistance(std::shared_ptr<FigureWorld> figureWorld) {
  int distance = m_height;

  if (!figureWorld) {
    return distance;
  }

  auto& figure = figureWorld->m_figure;
  const auto& position = figureWorld->m_position;

  for (int r = 0; r < figure->N; ++r) {
    for (int c = 0; c < figure->N; ++c) {
      if (figure->m_data[r][c] != CELL_EMPTY) {
        continue;
      }

      int pr = r + position.y;
      int pc = c + position.x;

      if (pr >= m_height || pc >= m_width) {
        distance = 0;
        continue;
      }

      int currentDistance = 0;
      while (pr + currentDistance + 1 < m_height && m_buffer[pr + currentDistance + 1][pc] == CELL_EMPTY) {
        currentDistance++;
      }

      distance = std::min(distance, currentDistance);
    }
  }
  return distance;
}

void State::checkIfFigureStopped(std::shared_ptr<FigureWorld>& figureWorld) {
  if (!figureWorld) {
    return;
  }

  auto& figure = figureWorld->m_figure;
  const auto& position = figureWorld->m_position;

  bool stop = false;

  for (int r = 0; r < figure->N; ++r) {
    for (int c = 0; c < figure->N; ++c) {
      if (figure->m_data[r][c] == CELL_EMPTY) {
        continue;
      }

      int pr = r + position.y;
      int pc = c + position.x;
  
      if (pr + 1 >= m_height || m_buffer[pr + 1][pc] == CELL_OCCUPIED) {
        stop = true;
      }
    }
  }
    

  if (!stop) {
    return;
  }

  for (int r = 0; r < figure->N; ++r) {
    for (int c = 0; c < figure->N; ++c) {
      if (figure->m_data[r][c] == CELL_EMPTY) {
        continue;
      }

      int pr = r + position.y;
      int pc = c + position.x;
      m_bufferColor[pr][pc] = figureWorld->m_color;
      m_buffer[pr][pc] = CELL_OCCUPIED;
    }
  }
  figure = nullptr;
}
  

void State::step(std::shared_ptr<FigureWorld>& figure, const GameAction action) {
  assert (figure != nullptr);

  int speed = 1;
  auto& position = figure->m_position;
  switch (action) {
    case GameAction::MoveLeft:
      if (position.x > 0) {
        position.x -= 1;
        if (!checkAction(figure)) {
          position.x += 1;
        }
      }
      break;
    case GameAction::MoveRight:
      if (position.x + 1 < m_width) {
        position.x += 1;
        if (!checkAction(figure)) {
          position.x -= 1;
        }
      }
      break;
    
    case GameAction::SpeedUp:
      speed += 1;
      break;

    case GameAction::Rotate:
      figure->m_figure->rotate(GameAction::Rotate);
      if (!checkAction(figure)) {
        figure->m_figure->rotate(GameAction::RotateInv);
      }
      break;
    
    case GameAction::Nothing:
    case GameAction::Count:
    case GameAction::Quit:
      break;

    case GameAction::RotateInv:
      throw std::logic_error("wrong action for state");
  }

  int figureDistance = findFigureDistance(figure);
  speed = std::min(speed, figureDistance);

  figure->m_position.y += speed;

  checkIfFigureStopped(figure);
} 

void State::drawCL() {
  for (int row = 0; row < m_height; ++row) {
    for (int col = 0; col < m_width; ++col) {
      std::cout << m_buffer[m_height - row - 1][col];
    }
    std::cout << '\n';
  }
}

}