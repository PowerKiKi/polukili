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

#ifndef B2_FIXTURE_H
#define B2_FIXTURE_H

#include "b2Body.h"
#include "../Collision/b2Collision.h"
#include "../Collision/Shapes/b2Shape.h"

class b2BlockAllocator;
class b2Body;
class b2BroadPhase;

/// This holds contact filtering data.
struct b2FilterData
{
	/// The collision category bits. Normally you would just set one bit.
	uint16 categoryBits;

	/// The collision mask bits. This states the categories that this
	/// shape would accept for collision.
	uint16 maskBits;

	/// Collision groups allow a certain group of objects to never collide (negative)
	/// or always collide (positive). Zero means no collision group. Non-zero group
	/// filtering always wins against the mask bits.
	int16 groupIndex;
};

/// A fixture definition is used to create a fixture. This class defines an
/// abstract fixture definition. You can reuse fixture definitions safely.
struct b2FixtureDef
{
	/// The constructor sets the default fixture definition values.
	b2FixtureDef()
	{
		type = b2_unknownShape;
		userData = NULL;
		friction = 0.2f;
		restitution = 0.0f;
		density = 0.0f;
		filter.categoryBits = 0x0001;
		filter.maskBits = 0xFFFF;
		filter.groupIndex = 0;
		isSensor = false;
	}

	virtual ~b2FixtureDef() {}

	/// Holds the shape type for down-casting.
	b2ShapeType type;

	/// Use this to store application specific fixture data.
	void* userData;

	/// The friction coefficient, usually in the range [0,1].
	float32 friction;

	/// The restitution (elasticity) usually in the range [0,1].
	float32 restitution;

	/// The density, usually in kg/m^2.
	float32 density;

	/// A sensor shape collects contact information but never generates a collision
	/// response.
	bool isSensor;

	/// Contact filtering data.
	b2FilterData filter;
};

/// This structure is used to build a fixture with a circle shape.
struct b2CircleDef : public b2FixtureDef
{
	b2CircleDef()
	{
		type = b2_circleShape;
		localPosition.SetZero();
		radius = 1.0f;
	}

	b2Vec2 localPosition;
	float32 radius;
};

/// Convex polygon. The vertices must be ordered so that the outside of
/// the polygon is on the right side of the edges (looking along the edge
/// from start to end).
struct b2PolygonDef : public b2FixtureDef
{
	b2PolygonDef()
	{
		type = b2_polygonShape;
		vertexCount = 0;
	}

	/// Build vertices to represent an axis-aligned box.
	/// @param hx the half-width.
	/// @param hy the half-height.
	void SetAsBox(float32 hx, float32 hy);

	/// Build vertices to represent an oriented box.
	/// @param hx the half-width.
	/// @param hy the half-height.
	/// @param center the center of the box in local coordinates.
	/// @param angle the rotation of the box in local coordinates.
	void SetAsBox(float32 hx, float32 hy, const b2Vec2& center, float32 angle);

	/// The polygon vertices in local coordinates.
	b2Vec2 vertices[b2_maxPolygonVertices];

	/// The number of polygon vertices.
	int32 vertexCount;
};

/// This structure is used to build a chain of edges.
struct b2EdgeDef : public b2FixtureDef
{
	b2EdgeDef()
	{
		type = b2_edgeShape;
	}

	/// The start vertex.
	b2Vec2 vertex1;

	/// The end vertex.
	b2Vec2 vertex2;
};


/// A fixture is used to attach a shape to a body for collision detection. A fixture
/// inherits its transform from its parent. Fixtures hold additional non-geometric data
/// such as friction, collision filters, etc.
/// Fixtures are created via b2Body::CreateFixture.
/// @warning you cannot reuse fixtures.
class b2Fixture
{
public:
	/// Get the type of the child shape. You can use this to down cast to the concrete shape.
	/// @return the shape type.
	b2ShapeType GetType() const;

	/// Get the child shape. You can modify the child shape, however you should not change the
	/// number of vertices because this will crash some collision caching mechanisms.
	const b2Shape* GetShape() const;
	b2Shape* GetShape();

	/// Is this fixture a sensor (non-solid)?
	/// @return the true if the shape is a sensor.
	bool IsSensor() const;

