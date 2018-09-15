//
//  HostMain.cpp
//  Game Box Online
//
//  Created by Bora Ozarslan on 2018-09-15.
//  Copyright © 2018 Gamebox. All rights reserved.
//

#include <iostream>
#include <SFML/Network.hpp>
#include "NetworkDefs.hpp"

sf::Mutex networkLock;

sf::TcpSocket tcpConnections[MAX_PLAYERS];
sf::Vector2i positions[MAX_PLAYERS];
unsigned short connectionLen = 0;

int main(int argc, char** argv)
{
  sf::Thread* thread = nullptr;
  
  // Listen in UDP for unreliable shtuff
  // Events it's listening for:
  //  player movement
  
  sf::UdpSocket socket;
  
  auto status = sf::Socket::NotReady;
  while(status != sf::Socket::Done)
  {
    status = socket.bind(UDP_PORT);
    if(status == sf::Socket::Error)
    {
      std::cout << "UDP Socket binding returned an ERROR code.\n";
    }
  }
  
  socket.setBlocking(false);
  
  // Listen in TCP for reliable shtuff
  // Events it's listening for
  //  player join
  
  sf::TcpListener tcpListener;
  
  status = sf::Socket::NotReady;
  while(status != sf::Socket::Done)
  {
    status = tcpListener.listen(TCP_PORT);
    if(status == sf::Socket::Error)
    {
      std::cout << "TCP Socket listening returned an ERROR code.\n";
    }
  }
  
  tcpListener.setBlocking(false);
  for(unsigned short i = 0; i < MAX_PLAYERS; ++i)
  {
    // Keep the connections non blocking
    tcpConnections[i].setBlocking(false);
    positions[i] = sf::Vector2i(0,0);
  }
  
  // Every update it should send all clients all positions
  // It should update everyone on a shoot
  // It should update everyone on hit
  while(true)
  {
    // Check for new connections
    if(connectionLen != MAX_PLAYERS)
    {
      for(unsigned short i = 0; i < MAX_PLAYERS; ++i)
      {
        if(tcpConnections[i].getRemoteAddress() == sf::IpAddress::None)
        {
          auto status = tcpListener.accept(tcpConnections[i]);
          if(status == sf::Socket::Done)
          {
            // There is a new connection
            connectionLen += 1;
            // Let everyone now
            for (unsigned short j = 0; j < MAX_PLAYERS; ++j) {
              if(i != j && tcpConnections[j].getRemoteAddress() != sf::IpAddress::None)
              {
                // TODO(BORA): This person needs to be let known
              }
            }
          }
          break;
        }
      }
    }
    
    // Check if a socket is disconnected
    for(unsigned short i = 0; i < MAX_PLAYERS; ++i)
    {
      if(tcpConnections[i].getRemoteAddress() != sf::IpAddress::None)
      {
        sf::Packet packet;
        auto status = tcpConnections[i].receive(packet);
        if(status == sf::Socket::Status::Disconnected)
        {
          positions[i] = sf::Vector2i(0,0);
          connectionLen -= 1;
          // TODO(BORA): Let everyone know
        }
      }
    }
    
    // Build positions packet
    for(unsigned short i = 0; i < MAX_PLAYERS; ++i)
    {
      if(tcpConnections[i].getRemoteAddress() != sf::IpAddress::None)
      {
        // Let everyone know of positions this position
        // Perhaps build it into a packet? and then send it afterwards
      }
    }
    // Send positions packet
    for(unsigned short i = 0; i < MAX_PLAYERS; ++i)
    {
      if(tcpConnections[i].getRemoteAddress() != sf::IpAddress::None)
      {
        // Send the packet to this person
      }
    }
  }
}
