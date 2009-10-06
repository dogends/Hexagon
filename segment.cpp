
#include "segment.h"

Segment::Segment()
{
    bounce_angle = 0.0f;
	bounce_max = 0.0f;
	bounce_offset = 0.0f;
	
	processed = false;
}

void Segment::setBounce( float amount )
{
    bounce_max = amount;
}

void Segment::resetProcessed()
{
	processed = false;
}

void Segment::setProcessed()
{
	processed = true;
}