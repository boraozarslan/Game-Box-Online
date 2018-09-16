//
//  NetworkManager.cpp
//  Game Box Online
//
//  Created by Bora Ozarslan on 2018-09-15.
//  Copyright © 2018 Gamebox. All rights reserved.
//

#include "NetworkManager.hpp"
#include "GameEngineMain.hpp"
#include "NetworkDefs.hpp"
#include "PlayerEntity.hpp"

#include <assert.h>
#include <iostream>

using namespace GameEngine;

NetworkManager* NetworkManager::sm_instance = nullptr;

NetworkManager::NetworkManager(bool host)
: m_host(host), m_listener(new sf::TcpListener())
{
  if(host)
  {
    auto status = sf::Socket::NotReady;
    while(status != sf::Socket::Done)
    {
      status = m_listener->listen(TCP_PORT);
      if(status == sf::Socket::Error)
      {
        std::cout << "TCP Socket listening returned an ERROR code.\n";
      }
    }
    m_listener->setBlocking(false);
    for(unsigned short i = 0; i < MAX_PLAYERS; ++i)
    {
      // Keep the connections non blocking
      tcpConnections[i].setBlocking(false);
    }
      
    std::cout << "Server is running!" << std::endl;
  }
  else
  {
      std::cerr << "host is false. This is the client" << std::endl;
  }
}


NetworkManager::~NetworkManager()
{
  delete m_listener;
}


void NetworkManager::PreUpdate()
{
  auto mainEngine = GameEngine::GameEngineMain::GetInstance();
  sf::Socket::Status status;
  if(m_host)
  {
    for(unsigned short i = 0; i < MAX_PLAYERS; ++i)
    {
      // If there is already an established connection
      if(tcpConnections[i].getRemoteAddress() != sf::IpAddress::None)
      {
        sf::Packet packet;
        status = tcpConnections[i].receive(packet);
        
        if(status == sf::Socket::Status::Done)
        {
          // Received a packet
          NetworkMessage msg;
          packet >> msg;
          if(msg.messageCode == HB)
          {
            // Heartbeat message
            HeartBeat hb;
            packet >> hb;
            
            mainEngine->UpdatePlayer(hb);
          }
          else if(msg.messageCode == BS)
          {
            BulletShot bs;
            packet >> bs;
            // TODO: Use the bulletshot message
            mainEngine->ShootBullet(bs);
            std::cout << "Somebody shot a bullet\n";
          }
          continue;
        }
        if(status == sf::Socket::Status::Disconnected)
        {
          // A player has disconnected
          mainEngine->RemovePlayer(i);
          std::cout << "A player has disconnected!\n";
        }
        continue;
      }
      // If the socket isn't open
      status = m_listener->accept(tcpConnections[i]);
      if(status == sf::Socket::Done)
      {
        // There is a new connection
        std::cout << "New guy\n";
        // First let the connection know what it's id is
        IdMsg msg;
        msg.id = i;
        sf::Packet packet;
        packet << msg;
        status = tcpConnections[i].send(packet);
        while(status == sf::Socket::Status::Partial)
          status = tcpConnections[i].send(packet);
        std::cout << "Id msg sent to new guy\n";
        // Add player
        mainEngine->SpawnPlayer(i);
      }
    }
  }
  else
  {
      // The below code should be in preupdate if it's not host
      sf::Packet packet;
      if (mainEngine->GetSocket().receive(packet) == sf::Socket::Status::Done) {
          //assert(packet.getDataSize() == sizeof(WorldUpdate));
          WorldUpdate worldUpdate;
          packet >> worldUpdate;
        
        mainEngine->UpdateWorld(worldUpdate);
//          std::cout << "Received world update packet!" << std::endl;
          // TODO diff the received packet
      }
  }
}

void NetworkManager::PostUpdate()
{
  auto mainEngine = GameEngine::GameEngineMain::GetInstance();
  sf::Socket::Status status;
  if(m_host)
  {
    sf::Packet packet = mainEngine->GetWorldUpdate();
    for(unsigned short i = 0; i < MAX_PLAYERS; ++i)
    {
      // If there is already an established connection
      if(tcpConnections[i].getRemoteAddress() != sf::IpAddress::None)
      {
        status = tcpConnections[i].send(packet);
        while(status == sf::Socket::Status::Partial)
          status = tcpConnections[i].send(packet);
      }
    }
  }
  else
  {
      HeartBeat heartBeatMsg (mainEngine->GetPlayerId(), mainEngine->GetGameBoard()->GetPlayer()->GetPos());
      sf::Packet packet;
      packet << heartBeatMsg;
      while (mainEngine->GetSocket().send(packet) == sf::Socket::Partial); // Block until packet is sent
  }
}
