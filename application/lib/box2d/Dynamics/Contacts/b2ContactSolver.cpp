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

#include "b2ContactSolver.h"
#include "b2Contact.h"
#include "../b2Body.h"
#include "../b2Fixture.h"
#include "../b2World.h"
#include "../../Common/b2StackAllocator.h"

#define B2_DEBUG_SOLVER 0

b2ContactSolver::b2ContactSolver(const b2TimeStep& step, b2Contact** contacts, int32 contactCount, b2StackAllocator* allocator)
{
	m_step = step;
	m_allocator = allocator;

	m_constraintCount = 0;
	for (int32 i = 0; i < contactCount; ++i)
	{
		b2Assert(contacts[i]->IsSolid());
		m_constraintCount += contacts[i]->GetManifoldCount();
	}

	m_constraints = (b2ContactConstraint*)m_allocator->Allocate(m_constraintCount * sizeof(b2ContactConstraint));

	int32 count = 0;
	for (int32 i = 0; i < contactCount; ++i)
	{
		b2Contact* contact = contacts[i];

		b2Fixture* fixtureA = contact->m_fixtureA;
		b2Fixture* fixtureB = contact->m_fixtureB;
		b2Body* bodyA = fixtureA->GetBody();
		b2Body* bodyB = fixtureB->GetBody();
		int32 manifoldCount = contact->GetManifoldCount();
		b2Manifold* manifolds = contact->GetManifolds();

		float32 friction = b2MixFriction(fixtureA->GetFriction(), fixtureB->GetFriction());
		float32 restitution = b2MixRestitution(fixtureA->GetRestitution(), fixtureB->GetRestitution());

		b2Vec2 v1 = bodyA->m_linearVelocity;
		b2Vec2 v2 = bodyB->m_linearVelocity;
		float32 w1 = bodyA->m_angularVelocity;
		float32 w2 = bodyB->m_angularVelocity;

		for (int32 j = 0; j < manifoldCount; ++j)
		{
			b2Manifold* manifold = manifolds + j;

			b2Assert(manifold->pointCount > 0);

			const b2Vec2 normal = manifold->normal;

			b2Assert(count < m_constraintCount);
			b2ContactConstraint* cc = m_constraints + count;
			cc->bodyA = bodyA;
			cc->bodyB = bodyB;
			cc->manifold = manifold;
			cc->normal = normal;
			cc->pointCount = manifold->pointCount;
			cc->friction = friction;
			cc->restitution = restitution;

			for (int32 k = 0; k < cc->pointCount; ++k)
			{
				b2ManifoldPoint* cp = manifold->points + k;
				b2ContactConstraintPoint* ccp = cc->points + k;

				ccp->normalImpulse = cp->normalImpulse;
				ccp->tangentImpulse = cp->tangentImpulse;
				ccp->separation = cp->separation;

				ccp->localAnchorA = cp->localPointA;
				ccp->localAnchorB = cp->localPointB;
				ccp->rA = b2Mul(bodyA->GetXForm().R, cp->localPointA - bodyA->GetLocalCenter());
				ccp->rB = b2Mul(bodyB->GetXForm().R, cp->localPointB - bodyB->GetLocalCenter());

				float32 rn1 = b2Cross(ccp->rA, normal);
				float32 rn2 = b2Cross(ccp->rB, normal);
				rn1 *= rn1;
				rn2 *= rn2;

				float32 kNormal = bodyA->m_invMass + bodyB->m_invMass + bodyA->m_invI * rn1 + bodyB->m_invI * rn2;

				b2Assert(kNormal > B2_FLT_EPSILON);
				ccp->normalMass = 1.0f / kNormal;

				float32 kEqualized = bodyA->m_mass * bodyA->m_invMass + bodyB->m_mass * bodyB->m_invMass;
				kEqualized += bodyA->m_mass * bodyA->m_invI * rn1 + bodyB->m_mass * bodyB->m_invI * rn2;

				b2Assert(kEqualized > B2_FLT_EPSILON);
				ccp->equalizedMass = 1.0f / kEqualized;

				b2Vec2 tangent = b2Cross(normal, 1.0f);

				float32 rt1 = b2Cross(ccp->rA, tangent);
				float32 rt2 = b2Cross(ccp->rB, tangent);
				rt1 *= rt1;
				rt2 *= rt2;

				float32 kTangent = bodyA->m_invMass + bodyB->m_invMass + bodyA->m_invI * rt1 + bodyB->m_invI * rt2;

				b2Assert(kTangent > B2_FLT_EPSILON);
				ccp->tangentMass = 1.0f /  kTangent;

				// Setup a velocity bias for restitution.
				ccp->velocityBias = 0.0f;
				if (ccp->separation > 0.0f)
				{
					ccp->velocityBias = -step.inv_dt * ccp->separation; // TODO_ERIN b2TimeStep
				}
				else
				{
					float32 vRel = b2Dot(cc->normal, v2 + b2Cross(w2, ccp->rB) - v1 - b2Cross(w1, ccp->rA));
					if (vRel < -b2_velocityThreshold)
					{
						ccp->velocityBias = -cc->restitution * vRel;
					}
				}
			}

			// If we have two points, then prepare the block solver.
			if (cc->pointCount == 2)
			{
				b2ContactConstraintPoint* ccp1 = cc->points + 0;
				b2ContactConstraintPoint* ccp2 = cc->points + 1;
				
				float32 invMass1 = bodyA->m_invMass;
				float32 invI1 = bodyA->m_invI;
				float32 invMass2 = bodyB->m_invMass;
				float32 invI2 = bodyB->m_invI;

				float32 rn11 = b2Cross(ccp1->rA, normal);
				float32 rn12 = b2Cross(ccp1->rB, normal);
				float32 rn21 = b2Cross(ccp2->rA, normal);
				float32 rn22 = b2Cross(ccp2->rB, normal);

				float32 k11 = invMass1 + invMass2 + invI1 * rn11 * rn11 + invI2 * rn12 * rn12;
				float32 k22 = invMass1 + invMass2 + invI1 * rn21 * rn21 + invI2 * rn22 * rn22;
				float32 k12 = invMass1 + invMass2 + invI1 * rn11 * rn21 + invI2 * rn12 * rn22;

				// Ensure a reasonable condition number.
				const float32 k_maxConditionNumber = 100.0f;
				if (k11 * k11 < k_maxConditionNumber * (k11 * k22 - k12 * k12))
				{
					// K is safe to invert.
					cc->K.col1.Set(k11, k12);
					cc->K.col2.Set(k12, k22);
					cc->normalMass = cc->K.GetInverse();
				}
				else
				{
					// The constraints are redundant, just use one.
					// TODO_ERIN use deepest?
					cc->pointCount = 1;
				}
			}

			++count;
		}
	}

	b2Assert(count == m_constraintCount);
}

