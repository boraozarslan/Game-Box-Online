#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "Game/GameBoard.hpp"
#include "EntitySystem/Entity.hpp"
#include "EntitySystem/Components/RenderComponent.hpp"

#include "./EntitySystem/Entity.hpp"
#include "./EntitySystem/Components/RenderComponent.hpp"

namespace GameEngine
{
	class GameEngineMain
	{
	public:		
		~GameEngineMain();
        
		static GameEngineMain* GetInstance(bool host = false) { if (!sm_instance) sm_instance = new GameEngineMain(host); return sm_instance; }
		//Returns time between update frames in seconds
		static float		   GetTimeDelta() { return GetInstance()->m_lastDT; }
		static float		   GetGameTime() { return sm_gameClock.getElapsedTime().asSeconds(); }

		sf::RenderWindow* GetRenderWindow() const { return m_renderWindow; }
		void Update();		
		void SetRenderTarget(sf::RenderTarget* target) { m_renderTarget = target; }

        Game::GameBoard* GetGameBoard() { return m_gameBoard; }
        
		void AddEntity(Entity* entity);
		void RemoveEntity(Entity* entity);

		void OnInitialised();
		bool IsGameOver() const { return m_gameBoard && m_gameBoard->IsGameOver(); }
        
        static float WINDOW_HEIGHT;
        static float WINDOW_WIDTH;
        
	private:
    GameEngineMain(bool host);

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
		static sf::Clock	   sm_deltaTimeClock;
		static sf::Clock	   sm_gameClock;

		std::vector<Entity*> m_entitiesToAdd;
		std::vector<Entity*> m_entities;
		std::vector<Entity*> m_entitiesToRemove;

		sf::RenderTarget*   m_renderTarget;
		sf::RenderWindow*   m_renderWindow; //In future they will be different						

		Game::GameBoard*    m_gameBoard;
		float				m_lastDT;
    
    bool m_host;


		bool m_windowInitialised;
	};
}
