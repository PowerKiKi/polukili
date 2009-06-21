/*
* Copyright (c) 2007-2009 Erin Catto http://www.gphysics.com
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

#include "b2Collision.h"

// Collision Detection in Interactive 3D Environments by Gino van den Bergen
// From Section 3.4.1
// x = mu1 * p1 + mu2 * p2
// mu1 + mu2 = 1 && mu1 >= 0 && mu2 >= 0
// mu1 = 1 - mu2;
// x = (1 - mu2) * p1 + mu2 * p2
//   = p1 + mu2 * (p2 - p1)
// x = s + a * r (s := start, r := end - start)
// s + a * r = p1 + mu2 * d (d := p2 - p1)
// -a * r + mu2 * d = b (b := s - p1)
// [-r d] * [a; mu2] = b
// Cramer's rule:
// denom = det[-r d]
// a = det[b d] / denom
// mu2 = det[-r b] / denom
bool b2Segment::TestSegment(float32* lambda, b2Vec2* normal, const b2Segment& segment, float32 maxLambda) const
{
	b2Vec2 s = segment.p1;
	b2Vec2 r = segment.p2 - s;
	b2Vec2 d = p2 - p1;
	b2Vec2 n = b2Cross(d, 1.0f);

	const float32 k_slop = 100.0f * B2_FLT_EPSILON;
	float32 denom = -b2Dot(r, n);

	// Cull back facing collision and ignore parallel segments.
	if (denom > k_slop)
	{
		// Does the segment intersect the infinite line associated with this segment?
		b2Vec2 b = s - p1;
		float32 a = b2Dot(b, n);

		if (0.0f <= a && a <= maxLambda * denom)
		{
			float32 mu2 = -r.x * b.y + r.y * b.x;

			// Does the segment intersect this segment?
			if (-k_slop * denom <= mu2 && mu2 <= denom * (1.0f + k_slop))
			{
				a /= denom;
				n.Normalize();
				*lambda = a;
				*normal = n;
				return true;
			}
		}
	}

	return false;
}

// From Real-time Collision Detection, p179.
void b2AABB::RayCast(b2RayCastOutput* output, const b2RayCastInput& input)
{
	float32 tmin = -B2_FLT_MAX;
	float32 tmax = B2_FLT_MAX;

	output->hit = false;

	b2Vec2 p = input.p1;
	b2Vec2 d = input.p2 - input.p1;
	b2Vec2 absD = b2Abs(d);

	b2Vec2 normal;

	for (int32 i = 0; i < 2; ++i)
	{
		if (absD(i) < B2_FLT_EPSILON)
		{
			// Parallel.
			if (p(i) < lowerBound(i) || upperBound(i) < p(i))
			{
				return;
			}
		}
		else
		{
			float32 inv_d = 1.0f / d(i);
			float32 t1 = (lowerBound(i) - p(i)) * inv_d;
			float32 t2 = (upperBound(i) - p(i)) * inv_d;

			// Sign of the normal vector.
			float32 s = -1.0f;

			if (t1 > t2)
			{
				b2Swap(t1, t2);
				s = 1.0f;
			}

			// Push the min up
			if (t1 > tmin)
			{
				normal.SetZero();
				normal(i) = s;
				tmin = t1;
			}

			// Pull the max down
			tmax = b2Min(tmax, t2);

			if (tmin > tmax)
			{
				return;
			}
		}
	}

	// Does the ray start inside the box?
	// Does the ray intersect beyond the max fraction?
	if (tmin < 0.0f || input.maxFraction < tmin)
	{
		return;
	}

	// Intersection.
	output->fraction = tmin;
	output->normal = normal;
	output->hit = true;
}