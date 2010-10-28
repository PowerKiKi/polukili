#include <DebugDraw.h>

#include <grrlib.h>

#include <Constants.h>
#include <Console.h>

namespace Polukili
{
   DebugDraw::DebugDraw()
   {
      // We want to draw everything by default
      this->SetFlags(
         e_shapeBit ///< draw shapes
         | e_jointBit ///< draw joint connections
         | e_aabbBit ///< draw axis aligned bounding boxes
         | e_pairBit ///< draw broad-phase pairs
         | e_centerOfMassBit
      );
   }

   void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
   {
      guVector v[vertexCount];
      u32 colors[vertexCount];
      for (int32 i = 0; i < vertexCount; i++)
      {
         v[i].x = Constants::pixelsPerUnits * vertices[i].x;
         v[i].y = Constants::pixelsPerUnits * vertices[i].y;
         v[i].z = 0;
         colors[i] = RGBA((int)(color.r * 255), (int)(color.g * 255), (int)(color.b * 255), 255);
      }

      GRRLIB_NGone(v, colors, vertexCount);
   }

   void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
   {
      guVector v[vertexCount];
      u32 colors[vertexCount];
      for (int32 i = 0; i < vertexCount; i++)
      {
         v[i].x = Constants::pixelsPerUnits * vertices[i].x;
         v[i].y = Constants::pixelsPerUnits * vertices[i].y;
         v[i].z = 0;
         colors[i] = RGBA((int)(color.r * 255), (int)(color.g * 255), (int)(color.b * 255), 255);
      }

      GRRLIB_NGoneFilled(v, colors, vertexCount);
   }

   void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
   {
      u32 c = RGBA((int)(color.r * 255), (int)(color.g * 255), (int)(color.b * 255), 255);
      GRRLIB_Circle(Constants::pixelsPerUnits * center.x, Constants::pixelsPerUnits * center.y, Constants::pixelsPerUnits * radius, c, 0);
   }

   void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
   {
      u32 c = RGBA((int)(color.r * 255), (int)(color.g * 255), (int)(color.b * 255), 255);
      GRRLIB_Circle(Constants::pixelsPerUnits * center.x, Constants::pixelsPerUnits * center.y, Constants::pixelsPerUnits * radius, c, 1);
   }

   void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
   {
      u32 c = RGBA((int)(color.r * 255), (int)(color.g * 255), (int)(color.b * 255), 255);
      GRRLIB_Line(Constants::pixelsPerUnits * p1.x, Constants::pixelsPerUnits * p1.y, Constants::pixelsPerUnits * p2.x, Constants::pixelsPerUnits * p2.y, c);
   }

   void DebugDraw::DrawTransform(const b2Transform& xf)
   {

   }
}
