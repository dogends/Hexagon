/*
 *  hexagon.h
 *  glut_03
 *
 *  Created by dadi on 23/09/2009.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

class Hexagon {

public:
	
	Hexagon* connections[6];
	
	float x,y,z;
	
	Hexagon();
	Hexagon(float pos_x, float pos_y, float pos_z);
	
};