/*
 *  Hexagons.cpp
 *  glut_03
 *
 *  Created by dadi on 23/09/2009.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "common.h"
#include "Hexagons.h"

Hexagons::Hexagons()
{
}

Hexagons::~Hexagons()
{
	std::vector<Hexagon*>::iterator current = begin();
	std::vector<Hexagon*>::iterator last = end();

	for(;current!=last;current++) {
		if (*current) delete *current;
	}
}

Hexagons* Hexagons::create( int radius ) {
	Hexagons* retval = new Hexagons();

	// first create the root hexagon, this is positioned centered at 0,0,0
	retval->root = new Hexagon(0,0,0);

	// create a list of hexagons that need to be processed
	std::vector<Hexagon*> to_process;

	// at the root to the current processing list
	to_process.push_back( retval->root );

    // work all the edge offsets
    float angle = deg_to_rad( 30.0f );
    float hyp = 2 * cos( angle );
    float offset_x = cos( angle ) * hyp;
    float offset_y = sin( angle ) * hyp;
    int cnt = 1; // number of hexagons created
    int max_cnt = 37;  // TODO :- need to calculate this

    float offsets[6][2] = {
        {  0.0f,     -hyp },         /* top */
        {  offset_x, -offset_y },    /* top right */
        {  offset_x,  offset_y },    /* bottom right */
        {  0.0f,      hyp},          /* bottom */
        { -offset_x, offset_y },    /* bottom left */
        { -offset_x, -offset_y }    /* top left */
    };

	// create the adjacent hexagons
	while ( to_process.size() > 0 ) {

		// each hexagon has 6 connections (0-5), 0 being the top side, incrementing clockwise
		Hexagon* current = to_process.back();

		// loop through each connection and see if it has already been assigned to a neighbour
		for (int edge=Hexagon::EdgeTop;edge<=Hexagon::EdgeTopLeft;edge++) {

			if (current->connections[edge]==NULL) {

				// attach a new hexagon
				Hexagon* hex = new Hexagon();

				// work out the position of the hexagon
				float x = current->x + offsets[edge][0];
				float y = current->y + offsets[edge][1];

				hex->setPosition( x, y, 0 );

			}

		}

	}

	return retval;
}

