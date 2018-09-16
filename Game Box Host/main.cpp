#include <iostream>
#include "GameEngineMain.hpp"
#include "NetworkManager.hpp"
#include "ResourcePath.hpp"

#define HOST true

bool quit;

int main(int argc, char** argv)
{
  std::cout << "Path: " << resourcePath() << '\n';
  
  GameEngine::GameEngineMain* mainEngine = GameEngine::GameEngineMain::GetInstance(true);
  quit = false;
  while (!quit)
  {
    mainEngine->Update();
  }
   
  delete mainEngine;
  return 0;
}
