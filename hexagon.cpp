/*
 *  hexagon.cpp
 *  glut_03
 *
 *  Created by dadi on 23/09/2009.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "hexagon.h"
#include <memory.h>

Hexagon::Hexagon() : x(0), y(0), z(0)
{
	// reset connections
	memset( connections, 0,  sizeof(connections) );
}


Hexagon::Hexagon( float x, float y, float z )
{
    setPosition( x, y, z );
}

void Hexagon::setPosition( float x, float y, float z )
{
    this->x = x;
    this->y = y;
    this->z = z;
}
