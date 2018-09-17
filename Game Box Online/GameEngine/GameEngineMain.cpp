#include "GameEngineMain.hpp"

#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Util/TextureManager.hpp"
#include "Util/AnimationManager.hpp"
#include "Util/CameraManager.hpp"
#include "SplashScreen.hpp"
#include "GameOverScreen.hpp"
#include "Menu.hpp"
#include "HealthStatusComponent.hpp"
#include "ResourcePath.hpp"
#include "NetworkManager.hpp"
#include "NetworkDefs.hpp"
#include "GameBoard.hpp"


using namespace GameEngine;

float GameEngineMain::WINDOW_HEIGHT = 1020;
float GameEngineMain::WINDOW_WIDTH = 1920;
//Nullptr init for singleton class
GameEngineMain* GameEngineMain::sm_instance = nullptr;
sf::Clock		GameEngineMain::sm_deltaTimeClock;
sf::Clock		GameEngineMain::sm_gameClock;
sf::Clock       GameEngineMain::sm_circleTimer;
const std::string HOST_ADDR = "127.0.0.1";

GameEngineMain::GameEngineMain(bool host)
	: m_renderTarget(nullptr)	
	, m_windowInitialised(false)
	, m_gameBoard(nullptr)
    , m_isInNetworkMode(false)
  , m_host(host)
{
  if(!m_host)
  {
	CreateAndSetUpWindow();
	//Load predefined textures
	TextureManager::GetInstance()->LoadTextures();
	//Create predefined animation definition vector
	AnimationManager::GetInstance()->InitStaticGameAnimations();

	CameraManager::GetInstance()->GetCameraView().setCenter(sf::Vector2f(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f));
	CameraManager::GetInstance()->GetCameraView().setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
  }
}


GameEngineMain::~GameEngineMain()
{
    // Disconnect from the host
    if (m_isInNetworkMode && !m_host) {
        m_socket.disconnect();
    }
    delete m_renderTarget;
}


void GameEngineMain::OnInitialised()
{
  if(m_host)
  {
    StartGame();
    return;
  }
  
  ShowSplashScreen();
}


void GameEngineMain::CreateAndSetUpWindow()
{
    auto fsmodes = sf::VideoMode::getFullscreenModes();
    WINDOW_WIDTH = fsmodes.back().width;
    WINDOW_HEIGHT = fsmodes.back().height;
    //1920 x 1080
    
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
    auto ignore = std::find(m_entitiesToRemove.begin(), m_entitiesToRemove.end(), entity);
    if (ignore != m_entitiesToRemove.end())
        return;

	auto found = std::find(m_entities.begin(), m_entities.end(), entity);
	if (found == m_entities.end())
	{
		auto found2 = std::find(m_entitiesToRemove.begin(), m_entitiesToRemove.end(), entity);
		assert(found2 != m_entitiesToRemove.end()); //Drop an assert if we remove a non existing entity (neither on entity list and on entity to remove list);
	}	

	if (found != m_entities.end())
	{
		m_entitiesToRemove.push_back(entity);
		entity->OnRemoveFromWorld();
	}
}


void GameEngineMain::Update()
{
  std::this_thread::sleep_for(std::chrono::milliseconds(20));
  if (!m_windowInitialised)
  {
    m_windowInitialised = true;
    OnInitialised();
  }
    
    NetworkManager* networkManager = nullptr;
    
    if (m_isInNetworkMode) {
        networkManager = NetworkManager::GetInstance(m_host);
        networkManager->PreUpdate();
    }

    if (m_isInNetworkMode && m_host)
    {
        if (m_gameBoard)
          m_gameBoard->Update();

        UpdateEntities();
    } else {
        RemovePendingEntities();
        
        UpdateWindowEvents();
        if (m_gameBoard)
            m_gameBoard->Update();
        
        UpdateEntities();
        RenderEntities();
        
        AddPendingEntities();
    }
    
    if (m_isInNetworkMode) {
        networkManager->PostUpdate();
    }
  
  m_lastDT = sm_deltaTimeClock.getElapsedTime().asSeconds();

  sm_deltaTimeClock.restart();
  
  // The below code should be networkManager postUpdate
  // Send heartbeat to the server
    if (m_isInNetworkMode && !m_host && m_gameBoard) {
        HeartBeat heartBeatMsg (m_playerId, m_gameBoard->GetPlayer()->GetPos());
        sf::Packet packet;
        packet << heartBeatMsg;
        while (m_socket.send(packet) == sf::Socket::Partial); // Block until packet is sent
    }
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
	for (auto entity : m_entities)
	{
		entity->Update();
	}
}


