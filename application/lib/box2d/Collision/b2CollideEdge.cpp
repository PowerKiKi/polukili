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
#include "Shapes/b2CircleShape.h"
#include "Shapes/b2EdgeShape.h"
#include "Shapes/b2PolygonShape.h"

void b2CollideEdgeAndCircle(b2Manifold* manifold,
							const b2EdgeShape* edge, 
							const b2XForm& transformA,
							const b2CircleShape* circle, 
							const b2XForm& transformB)
{
	manifold->pointCount = 0;
	b2Vec2 d;
	b2Vec2 c = b2Mul(transformB, circle->m_p);
	b2Vec2 cLocal = b2MulT(transformA, c);
	b2Vec2 n = edge->GetNormalVector();
	b2Vec2 v1 = edge->GetVertex1();
	b2Vec2 v2 = edge->GetVertex2();
	float32 radius = edge->m_radius + circle->m_radius;
	float32 separation;

	float32 dirDist = b2Dot((cLocal - v1), edge->GetDirectionVector());

	if (dirDist <= 0.0f)
	{
		// Behind v1
		d = cLocal - v1;
		if (b2Dot(d, edge->GetCorner1Vector()) < 0.0f)
		{
			// Contact handled by previous edge
			return;
		}
		d = c - b2Mul(transformA, v1);
	}
	else if (dirDist >= edge->GetLength())
	{
		// Ahead of v2
		d = cLocal - v2;
		if (b2Dot(d, edge->GetCorner2Vector()) > 0.0f)
		{
			// Contact handled by next edge
			return;
		}
		d = c - b2Mul(transformA, v2);
	}
	else
	{
		separation = b2Dot(cLocal - v1, n);
		if (separation > radius || separation < -radius)
		{
			return;
		}
		separation -= radius;
		manifold->normal = b2Mul(transformA.R, n);
		manifold->pointCount = 1;
		manifold->points[0].id.key = 0;
		manifold->points[0].separation = separation;
		c = c - radius * manifold->normal;
		manifold->points[0].localPointA = b2MulT(transformA, c);
		manifold->points[0].localPointB = b2MulT(transformB, c);
		return;
	}

	float32 distSqr = d.LengthSquared();
	if (distSqr > radius * radius)
	{
		return;
	}

	if (distSqr < B2_FLT_EPSILON)
	{
		separation = -radius;
		manifold->normal = b2Mul(transformA.R, n);
	}
	else
	{
		separation = d.Normalize() - radius;
		manifold->normal = d;
	}

	manifold->pointCount = 1;
	manifold->points[0].id.key = 0;
	manifold->points[0].separation = separation;
	c = c - radius * manifold->normal;
	manifold->points[0].localPointA = b2MulT(transformA, c);
	manifold->points[0].localPointB = b2MulT(transformB, c);
}