	/// Set if this fixture is a sensor.
	/// You must call b2World::Refilter to update existing contacts.
	void SetSensor(bool sensor);

	/// Set the contact filtering data. You must call b2World::Refilter to correct
	/// existing contacts/non-contacts.
	void SetFilterData(const b2FilterData& filter);

	/// Get the contact filtering data.
	const b2FilterData& GetFilterData() const;

	/// Get the parent body of this fixture. This is NULL if the fixture is not attached.
	/// @return the parent body.
	b2Body* GetBody();

	/// Get the next fixture in the parent body's fixture list.
	/// @return the next shape.
	b2Fixture* GetNext();

	/// Get the user data that was assigned in the fixture definition. Use this to
	/// store your application specific data.
	void* GetUserData();

	/// Set the user data. Use this to store your application specific data.
	void SetUserData(void* data);

	/// Test a point for containment in this fixture. This only works for convex shapes.
	/// @param xf the shape world transform.
	/// @param p a point in world coordinates.
	bool TestPoint(const b2Vec2& p) const;

	/// Perform a ray cast against this shape.
	/// @param xf the shape world transform.
	/// @param lambda returns the hit fraction. You can use this to compute the contact point
	/// p = (1 - lambda) * segment.p1 + lambda * segment.p2.
	/// @param normal returns the normal at the contact point. If there is no intersection, the normal
	/// is not set.
	/// @param segment defines the begin and end point of the ray cast.
	/// @param maxLambda a number typically in the range [0,1].
	b2SegmentCollide TestSegment(float32* lambda, b2Vec2* normal, const b2Segment& segment, float32 maxLambda) const;

	/// Compute the mass properties of this shape using its dimensions and density.
	/// The inertia tensor is computed about the local origin, not the centroid.
	/// @param massData returns the mass data for this shape.
	void ComputeMass(b2MassData* massData) const;

	/// Compute the volume and centroid of this fixture intersected with a half plane
	/// @param normal the surface normal
	/// @param offset the surface offset along normal
	/// @param c returns the centroid
	/// @return the total volume less than offset along normal
	float32 ComputeSubmergedArea(const b2Vec2& normal, float32 offset, b2Vec2* c) const;

	/// Get the maximum radius about the parent body's center of mass.
	float32 ComputeSweepRadius(const b2Vec2& pivot) const;

	/// Get the coefficient of friction.
	float32 GetFriction() const;

	/// Set the coefficient of friction.
	void SetFriction(float32 friction);

	/// Get the coefficient of restitution.
	float32 GetRestitution() const;

	/// Set the coefficient of restitution.
	void SetRestitution(float32 restitution);

	/// Get the density.
	float32 GetDensity() const;

	/// Set the density.
	/// @warning this does not automatically update the mass of the parent body.
	void SetDensity(float32 density);

protected:

	friend class b2Body;
	friend class b2World;

	b2Fixture();
	~b2Fixture();

	// We need separation create/destroy functions from the constructor/destructor because
	// the destructor cannot access the allocator or broad-phase (no destructor arguments allowed by C++).
	void Create(b2BlockAllocator* allocator, b2BroadPhase* broadPhase, b2Body* body, const b2XForm& xf, const b2FixtureDef* def);
	void Destroy(b2BlockAllocator* allocator, b2BroadPhase* broadPhase);

	bool Synchronize(b2BroadPhase* broadPhase, const b2XForm& xf1, const b2XForm& xf2);
	void RefilterProxy(b2BroadPhase* broadPhase, const b2XForm& xf);

	b2ShapeType m_type;
	b2Fixture* m_next;
	b2Body* m_body;

	b2Shape* m_shape;

	float32 m_density;
	float32 m_friction;
	float32 m_restitution;

	uint16 m_proxyId;
	b2FilterData m_filter;

	bool m_isSensor;

	void* m_userData;
};

inline b2ShapeType b2Fixture::GetType() const
{
	return m_type;
}

inline const b2Shape* b2Fixture::GetShape() const
{
	return m_shape;
}

inline b2Shape* b2Fixture::GetShape()
{
	return m_shape;
}

inline bool b2Fixture::IsSensor() const
{
	return m_isSensor;
}

