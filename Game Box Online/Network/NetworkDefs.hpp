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
#include <SFML/Network.hpp>

//const std::string IP("35.186.166.163");
const std::string IP("127.0.0.1");
const unsigned short TCP_PORT = 25930;
const unsigned short UDP_PORT = 25931;

const unsigned short MAX_PLAYERS = 16;

const unsigned short HB = 0; // Heart Beat
const unsigned short WU = 1; // world update
const unsigned short BS = 2; // bullet shot
const unsigned short ID = 3; // ID info that's sent initially

struct NetworkMessage
{
  unsigned short messageCode;
    
    NetworkMessage(unsigned short messageCode) : messageCode(messageCode) {}
    
    NetworkMessage() {}
};

sf::Packet& operator <<(sf::Packet& packet, const NetworkMessage& msg);

sf::Packet& operator >>(sf::Packet& packet, NetworkMessage& msg);

struct EntityMessage
{
  unsigned short id;
  float x, y;
};

sf::Packet& operator <<(sf::Packet& packet, const EntityMessage& msg);

sf::Packet& operator >>(sf::Packet& packet, EntityMessage& msg);

struct HeartBeat : public NetworkMessage
{
  EntityMessage player;
  
  HeartBeat(): NetworkMessage(HB) {}
  
    HeartBeat(unsigned short id, float x, float y) : NetworkMessage(HB) {
        player.id = id;
        player.x = x;
        player.y = y;
    }
    
    HeartBeat(unsigned short id, sf::Vector2f coords) : NetworkMessage(HB) {
        player.id = id;
        player.x = coords.x;
        player.y = coords.y;
    }
};

sf::Packet& operator <<(sf::Packet& packet, const HeartBeat& msg);

sf::Packet& operator >>(sf::Packet& packet, HeartBeat& msg);

struct WorldUpdate : public NetworkMessage
{
  std::vector<EntityMessage> entities;
};

sf::Packet& operator <<(sf::Packet& packet, const WorldUpdate& msg);

sf::Packet& operator >>(sf::Packet& packet, WorldUpdate& msg);

struct BulletShot : public NetworkMessage
{
  unsigned short whoId;
  unsigned int dir;
};

sf::Packet& operator <<(sf::Packet& packet, const BulletShot& msg);

sf::Packet& operator >>(sf::Packet& packet, BulletShot& msg);

struct IdMsg : public NetworkMessage
{
  unsigned short id;
};

sf::Packet& operator <<(sf::Packet& packet, const IdMsg& msg);

sf::Packet& operator >>(sf::Packet& packet, IdMsg& msg);
