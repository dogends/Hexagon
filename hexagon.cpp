/*
 *  hexagon.cpp
 *  glut_03
 *
 *  Created by dadi on 23/09/2009.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "hexagon.h"

const Hexagon::Edge Hexagon::EdgeOpposite[6] =
{
    EdgeBottom,
    EdgeBottomLeft,
    EdgeTopLeft,
    EdgeTop,
    EdgeTopRight,
    EdgeBottomRight
};

const Hexagon::Edge Hexagon::EdgeAjacents[6][2] =
{
    { EdgeTopLeft, EdgeTopRight },
    { EdgeTop, EdgeBottomRight },
    { EdgeTopRight, EdgeBottom },
    { EdgeBottomRight, EdgeBottomLeft },
    { EdgeBottom, EdgeTopLeft },
    { EdgeBottomLeft, EdgeTop }
};

Hexagon::Hexagon()
{
    setPosition(0,0,0);

	// reset connections
	memset( connections, 0,  sizeof(connections) );
}


Hexagon::Hexagon( float x, float y, float z )
{
    setPosition( x, y, z );

    // reset connections
	memset( connections, 0,  sizeof(connections) );
}

void Hexagon::setPosition( float x, float y, float z )
{
    this->x = x;
    this->y = y;
    this->z = z;
}