inline void b2Fixture::SetSensor(bool sensor)
{
	m_isSensor = sensor;
}

inline void b2Fixture::SetFilterData(const b2FilterData& filter)
{
	m_filter = filter;
}

inline const b2FilterData& b2Fixture::GetFilterData() const
{
	return m_filter;
}

inline void* b2Fixture::GetUserData()
{
	return m_userData;
}

inline void b2Fixture::SetUserData(void* data)
{
	m_userData = data;
}

inline b2Body* b2Fixture::GetBody()
{
	return m_body;
}

inline b2Fixture* b2Fixture::GetNext()
{
	return m_next;
}

inline float32 b2Fixture::ComputeSweepRadius(const b2Vec2& pivot) const
{
	return m_shape->ComputeSweepRadius(pivot);
}

inline float32 b2Fixture::GetFriction() const
{
	return m_friction;
}

inline void b2Fixture::SetFriction(float32 friction)
{
	m_friction = friction;
}

inline float32 b2Fixture::GetRestitution() const
{
	return m_restitution;
}

inline void b2Fixture::SetRestitution(float32 restitution)
{
	m_restitution = restitution;
}

inline float32 b2Fixture::GetDensity() const
{
	return m_density;
}

inline void b2Fixture::SetDensity(float32 density)
{
	m_density = density;
}

inline void b2Fixture::ComputeMass(b2MassData* massData) const
{
	m_shape->ComputeMass(massData, m_density);
}

inline float32 b2Fixture::ComputeSubmergedArea(const b2Vec2& normal, float32 offset, b2Vec2* c) const
{
	return m_shape->ComputeSubmergedArea(normal, offset, m_body->GetXForm(), c);
}

inline bool b2Fixture::TestPoint(const b2Vec2& p) const
{
	return m_shape->TestPoint(m_body->GetXForm(), p);
}

inline b2SegmentCollide
b2Fixture::TestSegment(	float32* lambda,
						 b2Vec2* normal,
						 const b2Segment& segment,
						 float32 maxLambda) const
{
	return m_shape->TestSegment(m_body->GetXForm(), lambda, normal, segment, maxLambda);
}

