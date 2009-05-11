using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml;
using System.Drawing;

namespace Editor
{
   abstract class Physic
   {
      private bool isVisible;
      public bool IsVisible
      {
         get { return this.isVisible; }
         set { this.isVisible = value; MainWindow.Singleton.UpdateControls(); }
      }

      public Physic()
      {
         this.IsVisible = true;
         MainWindow.Singleton.physics.Add(this);
         MainWindow.Singleton.UpdateControls();
      }

      public abstract void Paint(PaintEventArgs args, State state);
      public abstract void ToXML(XmlWriter writer);

      public void ToXML(XmlWriter writer, Point point)
      {
         writer.WriteStartElement("point");
         writer.WriteAttributeString("x", point.X.ToString());
         writer.WriteAttributeString("y", point.Y.ToString());
         writer.WriteEndElement();
      }

      public override string ToString()
      {
         return base.ToString(); //+ " " + this.GetHashCode();
      }
   }
}
