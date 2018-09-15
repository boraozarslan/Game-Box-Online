#include "GameBoard.hpp"

#include "../GameEngine/GameEngineMain.hpp"
#include "../GameEngine/EntitySystem/Components/CollidableComponent.hpp"
#include "../GameEngine/EntitySystem/Components/SpriteRenderComponent.hpp"
#include "GameEntities/PlayerEntity.hpp"
#include "GameEntities/ObstacleEntity.hpp"

using namespace Game;

GameBoard::GameBoard()
: m_lastObstacleSpawnTimer(0.f)
, m_isGameOver(false)
{
  m_player = new PlayerEntity();
  
  GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);
  m_player->SetPos(sf::Vector2f(50.f, 50.f));
  m_player->SetSize(sf::Vector2f(40.f, 40.f));
  
  CreateBackGround();
  //Debug
  for (int a = 0; a < 3; ++a)
  {
    //SpawnNewRandomObstacles();
  }
}


GameBoard::~GameBoard()
{
  
}


void GameBoard::Update()
{
  float dt = GameEngine::GameEngineMain::GetInstance()->GetTimeDelta();

  // Disabling this if
  if (!m_isGameOver && false)
  {
    m_lastObstacleSpawnTimer -= dt;
    if (m_lastObstacleSpawnTimer <= 0.f)
    {
      //SpawnNewRandomObstacles();
      SpawnNewRandomTiledObstacles();
    }
    
    UpdateObstacles(dt);
    UpdatePlayerDying();
  }
}


void GameBoard::UpdateObstacles(float dt)
{
  static float obstacleSpeed = 0.f;
  
  for (std::vector<GameEngine::Entity*>::iterator it = m_obstacles.begin(); it != m_obstacles.end(); ++it)
  {
    GameEngine::Entity* obstacle = (*it);
    sf::Vector2f currPos = obstacle->GetPos();
    currPos.x -= obstacleSpeed * dt;
    obstacle->SetPos(currPos);
    //If we are to remove ourselves
    if (currPos.x < -50.f)
    {
      GameEngine::GameEngineMain::GetInstance()->RemoveEntity(obstacle);
      it = m_obstacles.erase(it);
    }
  }
}


void GameBoard::UpdatePlayerDying()
{
  static float xToPlayerDie = 0.f;
  if (m_player->GetPos().x < xToPlayerDie)
  {
    m_isGameOver = true;
  }
}


void GameBoard::SpawnNewRandomObstacles()
{
  static float minNextSpawnTime = 0.3f;
  static float maxNextSpawnTime = 0.7f;
  
  static float minObstacleXPos = 50.f;
  static float maxObstacleXPos = 450.f;
  static float minObstacleYPos = 20.f;
  static float maxObstacleYPos = 450.f;
  
  static float minObstacleHeight = 50.f;
  static float maxObstacleHeight = 170.f;
  static float minObstacleWidth = 20.f;
  static float maxObstacleWidth = 40.f;
  
  sf::Vector2f pos = sf::Vector2f(RandomFloatRange(minObstacleXPos, maxObstacleXPos), RandomFloatRange(minObstacleYPos, maxObstacleYPos));
  sf::Vector2f size = sf::Vector2f(RandomFloatRange(minObstacleWidth, maxObstacleWidth), RandomFloatRange(minObstacleHeight, maxObstacleHeight));
  
  SpawnNewObstacle(pos, size);
  
  m_lastObstacleSpawnTimer = RandomFloatRange(minNextSpawnTime, maxNextSpawnTime);
}


void GameBoard::SpawnNewRandomTiledObstacles()
{
  static int minObstacleCount = 2;
  static int maxObstacleCount = 7;
  
  static float minNextSpawnTime = 0.3f;
  static float maxNextSpawnTime = 0.7f;
  
  static float minObstacleXPos = 350.f;
  static float maxObstacleXPos = 450.f;
  static float minObstacleYPos = 20.f;
  static float maxObstacleYPos = 450.f;
  
  sf::Vector2f pos = sf::Vector2f(RandomFloatRange(minObstacleXPos, maxObstacleXPos), RandomFloatRange(minObstacleYPos, maxObstacleYPos));
  sf::Vector2f size = sf::Vector2f(32.f, 32.f);
  
  int obstacleCount = (int)RandomFloatRange((float)minObstacleCount, (float)maxObstacleCount);
  for (int a = 0; a < obstacleCount; ++a)
  {
    SpawnNewObstacle(pos, size);
    pos.y += size.y;
  }
  
  m_lastObstacleSpawnTimer = RandomFloatRange(minNextSpawnTime, maxNextSpawnTime);
}


void GameBoard::SpawnNewObstacle(const sf::Vector2f& pos, const sf::Vector2f& size)
{
  ObstacleEntity* obstacle = new ObstacleEntity();
  GameEngine::GameEngineMain::GetInstance()->AddEntity(obstacle);
  obstacle->SetPos(pos);
  obstacle->SetSize(sf::Vector2f(size.x, size.y));
  
  m_obstacles.push_back(obstacle);
}


void GameBoard::CreateBackGround()
{
  GameEngine::Entity* bgEntity = new GameEngine::Entity();
  GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(bgEntity->AddComponent<GameEngine::SpriteRenderComponent>());
  render->SetTexture(GameEngine::eTexture::BG);
  render->SetZLevel(0);
  bgEntity->SetPos(sf::Vector2f(250.f, 250.f));
  bgEntity->SetSize(sf::Vector2f(500.f, 500.f));
  GameEngine::GameEngineMain::GetInstance()->AddEntity(bgEntity);
}
