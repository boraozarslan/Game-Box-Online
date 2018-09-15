#include "GameEngineMain.hpp"

#include <assert.h>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "Util/TextureManager.hpp"
#include "Util/AnimationManager.hpp"

using namespace GameEngine;

float GameEngineMain::WINDOW_HEIGHT = 500;
float GameEngineMain::WINDOW_WIDTH = 500;
//Nullptr init for singleton class
GameEngineMain* GameEngineMain::sm_instance = nullptr;
sf::Clock    GameEngineMain::sm_deltaTimeClock;
sf::Clock    GameEngineMain::sm_gameClock;

GameEngineMain::GameEngineMain()
: m_renderTarget(nullptr)
, m_windowInitialised(false)
, m_gameBoard(nullptr)
{
  CreateAndSetUpWindow();
  TextureManager::GetInstance()->LoadTextures();
  AnimationManager::GetInstance()->InitStaticGameAnimations();
}


GameEngineMain::~GameEngineMain()
{
  delete m_renderTarget;
}


void GameEngineMain::OnInitialised()
{
  m_gameBoard = new Game::GameBoard();
  sm_deltaTimeClock.restart();
  sm_gameClock.restart();
}


void GameEngineMain::CreateAndSetUpWindow()
{
  m_renderWindow = new sf::RenderWindow(sf::VideoMode((unsigned int)WINDOW_WIDTH, (unsigned int)WINDOW_HEIGHT), "Hack The North");
  m_renderTarget = m_renderWindow;
}


void GameEngineMain::AddEntity(Entity* entity)
{
  auto found = std::find(m_entities.begin(), m_entities.end(), entity);
  assert(found == m_entities.end()); //Drop an assert if we add duplicate;
  if (found == m_entities.end())
  {
    m_entitiesToAdd.push_back(entity);
  }
}


void GameEngineMain::RemoveEntity(Entity* entity)
{
  auto found = std::find(m_entities.begin(), m_entities.end(), entity);
  assert(found != m_entities.end()); //Drop an assert if we remove a non existing entity;
  
  if (found != m_entities.end())
  {
    m_entitiesToRemove.push_back(entity);
    entity->OnRemoveFromWorld();
  }
}


void GameEngineMain::Update()
{
  std::this_thread::sleep_for(std::chrono::milliseconds(20));
  //First update will happen after init for the time being (we will add loading later)
  if (!m_windowInitialised)
  {
    m_windowInitialised = true;
    OnInitialised();
  }
  
  RemovePendingEntities();
  
  UpdateWindowEvents();
  if (m_gameBoard)
    m_gameBoard->Update();
  
  UpdateEntities();
  RenderEntities();
  
  AddPendingEntities();
  
  sm_deltaTimeClock.restart();
}


void GameEngineMain::AddPendingEntities()
{
  for (int a = 0; a < m_entitiesToAdd.size(); ++a)
  {
    m_entities.push_back(m_entitiesToAdd[a]);
    m_entitiesToAdd[a]->OnAddToWorld();
  }
  
  m_entitiesToAdd.clear();
}


void GameEngineMain::RemovePendingEntities()
{
  for (int a = 0; a < m_entitiesToRemove.size(); ++a)
  {
    Entity* entity = m_entitiesToRemove[a];
    
    auto found = std::find(m_entities.begin(), m_entities.end(), entity);
    assert(found != m_entities.end());
    
    if (found != m_entities.end())
    {
      m_entities.erase(found);
      
      delete entity;
    }
  }
  
  m_entitiesToRemove.clear();
}


void GameEngineMain::UpdateWindowEvents()
{
  if (!m_renderWindow)
    return;
  
  sf::Event event;
  while (m_renderWindow->pollEvent(event))
  {
    if (event.type == sf::Event::Closed)
    {
      m_renderWindow->close();
      m_renderTarget = nullptr;
      break;
    }
  }
}


void GameEngineMain::UpdateEntities()
{
  //Update que
  for(auto entity : m_entities)
  {
    entity->Update();
  }
}


void GameEngineMain::RenderEntities()
{
  if (!m_renderTarget)
    return;
  
  m_renderTarget->clear();
  
  //Render que
  std::vector<RenderComponent*> renderers;
  for(auto entity : m_entities)
  {
    if (RenderComponent* render = entity->GetComponent< RenderComponent >())
    {
      renderers.push_back(render);
    }
  }
  
  // sort using a lambda expression
  std::sort(renderers.begin(), renderers.end(), [](RenderComponent* a, RenderComponent* b)
            {
              return a->GetZLevel() < b->GetZLevel();
            });
  
  for(auto renderer : renderers)
  {
    renderer->Render(m_renderTarget);
  }
  
  if (m_renderWindow && m_renderWindow->isOpen())
  {
    m_renderWindow->display();
  }
}