b2ContactSolver::~b2ContactSolver()
{
	m_allocator->Free(m_constraints);
}

void b2ContactSolver::InitVelocityConstraints(const b2TimeStep& step)
{
	// Warm start.
	for (int32 i = 0; i < m_constraintCount; ++i)
	{
		b2ContactConstraint* c = m_constraints + i;

		b2Body* bodyA = c->bodyA;
		b2Body* bodyB = c->bodyB;
		float32 invMass1 = bodyA->m_invMass;
		float32 invI1 = bodyA->m_invI;
		float32 invMass2 = bodyB->m_invMass;
		float32 invI2 = bodyB->m_invI;
		b2Vec2 normal = c->normal;
		b2Vec2 tangent = b2Cross(normal, 1.0f);

		if (step.warmStarting)
		{
			for (int32 j = 0; j < c->pointCount; ++j)
			{
				b2ContactConstraintPoint* ccp = c->points + j;
				ccp->normalImpulse *= step.dtRatio;
				ccp->tangentImpulse *= step.dtRatio;
				b2Vec2 P = ccp->normalImpulse * normal + ccp->tangentImpulse * tangent;
				bodyA->m_angularVelocity -= invI1 * b2Cross(ccp->rA, P);
				bodyA->m_linearVelocity -= invMass1 * P;
				bodyB->m_angularVelocity += invI2 * b2Cross(ccp->rB, P);
				bodyB->m_linearVelocity += invMass2 * P;
			}
		}
		else
		{
			for (int32 j = 0; j < c->pointCount; ++j)
			{
				b2ContactConstraintPoint* ccp = c->points + j;
				ccp->normalImpulse = 0.0f;
				ccp->tangentImpulse = 0.0f;
			}
		}
	}
}

