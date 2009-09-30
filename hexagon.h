/*
 *  hexagon.h
 *  glut_03
 *
 *  Created by dadi on 23/09/2009.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "common.h"
#include "segment.h"

class Hexagon {

public:

	enum Edge
	{
	    EdgeTop=0,
	    EdgeTopRight=1,
	    EdgeBottomRight=2,
	    EdgeBottom=3,
	    EdgeBottomLeft=4,
	    EdgeTopLeft=5
	};

	static const Edge EdgeOpposite[6];
	static const Edge EdgeAjacents[6][2];

	Hexagon* connections[6];
	Segment* segments[6];

	float x,y,z;
	float bounce_offset;

	Hexagon();
	~Hexagon();

    void Hexagon::setBounce( float max );
    void setPosition( float x, float y, float z );

    void process();
};


