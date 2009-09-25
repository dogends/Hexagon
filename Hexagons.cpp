/*
 *  Hexagons.cpp
 *  glut_03
 *
 *  Created by dadi on 23/09/2009.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

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
	
	// create the adjacent hexagons
	while ( to_process.size() > 0 ) {
	
		// each hexagon has 6 connections (0-5), 0 being the top side, incrementing clockwise
		Hexagon* current = to_process.back();
		// loop through each connection and see if it has already been assigned to a neighbour
		for (int i=0;i<6;i++) {
			
			if (current->connections[i]==NULL) {
				
				// attach a new hexagon
				Hexagon* hex = new Hexagon();
		
				// work out the position of the hexagon
				
				
			}
		
		}
		
	}
	
	return retval;
}