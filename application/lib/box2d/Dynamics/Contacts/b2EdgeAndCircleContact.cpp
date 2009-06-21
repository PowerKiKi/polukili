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

#include "b2EdgeAndCircleContact.h"
#include "../b2Body.h"
#include "../b2Fixture.h"
#include "../b2WorldCallbacks.h"
#include "../../Collision/b2TimeOfImpact.h"
#include "../../Collision/Shapes/b2EdgeShape.h"
#include "../../Collision/Shapes/b2CircleShape.h"
#include "../../Common/b2BlockAllocator.h"

#include <new>
#include <string.h>

b2Contact* b2EdgeAndCircleContact::Create(b2Fixture* fixtureA, b2Fixture* fixtureB, b2BlockAllocator* allocator)
{
	void* mem = allocator->Allocate(sizeof(b2EdgeAndCircleContact));
	return new (mem) b2EdgeAndCircleContact(fixtureA, fixtureB);
}

void b2EdgeAndCircleContact::Destroy(b2Contact* contact, b2BlockAllocator* allocator)
{
	((b2EdgeAndCircleContact*)contact)->~b2EdgeAndCircleContact();
	allocator->Free(contact, sizeof(b2EdgeAndCircleContact));
}

b2EdgeAndCircleContact::b2EdgeAndCircleContact(b2Fixture* fixtureA, b2Fixture* fixtureB)
: b2Contact(fixtureA, fixtureB)
{
	b2Assert(m_fixtureA->GetType() == b2_edgeShape);
	b2Assert(m_fixtureB->GetType() == b2_circleShape);
	m_manifold.pointCount = 0;
	m_manifold.points[0].normalImpulse = 0.0f;
	m_manifold.points[0].tangentImpulse = 0.0f;
}

void b2EdgeAndCircleContact::Evaluate(b2ContactListener* listener)
{
	b2Body* bodyA = m_fixtureA->GetBody();
	b2Body* bodyB = m_fixtureB->GetBody();

	b2Manifold m0;
	memcpy(&m0, &m_manifold, sizeof(b2Manifold));

	b2CollideEdgeAndCircle(	&m_manifold,
							(b2EdgeShape*)m_fixtureA->GetShape(), bodyA->GetXForm(),
							(b2CircleShape*)m_fixtureB->GetShape(), bodyB->GetXForm());

	b2ContactPoint cp;
	cp.fixtureA = m_fixtureA;
	cp.fixtureB = m_fixtureB;
	cp.friction = b2MixFriction(m_fixtureA->GetFriction(), m_fixtureB->GetFriction());
	cp.restitution = b2MixRestitution(m_fixtureA->GetRestitution(), m_fixtureB->GetRestitution());

	if (m_manifold.pointCount > 0)
	{
		m_manifoldCount = 1;
		b2ManifoldPoint* mp = m_manifold.points + 0;

		if (m0.pointCount == 0)
		{
			mp->normalImpulse = 0.0f;
			mp->tangentImpulse = 0.0f;

			if (listener)
			{
				cp.position = bodyA->GetWorldPoint(mp->localPointA);
				b2Vec2 v1 = bodyA->GetLinearVelocityFromLocalPoint(mp->localPointA);
				b2Vec2 v2 = bodyB->GetLinearVelocityFromLocalPoint(mp->localPointB);
				cp.velocity = v2 - v1;
				cp.normal = m_manifold.normal;
				cp.separation = mp->separation;
				cp.id = mp->id;
				listener->Add(&cp);
			}
		}
		else
		{
			b2ManifoldPoint* mp0 = m0.points + 0;
			mp->normalImpulse = mp0->normalImpulse;
			mp->tangentImpulse = mp0->tangentImpulse;

			if (listener)
			{
				cp.position = bodyA->GetWorldPoint(mp->localPointA);
				b2Vec2 v1 = bodyA->GetLinearVelocityFromLocalPoint(mp->localPointA);
				b2Vec2 v2 = bodyB->GetLinearVelocityFromLocalPoint(mp->localPointB);
				cp.velocity = v2 - v1;
				cp.normal = m_manifold.normal;
				cp.separation = mp->separation;
				cp.id = mp->id;
				listener->Persist(&cp);
			}
		}
	}
	else
	{
		m_manifoldCount = 0;
		if (m0.pointCount > 0 && listener)
		{
			b2ManifoldPoint* mp0 = m0.points + 0;
			cp.position = bodyA->GetWorldPoint(mp0->localPointA);
			b2Vec2 v1 = bodyA->GetLinearVelocityFromLocalPoint(mp0->localPointA);
			b2Vec2 v2 = bodyB->GetLinearVelocityFromLocalPoint(mp0->localPointB);
			cp.velocity = v2 - v1;
			cp.normal = m0.normal;
			cp.separation = mp0->separation;
			cp.id = mp0->id;
			listener->Remove(&cp);
		}
	}
}

float32 b2EdgeAndCircleContact::ComputeTOI(const b2Sweep& sweepA, const b2Sweep& sweepB) const
{
	b2TOIInput input;
	input.sweepA = sweepA;
	input.sweepB = sweepB;
	input.sweepRadiusA = m_fixtureA->ComputeSweepRadius(sweepA.localCenter);
	input.sweepRadiusB = m_fixtureB->ComputeSweepRadius(sweepB.localCenter);
	input.tolerance = b2_linearSlop;

	return b2TimeOfImpact(&input, (const b2EdgeShape*)m_fixtureA->GetShape(), (const b2CircleShape*)m_fixtureB->GetShape());
}
