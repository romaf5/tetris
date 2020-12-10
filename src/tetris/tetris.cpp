//
//  main.cpp
//  tetris-cl
//
//  Created by Roman Furko on 11/11/20.
//

#include <iostream>

#include "sdl2window.hpp"

namespace tetris {

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
      step();
    }
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
    m_world->visualize(m_figure);
  }

private:
  bool m_finished { false };

  std::shared_ptr<State> m_board;
  std::unique_ptr<SDL2Window> m_world;
  std::shared_ptr<FigureWorld> m_figure;
};

};

void test_state() {
  tetris::State state;
  state.occupy_random();
  state.drawCL();
  std::cout << ">>>>>>>>>>>>>>" << '\n';
  state.update();
  state.drawCL();
}

void test_figures() {
  auto figure = tetris::Figure::build(tetris::FigureType::I);
  figure->print();
  figure->rotate();
  figure->print();
}

void test_game() {
  auto client = std::make_unique<tetris::Game>();
  client->loop();
}

const bool enableTests = true;

int main(int argc, const char * argv[]) {
  if (enableTests) {
    test_state();
    test_figures();
    test_game();
  }
  return 0;
}