void GameEngineMain::RenderEntities()
{
	if (!m_renderTarget)
		return;

	//Here we use a windowRender target - it's more than enough for provided example, but in more complex versions this could end up flickering on the screen
	//If that is the case - one could try to implement doubleBuffer functionality, where the render target is a TEXTURE in memory and objects render there
	//And only at the last bit we render the prepared texture on the window.
	m_renderTarget->clear();

	//The VIEW is the way to control what renders in the window in a very convenient way - view does not modify the local coordinates, but rather than that it defines the rectangle that the window
	//Is supposed to render - by default our camera manager is not doing anything, as it was not needed in bird implementation, but it can be set to follow the player (by modifying the IsFollow enabled static return)
	//If that setting is on, PlayerCamera component will update the camera position to player position - making our camera center on player entity
	//With that test setting on, our bird implementation changes a bunch of rules, just so we can test it easilly
	m_renderTarget->setView(CameraManager::GetInstance()->GetCameraView());
    std::cout << "Current location: x[" << CameraManager::GetInstance()->GetCameraView().getCenter().x << "] y[" << CameraManager::GetInstance()->GetCameraView().getCenter().x << "]\n";

	//Render que
	std::vector<RenderComponent*> renderers;
	//Every entity that has RenderComponent, or a component that extends RenderComponent - should end up in a render que
	for (auto&& entity : m_entities)
	{
		if (RenderComponent* render = entity->GetComponent< RenderComponent >())
		{
			renderers.push_back(render);
		}
	}

	// sort using a lambda expression
	// We sort entities according to their Z level, meaning that the ones with that value lower will be draw FIRST (background), and higher LAST (player)
	std::sort(renderers.begin(), renderers.end(), [](RenderComponent* a, RenderComponent* b) 
	{
		return a->GetZLevel() < b->GetZLevel();
	});	

	for (auto&& renderer : renderers)
	{		
		renderer->Render(m_renderTarget);
	}
    
    sf::Font font;
    std::string filePath = resourcePath();
    filePath.append("sansation.ttf");
    if (!font.loadFromFile(filePath))
    {
        std::cout << "Can't find the font file" << std::endl;
    }
    

    sf::Text text;
    text.setFont(font);
    text.setStyle(sf::Text::Bold);
    text.setCharacterSize((GameEngineMain::WINDOW_WIDTH)/42);
    text.setFillColor(sf::Color::Black);
    
    float hpBoxWidth = (GameEngineMain::WINDOW_WIDTH) / 10;
    float hpBoxHeight = (GameEngineMain::WINDOW_HEIGHT) / 22;
    
    
    for(auto healthStatus : Game::HealthStatusComponent::healths)
    {
        if(healthStatus->m_player == nullptr)
            continue;
        
        std::string hp(std::to_string((int)healthStatus->m_player->m_health));
        hpBoxWidth = (GameEngineMain::WINDOW_WIDTH/10)*(healthStatus->m_player->m_health / 100);
        text.setString(hp+"%");
        text.setPosition(healthStatus->HealthPos.x - 130.f,healthStatus->HealthPos.y - 170.f);
        
        sf::RectangleShape hpBox(sf::Vector2f(hpBoxWidth, hpBoxHeight));
        sf::RectangleShape hpMaxBox(sf::Vector2f((GameEngineMain::WINDOW_WIDTH) / 10, hpBoxHeight));
        hpMaxBox.setPosition(healthStatus->HealthPos.x - 170.f,healthStatus->HealthPos.y - 170.f);
        hpMaxBox.setOutlineColor(sf::Color(250,0,0));
        hpMaxBox.setOutlineThickness(1);
        hpBox.setFillColor(sf::Color(250,0,0));
        
        hpBox.setPosition(healthStatus->HealthPos.x - 170.f,healthStatus->HealthPos.y - 170.f);
        hpBox.setFillColor(sf::Color(50, 250, 50));
        
        // Draw Diminishing Circle
        float initialRadius = 500;
        
        sf::CircleShape circle(initialRadius);
        circle.setFillColor(sf::Color::Transparent);
        circle.setOutlineThickness(3);
        circle.setOutlineColor(sf::Color(0, 250, 0));
       // circle.setPosition(sf::Vector2f(m_renderWindow->getView().getCenter().x- (GameEngineMain::WINDOW_WIDTH/2),
                                       // m_renderWindow->getView().getCenter().y- (GameEngineMain::WINDOW_HEIGHT/2))); // always same origin
        
        circle.setPosition(sf::Vector2f((GameEngineMain::WINDOW_WIDTH/2),
                                        (GameEngineMain::WINDOW_HEIGHT/2)));
        
        
      //  m_lastDT = sm_deltaTimeClock.getElapsedTime().asSeconds();
        
        circle.setRadius(fmax(0, circle.getRadius() - sm_circleTimer.getElapsedTime().asSeconds()));
        
        
        m_renderWindow->draw(circle);
        
        m_renderWindow->draw(hpMaxBox);
        m_renderWindow->draw(hpBox);
        m_renderWindow->draw(text);
    }

    sf::Text score;
    Game::PlayerEntity* playerEntity = GetGameBoard()->GetPlayer();
    score.setFont(font);
    score.setStyle(sf::Text::Bold);
    score.setCharacterSize((GameEngineMain::WINDOW_WIDTH)/30);
    score.setFillColor(sf::Color::Black);
    score.setString("Score: " + std::to_string(playerEntity->GetScore()));
    score.setPosition(playerEntity->GetPos().x + 450.f, playerEntity->GetPos().y + 400.f);

    m_renderWindow->draw(score);

	if (m_renderWindow && m_renderWindow->isOpen())
	{
		m_renderWindow->display();
	}	
}

