using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml;

namespace Editor
{
   internal partial class MainWindow : Form
   {
      public static MainWindow Singleton { get; private set; }

      private XmlView xmlView = new XmlView();
      private bool updating = false;

      public MainWindow()
      {
         InitializeComponent();
         MainWindow.Singleton = this;
         this.InitLevel();
      }

      private void ClearLevel()
      {
         this.lstLevel.Items.Clear();
         this.lstActors.Items.Clear();
         this.lstPhysics.Items.Clear();
      }

      private void InitLevel()
      {
         this.updating = true;

         this.ClearLevel();
         new Circle(new Point(20, 20), 20);
         new Circle(new Point(50, 50), 200);
         new Circle(new Point(300, 200), 200);
         new Polygon();
         new Actor(Actor.ActorType.kiki);
         new Actor(Actor.ActorType.luna);
         new Actor(Actor.ActorType.poupa);
         new Actor(Actor.ActorType.lila);
         this.lstLevel.Items.Add(new Level());

         this.updating = false;
         this.UpdateControls();
      }

      private void ReadLevel()
      {
         this.updating = true;

         var d = new OpenFileDialog();
         if (d.ShowDialog() == DialogResult.OK)
         {
            this.ClearLevel();


            var level = new Level();
            level.SetFileName(d.FileName);
            this.lstLevel.Items.Add(level);

            XmlDocument xml = new XmlDocument();
            xml.Load(d.FileName);
            level.Read(xml["level"]);
            foreach (XmlElement el in xml["level"]["actors"])
            {
               Actor actor = new Actor();
               actor.Read(el);
            }
            foreach (XmlElement el in xml["level"]["physics"])
            {
               Physic p;
               if (el.Name == "circle")
                  p = new Circle();
               else if (el.Name == "polygon")
                  p = new Polygon();
               else
               {
                  MessageBox.Show(string.Format("unsupported physic '{0}'. Element skipped.", el.Name));
                  continue;
               }
               p.Read(el);
            }
         }

         this.updating = false;
         this.UpdateControls();
         this.GetCurrent().SelectedItem = this.GetCurrent().Items[0];
      }

      public void WriteLevel(XmlWriter writer)
      {
         writer.WriteStartDocument();
         foreach (Level level in this.lstLevel.Items)
            level.ToXML(writer);

         writer.WriteStartElement("physics");
         foreach (Item p in this.lstPhysics.Items)
            p.ToXML(writer);
         writer.WriteEndElement();
         writer.WriteStartElement("actors");
         foreach (Item p in this.lstActors.Items)
            p.ToXML(writer);

         writer.WriteEndElement();
         writer.WriteEndDocument();
         writer.Close();
      }

      private void Form1_Load(object sender, EventArgs e)
      {
         this.pictureBox1.Image = Image.FromFile(@"D:\bordel\private\projets\polukili\application\data\level_0_background.png");
         this.pictureBox1.Paint += new PaintEventHandler(pictureBox1_Paint);
      }

      void pictureBox1_Paint(object sender, PaintEventArgs e)
      {
         foreach (Item item in this.lstLevel.Items)
            if (item.IsVisible)
               item.Paint(e, State.Normal);

         foreach (Item item in this.lstPhysics.Items)
            if (item.IsVisible)
               item.Paint(e, State.Normal);

         foreach (Item item in this.lstActors.Items)
            if (item.IsVisible)
               item.Paint(e, State.Normal);
      }

      public void UpdateControls()
      {
         if (this.updating) return;
         this.updating = true;

         this.UpdateCheckedList(this.lstPhysics);
         this.UpdateCheckedList(this.lstActors);
         this.UpdateCheckedList(this.lstLevel);
         this.propertyGrid.Refresh();
         this.pictureBox1.Refresh();
         if (this.xmlView.Visible)
         {
            XmlWriterSettings writerSettings = new XmlWriterSettings();
            writerSettings.Indent = true;
            var w = new System.IO.StringWriter();
            XmlWriter writer = XmlWriter.Create(w, writerSettings);
            this.WriteLevel(writer);

            this.xmlView.txtXML.Text = w.ToString();
         }
         this.updating = false;
      }

