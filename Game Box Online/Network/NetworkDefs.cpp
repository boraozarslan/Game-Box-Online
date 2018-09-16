//
//  NetworkDefs.cpp
//  Game Box Online
//
//  Created by Ben Zhang on 2018-09-16.
//  Copyright © 2018 Gamebox. All rights reserved.
//

#include "NetworkDefs.hpp"

sf::Packet& operator <<(sf::Packet& packet, const NetworkMessage& msg)
{
    return packet << msg.messageCode;
}

sf::Packet& operator >>(sf::Packet& packet, NetworkMessage& msg)
{
    return packet >> msg.messageCode;
}

sf::Packet& operator <<(sf::Packet& packet, const EntityMessage& msg)
{
    return packet << msg.id << msg.type << msg.x << msg.y;
}

sf::Packet& operator >>(sf::Packet& packet, EntityMessage& msg)
{
    return packet >> msg.id >> msg.type >> msg.x >> msg.y;
}

sf::Packet& operator <<(sf::Packet& packet, const HeartBeat& msg)
{
    return packet << msg.messageCode << msg.player;
}

sf::Packet& operator >>(sf::Packet& packet, HeartBeat& msg)
{
    return packet >> msg.messageCode >> msg.player;
}

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

sf::Packet& operator <<(sf::Packet& packet, const BulletShot& msg)
{
    return packet << msg.messageCode << msg.whoId << msg.dir;
}

sf::Packet& operator >>(sf::Packet& packet, BulletShot& msg)
{
    return packet >> msg.messageCode >> msg.whoId >> msg.dir;
}

sf::Packet& operator <<(sf::Packet& packet, const IdMsg& msg)
{
    return packet << msg.messageCode << msg.id;
}

sf::Packet& operator >>(sf::Packet& packet, IdMsg& msg)
{
    return packet >> msg.messageCode >> msg.id;
}
