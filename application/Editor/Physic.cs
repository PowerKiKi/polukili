using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml;
using System.Drawing;

namespace Editor
{
   abstract class Physic : Item
   {
      public Physic()
      {
         MainWindow.Singleton.lstPhysics.Items.Add(this);
         MainWindow.Singleton.UpdateControls();
      }
   }
}
