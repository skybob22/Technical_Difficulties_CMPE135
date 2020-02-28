#include <iostream>
#include "GameManager.h"

int main(){
  GameManager GM;
  GM.startGame(Game::GameMode::PVE);
  std::cout << std::endl << GM << std::endl;
}
