/*
 *  Hexagons.h
 *  glut_03
 *
 *  Created by dadi on 23/09/2009.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "common.h"
#include "hexagon.h"

class Hexagons : public std::vector<Hexagon*>
{
public:

    Hexagon* root;

	Hexagons();
	~Hexagons();

	static Hexagons* create( int radius );

};