#endif
/*
* Copyright (c) 2006-2007 Erin Catto http://www.gphysics.com
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

#ifndef B2_FIXTURE_H
#define B2_FIXTURE_H

#include "b2Body.h"
#include "../Collision/b2Collision.h"
#include "../Collision/Shapes/b2Shape.h"

class b2BlockAllocator;
class b2Body;
class b2BroadPhase;

/// This holds contact filtering data.
struct b2FilterData
{
	/// The collision category bits. Normally you would just set one bit.
	uint16 categoryBits;

	/// The collision mask bits. This states the categories that this
	/// shape would accept for collision.
	uint16 maskBits;

	/// Collision groups allow a certain group of objects to never collide (negative)
	/// or always collide (positive). Zero means no collision group. Non-zero group
	/// filtering always wins against the mask bits.
	int16 groupIndex;
};

/// A fixture definition is used to create a fixture. This class defines an
/// abstract fixture definition. You can reuse fixture definitions safely.
struct b2FixtureDef
{
	/// The constructor sets the default fixture definition values.
	b2FixtureDef()
	{
		type = b2_unknownShape;
		userData = NULL;
		friction = 0.2f;
		restitution = 0.0f;
		density = 0.0f;
		filter.categoryBits = 0x0001;
		filter.maskBits = 0xFFFF;
		filter.groupIndex = 0;
		isSensor = false;
	}

	virtual ~b2FixtureDef() {}

	/// Holds the shape type for down-casting.
	b2ShapeType type;

	/// Use this to store application specific fixture data.
	void* userData;

	/// The friction coefficient, usually in the range [0,1].
	float32 friction;

	/// The restitution (elasticity) usually in the range [0,1].
	float32 restitution;

	/// The density, usually in kg/m^2.
	float32 density;

	/// A sensor shape collects contact information but never generates a collision
	/// response.
	bool isSensor;

	/// Contact filtering data.
	b2FilterData filter;
};

/// This structure is used to build a fixture with a circle shape.
struct b2CircleDef : public b2FixtureDef
{
	b2CircleDef()
	{
		type = b2_circleShape;
		localPosition.SetZero();
		radius = 1.0f;
	}

	b2Vec2 localPosition;
	float32 radius;
};

/// Convex polygon. The vertices must be ordered so that the outside of
/// the polygon is on the right side of the edges (looking along the edge
/// from start to end).
struct b2PolygonDef : public b2FixtureDef
{
	b2PolygonDef()
	{
		type = b2_polygonShape;
		vertexCount = 0;
	}

	/// Build vertices to represent an axis-aligned box.
	/// @param hx the half-width.
	/// @param hy the half-height.
	void SetAsBox(float32 hx, float32 hy);

	/// Build vertices to represent an oriented box.
	/// @param hx the half-width.
	/// @param hy the half-height.
	/// @param center the center of the box in local coordinates.
	/// @param angle the rotation of the box in local coordinates.
	void SetAsBox(float32 hx, float32 hy, const b2Vec2& center, float32 angle);

	/// The polygon vertices in local coordinates.
	b2Vec2 vertices[b2_maxPolygonVertices];

	/// The number of polygon vertices.
	int32 vertexCount;
};

/// This structure is used to build a chain of edges.
struct b2EdgeDef : public b2FixtureDef
{
	b2EdgeDef()
	{
		type = b2_edgeShape;
	}

	/// The start vertex.
	b2Vec2 vertex1;

	/// The end vertex.
	b2Vec2 vertex2;
};


/// A fixture is used to attach a shape to a body for collision detection. A fixture
/// inherits its transform from its parent. Fixtures hold additional non-geometric data
/// such as friction, collision filters, etc.
/// Fixtures are created via b2Body::CreateFixture.
/// @warning you cannot reuse fixtures.
class b2Fixture
{
public:
	/// Get the type of the child shape. You can use this to down cast to the concrete shape.
	/// @return the shape type.
	b2ShapeType GetType() const;

	/// Get the child shape. You can modify the child shape, however you should not change the
	/// number of vertices because this will crash some collision caching mechanisms.
	const b2Shape* GetShape() const;
	b2Shape* GetShape();

	/// Is this fixture a sensor (non-solid)?
	/// @return the true if the shape is a sensor.
	bool IsSensor() const;

	/// Set if this fixture is a sensor.
	/// You must call b2World::Refilter to update existing contacts.
	void SetSensor(bool sensor);

	/// Set the contact filtering data. You must call b2World::Refilter to correct
	/// existing contacts/non-contacts.
	void SetFilterData(const b2FilterData& filter);

	/// Get the contact filtering data.
	const b2FilterData& GetFilterData() const;

	/// Get the parent body of this fixture. This is NULL if the fixture is not attached.
	/// @return the parent body.
	b2Body* GetBody();

	/// Get the next fixture in the parent body's fixture list.
	/// @return the next shape.
	b2Fixture* GetNext();

	/// Get the user data that was assigned in the fixture definition. Use this to
	/// store your application specific data.
	void* GetUserData();

	/// Set the user data. Use this to store your application specific data.
	void SetUserData(void* data);

	/// Test a point for containment in this fixture. This only works for convex shapes.
	/// @param xf the shape world transform.
	/// @param p a point in world coordinates.
	bool TestPoint(const b2Vec2& p) const;

	/// Perform a ray cast against this shape.
	/// @param xf the shape world transform.
	/// @param lambda returns the hit fraction. You can use this to compute the contact point
	/// p = (1 - lambda) * segment.p1 + lambda * segment.p2.
	/// @param normal returns the normal at the contact point. If there is no intersection, the normal
	/// is not set.
	/// @param segment defines the begin and end point of the ray cast.
	/// @param maxLambda a number typically in the range [0,1].
	b2SegmentCollide TestSegment(float32* lambda, b2Vec2* normal, const b2Segment& segment, float32 maxLambda) const;

	/// Compute the mass properties of this shape using its dimensions and density.
	/// The inertia tensor is computed about the local origin, not the centroid.
	/// @param massData returns the mass data for this shape.
	void ComputeMass(b2MassData* massData) const;

	/// Compute the volume and centroid of this fixture intersected with a half plane
	/// @param normal the surface normal
	/// @param offset the surface offset along normal
	/// @param c returns the centroid
	/// @return the total volume less than offset along normal
	float32 ComputeSubmergedArea(const b2Vec2& normal, float32 offset, b2Vec2* c) const;

	/// Get the maximum radius about the parent body's center of mass.
	float32 GetSweepRadius() const;

	/// Get the coefficient of friction.
	float32 GetFriction() const;

	/// Set the coefficient of friction.
	void SetFriction(float32 friction);

	/// Get the coefficient of restitution.
	float32 GetRestitution() const;

	/// Set the coefficient of restitution.
	void SetRestitution(float32 restitution);

	/// Get the density.
	float32 GetDensity() const;

	/// Set the density.
	/// @warning this does not automatically update the mass of the parent body.
	void SetDensity(float32 density);

protected:

	friend class b2Body;
	friend class b2World;

	b2Fixture();
	~b2Fixture();

	// We need separation create/destroy functions from the constructor/destructor because
	// the destructor cannot access the allocator or broad-phase (no destructor arguments allowed by C++).
	void Create(const b2FixtureDef* def, b2BlockAllocator* allocator, b2BroadPhase* broadPhase, const b2XForm& xf);
	void Destroy(b2BlockAllocator* allocator, b2BroadPhase* broadPhase);

	bool Synchronize(b2BroadPhase* broadPhase, const b2XForm& xf1, const b2XForm& xf2);
	void RefilterProxy(b2BroadPhase* broadPhase, const b2XForm& xf);

	b2ShapeType m_type;
	b2Fixture* m_next;
	b2Body* m_body;

	b2Shape* m_shape;

	// Sweep radius relative to the parent body's center of mass.
	float32 m_sweepRadius;

	float32 m_density;
	float32 m_friction;
	float32 m_restitution;

	uint16 m_proxyId;
	b2FilterData m_filter;

	bool m_isSensor;

	void* m_userData;
};

inline b2ShapeType b2Fixture::GetType() const
{
	return m_type;
}

inline const b2Shape* b2Fixture::GetShape() const
{
	return m_shape;
}

inline b2Shape* b2Fixture::GetShape()
{
	return m_shape;
}

inline bool b2Fixture::IsSensor() const
{
	return m_isSensor;
}

inline void b2Fixture::SetSensor(bool sensor)
{
	m_isSensor = sensor;
}

inline void b2Fixture::SetFilterData(const b2FilterData& filter)
{
	m_filter = filter;
}

inline const b2FilterData& b2Fixture::GetFilterData() const
{
	return m_filter;
}

inline void* b2Fixture::GetUserData()
{
	return m_userData;
}

inline void b2Fixture::SetUserData(void* data)
{
	m_userData = data;
}

inline b2Body* b2Fixture::GetBody()
{
	return m_body;
}

inline b2Fixture* b2Fixture::GetNext()
{
	return m_next;
}

inline float32 b2Fixture::GetSweepRadius() const
{
	return m_sweepRadius;
}

inline float32 b2Fixture::GetFriction() const
{
	return m_friction;
}

inline void b2Fixture::SetFriction(float32 friction)
{
	m_friction = friction;
}

inline float32 b2Fixture::GetRestitution() const
{
	return m_restitution;
}

inline void b2Fixture::SetRestitution(float32 restitution)
{
	m_restitution = restitution;
}

inline float32 b2Fixture::GetDensity() const
{
	return m_density;
}

inline void b2Fixture::SetDensity(float32 density)
{
	m_density = density;
}

inline void b2Fixture::ComputeMass(b2MassData* massData) const
{
	m_shape->ComputeMass(massData, m_density);
}

inline float32 b2Fixture::ComputeSubmergedArea(const b2Vec2& normal, float32 offset, b2Vec2* c) const
{
	return m_shape->ComputeSubmergedArea(normal, offset, m_body->GetXForm(), c);
}

inline bool b2Fixture::TestPoint(const b2Vec2& p) const
{
	return m_shape->TestPoint(m_body->GetXForm(), p);
}

inline b2SegmentCollide
b2Fixture::TestSegment(	float32* lambda,
						 b2Vec2* normal,
						 const b2Segment& segment,
						 float32 maxLambda) const
{
	return m_shape->TestSegment(m_body->GetXForm(), lambda, normal, segment, maxLambda);
}

#endif