      private void UpdateCheckedList(CheckedListBox list)
      {
         object wasSelected = list.SelectedItem;
         list.BeginUpdate();
         for (int i = 0; i < list.Items.Count; i++)
            list.SetItemChecked(i, ((Item)list.Items[i]).IsVisible);
         list.SelectedItem = wasSelected;
         list.EndUpdate();
      }

      private void checkedListBox1_SelectedIndexChanged(object sender, EventArgs e)
      {
         var i = this.GetCurrent().SelectedItem;
         this.propertyGrid.SelectedObject = this.GetCurrent().SelectedItem;
      }

      private void checkedListBox1_ItemCheck(object sender, ItemCheckEventArgs e)
      {
         if (((CheckedListBox)sender).SelectedItem != null)
            ((Item)((CheckedListBox)sender).SelectedItem).IsVisible = e.NewValue == CheckState.Checked;
      }

      private void loadImageToolStripMenuItem_Click(object sender, EventArgs e)
      {
         var d = new OpenFileDialog();
         if (d.ShowDialog() == DialogResult.OK)
         {
            try
            {
               this.pictureBox1.Image = Image.FromFile(d.FileName);
            }
            catch (Exception err)
            {
               MessageBox.Show("Bad image format ! \n\n" + err.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
         }
      }

      private void exitToolStripMenuItem_Click(object sender, EventArgs e)
      {
         Application.Exit();
      }
      private CheckedListBox GetCurrent()
      {
         if (this.tabControl1.SelectedTab == this.tabPage1)
            return this.lstPhysics;
         else if (this.tabControl1.SelectedTab == this.tabPage2)
            return this.lstActors;
         else
            return this.lstLevel;
      }

      private void allVisibleToolStripMenuItem_Click(object sender, EventArgs e)
      {
         this.updating = true;
         foreach (Item p in this.GetCurrent().Items)
            p.IsVisible = true;
         this.updating = false;
         this.UpdateControls();
      }

      private void noneVisibleToolStripMenuItem_Click(object sender, EventArgs e)
      {
         this.updating = true;
         foreach (Item p in this.GetCurrent().Items)
            p.IsVisible = false;
         this.updating = false;
         this.UpdateControls();
      }

      private void invertVisibilityToolStripMenuItem_Click(object sender, EventArgs e)
      {
         this.updating = true;
         foreach (Item p in this.GetCurrent().Items)
            p.IsVisible = !p.IsVisible;
         this.updating = false;
         this.UpdateControls();
      }

      private void generatedXMLToolStripMenuItem_Click(object sender, EventArgs e)
      {
         this.xmlView.Show();
         this.UpdateControls();
      }

      private void toolStripButton1_Click(object sender, EventArgs e)
      {
         new Circle(new Point(100, 100), 50);
      }

      private void toolStripButton3_Click(object sender, EventArgs e)
      {
         new Polygon();
      }

      private void tabControl1_SelectedIndexChanged(object sender, EventArgs e)
      {
         this.checkedListBox1_SelectedIndexChanged(null, null);
         this.UpdateControls();
      }

      private void toolStripButton2_Click(object sender, EventArgs e)
      {
         new Actor();
      }

      private void deleteItem(object sender, KeyEventArgs e)
      {
         var list = ((CheckedListBox)sender);
         if (list.SelectedItem != null && e.KeyCode == Keys.Delete)
         {
            list.Items.Remove(list.SelectedItem);
            this.UpdateControls();
         }
      }

      private void loadXmlToolStripMenuItem_Click(object sender, EventArgs e)
      {
         this.ReadLevel();
      }

      private void newToolStripMenuItem_Click(object sender, EventArgs e)
      {
         this.InitLevel();
      }

      private void saveXmlToolStripMenuItem_Click(object sender, EventArgs e)
      {
         Level level = (Level)this.lstLevel.Items[0];
         if (level.FileName == string.Empty)
         {
            var d = new SaveFileDialog();
            if (d.ShowDialog() != DialogResult.OK)
               return;
            level.SetFileName(d.FileName);
         }

         XmlWriterSettings writerSettings = new XmlWriterSettings();
         writerSettings.Indent = true;
         XmlWriter writer = XmlWriter.Create(level.FileName, writerSettings);
         this.WriteLevel(writer);
         this.UpdateControls();
      }
   }
}
