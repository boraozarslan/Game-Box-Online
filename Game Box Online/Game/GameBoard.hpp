#pragma once
#include "GameEngine/EntitySystem/Entity.hpp"
#include "GameEngine/Defs.h"

#include <SFML/System/Vector2.hpp>
#include <vector>
#include <math.h>

namespace Game
{
	//Used for storing and controling all game related entities
	class PlayerEntity;	

	class GameBoard
	{
	public:
		GameBoard();
		virtual ~GameBoard();

		//Temp - for nice architecture this should be within some sort of IUpdatable interface that GameEngine handles (so that not only entities can be updated)
		void Update();
		void UpdateObstacles(float dt);
		void UpdatePlayerDying();
		void SpawnNewRandomObstacles();
		void SpawnNewRandomTiledObstacles();
		void SpawnNewObstacle(const sf::Vector2f& pos, const sf::Vector2f& size);

        static constexpr float SCREEN_DIMENSION = UNITS(100);

		bool IsGameOver() const { return m_isGameOver; }
        
        PlayerEntity* GetPlayer() const { return m_player; }
        void DeleteIfEnemy(PlayerEntity* enemy);
        std::vector<PlayerEntity*> GetEnemies() const { return m_enemies; }
    //Placeholder temp - should go to helpers or smth.
    static float RandomFloatRange(float a, float b)
    {
      return ((b - a) * ((float)rand() / RAND_MAX)) + a;
    }

	protected:
		void CreateBackGround();
		void UpdateBackGround();

		PlayerEntity* m_player;
        std::vector<PlayerEntity*> m_enemies;
		GameEngine::Entity* m_backGround;

		std::vector<GameEngine::Entity*> m_obstacles;
		float m_lastObstacleSpawnTimer;
		bool  m_isGameOver;
	};
}

