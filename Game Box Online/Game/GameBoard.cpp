#include "GameBoard.hpp"

#include "GameEngine/GameEngineMain.hpp"
#include "GameEngine/EntitySystem/Components/CollidableComponent.hpp"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.hpp"
#include "GameEngine/Util/CameraManager.hpp"
#include "Game/GameEntities/PlayerEntity.hpp"
#include "Game/GameEntities/ObstacleEntity.hpp"

using namespace Game;

GameBoard::GameBoard()
	: m_lastObstacleSpawnTimer(0.f)
	, m_isGameOver(false)
	, m_backGround(nullptr)
{
  if(!GameEngine::GameEngineMain::GetInstance()->IsHost())
  {
	m_player = new PlayerEntity(false);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);
	m_player->SetPos(sf::Vector2f(SCREEN_DIMENSION / 2, SCREEN_DIMENSION / 2));
	m_player->SetSize(sf::Vector2f(40.f, 40.f));
	
    // Initialize enemies (TODO: replace this with networks code)
    int numEnemies = GameEngine::GameEngineMain::GetInstance()->IsInNetworkMode() ? 0 : RandomFloatRange(4, 7);

    for (int i = 0; i < numEnemies; ++i) {
        PlayerEntity* enemy = new PlayerEntity(true);
        m_enemies.push_back(enemy);

        GameEngine::GameEngineMain::GetInstance()->AddEntity(enemy);
        enemy->SetPos(sf::Vector2f(
            RandomFloatRange(1.f, SCREEN_DIMENSION - 1.f),
            RandomFloatRange(1.f, SCREEN_DIMENSION - 1.f)
        ));
        enemy->SetSize(sf::Vector2f(50.f, 50.f));
    }
  }

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
	//float dt = GameEngine::GameEngineMain::GetInstance()->GetTimeDelta();
    if (!m_isGameOver)
	{
        /*
		m_lastObstacleSpawnTimer -= dt;
		if (m_lastObstacleSpawnTimer <= 0.f)
		{
			//SpawnNewRandomObstacles();
			SpawnNewRandomTiledObstacles();
		}
        */

		//UpdateObstacles(dt);
		//UpdateBackGround();
		UpdatePlayerDying();
	}
    else {
        GameEngine::GameEngineMain::GetInstance()->ShowGameOver();
    }
}


void GameBoard::UpdateObstacles(float dt)
{
	static float obstacleSpeed = 0.f;
	
	for (std::vector<GameEngine::Entity*>::iterator it = m_obstacles.begin(); it != m_obstacles.end();)
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
		else
		{
			it++;
		}
	}
}


void GameBoard::UpdatePlayerDying()
{	
	bool noGameOver = GameEngine::CameraManager::IsFollowCameraEnabled();

	if (noGameOver && false)
		return;

    if (!m_player->IsAlive())
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
  if(GameEngine::GameEngineMain::GetInstance()->IsHost())
  {
    m_backGround = nullptr;
  }
  else
  {
	GameEngine::Entity* bgEntity = new GameEngine::Entity();
	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(bgEntity->AddComponent<GameEngine::SpriteRenderComponent>());
	render->SetTexture(GameEngine::eTexture::BG);
	render->SetZLevel(0);
	bgEntity->SetPos(sf::Vector2f(SCREEN_DIMENSION / 2, SCREEN_DIMENSION / 2));
	bgEntity->SetSize(sf::Vector2f(SCREEN_DIMENSION, SCREEN_DIMENSION));
	GameEngine::GameEngineMain::GetInstance()->AddEntity(bgEntity);

	m_backGround = bgEntity;
  }
    // Adding walls
    GameEngine::Entity* topWall = new GameEngine::Entity();
    GameEngine::Entity* bottomWall = new GameEngine::Entity();
    GameEngine::Entity* leftWall = new GameEngine::Entity();
    GameEngine::Entity* rightWall = new GameEngine::Entity();

    topWall->SetPos(sf::Vector2f(SCREEN_DIMENSION / 2, 0.f));
    bottomWall->SetPos(sf::Vector2f(SCREEN_DIMENSION / 2, SCREEN_DIMENSION));
    leftWall->SetPos(sf::Vector2f(0.f, SCREEN_DIMENSION / 2));
    rightWall->SetPos(sf::Vector2f(SCREEN_DIMENSION, SCREEN_DIMENSION / 2));

    topWall->SetSize(sf::Vector2f(SCREEN_DIMENSION, 10.f));
    bottomWall->SetSize(sf::Vector2f(SCREEN_DIMENSION, 10.f));
    leftWall->SetSize(sf::Vector2f(10.f, SCREEN_DIMENSION));
    rightWall->SetSize(sf::Vector2f(10.f, SCREEN_DIMENSION));

    topWall->AddComponent<GameEngine::CollidableComponent>();
    bottomWall->AddComponent<GameEngine::CollidableComponent>();
    leftWall->AddComponent<GameEngine::CollidableComponent>();
    rightWall->AddComponent<GameEngine::CollidableComponent>();

    GameEngine::GameEngineMain::GetInstance()->AddEntity(topWall);
    GameEngine::GameEngineMain::GetInstance()->AddEntity(bottomWall);
    GameEngine::GameEngineMain::GetInstance()->AddEntity(leftWall);
    GameEngine::GameEngineMain::GetInstance()->AddEntity(rightWall);
}


void GameBoard::UpdateBackGround()
{
	if (!m_backGround || !m_player)
		return;

	if (!GameEngine::CameraManager::IsFollowCameraEnabled())
		return;

	m_backGround->SetPos(m_player->GetPos());
}


void GameBoard::DeleteIfEnemy(Game::PlayerEntity* enemy) {
    auto found = std::find(m_enemies.begin(), m_enemies.end(), enemy);

    if (found != m_enemies.end())
    {
        m_enemies.erase(found);
    }

}
