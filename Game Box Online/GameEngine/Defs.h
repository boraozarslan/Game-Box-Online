//
//  Defs.h
//  Game Box Online
//
//  Created by Bora Ozarslan on 2018-09-15.
//  Copyright © 2018 Gamebox. All rights reserved.
//

#pragma once

#include <climits>

#define UNITS(x) (x * 32.0f)

#define INVALID_ID USHRT_MAX

typedef unsigned short Type;

enum Types
{
  Default = 0,
  Player  = 1,
  Projectile  = 2,
};
