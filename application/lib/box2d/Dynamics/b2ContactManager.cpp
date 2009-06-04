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

#include "b2ContactManager.h"
#include "b2World.h"
#include "b2Body.h"
#include "b2Fixture.h"

// This is a callback from the broad-phase when two AABB proxies begin
// to overlap. We create a b2Contact to manage the narrow phase.
void* b2ContactManager::PairAdded(void* proxyUserDataA, void* proxyUserDataB)
{
	b2Fixture* fixtureA = (b2Fixture*)proxyUserDataA;
	b2Fixture* fixtureB = (b2Fixture*)proxyUserDataB;

	b2Body* bodyA = fixtureA->GetBody();
	b2Body* bodyB = fixtureB->GetBody();

	if (bodyA->IsStatic() && bodyB->IsStatic())
	{
		return &m_nullContact;
	}

	if (fixtureA->GetBody() == fixtureB->GetBody())
	{
		return &m_nullContact;
	}

	if (bodyB->IsConnected(bodyA))
	{
		return &m_nullContact;
	}

	if (m_world->m_contactFilter != NULL && m_world->m_contactFilter->ShouldCollide(fixtureA, fixtureB) == false)
	{
		return &m_nullContact;
	}

	// Call the factory.
	b2Contact* c = b2Contact::Create(fixtureA, fixtureB, &m_world->m_blockAllocator);

	if (c == NULL)
	{
		return &m_nullContact;
	}

	// Contact creation may swap shapes.
	fixtureA = c->GetFixtureA();
	fixtureB = c->GetFixtureB();
	bodyA = fixtureA->GetBody();
	bodyB = fixtureB->GetBody();

	// Insert into the world.
	c->m_prev = NULL;
	c->m_next = m_world->m_contactList;
	if (m_world->m_contactList != NULL)
	{
		m_world->m_contactList->m_prev = c;
	}
	m_world->m_contactList = c;

	// Connect to island graph.

	// Connect to body A
	c->m_nodeA.contact = c;
	c->m_nodeA.other = bodyB;

	c->m_nodeA.prev = NULL;
	c->m_nodeA.next = bodyA->m_contactList;
	if (bodyA->m_contactList != NULL)
	{
		bodyA->m_contactList->prev = &c->m_nodeA;
	}
	bodyA->m_contactList = &c->m_nodeA;

	// Connect to body B
	c->m_nodeB.contact = c;
	c->m_nodeB.other = bodyA;

	c->m_nodeB.prev = NULL;
	c->m_nodeB.next = bodyB->m_contactList;
	if (bodyB->m_contactList != NULL)
	{
		bodyB->m_contactList->prev = &c->m_nodeB;
	}
	bodyB->m_contactList = &c->m_nodeB;

	++m_world->m_contactCount;
	return c;
}

// This is a callback from the broad-phase when two AABB proxies cease
// to overlap. We retire the b2Contact.
void b2ContactManager::PairRemoved(void* proxyUserDataA, void* proxyUserDataB, void* pairUserData)
{
	B2_NOT_USED(proxyUserDataA);
	B2_NOT_USED(proxyUserDataB);

	if (pairUserData == NULL)
	{
		return;
	}

	b2Contact* c = (b2Contact*)pairUserData;
	if (c == &m_nullContact)
	{
		return;
	}

	// An attached body is being destroyed, we must destroy this contact
	// immediately to avoid orphaned shape pointers.
	Destroy(c);
}

void b2ContactManager::Destroy(b2Contact* c)
{
	b2Fixture* fixtureA = c->GetFixtureA();
	b2Fixture* fixtureB = c->GetFixtureB();
	b2Body* bodyA = fixtureA->GetBody();
	b2Body* bodyB = fixtureB->GetBody();

	b2ContactPoint cp;
	cp.fixtureA = fixtureA;
	cp.fixtureB = fixtureB;
	cp.friction = b2MixFriction(fixtureA->GetFriction(), fixtureB->GetFriction());
	cp.restitution = b2MixRestitution(fixtureA->GetRestitution(), fixtureB->GetRestitution());

	// Inform the user that this contact is ending.
	int32 manifoldCount = c->GetManifoldCount();
	if (manifoldCount > 0 && m_world->m_contactListener)
	{
		b2Manifold* manifolds = c->GetManifolds();

		for (int32 i = 0; i < manifoldCount; ++i)
		{
			b2Manifold* manifold = manifolds + i;
			cp.normal = manifold->normal;

			for (int32 j = 0; j < manifold->pointCount; ++j)
			{
				b2ManifoldPoint* mp = manifold->points + j;
				cp.position = bodyA->GetWorldPoint(mp->localPointA);
				b2Vec2 v1 = bodyA->GetLinearVelocityFromLocalPoint(mp->localPointA);
				b2Vec2 v2 = bodyB->GetLinearVelocityFromLocalPoint(mp->localPointB);
				cp.velocity = v2 - v1;
				cp.separation = mp->separation;
				cp.id = mp->id;
				m_world->m_contactListener->Remove(&cp);
			}
		}
	}

	// Remove from the world.
	if (c->m_prev)
	{
		c->m_prev->m_next = c->m_next;
	}

	if (c->m_next)
	{
		c->m_next->m_prev = c->m_prev;
	}

	if (c == m_world->m_contactList)
	{
		m_world->m_contactList = c->m_next;
	}

	// Remove from body 1
	if (c->m_nodeA.prev)
	{
		c->m_nodeA.prev->next = c->m_nodeA.next;
	}

	if (c->m_nodeA.next)
	{
		c->m_nodeA.next->prev = c->m_nodeA.prev;
	}

	if (&c->m_nodeA == bodyA->m_contactList)
	{
		bodyA->m_contactList = c->m_nodeA.next;
	}

	// Remove from body 2
	if (c->m_nodeB.prev)
	{
		c->m_nodeB.prev->next = c->m_nodeB.next;
	}

	if (c->m_nodeB.next)
	{
		c->m_nodeB.next->prev = c->m_nodeB.prev;
	}

	if (&c->m_nodeB == bodyB->m_contactList)
	{
		bodyB->m_contactList = c->m_nodeB.next;
	}

	// Call the factory.
	b2Contact::Destroy(c, &m_world->m_blockAllocator);
	--m_world->m_contactCount;
}

// This is the top level collision call for the time step. Here
// all the narrow phase collision is processed for the world
// contact list.
void b2ContactManager::Collide()
{
	// Update awake contacts.
	for (b2Contact* c = m_world->m_contactList; c; c = c->GetNext())
	{
		b2Body* bodyA = c->GetFixtureA()->GetBody();
		b2Body* bodyB = c->GetFixtureB()->GetBody();
		if (bodyA->IsSleeping() && bodyB->IsSleeping())
		{
			continue;
		}

		c->Update(m_world->m_contactListener);
	}
}
