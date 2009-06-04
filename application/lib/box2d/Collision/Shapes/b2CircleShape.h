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

#ifndef B2_CIRCLE_SHAPE_H
#define B2_CIRCLE_SHAPE_H

#include "b2Shape.h"

/// A circle shape.
class b2CircleShape : public b2Shape
{
public:
	b2CircleShape() { m_type = b2_circleShape; }

	/// @see b2Shape::TestPoint
	bool TestPoint(const b2XForm& transform, const b2Vec2& p) const;

	/// @see b2Shape::TestSegment
	b2SegmentCollide TestSegment(	const b2XForm& transform,
						float32* lambda,
						b2Vec2* normal,
						const b2Segment& segment,
						float32 maxLambda) const;

	/// @see b2Shape::ComputeAABB
	void ComputeAABB(b2AABB* aabb, const b2XForm& transform) const;

	/// @see b2Shape::ComputeMass
	void ComputeMass(b2MassData* massData, float32 density) const;

	/// @see b2Shape::ComputeSubmergedArea
	float32 ComputeSubmergedArea(	const b2Vec2& normal,
									float32 offset,
									const b2XForm& xf, 
									b2Vec2* c) const;

	/// @see b2Shape::ComputeSweepRadius
	float32 ComputeSweepRadius(const b2Vec2& pivot) const;

	/// Get the supporting vertex index in the given direction.
	int32 GetSupport(const b2Vec2& d) const;

	/// Get the supporting vertex in the given direction.
	const b2Vec2& GetSupportVertex(const b2Vec2& d) const;

	/// Get the vertex count.
	int32 GetVertexCount() const { return 1; }

	/// Get a vertex by index. Used by b2Distance.
	const b2Vec2& GetVertex(int32 index) const;

	/// Position
	b2Vec2 m_p;
};

inline int32 b2CircleShape::GetSupport(const b2Vec2 &d) const
{
	B2_NOT_USED(d);
	return 0;
}

inline const b2Vec2& b2CircleShape::GetSupportVertex(const b2Vec2 &d) const
{
	B2_NOT_USED(d);
	return m_p;
}

inline const b2Vec2& b2CircleShape::GetVertex(int32 index) const
{
	B2_NOT_USED(index);
	b2Assert(index == 0);
	return m_p;
}

inline float32 b2CircleShape::ComputeSweepRadius(const b2Vec2& pivot) const
{
	return b2Distance(m_p, pivot);
}

#endif
