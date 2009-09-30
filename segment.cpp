
#include "segment.h"

Segment::Segment()
{
    bounce_angle = 0.0f;
	bounce_max = 0.0f;
	bounce_offset = 0.0f;
}

void Segment::setBounce( float amount )
{
    bounce_max = amount;
}