void b2ContactSolver::SolveVelocityConstraints()
{
	for (int32 i = 0; i < m_constraintCount; ++i)
	{
		b2ContactConstraint* c = m_constraints + i;
		b2Body* bodyA = c->bodyA;
		b2Body* bodyB = c->bodyB;
		float32 w1 = bodyA->m_angularVelocity;
		float32 w2 = bodyB->m_angularVelocity;
		b2Vec2 v1 = bodyA->m_linearVelocity;
		b2Vec2 v2 = bodyB->m_linearVelocity;
		float32 invMass1 = bodyA->m_invMass;
		float32 invI1 = bodyA->m_invI;
		float32 invMass2 = bodyB->m_invMass;
		float32 invI2 = bodyB->m_invI;
		b2Vec2 normal = c->normal;
		b2Vec2 tangent = b2Cross(normal, 1.0f);
		float32 friction = c->friction;

		b2Assert(c->pointCount == 1 || c->pointCount == 2);

		// Solve normal constraints
		if (c->pointCount == 1)
		{
			b2ContactConstraintPoint* ccp = c->points + 0;

			// Relative velocity at contact
			b2Vec2 dv = v2 + b2Cross(w2, ccp->rB) - v1 - b2Cross(w1, ccp->rA);

			// Compute normal impulse
			float32 vn = b2Dot(dv, normal);
			float32 lambda = -ccp->normalMass * (vn - ccp->velocityBias);

			// b2Clamp the accumulated impulse
			float32 newImpulse = b2Max(ccp->normalImpulse + lambda, 0.0f);
			lambda = newImpulse - ccp->normalImpulse;

			// Apply contact impulse
			b2Vec2 P = lambda * normal;
			v1 -= invMass1 * P;
			w1 -= invI1 * b2Cross(ccp->rA, P);

			v2 += invMass2 * P;
			w2 += invI2 * b2Cross(ccp->rB, P);
			ccp->normalImpulse = newImpulse;
		}
		else
		{
			// Block solver developed in collaboration with Dirk Gregorius (back in 01/07 on Box2D_Lite).
			// Build the mini LCP for this contact patch
			//
			// vn = A * x + b, vn >= 0, , vn >= 0, x >= 0 and vn_i * x_i = 0 with i = 1..2
			//
			// A = J * W * JT and J = ( -n, -r1 x n, n, r2 x n )
			// b = vn_0 - velocityBias
			//
			// The system is solved using the "Total enumeration method" (s. Murty). The complementary constraint vn_i * x_i
			// implies that we must have in any solution either vn_i = 0 or x_i = 0. So for the 2D contact problem the cases
			// vn1 = 0 and vn2 = 0, x1 = 0 and x2 = 0, x1 = 0 and vn2 = 0, x2 = 0 and vn1 = 0 need to be tested. The first valid
			// solution that satisfies the problem is chosen.
			// 
			// In order to account of the accumulated impulse 'a' (because of the iterative nature of the solver which only requires
			// that the accumulated impulse is clamped and not the incremental impulse) we change the impulse variable (x_i).
			//
			// Substitute:
			// 
			// x = x' - a
			// 
			// Plug into above equation:
			//
			// vn = A * x + b
			//    = A * (x' - a) + b
			//    = A * x' + b - A * a
			//    = A * x' + b'
			// b' = b - A * a;

			b2ContactConstraintPoint* cp1 = c->points + 0;
			b2ContactConstraintPoint* cp2 = c->points + 1;

			b2Vec2 a(cp1->normalImpulse, cp2->normalImpulse);
			b2Assert(a.x >= 0.0f && a.y >= 0.0f);

			// Relative velocity at contact
			b2Vec2 dv1 = v2 + b2Cross(w2, cp1->rB) - v1 - b2Cross(w1, cp1->rA);
			b2Vec2 dv2 = v2 + b2Cross(w2, cp2->rB) - v1 - b2Cross(w1, cp2->rA);

			// Compute normal velocity
			float32 vn1 = b2Dot(dv1, normal);
			float32 vn2 = b2Dot(dv2, normal);

			b2Vec2 b;
			b.x = vn1 - cp1->velocityBias;
			b.y = vn2 - cp2->velocityBias;
			b -= b2Mul(c->K, a);

			const float32 k_errorTol = 1e-3f;
			B2_NOT_USED(k_errorTol);

			for (;;)
			{
				//
				// Case 1: vn = 0
				//
				// 0 = A * x' + b'
				//
				// Solve for x':
				//
				// x' = - inv(A) * b'
				//
				b2Vec2 x = - b2Mul(c->normalMass, b);

				if (x.x >= 0.0f && x.y >= 0.0f)
				{
					// Resubstitute for the incremental impulse
					b2Vec2 d = x - a;

					// Apply incremental impulse
					b2Vec2 P1 = d.x * normal;
					b2Vec2 P2 = d.y * normal;
					v1 -= invMass1 * (P1 + P2);
					w1 -= invI1 * (b2Cross(cp1->rA, P1) + b2Cross(cp2->rA, P2));

					v2 += invMass2 * (P1 + P2);
					w2 += invI2 * (b2Cross(cp1->rB, P1) + b2Cross(cp2->rB, P2));

					// Accumulate
					cp1->normalImpulse = x.x;
					cp2->normalImpulse = x.y;

#if B2_DEBUG_SOLVER == 1
					// Postconditions
					dv1 = v2 + b2Cross(w2, cp1->rB) - v1 - b2Cross(w1, cp1->rA);
					dv2 = v2 + b2Cross(w2, cp2->rB) - v1 - b2Cross(w1, cp2->rA);

					// Compute normal velocity
					vn1 = b2Dot(dv1, normal);
					vn2 = b2Dot(dv2, normal);

					b2Assert(b2Abs(vn1 - cp1->velocityBias) < k_errorTol);
					b2Assert(b2Abs(vn2 - cp2->velocityBias) < k_errorTol);
#endif
					break;
				}

				//
				// Case 2: vn1 = 0 and x2 = 0
				//
				//   0 = a11 * x1' + a12 * 0 + b1' 
				// vn2 = a21 * x1' + a22 * 0 + b2'
				//
				x.x = - cp1->normalMass * b.x;
				x.y = 0.0f;
				vn1 = 0.0f;
				vn2 = c->K.col1.y * x.x + b.y;

				if (x.x >= 0.0f && vn2 >= 0.0f)
				{
					// Resubstitute for the incremental impulse
					b2Vec2 d = x - a;

					// Apply incremental impulse
					b2Vec2 P1 = d.x * normal;
					b2Vec2 P2 = d.y * normal;
					v1 -= invMass1 * (P1 + P2);
					w1 -= invI1 * (b2Cross(cp1->rA, P1) + b2Cross(cp2->rA, P2));

					v2 += invMass2 * (P1 + P2);
					w2 += invI2 * (b2Cross(cp1->rB, P1) + b2Cross(cp2->rB, P2));

					// Accumulate
					cp1->normalImpulse = x.x;
					cp2->normalImpulse = x.y;

#if B2_DEBUG_SOLVER == 1
					// Postconditions
					dv1 = v2 + b2Cross(w2, cp1->rB) - v1 - b2Cross(w1, cp1->rA);

					// Compute normal velocity
					vn1 = b2Dot(dv1, normal);

					b2Assert(b2Abs(vn1 - cp1->velocityBias) < k_errorTol);
#endif
					break;
				}


				//
				// Case 3: w2 = 0 and x1 = 0
				//
				// vn1 = a11 * 0 + a12 * x2' + b1' 
				//   0 = a21 * 0 + a22 * x2' + b2'
				//
				x.x = 0.0f;
				x.y = - cp2->normalMass * b.y;
				vn1 = c->K.col2.x * x.y + b.x;
				vn2 = 0.0f;

				if (x.y >= 0.0f && vn1 >= 0.0f)
				{
					// Resubstitute for the incremental impulse
					b2Vec2 d = x - a;

					// Apply incremental impulse
					b2Vec2 P1 = d.x * normal;
					b2Vec2 P2 = d.y * normal;
					v1 -= invMass1 * (P1 + P2);
					w1 -= invI1 * (b2Cross(cp1->rA, P1) + b2Cross(cp2->rA, P2));

					v2 += invMass2 * (P1 + P2);
					w2 += invI2 * (b2Cross(cp1->rB, P1) + b2Cross(cp2->rB, P2));

					// Accumulate
					cp1->normalImpulse = x.x;
					cp2->normalImpulse = x.y;

#if B2_DEBUG_SOLVER == 1
					// Postconditions
					dv2 = v2 + b2Cross(w2, cp2->rB) - v1 - b2Cross(w1, cp2->rA);

					// Compute normal velocity
					vn2 = b2Dot(dv2, normal);

					b2Assert(b2Abs(vn2 - cp2->velocityBias) < k_errorTol);
#endif
					break;
				}

				//
				// Case 4: x1 = 0 and x2 = 0
				// 
				// vn1 = b1
				// vn2 = b2;
				x.x = 0.0f;
				x.y = 0.0f;
				vn1 = b.x;
				vn2 = b.y;

				if (vn1 >= 0.0f && vn2 >= 0.0f )
				{
					// Resubstitute for the incremental impulse
					b2Vec2 d = x - a;

					// Apply incremental impulse
					b2Vec2 P1 = d.x * normal;
					b2Vec2 P2 = d.y * normal;
					v1 -= invMass1 * (P1 + P2);
					w1 -= invI1 * (b2Cross(cp1->rA, P1) + b2Cross(cp2->rA, P2));

					v2 += invMass2 * (P1 + P2);
					w2 += invI2 * (b2Cross(cp1->rB, P1) + b2Cross(cp2->rB, P2));

					// Accumulate
					cp1->normalImpulse = x.x;
					cp2->normalImpulse = x.y;

					break;
				}

				// No solution, give up. This is hit sometimes, but it doesn't seem to matter.
				break;
			}
		}

		// Solve tangent constraints
		for (int32 j = 0; j < c->pointCount; ++j)
		{
			b2ContactConstraintPoint* ccp = c->points + j;

			// Relative velocity at contact
			b2Vec2 dv = v2 + b2Cross(w2, ccp->rB) - v1 - b2Cross(w1, ccp->rA);

			// Compute tangent force
			float32 vt = b2Dot(dv, tangent);
			float32 lambda = ccp->tangentMass * (-vt);

			// b2Clamp the accumulated force
			float32 maxFriction = friction * ccp->normalImpulse;
			float32 newImpulse = b2Clamp(ccp->tangentImpulse + lambda, -maxFriction, maxFriction);
			lambda = newImpulse - ccp->tangentImpulse;

			// Apply contact impulse
			b2Vec2 P = lambda * tangent;

			v1 -= invMass1 * P;
			w1 -= invI1 * b2Cross(ccp->rA, P);

			v2 += invMass2 * P;
			w2 += invI2 * b2Cross(ccp->rB, P);

			ccp->tangentImpulse = newImpulse;
		}

		bodyA->m_linearVelocity = v1;
		bodyA->m_angularVelocity = w1;
		bodyB->m_linearVelocity = v2;
		bodyB->m_angularVelocity = w2;
	}
}

