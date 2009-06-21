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

#ifndef B2_SHAPE_H
#define B2_SHAPE_H

#include "../../Common/b2Math.h"
#include "../b2Collision.h"

/// This holds the mass data computed for a shape.
struct b2MassData
{
	/// The mass of the shape, usually in kilograms.
	float32 mass;

	/// The position of the shape's centroid relative to the shape's origin.
	b2Vec2 center;

	/// The rotational inertia of the shape.
	float32 I;
};

/// The various collision shape types supported by Box2D.
enum b2ShapeType
{
	b2_unknownShape = -1,
	b2_circleShape,
	b2_polygonShape,
	b2_edgeShape,
	b2_shapeTypeCount,
};

/// Return codes from TestSegment
enum b2SegmentCollide
{
	b2_startsInsideCollide = -1,
	b2_missCollide = 0,
	b2_hitCollide = 1
};

/// A shape is used for collision detection. You can create a shape however you like.
/// Shapes used for simulation in b2World are created automatically when a b2Fixture
/// is created.
class b2Shape
{
public:
	
	b2Shape() { m_type = b2_unknownShape; }
	virtual ~b2Shape() {}

	/// Get the type of this shape. You can use this to down cast to the concrete shape.
	/// @return the shape type.
	b2ShapeType GetType() const;

	/// Test a point for containment in this shape. This only works for convex shapes.
	/// @param xf the shape world transform.
	/// @param p a point in world coordinates.
	virtual bool TestPoint(const b2XForm& xf, const b2Vec2& p) const = 0;

	/// Perform a ray cast against this shape.
	/// @param xf the shape world transform.
	/// @param lambda returns the hit fraction. You can use this to compute the contact point
	/// p = (1 - lambda) * segment.p1 + lambda * segment.p2.
	/// @param normal returns the normal at the contact point. If there is no intersection, the normal
	/// is not set.
	/// @param segment defines the begin and end point of the ray cast.
	/// @param maxLambda a number typically in the range [0,1].
	virtual b2SegmentCollide TestSegment(	const b2XForm& xf,
											float32* lambda,
											b2Vec2* normal,
											const b2Segment& segment,
											float32 maxLambda) const = 0;

	/// Given a transform, compute the associated axis aligned bounding box for this shape.
	/// @param aabb returns the axis aligned box.
	/// @param xf the world transform of the shape.
	virtual void ComputeAABB(b2AABB* aabb, const b2XForm& xf) const = 0;

	/// Compute the mass properties of this shape using its dimensions and density.
	/// The inertia tensor is computed about the local origin, not the centroid.
	/// @param massData returns the mass data for this shape.
	/// @param density the density in kilograms per meter squared.
	virtual void ComputeMass(b2MassData* massData, float32 density) const = 0;

	/// Compute the volume and centroid of this shape intersected with a half plane
	/// @param normal the surface normal
	/// @param offset the surface offset along normal
	/// @param xf the shape transform
	/// @param c returns the centroid
	/// @return the total volume less than offset along normal
	virtual float32 ComputeSubmergedArea(	const b2Vec2& normal,
											float32 offset,
											const b2XForm& xf, 
											b2Vec2* c) const = 0;

	/// Compute the sweep radius. This is used for conservative advancement (continuous
	/// collision detection).
	/// @param pivot is the pivot point for rotation.
	/// @return the distance of the furthest point from the pivot.
	virtual float32 ComputeSweepRadius(const b2Vec2& pivot) const = 0;

	b2ShapeType m_type;
	float32 m_radius;
};

inline b2ShapeType b2Shape::GetType() const
{
	return m_type;
}

#endif
