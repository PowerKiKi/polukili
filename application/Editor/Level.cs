using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Windows.Forms;
using System.ComponentModel;

namespace Editor
{
   class Level : Item
   {
      private string filename = "";
      [Category("Editor only")]
      public string FileName
      {
         get { return this.filename; }
         private set { this.filename = value; }
      }
      private string name = "";
      public string Name
      {
         get { return this.name; }
         set { this.name = value; MainWindow.Singleton.UpdateControls(); }
      }
      private string nextLevel = "";
      public string NextLevel
      {
         get { return this.nextLevel; }
         set { this.nextLevel = value; MainWindow.Singleton.UpdateControls(); }
      }

      private string background = "";
      public string Background
      {
         get { return this.background; }
         set { this.background = value; MainWindow.Singleton.UpdateControls(); }
      }

      private string foreground = "";
      public string Foreground
      {
         get { return this.foreground; }
         set { this.foreground = value; MainWindow.Singleton.UpdateControls(); }
      }

      public void SetFileName(string filename)
      {
         this.FileName = filename;
      }

      public override void Paint(System.Windows.Forms.PaintEventArgs args, State state)
      {
         try
         {
            Image img = Image.FromFile(this.Background);
            args.Graphics.DrawImage(img, new Point(0, 0));
         }
         catch
         { // Nothing to do
         }
      }

      public override void ToXML(System.Xml.XmlWriter writer)
      {
         writer.WriteStartElement("level");
         writer.WriteAttributeString("name", this.Name);
         writer.WriteAttributeString("nextLevel", this.NextLevel);
         writer.WriteAttributeString("background", this.Background);
         writer.WriteAttributeString("foreground", this.Foreground);
      }

      public override void Read(System.Xml.XmlElement element)
      {
         this.Name = element.GetAttribute("name");
         this.NextLevel = element.GetAttribute("nextLevel");
         this.Background = element.GetAttribute("background");
         this.Foreground = element.GetAttribute("foreground");
      }
   }
}
