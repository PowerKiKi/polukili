using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace Editor
{
   class Circle : Physic
   {
      private Point center = new Point(100, 100);
      public Point Center
      {
         get { return this.center; }
         set { this.center = value; MainWindow.Singleton.UpdateControls(); }
      }

      private int radius = 50;
      public int Radius
      {
         get { return this.radius; }
         set { this.radius = value; MainWindow.Singleton.UpdateControls(); }
      }

      public Circle(Point center, int radius)
      {
         this.Center = center;
         this.Radius = radius;
      }

      public override void Paint(System.Windows.Forms.PaintEventArgs args, State state)
      {
         args.Graphics.FillPie(Brushes.Blue, this.Center.X - this.Radius, this.Center.Y - this.Radius, this.Radius, this.Radius, 0, 360);
      }

      public override void ToXML(System.Xml.XmlWriter writer)
      {
         writer.WriteStartElement("circle");
         writer.WriteAttributeString("radius", this.radius.ToString());
         this.ToXML(writer, this.center);
         writer.WriteEndElement();
      }
   }
}
