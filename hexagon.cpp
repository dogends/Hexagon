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

	bounce_offset = 0.0f;
    bounce_angle = 0.0f;
	bounce_max = 0.0f;
	processed = false;
	
	// reset connections
	memset( connections, 0,  sizeof(connections) );

	for( int i=0; i<7; i++) segments[i] = new Segment();
}

Hexagon::~Hexagon()
{
    for( int i=0; i<6; i++) delete segments[i];
}

void Hexagon::setBounce( float max )
{
	bounce_max = max;
	bounce_angle = 0.0f;
	
    for( int i=0; i<6; i++) {
		segments[i]->setBounce( max );
		segments[i]->bounce_angle=0.0f;
	}
}

void Hexagon::setPosition( float x, float y, float z )
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Hexagon::process()
{
	// reset to 0 in case there is nothing to do!
	bounce_offset = 0.0f;
/*	
	if (bounce_max>0.0f) {
		bounce_angle+=2.0f;
		if (bounce_angle>360.0f)bounce_angle-=360.0f;
		bounce_offset = sin( deg_to_rad(bounce_angle) ) * bounce_max;
		bounce_max*=0.995f;
	}
	
	return;
*/
	
    // calc amount of bounce
    float cnt = 0.0f;
    float bounce = 0.0f;
    float angle = 0.0f;
    for (int i=0; i<6; i++) {
        if (segments[i]->bounce_max>0.0f) {
            cnt+=1.0f;
            bounce+=segments[i]->bounce_max;
            angle+=segments[i]->bounce_angle;
			
			segments[i]->bounce_angle+=2.0f;
			if (segments[i]->bounce_angle>360.0f) segments[i]->bounce_angle-=360.0f;
			segments[i]->bounce_max*=0.995f;
			
			if (segments[i]->bounce_max<0.01f) segments[i]->bounce_max=0.0f;
        }

    }

    if (bounce>0.0f) {
		angle/=cnt;
	 	bounce/=cnt;
        bounce_offset = sin( deg_to_rad(angle) ) * bounce;
    }

}