void b2ContactSolver::FinalizeVelocityConstraints()
{
	for (int32 i = 0; i < m_constraintCount; ++i)
	{
		b2ContactConstraint* c = m_constraints + i;
		b2Manifold* m = c->manifold;

		for (int32 j = 0; j < c->pointCount; ++j)
		{
			m->points[j].normalImpulse = c->points[j].normalImpulse;
			m->points[j].tangentImpulse = c->points[j].tangentImpulse;
		}
	}
}

#if 1
// Sequential solver.
bool b2ContactSolver::SolvePositionConstraints(float32 baumgarte)
{
	float32 minSeparation = 0.0f;

	for (int32 i = 0; i < m_constraintCount; ++i)
	{
		b2ContactConstraint* c = m_constraints + i;
		b2Body* bodyA = c->bodyA;
		b2Body* bodyB = c->bodyB;
		float32 invMass1 = bodyA->m_mass * bodyA->m_invMass;
		float32 invI1 = bodyA->m_mass * bodyA->m_invI;
		float32 invMass2 = bodyB->m_mass * bodyB->m_invMass;
		float32 invI2 = bodyB->m_mass * bodyB->m_invI;

		b2Vec2 normal = c->normal;

		// Solver normal constraints
		for (int32 j = 0; j < c->pointCount; ++j)
		{
			b2ContactConstraintPoint* ccp = c->points + j;

			b2Vec2 r1 = b2Mul(bodyA->GetXForm().R, ccp->localAnchorA - bodyA->GetLocalCenter());
			b2Vec2 r2 = b2Mul(bodyB->GetXForm().R, ccp->localAnchorB - bodyB->GetLocalCenter());

			b2Vec2 p1 = bodyA->m_sweep.c + r1;
			b2Vec2 p2 = bodyB->m_sweep.c + r2;
			b2Vec2 dp = p2 - p1;

			// Approximate the current separation.
			float32 separation = b2Dot(dp, normal) + ccp->separation;

			// Track max constraint error.
			minSeparation = b2Min(minSeparation, separation);

			// Prevent large corrections and allow slop.
			float32 C = baumgarte * b2Clamp(separation + b2_linearSlop, -b2_maxLinearCorrection, 0.0f);

			// Compute normal impulse
			float32 impulse = -ccp->equalizedMass * C;

			b2Vec2 P = impulse * normal;

			bodyA->m_sweep.c -= invMass1 * P;
			bodyA->m_sweep.a -= invI1 * b2Cross(r1, P);
			bodyA->SynchronizeTransform();

			bodyB->m_sweep.c += invMass2 * P;
			bodyB->m_sweep.a += invI2 * b2Cross(r2, P);
			bodyB->SynchronizeTransform();
		}
	}

	// We can't expect minSpeparation >= -b2_linearSlop because we don't
	// push the separation above -b2_linearSlop.
	return minSeparation >= -1.5f * b2_linearSlop;
}

