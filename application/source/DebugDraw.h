#ifndef Polukili_DebugDraw_h
#define Polukili_DebugDraw_h

#include <Box2D/Box2D.h>

namespace Polukili
{
   /**
    * This class implements debug drawing callbacks that are invoked via b2World
    */
   class DebugDraw : public b2DebugDraw
   {
   public:

      DebugDraw();

      /// Draw a closed polygon provided in CCW order.
      virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

      /// Draw a solid closed polygon provided in CCW order.
      virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

      /// Draw a circle.
      virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);

      /// Draw a solid circle.
      virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);

      /// Draw a line segment.
      virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);

      /// Draw a transform. Choose your own length scale.
      /// @param xf a transform.
      virtual void DrawTransform(const b2Transform& xf);
   };
}

#endif
