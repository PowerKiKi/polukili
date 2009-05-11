using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace Editor
{

   class Polygon : Physic
   {
      private List<Point> points = new List<Point>() {new Point(100, 100), 
            new Point(100, 100),
            new Point(300, 300),
            new Point(100, 400) };
      public List<Point> Points
      {
         get { return this.points; }
         set { this.points = value; MainWindow.Singleton.UpdateControls(); }
      }

      public Polygon()
      {
      }

      public override void Paint(System.Windows.Forms.PaintEventArgs args, State state)
      {
         args.Graphics.FillPolygon(Brushes.Pink, this.Points.ToArray());
      }

      public override void ToXML(System.Xml.XmlWriter writer)
      {
         writer.WriteStartElement("polygon");
         foreach (Point p in this.Points)
            this.ToXML(writer, p);
         writer.WriteEndElement();
         
      }
   }
}
