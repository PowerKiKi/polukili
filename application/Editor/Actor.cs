using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace Editor
{
   class Actor : Item
   {
      static ActorType lastType = Actor.ActorType.kiki;
      public enum ActorType
      {
         poupa,
         luna,
         kiki,
         lila,

         bee,
         spider,
         worm,
      }

      private ActorType type = Actor.lastType;
      public ActorType Type
      {
         get { return this.type; }
         set { this.type = value; Actor.lastType = this.type; MainWindow.Singleton.UpdateControls(); }
      }

      private Point position = new Point(50, 50);
      public Point Position
      {
         get { return this.position; }
         set { this.position = value; MainWindow.Singleton.UpdateControls(); }
      }
      private int powerFactor = 1;
      public int PowerFactor
      {
         get { return this.powerFactor; }
         set { this.powerFactor = value; MainWindow.Singleton.UpdateControls(); }
      }

      public Actor()
      {
         MainWindow.Singleton.lstActors.Items.Add(this);
         MainWindow.Singleton.UpdateControls();
      }

      public Actor(ActorType type)
         : this()
      {
         this.Type = type;
      }

      public override void Paint(System.Windows.Forms.PaintEventArgs args, State state)
      {
         args.Graphics.DrawString(this.type.ToString(), new Font(FontFamily.GenericSansSerif, 10 * this.PowerFactor, FontStyle.Bold), Brushes.Green, this.Position);
      }

      public override void ToXML(System.Xml.XmlWriter writer)
      {
         writer.WriteStartElement("actor");
         writer.WriteAttributeString("type", this.type.ToString());
         writer.WriteAttributeString("powerFactor", this.PowerFactor.ToString());
         writer.WriteEndElement();
      }

      public override string ToString()
      {
         return base.ToString() + " " + this.type.ToString();
      }
   }
}
