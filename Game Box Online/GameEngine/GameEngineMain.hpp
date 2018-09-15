#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "EntitySystem/Entity.hpp"
#include "EntitySystem/Components/RenderComponent.hpp"

// TODO(BORA): How was this working without this include
#include "../Game/GameBoard.hpp"

namespace GameEngine
{
  class GameEngineMain
  {
  public:
    ~GameEngineMain();
    
    static GameEngineMain* GetInstance() { if (!sm_instance) sm_instance = new GameEngineMain(); return sm_instance; }
    //Returns time between update frames in seconds
    static float       GetTimeDelta() { return sm_deltaTimeClock.getElapsedTime().asSeconds(); }
    static float       GetGameTime() { return sm_gameClock.getElapsedTime().asSeconds(); }
    
    sf::RenderWindow* GetRenderWindow() const { return m_renderWindow; }
    void Update();
    void SetRenderTarget(sf::RenderTarget* target) { m_renderTarget = target; }
    
    void AddEntity(Entity* entity);
    void RemoveEntity(Entity* entity);
    
    void OnInitialised();
    bool IsGameOver() const { return m_gameBoard && m_gameBoard->IsGameOver(); }
      
      static float WINDOW_HEIGHT;
      static float WINDOW_WIDTH;
    
  private:
    GameEngineMain();
    
    void CreateAndSetUpWindow();
      
    void ShowSplashScreen();
    void ShowMenu();
    void StartGame();
    
    void AddPendingEntities();
    void RemovePendingEntities();
    void UpdateWindowEvents();
    void UpdateEntities();
    void RenderEntities();
    
    static GameEngineMain* sm_instance;
    static sf::Clock     sm_deltaTimeClock;
    static sf::Clock     sm_gameClock;
    
    std::vector<Entity*> m_entitiesToAdd;
    std::vector<Entity*> m_entities;
    std::vector<Entity*> m_entitiesToRemove;
    
    sf::RenderTarget*   m_renderTarget;
    sf::RenderWindow*   m_renderWindow; //In future they will be different
    
    Game::GameBoard*    m_gameBoard; //TODO - better spot for this?
    
    bool m_windowInitialised;
  };
}
