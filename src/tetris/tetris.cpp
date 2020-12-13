//
//  main.cpp
//  tetris-cl
//
//  Created by Roman Furko on 11/11/20.
//

#include <iostream>

#include "sdl2window.hpp"

namespace tetris {

const int FPS = 10;

class Game {
public:
  Game() {
    m_board = std::make_shared<State>();
    m_figure = nullptr;

    m_world = std::make_unique<SDL2Window>();
    // bad design, can be missed
    m_world->setBoard(m_board);
  }

  void loop() {
    while (!m_finished) {
      auto start = SDL_GetPerformanceCounter();
      step();
      auto end = SDL_GetPerformanceCounter();

      float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
      std::cout << "Elapsed ms: " << elapsedMS << '\n';
      
      float delay = 1000.0 / FPS - elapsedMS;
      SDL_Delay(std::max(0, int(delay)));
      
      if (m_board->gameFinished) {
        m_finished = true;
      }
    }
    std::cout << "Game over!\n";
  }

  void step() {
    assert (m_board != nullptr);
    assert (m_world != nullptr);

    if (m_figure == nullptr) {
      m_figure = FigureWorld::create(m_board->m_width);
    }
    
    auto action = m_world->getAction();
    if (action == GameAction::Quit) {
      m_finished = true;
    }

    // DEBUG CODE
    printAction(action);

    m_board->step(m_figure, action);
    m_board->update();
    m_world->visualize(m_figure);
    
  }

private:
  bool m_finished { false };

  int m_iteration = 0;
  std::shared_ptr<State> m_board;
  std::unique_ptr<SDL2Window> m_world;
  std::shared_ptr<FigureWorld> m_figure;
};

};

int main(int argc, const char * argv[]) {
  auto client = std::make_unique<tetris::Game>();
  client->loop();
  return 0;
}
