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

      public List<Physic> physics = new List<Physic>();
      private XmlView xmlView = new XmlView();

      public MainWindow()
      {
         InitializeComponent();
         MainWindow.Singleton = this;
         new Circle(new Point(20, 20), 20);
         new Circle(new Point(50, 50), 200);
         new Circle(new Point(300, 200), 200);
         new Polygon();
      }

      private void Form1_Load(object sender, EventArgs e)
      {
         this.pictureBox1.Image = Image.FromFile(@"D:\bordel\private\projets\polukili\application\data\level_0_background.png");
         this.pictureBox1.Paint += new PaintEventHandler(pictureBox1_Paint);
      }

      void pictureBox1_Paint(object sender, PaintEventArgs e)
      {
         foreach (Physic physic in this.physics)
            if (physic.IsVisible)
               physic.Paint(e, State.Normal);
      }

      public void UpdateControls()
      {
         object wasSelected = this.checkedListBox1.SelectedItem;
         this.checkedListBox1.BeginUpdate();
         this.checkedListBox1.Items.Clear();
         this.checkedListBox1.Items.AddRange(this.physics.ToArray());
         for (int i = 0; i < this.checkedListBox1.Items.Count; i++)
         {
            this.checkedListBox1.SetItemChecked(i, ((Physic)this.checkedListBox1.Items[i]).IsVisible);
         }
         this.checkedListBox1.SelectedItem = wasSelected;
         this.checkedListBox1.EndUpdate();

         this.propertyGrid1.Refresh();
         this.pictureBox1.Refresh();
         if (this.xmlView.Visible)
         {
            XmlWriterSettings writerSettings = new XmlWriterSettings();
            
            writerSettings.Indent = true;
            var w = new System.IO.StringWriter();
            XmlWriter writer = XmlWriter.Create(w, writerSettings);

            writer.WriteStartDocument();
            writer.WriteStartElement("level");
            foreach (Physic p in this.physics)
               p.ToXML(writer);

            writer.WriteEndElement();
            writer.WriteEndDocument();
            writer.Close();

            this.xmlView.txtXML.Text = w.ToString();
         }
      }

      private void checkedListBox1_SelectedIndexChanged(object sender, EventArgs e)
      {
         this.propertyGrid1.SelectedObject = this.checkedListBox1.SelectedItem;
      }

      private void checkedListBox1_ItemCheck(object sender, ItemCheckEventArgs e)
      {
         if (this.checkedListBox1.SelectedItem != null)
            ((Physic)this.checkedListBox1.SelectedItem).IsVisible = e.NewValue == CheckState.Checked;
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

      private void allVisibleToolStripMenuItem_Click(object sender, EventArgs e)
      {
         foreach (Physic p in this.physics)
            p.IsVisible = true;
      }

      private void noneVisibleToolStripMenuItem_Click(object sender, EventArgs e)
      {
         foreach (Physic p in this.physics)
            p.IsVisible = false;

      }

      private void invertVisibilityToolStripMenuItem_Click(object sender, EventArgs e)
      {
         foreach (Physic p in this.physics)
            p.IsVisible = !p.IsVisible;
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

   }
}
