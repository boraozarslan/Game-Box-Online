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
          packet = packet >> msg;
          if(msg.messageCode == HB)
          {
            // Heartbeat message
            HeartBeat hb;
            
            // Fuck sfml packets... do it by hand
            //packet >> hb;
            auto p1 = (char *) packet.getData();
            auto p2 = p1 + 2;
            auto p3 = p2 + 2;
            auto p4 = p3 + 4;
            hb.messageCode = *reinterpret_cast<const unsigned short*>(p1);
            hb.player.id = *reinterpret_cast<const unsigned short*>(p2);
            hb.player.x = *reinterpret_cast<const float*>(p3);
            hb.player.y = *reinterpret_cast<float*>(p4);
            hb.player.type = Types::Player;
            
            mainEngine->UpdatePlayer(hb);
          }
          else if(msg.messageCode == BS)
          {
            BulletShot bs;
            // Fuck sfml packets... do it by hand
            //packet >> bs;
            auto p = (char *) packet.getData();
            bs.messageCode = *reinterpret_cast<unsigned short*>(p);
            bs.whoId = *reinterpret_cast<unsigned short *>(p + 2);
            bs.dir = *reinterpret_cast<unsigned int *>(p + 4);
            
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
        assert(worldUpdate.messageCode == WU);
        
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
    auto pos =mainEngine->GetGameBoard()->GetPlayer()->GetPos();
      HeartBeat heartBeatMsg(mainEngine->GetPlayerId(), pos.x, pos.y);
      sf::Packet packet;
      packet << heartBeatMsg;
      while (mainEngine->GetSocket().send(packet) == sf::Socket::Partial); // Block until packet is sent
    
    std::cout << "My Id: " << mainEngine->GetPlayerId() << " x: " << pos.x << " y: " << pos.y << '\n';
    for(int i = 0; i < packet.getDataSize(); ++i)
    {
      std::cout << "Step [" << i << "]: " << (int)((char *)packet.getData())[i] <<' ';
    }
    std::cout << '\n';
    unsigned short a, b;
    float x, y;
    packet >> a >> b >> x >> y;
    std::cout << "a: " << a << " b: " << b << " x: " << x << " y: " << y << '\n';
    
  }
}
