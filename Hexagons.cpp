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

	// add this hexagon to the complete list
	retval->push_back( retval->root );

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

    // calulate the maximum number of hexagons based on the radius
    int max_cnt = 1;
    for (int i=0; i<radius; i++) max_cnt+=(i*6);

    float offsets[6][2] = {
        {  0.0f,     -hyp },         /* top */
        {  offset_x, -offset_y },    /* top right */
        {  offset_x,  offset_y },    /* bottom right */
        {  0.0f,      hyp},          /* bottom */
        { -offset_x,  offset_y },    /* bottom left */
        { -offset_x, -offset_y }    /* top left */
    };

	// create the adjacent hexagons
	while ( to_process.size() > 0 && cnt<max_cnt ) {

		// each hexagon has 6 connections (0-5), 0 being the top side, incrementing clockwise
		Hexagon* current = to_process.back();
        to_process.pop_back();

		// loop through each connection and see if it has already been assigned to a neighbour
		for (int edge=Hexagon::EdgeTop;edge<=Hexagon::EdgeTopLeft && cnt<max_cnt;edge++) {

			if (current->connections[edge]==NULL) {

				// attach a new hexagon
				Hexagon* hex = new Hexagon();
				cnt++;

				// work out the position of the hexagon
				float x = current->x + offsets[edge][0];
				float y = current->y + offsets[edge][1];

				hex->setPosition( x, y, 0 );

                // update connections
				hex->connections[ Hexagon::EdgeOpposite[ edge ] ] = current;
				current->connections[ edge ] = hex;

				switch (edge)
				{
				    case Hexagon::EdgeTop:

                        // is there a hexagon at top left position?
                        if (current->connections[ Hexagon::EdgeTopLeft ]) {
                            hex->connections[ Hexagon::EdgeBottomLeft ] = current->connections[ Hexagon::EdgeTopLeft ];
                            current->connections[ Hexagon::EdgeTopLeft ]->connections[ Hexagon::EdgeTopRight ] = hex;
                        }

                        // is there a hexagon at top right position?
                        if (current->connections[ Hexagon::EdgeTopRight ]) {
                            hex->connections[ Hexagon::EdgeBottomRight ] = current->connections[ Hexagon::EdgeTopRight ];
                            current->connections[ Hexagon::EdgeTopRight ]->connections[ Hexagon::EdgeTopLeft ] = hex;
                        }
                        break;

				    case Hexagon::EdgeTopRight:

				        // is there a hexagon at top position?
                        if (current->connections[ Hexagon::EdgeTop ]) {
                            hex->connections[ Hexagon::EdgeTopLeft ] = current->connections[ Hexagon::EdgeTop ];
                            current->connections[ Hexagon::EdgeTop ]->connections[ Hexagon::EdgeBottomRight ] = hex;
                        }

				        // is there a hexagon at bottom right position?
                        if (current->connections[ Hexagon::EdgeBottomRight ]) {
                            hex->connections[ Hexagon::EdgeBottom ] = current->connections[ Hexagon::EdgeBottomRight ];
                            current->connections[ Hexagon::EdgeBottomRight ]->connections[ Hexagon::EdgeTop ] = hex;
                        }
                        break;

				    case Hexagon::EdgeBottomRight:

				        // is there a hexagon at top right position?
                        if (current->connections[ Hexagon::EdgeTopRight ]) {
                            hex->connections[ Hexagon::EdgeTop ] = current->connections[ Hexagon::EdgeTopRight ];
                            current->connections[ Hexagon::EdgeTopRight ]->connections[ Hexagon::EdgeBottom ] = hex;
                        }

				        // is there a hexagon at bottom position?
                        if (current->connections[ Hexagon::EdgeBottom ]) {
                            hex->connections[ Hexagon::EdgeBottomLeft ] = current->connections[ Hexagon::EdgeBottom ];
                            current->connections[ Hexagon::EdgeBottom ]->connections[ Hexagon::EdgeTopRight ] = hex;
                        }

                        break;

				    case Hexagon::EdgeBottom:

				        // is there a hexagon at bottom right position?
                        if (current->connections[ Hexagon::EdgeBottomRight ]) {
                            hex->connections[ Hexagon::EdgeTopRight ] = current->connections[ Hexagon::EdgeBottomRight ];
                            current->connections[ Hexagon::EdgeBottomRight ]->connections[ Hexagon::EdgeBottomLeft ] = hex;
                        }

				        // is there a hexagon at bottom left position?
                        if (current->connections[ Hexagon::EdgeBottomLeft ]) {
                            hex->connections[ Hexagon::EdgeTopLeft ] = current->connections[ Hexagon::EdgeBottomLeft ];
                            current->connections[ Hexagon::EdgeBottomLeft ]->connections[ Hexagon::EdgeBottomRight ] = hex;
                        }

                        break;

				    case Hexagon::EdgeBottomLeft:

                        // is there a hexagon at top left position?
                        if (current->connections[ Hexagon::EdgeTopLeft ]) {
                            hex->connections[ Hexagon::EdgeTop ] = current->connections[ Hexagon::EdgeTopLeft ];
                            current->connections[ Hexagon::EdgeTopLeft ]->connections[ Hexagon::EdgeBottom ] = hex;
                        }

                        // is there a hexagon at bottom position?
                        if (current->connections[ Hexagon::EdgeBottom ]) {
                            hex->connections[ Hexagon::EdgeBottomRight ] = current->connections[ Hexagon::EdgeBottom ];
                            current->connections[ Hexagon::EdgeBottom ]->connections[ Hexagon::EdgeTopLeft ] = hex;
                        }
                        break;

				    case Hexagon::EdgeTopLeft:

                        // is there a hexagon at top?
                        if (current->connections[ Hexagon::EdgeTop ]) {
                            hex->connections[ Hexagon::EdgeTopRight ] = current->connections[ Hexagon::EdgeTop ];
                            current->connections[ Hexagon::EdgeTop ]->connections[ Hexagon::EdgeBottomLeft ] = hex;
                        }

                        // is there a hexagon at bottom left?
                        if (current->connections[ Hexagon::EdgeBottomLeft ]) {
                            hex->connections[ Hexagon::EdgeBottom ] = current->connections[ Hexagon::EdgeBottomLeft ];
                            current->connections[ Hexagon::EdgeBottomLeft ]->connections[ Hexagon::EdgeTop ] = hex;
                        }

                        break;

				}

                // add this hexagon to the complete list
                retval->push_back( hex );

                //  to_process.push_back( hex );
                to_process.insert( to_process.begin(), hex );

			}

		}

	}

	return retval;
}

