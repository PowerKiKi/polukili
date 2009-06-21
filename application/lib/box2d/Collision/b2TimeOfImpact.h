/*
* Copyright (c) 2006-2009 Erin Catto http://www.gphysics.com
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef B2_TIME_OF_IMPACT_H
#define B2_TIME_OF_IMPACT_H

#include "../Common/b2Math.h"
#include <limits.h>

struct b2TOIInput
{
	b2Sweep sweepA;
	b2Sweep sweepB;
	float32 sweepRadiusA;
	float32 sweepRadiusB;
	float32 tolerance;
};

/// Compute the time when two shapes begin to touch or touch at a closer distance.
/// @warning the sweeps must have the same time interval.
/// @return the fraction between [0,1] in which the shapes first touch.
/// fraction=0 means the shapes begin touching/overlapped, and fraction=1 means the shapes don't touch.
template <typename TA, typename TB>
float32 b2TimeOfImpact(const b2TOIInput* input, const TA* shapeA, const TB* shapeB);

#endif