#else

// Block solver. Doesn't seem that great.
void b2ContactSolver::SolvePositionConstraints(float32 baumgarte)
{
	for (int32 i = 0; i < m_constraintCount; ++i)
	{
		b2ContactConstraint* c = m_constraints + i;
		b2Body* bodyA = c->bodyA;
		b2Body* bodyB = c->bodyB;
		float32 invMass1 = bodyA->m_mass * bodyA->m_invMass;
		float32 invI1 = bodyA->m_mass * bodyA->m_invI;
		float32 invMass2 = bodyB->m_mass * bodyB->m_invMass;
		float32 invI2 = bodyB->m_mass * bodyB->m_invI;

		b2Vec2 normal = c->normal;
		bool singlePoint = c->pointCount == 1;

		if (c->pointCount == 2)
		{
			b2ContactConstraintPoint* ccp1 = c->points + 0;
			b2ContactConstraintPoint* ccp2 = c->points + 1;

			b2Vec2 r11 = b2Mul(bodyA->GetXForm().R, ccp1->localAnchorA - bodyA->GetLocalCenter());
			b2Vec2 r12 = b2Mul(bodyB->GetXForm().R, ccp1->localAnchorB - bodyB->GetLocalCenter());

			b2Vec2 r21 = b2Mul(bodyA->GetXForm().R, ccp2->localAnchorA - bodyA->GetLocalCenter());
			b2Vec2 r22 = b2Mul(bodyB->GetXForm().R, ccp2->localAnchorB - bodyB->GetLocalCenter());

			b2Vec2 p11 = bodyA->m_sweep.c + r11;
			b2Vec2 p12 = bodyB->m_sweep.c + r12;
			b2Vec2 dp1 = p12 - p11;

			b2Vec2 p21 = bodyA->m_sweep.c + r21;
			b2Vec2 p22 = bodyB->m_sweep.c + r22;
			b2Vec2 dp2 = p22 - p21;

			float32 rn11 = b2Cross(r11, normal);
			float32 rn12 = b2Cross(r12, normal);
			float32 rn21 = b2Cross(r21, normal);
			float32 rn22 = b2Cross(r22, normal);

			float32 k11 = invMass1 + invMass2 + invI1 * rn11 * rn11 + invI2 * rn12 * rn12;
			float32 k22 = invMass1 + invMass2 + invI1 * rn21 * rn21 + invI2 * rn22 * rn22;
			float32 k12 = invMass1 + invMass2 + invI1 * rn11 * rn21 + invI2 * rn12 * rn22;

			// Ensure a reasonable condition number.
			const float32 k_maxConditionNumber = 100.0f;
			if (k11 * k11 < k_maxConditionNumber * (k11 * k22 - k12 * k12))
			{
				b2Mat22 K;
				K.col1.Set(k11, k12);
				K.col2.Set(k12, k22);

				float32 separation1 = b2Dot(dp1, normal) + ccp1->separation;
				float32 separation2 = b2Dot(dp2, normal) + ccp2->separation;

				b2Vec2 C;
				C.x = baumgarte * (separation1 + b2_linearSlop);
				C.y = baumgarte * (separation2 + b2_linearSlop);

				b2Vec2 f = K.Solve(-C);

				if (f.x < 0.0f && f.y < 0.0f)
				{
					f.SetZero();
				}
				else if (f.x < 0.0f)
				{
					f.x = 0.0f;
					f.y = -C.y / k22;
				}
				else if (f.y < 0.0f)
				{
					f.x = -C.x / k11;
					f.y = 0.0f;
				}

				b2Vec2 P1 = f.x * normal;
				b2Vec2 P2 = f.y * normal;

				bodyA->m_sweep.c -= invMass1 * (P1 + P2);
				bodyA->m_sweep.a -= invI1 * (b2Cross(r11, P1) + b2Cross(r21, P2));
				bodyA->SynchronizeTransform();

				bodyB->m_sweep.c += invMass2 * (P1 + P2);
				bodyB->m_sweep.a += invI2 * (b2Cross(r12, P1) + b2Cross(r22, P2));
				bodyB->SynchronizeTransform();
			}
			else
			{
				// The constraints are linearly dependent, so just use the first one.
				// This my cause a problem if the deepest one is ignored.
				singlePoint = true;
			}
		}

		if (singlePoint)
		{
			b2ContactConstraintPoint* ccp = c->points + 0;

			b2Vec2 r1 = b2Mul(bodyA->GetXForm().R, ccp->localAnchorA - bodyA->GetLocalCenter());
			b2Vec2 r2 = b2Mul(bodyB->GetXForm().R, ccp->localAnchorB - bodyB->GetLocalCenter());

			b2Vec2 p1 = bodyA->m_sweep.c + r1;
			b2Vec2 p2 = bodyB->m_sweep.c + r2;
			b2Vec2 dp = p2 - p1;

			// Approximate the current separation.
			float32 separation = b2Dot(dp, normal) + ccp->separation;

			// Prevent large corrections and allow slop.
			float32 C = baumgarte * b2Clamp(separation + b2_linearSlop, -b2_maxLinearCorrection, 0.0f);

			// Compute normal impulse
			float32 impulse = -ccp->equalizedMass * C;

			b2Vec2 P = impulse * normal;

			bodyA->m_sweep.c -= invMass1 * P;
			bodyA->m_sweep.a -= invI1 * b2Cross(r1, P);
			bodyA->SynchronizeTransform();

			bodyB->m_sweep.c += invMass2 * P;
			bodyB->m_sweep.a += invI2 * b2Cross(r2, P);
			bodyB->SynchronizeTransform();
		}
	}
}

#endif