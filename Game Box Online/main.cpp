#include "./GameEngine/GameEngineMain.hpp"
#include "ResourcePath.hpp"
#include <iostream>

int main()
{
    std::cout << "[INFO] Resources folder: " << resourcePath() << '\n';
    GameEngine::GameEngineMain* mainEngine = GameEngine::GameEngineMain::GetInstance();
    while (mainEngine->GetRenderWindow()->isOpen())
    {
        mainEngine->Update();
    }
    
    delete mainEngine;
    return 0;
}
