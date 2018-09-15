//
//  NetworkDefs.hpp
//  Game Box Online
//
//  Created by Bora Ozarslan on 2018-09-15.
//  Copyright © 2018 Gamebox. All rights reserved.
//
#pragma once

#include <string>

const std::string IP("35.186.166.163");
const unsigned short TCP_PORT = 25931;
const unsigned short UDP_PORT = 25930;

const unsigned short MAX_PLAYERS = 16;

const unsigned short POS_MSG = 0;
const unsigned short MSG2 = 1;

class NetworkMessage
{
public:
  unsigned short messageCode;
};

sf::Packet& operator <<(sf::Packet& packet, const NetworkMessage& msg)
{
  return packet << msg.messageCode;
}

sf::Packet& operator >>(sf::Packet& packet, NetworkMessage& msg)
{
  return packet >> msg.messageCode;
}

class PositionMessage :public NetworkMessage
{
public:
  unsigned short id;
  int x, y;
  
};

sf::Packet& operator <<(sf::Packet& packet, const PositionMessage& posMsg)
{
  return packet << posMsg.messageCode << posMsg.id << posMsg.x << posMsg.y;
}

sf::Packet& operator >>(sf::Packet& packet, PositionMessage& posMsg)
{
  return packet >> posMsg.messageCode >> posMsg.id >> posMsg.x >> posMsg.y;
}

class HostPositionMessage :public NetworkMessage
{
public:
  unsigned short id[MAX_PLAYERS];
  int x[MAX_PLAYERS];
  int y[MAX_PLAYERS];
  
};

sf::Packet& operator <<(sf::Packet& packet, const HostPositionMessage& posMsg)
{
  return packet << posMsg.messageCode;
  unsigned short i = 0;
  while(packet << posMsg.id[i])
  {
    packet << posMsg.x[i] << posMsg.y[i];
    ++i;
  }
}

sf::Packet& operator >>(sf::Packet& packet, HostPositionMessage& posMsg)
{
  return packet >> posMsg.messageCode >> posMsg.id >> posMsg.x >> posMsg.y;
}
