//
//  NetworkDefs.hpp
//  Game Box Online
//
//  Created by Bora Ozarslan on 2018-09-15.
//  Copyright © 2018 Gamebox. All rights reserved.
//
#pragma once

#include <string>
#include <vector>

const std::string IP("35.186.166.163");
const unsigned short TCP_PORT = 25931;
const unsigned short UDP_PORT = 25930;

const unsigned short MAX_PLAYERS = 16;

const unsigned short HB = 0; // Heart Beat
const unsigned short WU = 1; // world update
const unsigned short BS = 2; // bullet shot

struct NetworkMessage
{
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

struct EntityMessage
{
  unsigned short id;
  float x, y;
};

sf::Packet& operator <<(sf::Packet& packet, const EntityMessage& msg)
{
  return packet << msg.id << msg.x << msg.y;
}

sf::Packet& operator >>(sf::Packet& packet, EntityMessage& msg)
{
  return packet >> msg.id >> msg.x >> msg.y;
}

struct HeartBeat : public NetworkMessage
{
  EntityMessage player;
};

sf::Packet& operator <<(sf::Packet& packet, const HeartBeat& msg)
{
  return packet << msg.messageCode << msg.player;
}

sf::Packet& operator >>(sf::Packet& packet, HeartBeat& msg)
{
  return packet >> msg.messageCode >> msg.player;
}

struct WorldUpdate : public NetworkMessage
{
  std::vector<EntityMessage> entities;
};

sf::Packet& operator <<(sf::Packet& packet, const WorldUpdate& msg)
{
  packet = packet << msg.messageCode;
  
  for(int i = 0; i < msg.entities.size(); ++i)
  {
    packet = packet << msg.entities[i];
  }
  
  return packet;
}

sf::Packet& operator >>(sf::Packet& packet, WorldUpdate& msg)
{
  return packet >> msg.messageCode;
  
  EntityMessage ent;
  while((packet = (packet >> ent)))
  {
    msg.entities.push_back(ent);
  }
  return packet;
}

struct BulletShot : public NetworkMessage
{
  unsigned short whoId;
  unsigned int dir;
};

sf::Packet& operator <<(sf::Packet& packet, const BulletShot& msg)
{
  return packet << msg.messageCode << msg.whoId << msg.dir;
}

sf::Packet& operator >>(sf::Packet& packet, BulletShot& msg)
{
  return packet >> msg.messageCode >> msg.whoId >> msg.dir;
}
