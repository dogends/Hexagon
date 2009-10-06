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
	
	bool processed;

    void setBounce( float amount );
	
	void resetProcessed();
	void setProcessed();
};

#endif // SEGMENT_H_INCLUDED
