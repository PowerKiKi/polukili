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

#include "b2PolyAndEdgeContact.h"
#include "../b2Body.h"
#include "../b2Fixture.h"
#include "../b2WorldCallbacks.h"
#include "../../Collision/Shapes/b2EdgeShape.h"
#include "../../Collision/Shapes/b2PolygonShape.h"
#include "../../Collision/b2TimeOfImpact.h"
#include "../../Common/b2BlockAllocator.h"

#include <new.h>
#include <string.h>

b2Contact* b2PolyAndEdgeContact::Create(b2Fixture* fixtureA, b2Fixture* fixtureB, b2BlockAllocator* allocator)
{
	void* mem = allocator->Allocate(sizeof(b2PolyAndEdgeContact));
	return new (mem) b2PolyAndEdgeContact(fixtureA, fixtureB);
}

void b2PolyAndEdgeContact::Destroy(b2Contact* contact, b2BlockAllocator* allocator)
{
	((b2PolyAndEdgeContact*)contact)->~b2PolyAndEdgeContact();
	allocator->Free(contact, sizeof(b2PolyAndEdgeContact));
}

b2PolyAndEdgeContact::b2PolyAndEdgeContact(b2Fixture* fixtureA, b2Fixture* fixtureB)
: b2Contact(fixtureA, fixtureB)
{
	b2Assert(m_fixtureA->GetType() == b2_polygonShape);
	b2Assert(m_fixtureB->GetType() == b2_edgeShape);
	m_manifold.pointCount = 0;
}

void b2PolyAndEdgeContact::Evaluate(b2ContactListener* listener)
{
	b2Body* bodyA = m_fixtureA->GetBody();
	b2Body* bodyB = m_fixtureB->GetBody();

	b2Manifold m0;
	memcpy(&m0, &m_manifold, sizeof(b2Manifold));

	b2CollidePolyAndEdge(	&m_manifold,
							(b2PolygonShape*)m_fixtureA->GetShape(), bodyA->GetXForm(),
							(b2EdgeShape*)m_fixtureB->GetShape(), bodyB->GetXForm());

	bool persisted[b2_maxManifoldPoints] = {false, false};

	b2ContactPoint cp;
	cp.fixtureA = m_fixtureA;
	cp.fixtureB = m_fixtureB;
	cp.friction = b2MixFriction(m_fixtureA->GetFriction(), m_fixtureB->GetFriction());
	cp.restitution = b2MixRestitution(m_fixtureA->GetRestitution(), m_fixtureB->GetRestitution());

	// Match contact ids to facilitate warm starting.
	if (m_manifold.pointCount > 0)
	{
		// Match old contact ids to new contact ids and copy the
		// stored impulses to warm start the solver.
		for (int32 i = 0; i < m_manifold.pointCount; ++i)
		{
			b2ManifoldPoint* mp = m_manifold.points + i;
			mp->normalImpulse = 0.0f;
			mp->tangentImpulse = 0.0f;
			bool found = false;
			b2ContactID id = mp->id;

			for (int32 j = 0; j < m0.pointCount; ++j)
			{
				if (persisted[j] == true)
				{
					continue;
				}

				b2ManifoldPoint* mp0 = m0.points + j;

				if (mp0->id.key == id.key)
				{
					persisted[j] = true;
					mp->normalImpulse = mp0->normalImpulse;
					mp->tangentImpulse = mp0->tangentImpulse;

					// A persistent point.
					found = true;

					// Report persistent point.
					if (listener != NULL)
					{
						cp.position = bodyA->GetWorldPoint(mp->localPointA);
						b2Vec2 vA = bodyA->GetLinearVelocityFromLocalPoint(mp->localPointA);
						b2Vec2 vB = bodyB->GetLinearVelocityFromLocalPoint(mp->localPointB);
						cp.velocity = vB - vA;
						cp.normal = m_manifold.normal;
						cp.separation = mp->separation;
						cp.id = id;
						listener->Persist(&cp);
					}
					break;
				}
			}

			// Report added point.
			if (found == false && listener != NULL)
			{
				cp.position = bodyA->GetWorldPoint(mp->localPointA);
				b2Vec2 vA = bodyA->GetLinearVelocityFromLocalPoint(mp->localPointA);
				b2Vec2 vB = bodyB->GetLinearVelocityFromLocalPoint(mp->localPointB);
				cp.velocity = vB - vA;
				cp.normal = m_manifold.normal;
				cp.separation = mp->separation;
				cp.id = id;
				listener->Add(&cp);
			}
		}

		m_manifoldCount = 1;
	}
	else
	{
		m_manifoldCount = 0;
	}

	if (listener == NULL)
	{
		return;
	}

	// Report removed points.
	for (int32 i = 0; i < m0.pointCount; ++i)
	{
		if (persisted[i])
		{
			continue;
		}

		b2ManifoldPoint* mp0 = m0.points + i;
		cp.position = bodyA->GetWorldPoint(mp0->localPointA);
		b2Vec2 vA = bodyA->GetLinearVelocityFromLocalPoint(mp0->localPointA);
		b2Vec2 vB = bodyB->GetLinearVelocityFromLocalPoint(mp0->localPointB);
		cp.velocity = vB - vA;
		cp.normal = m0.normal;
		cp.separation = mp0->separation;
		cp.id = mp0->id;
		listener->Remove(&cp);
	}
}

float32 b2PolyAndEdgeContact::ComputeTOI(const b2Sweep& sweepA, const b2Sweep& sweepB) const
{
	b2TOIInput input;
	input.sweepA = sweepA;
	input.sweepB = sweepB;
	input.sweepRadiusA = m_fixtureA->ComputeSweepRadius(sweepA.localCenter);
	input.sweepRadiusB = m_fixtureB->ComputeSweepRadius(sweepB.localCenter);
	input.tolerance = b2_linearSlop;

	return b2TimeOfImpact(&input, (const b2PolygonShape*)m_fixtureA->GetShape(), (const b2EdgeShape*)m_fixtureB->GetShape());
}
