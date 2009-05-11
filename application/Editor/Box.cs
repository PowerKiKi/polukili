using System;
using System.Collections.Generic;
using System.Linq;
using System.Drawing;
using System.Text;

namespace Editor
{
   class Box : Physic
   {
      private Rectangle dimension = new Rectangle(new Point(100, 100), new Size(100, 100));
      public Rectangle Dimension
      {
         get { return this.dimension; }
         set { this.dimension = value; MainWindow.Singleton.UpdateControls(); }
      }

      public Box()
      {
      }

      public Box(Rectangle dimension)
      {
         this.Dimension = dimension;
      }

      public override void Paint(System.Windows.Forms.PaintEventArgs args, State state)
      {
         args.Graphics.FillRectangle(Brushes.Red, this.Dimension);
      }

      public override void ToXML(System.Xml.XmlWriter writer)
      {
         writer.WriteElementString("circle", "value");
      }
   }
}