void b2CollidePolyAndEdge(b2Manifold* manifold,
							const b2PolygonShape* polygon, 
							const b2XForm& transformA,
							const b2EdgeShape* edge, 
							const b2XForm& transformB)
{
	manifold->pointCount = 0;
	b2Vec2 v1 = b2Mul(transformB, edge->GetVertex1());
	b2Vec2 v2 = b2Mul(transformB, edge->GetVertex2());
	b2Vec2 n = b2Mul(transformB.R, edge->GetNormalVector());
	b2Vec2 v1Local = b2MulT(transformA, v1);
	b2Vec2 v2Local = b2MulT(transformA, v2);
	b2Vec2 nLocal = b2MulT(transformA.R, n);

	float32 totalRadius = polygon->m_radius + edge->m_radius;

	float32 separation1;
	int32 separationIndex1 = -1;			// which normal on the polygon found the shallowest depth?
	float32 separationMax1 = -B2_FLT_MAX;	// the shallowest depth of edge in polygon
	float32 separation2;
	int32 separationIndex2 = -1;			// which normal on the polygon found the shallowest depth?
	float32 separationMax2 = -B2_FLT_MAX;	// the shallowest depth of edge in polygon
	float32 separationMax = -B2_FLT_MAX;	// the shallowest depth of edge in polygon
	bool separationV1 = false;				// is the shallowest depth from edge's v1 or v2 vertex?
	int32 separationIndex = -1;				 // which normal on the polygon found the shallowest depth?

	int32 vertexCount = polygon->m_vertexCount;
	const b2Vec2* vertices = polygon->m_vertices;
	const b2Vec2* normals = polygon->m_normals;

	int32 enterStartIndex = -1; // the last polygon vertex above the edge
	int32 enterEndIndex = -1;	// the first polygon vertex below the edge
	int32 exitStartIndex = -1;	// the last polygon vertex below the edge
	int32 exitEndIndex = -1;	// the first polygon vertex above the edge
	//int32 deepestIndex;

	// the "N" in the following variables refers to the edge's normal. 
	// these are projections of polygon vertices along the edge's normal, 
	// a.k.a. they are the separation of the polygon from the edge. 
	float32 prevSepN = totalRadius;
	float32 nextSepN = totalRadius;
	float32 enterSepN = totalRadius;	// the depth of enterEndIndex under the edge (stored as a separation, so it's negative)
	float32 exitSepN = totalRadius;	// the depth of exitStartIndex under the edge (stored as a separation, so it's negative)
	float32 deepestSepN = B2_FLT_MAX; // the depth of the deepest polygon vertex under the end (stored as a separation, so it's negative)

	// for each polygon normal, get the edge's depth into the polygon. 
	// for each polygon vertex, get the vertex's depth into the edge. 
	// use these calculations to define the remaining variables declared above.
	prevSepN = b2Dot(vertices[vertexCount-1] - v1Local, nLocal);
	for (int32 i = 0; i < vertexCount; i++)
	{
		// Polygon normal separation.
		separation1 = b2Dot(v1Local - vertices[i], normals[i]);
		separation2 = b2Dot(v2Local - vertices[i], normals[i]);

		if (separation2 < separation1)
		{
			if (separation2 > separationMax)
			{
				separationMax = separation2;
				separationV1 = false;
				separationIndex = i;
			}
		}
		else
		{
			if (separation1 > separationMax)
			{
				separationMax = separation1;
				separationV1 = true;
				separationIndex = i;
			}
		}

		if (separation1 > separationMax1)
		{
			separationMax1 = separation1;
			separationIndex1 = i;
		}

		if (separation2 > separationMax2)
		{
			separationMax2 = separation2;
			separationIndex2 = i;
		}

		// Edge normal separation
		nextSepN = b2Dot(vertices[i] - v1Local, nLocal);
		if (nextSepN >= totalRadius && prevSepN < totalRadius)
		{
			exitStartIndex = (i == 0) ? vertexCount-1 : i-1;
			exitEndIndex = i;
			exitSepN = prevSepN;
		}
		else if (nextSepN < totalRadius && prevSepN >= totalRadius)
		{
			enterStartIndex = (i == 0) ? vertexCount-1 : i-1;
			enterEndIndex = i;
			enterSepN = nextSepN;
		}

		if (nextSepN < deepestSepN)
		{
			deepestSepN = nextSepN;
			//deepestIndex = i;
		}
		prevSepN = nextSepN;
	}

	if (enterStartIndex == -1)
	{
		// Edge normal separation
		// polygon is entirely below or entirely above edge, return with no contact:
		return;
	}

	if (separationMax > totalRadius)
	{
		// Face normal separation
		// polygon is laterally disjoint with edge, return with no contact:
		return;
	}

	// if the polygon is near a convex corner on the edge
	if ((separationV1 && edge->Corner1IsConvex()) || (!separationV1 && edge->Corner2IsConvex()))
	{
		// if shallowest depth was from a polygon normal (meaning the polygon face is longer than the edge shape),
		// use the edge's vertex as the contact point:
		if (separationMax > deepestSepN + b2_linearSlop)
		{
			// if -normal angle is closer to adjacent edge than this edge, 
			// let the adjacent edge handle it and return with no contact:
			if (separationV1)
			{
				if (b2Dot(normals[separationIndex1], b2MulT(transformA.R, b2Mul(transformB.R, edge->GetCorner1Vector()))) >= 0.0f)
				{
					return;
				}
			}
			else
			{
				if (b2Dot(normals[separationIndex2], b2MulT(transformA.R, b2Mul(transformB.R, edge->GetCorner2Vector()))) <= 0.0f)
				{
					return;
				}
			}

			manifold->pointCount = 1;
			manifold->normal = b2Mul(transformA.R, normals[separationIndex]);
			manifold->points[0].separation = separationMax - totalRadius;
			manifold->points[0].id.features.incidentEdge = (uint8)separationIndex;
			manifold->points[0].id.features.incidentVertex = b2_nullFeature;
			manifold->points[0].id.features.referenceEdge = 0;
			manifold->points[0].id.features.flip = 0;
			if (separationV1)
			{
				manifold->points[0].localPointA = v1Local;
				manifold->points[0].localPointB = edge->GetVertex1();
			}
			else
			{
				manifold->points[0].localPointA = v2Local;
				manifold->points[0].localPointB = edge->GetVertex2();
			}
			return;
		}
	}

	// We're going to use the edge's normal now.
	manifold->normal = -n;

	// Check whether we only need one contact point.
	if (enterEndIndex == exitStartIndex)
	{
		manifold->pointCount = 1;
		manifold->points[0].id.features.incidentEdge = (uint8)enterEndIndex;
		manifold->points[0].id.features.incidentVertex = b2_nullFeature;
		manifold->points[0].id.features.referenceEdge = 0;
		manifold->points[0].id.features.flip = 0;
		manifold->points[0].localPointA = vertices[enterEndIndex];
		manifold->points[0].localPointB = b2MulT(transformB, b2Mul(transformA, vertices[enterEndIndex]));
		manifold->points[0].separation = enterSepN - totalRadius;
		return;
	}

	manifold->pointCount = 2;

	// dirLocal should be the edge's direction vector, but in the frame of the polygon.
	b2Vec2 dirLocal = b2Cross(nLocal, -1.0f); // TODO: figure out why this optimization didn't work
	//b2Vec2 dirLocal = b2MulT(transformA.R, b2Mul(transformB.R, edge->GetDirectionVector()));

	float32 dirProj1 = b2Dot(dirLocal, vertices[enterEndIndex] - v1Local);
	float32 dirProj2;

	// The contact resolution is more robust if the two manifold points are 
	// adjacent to each other on the polygon. So pick the first two polygon
	// vertices that are under the edge:
	exitEndIndex = (enterEndIndex == vertexCount - 1) ? 0 : enterEndIndex + 1;
	if (exitEndIndex != exitStartIndex)
	{
		exitStartIndex = exitEndIndex;
		exitSepN = b2Dot(nLocal, vertices[exitStartIndex] - v1Local);
	}
	dirProj2 = b2Dot(dirLocal, vertices[exitStartIndex] - v1Local);

	manifold->points[0].id.features.incidentEdge = (uint8)enterEndIndex;
	manifold->points[0].id.features.incidentVertex = b2_nullFeature;
	manifold->points[0].id.features.referenceEdge = 0;
	manifold->points[0].id.features.flip = 0;

	if (dirProj1 > edge->GetLength())
	{
		manifold->points[0].localPointA = v2Local;
		manifold->points[0].localPointB = edge->GetVertex2();
		float32 ratio = (edge->GetLength() - dirProj2) / (dirProj1 - dirProj2);
		if (ratio > 100.0f * B2_FLT_EPSILON && ratio < 1.0f)
		{
			manifold->points[0].separation = exitSepN * (1.0f - ratio) + enterSepN * ratio - totalRadius;
		}
		else
		{
			manifold->points[0].separation = enterSepN - totalRadius;
		}
	}
	else
	{
		manifold->points[0].localPointA = vertices[enterEndIndex];
		manifold->points[0].localPointB = b2MulT(transformB, b2Mul(transformA, vertices[enterEndIndex]));
		manifold->points[0].separation = enterSepN - totalRadius;
	}

	manifold->points[1].id.features.incidentEdge = (uint8)exitStartIndex;
	manifold->points[1].id.features.incidentVertex = b2_nullFeature;
	manifold->points[1].id.features.referenceEdge = 0;
	manifold->points[1].id.features.flip = 0;

	if (dirProj2 < 0.0f)
	{
		manifold->points[1].localPointA = v1Local;
		manifold->points[1].localPointB = edge->GetVertex1();
		float32 ratio = (-dirProj1) / (dirProj2 - dirProj1);
		if (ratio > 100.0f * B2_FLT_EPSILON && ratio < 1.0f)
		{
			manifold->points[1].separation = enterSepN * (1.0f - ratio) + exitSepN * ratio - totalRadius;
		}
		else
		{
			manifold->points[1].separation = exitSepN - totalRadius;
		}
	}
	else
	{
		manifold->points[1].localPointA = vertices[exitStartIndex];
		manifold->points[1].localPointB = b2MulT(transformB, b2Mul(transformA, vertices[exitStartIndex]));
		manifold->points[1].separation = exitSepN - totalRadius;
	}
}