void GameEngineMain::ShowGameOver()
{
    GameOverScreen gameOverScreen(m_renderTarget, m_renderWindow);
    gameOverScreen.WaitForKeystroke();
    exit(0);
}


void GameEngineMain::ShowSplashScreen()
{
    SplashScreen splashScreen{m_renderTarget, m_renderWindow};
    splashScreen.WaitForKeystroke();
    ShowMenu();
}

void GameEngineMain::ShowMenu()
{
    Menu menu{m_renderTarget, m_renderWindow};
    Menu::MenuResult buttonClicked = menu.ShowMenu();
    
    switch (buttonClicked) {
        case Menu::Exit:
            exit(0);
        case Menu::Play:
            StartGame();
            break;
        case Menu::Online:
            if (!m_host) {
                m_isInNetworkMode = true;
                // Open a connection with the host
                sf::Socket::Status connectStatus = m_socket.connect(HOST_ADDR, TCP_PORT);
                if (connectStatus != sf::Socket::Status::Done) {
                    std::cerr << "Error connecting to the server! Status " << connectStatus << std::endl;
                    throw "Connection failed";
                }
                sf::Packet packet;
                m_socket.receive(packet);
                
                assert(packet.getDataSize() == sizeof(IdMsg));
                IdMsg idMsg;
                packet >> idMsg;
                assert(idMsg.messageCode == ID);
                std::cout << "Received ID: " << idMsg.id << std::endl;
                m_playerId = idMsg.id;
                
                // TODO: Receive the initial World update
                m_socket.receive(packet);
                WorldUpdate worldUpdate;
                packet >> worldUpdate;
                assert(worldUpdate.messageCode == WU);
                std::cout << "Received World Update!" << std::endl;
                
                // Set TCP to non-blocking
                m_socket.setBlocking(false);
                StartGame();
            } else {
                std::cerr << "Online mode is not enabled!" << std::endl;
            }
            break;
        case Menu::Nothing:
            std::cerr << "This game mode is not yet implemented!" << std::endl;
            break;
    }
}

void GameEngineMain::StartGame()
{
    m_gameBoard = new Game::GameBoard();
    sm_deltaTimeClock.restart();
    sm_gameClock.restart();
    sm_circleTimer.restart();
}


void GameEngineMain::SpawnPlayer(unsigned short i)
{
  Game::PlayerEntity* player = new Game::PlayerEntity(true);
  
  AddEntity(player);
  player->SetPos(sf::Vector2f(
                              Game::GameBoard::RandomFloatRange(1.f, Game::GameBoard::SCREEN_DIMENSION - 1.f),
                              Game::GameBoard::RandomFloatRange(1.f, Game::GameBoard::SCREEN_DIMENSION - 1.f)
                             ));
  player->SetSize(sf::Vector2f(50.f, 50.f));
  
  player->id = i;
}

void GameEngineMain::RemovePlayer(unsigned short i)
{
  int j;
  for(j = 0; j < m_entities.size(); ++j)
  {
    if(m_entities[j]->id == i)
      break;
  }
  assert(j != m_entities.size());
  RemoveEntity(m_entities[j]);
}

sf::Packet GameEngineMain::GetWorldUpdate()
{
  WorldUpdate wu;
  for(int i = 0; i < m_entities.size(); ++i)
  {
    if(m_entities[i]->id == INVALID_ID)
      continue;
    EntityMessage msg;
    msg.id = m_entities[i]->id;
    auto pos = m_entities[i]->GetPos();
    msg.x = pos.x;
    msg.y = pos.y;
    wu.entities.push_back(msg);
  }
  
  sf::Packet packet;
  packet << wu;
  return packet;
}


void GameEngineMain::ShootBullet(BulletShot bs)
{
  Game::PlayerEntity* player = nullptr;
  for(auto entity : m_entities)
  {
    if(entity->id == bs.whoId)
    {
      player = static_cast<Game::PlayerEntity*>(entity);
    }
  }
  
  assert(player != nullptr);
}


void GameEngineMain::UpdatePlayer(HeartBeat hb)
{
  for(auto entity : m_entities)
  {
    if(entity->id == hb.player.id)
    {
      Game::PlayerEntity* player = static_cast<Game::PlayerEntity*>(entity);
      player->SetPos(sf::Vector2f(hb.player.x, hb.player.y));
      return;
    }
  }
  assert(false);
}

