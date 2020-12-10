#ifndef TETRIS_SDL2WINDOW_HPP
#define TETRIS_SDL2WINDOW_HPP

#include <unordered_map>

#include <SDL2/SDL.h>

#include "state.hpp"

namespace tetris {

class SDL2ActionManager {
public:
  SDL2ActionManager() = default;

  GameAction getAction() {
    static std::unordered_map<int, GameAction> key2action {
      {SDLK_ESCAPE, GameAction::Quit},
      {SDLK_LEFT, GameAction::MoveLeft},
      {SDLK_RIGHT, GameAction::MoveRight},
      {SDLK_DOWN, GameAction::SpeedUp},
      {SDLK_UP, GameAction::Rotate}
    };

    SDL_PollEvent(&m_event);

    if (m_event.type != SDL_KEYDOWN) {
      return GameAction::Nothing;
    }

    auto keycode = m_event.key.keysym.sym;
    if (key2action.count(keycode)) {
      return key2action[keycode];
    }

    return GameAction::Nothing;
  } 

private:
  SDL_Event m_event;
};

class SDL2Window {
public:
  SDL2Window() {
    m_window = SDL_CreateWindow(
      "tetris", 
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      m_windowWidth,
      m_windowHeight,
      SDL_WINDOW_SHOWN
    );

    m_renderer =  SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    m_actionManager = std::make_unique<SDL2ActionManager>();
  }

  ~SDL2Window() {
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
  } 

  GameAction getAction() {
    if (!m_actionManager) {
      return GameAction::Nothing;
    }

    return m_actionManager->getAction();
  }

  void setBoard(std::shared_ptr<State> board) {
    m_board = board;
  }
  
  void visualize(std::shared_ptr<FigureWorld> figure) {
    if (!m_board) {
      std::cout << "[SDL2Window/visualize] m_board is nullptr\n";
      return;
    }
    
    SDL_SetRenderDrawColor( m_renderer, 0, 0, 0, 255 );

    SDL_RenderClear( m_renderer );

    for (int r = 0; r < m_board->m_height; ++r) {
      for (int c = 0; c < m_board->m_width; ++c) {
        drawRectangle(r, c);   
      }
    }

    drawFigure(figure);

    drawGrid();

    SDL_RenderPresent(m_renderer);
  }

private:
  glm::vec2 worldToScreen(glm::vec2 p) {
    glm::vec2 r;
    r.x = (float)p.x / m_board->m_width * m_windowWidth;
    r.y = (1 - (float)p.y / m_board->m_height) * m_windowHeight;
    return r;
  }

  void drawRectangle(int r, int c) {
    if (m_board->m_buffer[r][c] == CELL_EMPTY) {
      return;
    }
    
    auto tl = worldToScreen({c, r});
    auto br = worldToScreen({c + 1, r + 1});
    
    const auto color = m_board->m_bufferColor[r][c];
    
    SDL_Rect dr;
    dr.x = tl.x;
    dr.y = tl.y;
    dr.w = br.x - tl.x;
    dr.h = br.y - tl.y;

    SDL_SetRenderDrawColor( m_renderer, color.r, color.g, color.b, 255 );

    SDL_RenderFillRect( m_renderer, &dr );

  }

  void drawGrid() {
    assert (m_board != nullptr);
    
    // white color
    SDL_SetRenderDrawColor( m_renderer, 255, 255, 255, 255 );

    for (int r = 0; r < m_board->m_height; ++r) {
      auto start = worldToScreen({0, r});
      auto finish = worldToScreen({m_board->m_width, r});

      SDL_RenderDrawLine(m_renderer, start.x, start.y, finish.x, finish.y);
    }


    for (int c = 0; c < m_board->m_width; ++c) {
      auto start = worldToScreen({c, 0});
      auto finish = worldToScreen({c, m_board->m_height});

      SDL_RenderDrawLine(m_renderer, start.x, start.y, finish.x, finish.y);
    }
  }

  void drawFigure(std::shared_ptr<FigureWorld> figure) {
    if (!figure) {
      std::cout << "No figure\n";
      return;
    }

    std::cout << "[drawFigure] TODO: implement figure!\n";
  }

  int m_windowWidth = 250;
  int m_windowHeight = 600;

  SDL_Window* m_window = nullptr;
  SDL_Renderer* m_renderer = nullptr;
  std::shared_ptr<State> m_board;
  std::unique_ptr<SDL2ActionManager> m_actionManager;
};
  
}

#endif