#include "sdl2window.hpp"

using namespace tetris;

int main() {
  SDL2Window window;
  for (;;) {
    auto board = std::make_shared<State>();
    window.setBoard(board);
    SDL_Delay(1000);
    window.visualize(nullptr);
    if (window.getAction() == GameAction::Quit) {
      break;
    }
  }
}