#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#ifdef __APPLE__
#include <glut/glut.h>
#else
#include <GL/glut.h>
#endif
#include <memory>
#include <math.h>
#include <vector>
#include <SOIL.h>


#ifndef PI
	#define PI       3.14159265358979323846
#endif

#define deg_to_rad(d) d*(PI/180.0f)



#endif // COMMON_H_INCLUDED
