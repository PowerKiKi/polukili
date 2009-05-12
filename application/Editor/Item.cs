using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Xml;
using System.Windows.Forms;

namespace Editor
{
   abstract class Item
   {
      private bool isVisible;
      public bool IsVisible
      {
         get { return this.isVisible; }
         set { this.isVisible = value; MainWindow.Singleton.UpdateControls(); }
      }

      public Item()
      {
         this.IsVisible = true;
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
