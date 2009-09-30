#ifndef SEGMENT_H_INCLUDED
#define SEGMENT_H_INCLUDED

#include "common.h"

class Segment
{
public:

    Segment();

    float bounce_angle;
	float bounce_max;
	float bounce_offset;

    void setBounce( float amount );

};

#endif // SEGMENT_H_INCLUDED
