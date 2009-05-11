namespace Editor
{
   partial class MainWindow
   {
      /// <summary>
      /// Required designer variable.
      /// </summary>
      private System.ComponentModel.IContainer components = null;

      /// <summary>
      /// Clean up any resources being used.
      /// </summary>
      /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
      protected override void Dispose(bool disposing)
      {
         if (disposing && (components != null))
         {
            components.Dispose();
         }
         base.Dispose(disposing);
      }

      #region Windows Form Designer generated code

      /// <summary>
      /// Required method for Designer support - do not modify
      /// the contents of this method with the code editor.
      /// </summary>
      private void InitializeComponent()
      {
         System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainWindow));
         this.pictureBox1 = new System.Windows.Forms.PictureBox();
         this.checkedListBox1 = new System.Windows.Forms.CheckedListBox();
         this.propertyGrid1 = new System.Windows.Forms.PropertyGrid();
         this.splitContainer1 = new System.Windows.Forms.SplitContainer();
         this.splitContainer2 = new System.Windows.Forms.SplitContainer();
         this.toolStripContainer1 = new System.Windows.Forms.ToolStripContainer();
         this.menuStrip2 = new System.Windows.Forms.MenuStrip();
         this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
         this.loadImageToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
         this.saveXmlToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
         this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
         this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
         this.viewToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
         this.allVisibleToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
         this.noneVisibleToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
         this.invertVisibilityToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
         this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripSeparator();
         this.generatedXMLToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
         this.toolStrip1 = new System.Windows.Forms.ToolStrip();
         this.toolStripButton1 = new System.Windows.Forms.ToolStripButton();
         this.toolStripButton3 = new System.Windows.Forms.ToolStripButton();
         this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
         this.toolStripButton4 = new System.Windows.Forms.ToolStripButton();
         ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
         this.splitContainer1.Panel1.SuspendLayout();
         this.splitContainer1.Panel2.SuspendLayout();
         this.splitContainer1.SuspendLayout();
         this.splitContainer2.Panel1.SuspendLayout();
         this.splitContainer2.Panel2.SuspendLayout();
         this.splitContainer2.SuspendLayout();
         this.toolStripContainer1.ContentPanel.SuspendLayout();
         this.toolStripContainer1.TopToolStripPanel.SuspendLayout();
         this.toolStripContainer1.SuspendLayout();
         this.menuStrip2.SuspendLayout();
         this.toolStrip1.SuspendLayout();
         this.SuspendLayout();
         // 
         // pictureBox1
         // 
         this.pictureBox1.Dock = System.Windows.Forms.DockStyle.Fill;
         this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
         this.pictureBox1.InitialImage = ((System.Drawing.Image)(resources.GetObject("pictureBox1.InitialImage")));
         this.pictureBox1.Location = new System.Drawing.Point(0, 0);
         this.pictureBox1.Name = "pictureBox1";
         this.pictureBox1.Size = new System.Drawing.Size(646, 487);
         this.pictureBox1.TabIndex = 0;
         this.pictureBox1.TabStop = false;
         // 
         // checkedListBox1
         // 
         this.checkedListBox1.CheckOnClick = true;
         this.checkedListBox1.Dock = System.Windows.Forms.DockStyle.Fill;
         this.checkedListBox1.FormattingEnabled = true;
         this.checkedListBox1.Location = new System.Drawing.Point(0, 0);
         this.checkedListBox1.Name = "checkedListBox1";
         this.checkedListBox1.Size = new System.Drawing.Size(178, 244);
         this.checkedListBox1.TabIndex = 1;
         this.checkedListBox1.SelectedIndexChanged += new System.EventHandler(this.checkedListBox1_SelectedIndexChanged);
         this.checkedListBox1.ItemCheck += new System.Windows.Forms.ItemCheckEventHandler(this.checkedListBox1_ItemCheck);
         // 
         // propertyGrid1
         // 
         this.propertyGrid1.Dock = System.Windows.Forms.DockStyle.Fill;
         this.propertyGrid1.Location = new System.Drawing.Point(0, 0);
         this.propertyGrid1.Name = "propertyGrid1";
         this.propertyGrid1.Size = new System.Drawing.Size(178, 233);
         this.propertyGrid1.TabIndex = 2;
         // 
         // splitContainer1
         // 
         this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
         this.splitContainer1.Location = new System.Drawing.Point(0, 0);
         this.splitContainer1.Name = "splitContainer1";
         // 
         // splitContainer1.Panel1
         // 
         this.splitContainer1.Panel1.Controls.Add(this.splitContainer2);
         // 
         // splitContainer1.Panel2
         // 
         this.splitContainer1.Panel2.Controls.Add(this.pictureBox1);
         this.splitContainer1.Size = new System.Drawing.Size(828, 487);
         this.splitContainer1.SplitterDistance = 178;
         this.splitContainer1.TabIndex = 3;
         // 
         // splitContainer2
         // 
         this.splitContainer2.Dock = System.Windows.Forms.DockStyle.Fill;
         this.splitContainer2.Location = new System.Drawing.Point(0, 0);
         this.splitContainer2.Name = "splitContainer2";
         this.splitContainer2.Orientation = System.Windows.Forms.Orientation.Horizontal;
         // 
         // splitContainer2.Panel1
         // 
         this.splitContainer2.Panel1.Controls.Add(this.checkedListBox1);
         // 
         // splitContainer2.Panel2
         // 
         this.splitContainer2.Panel2.Controls.Add(this.propertyGrid1);
         this.splitContainer2.Size = new System.Drawing.Size(178, 487);
         this.splitContainer2.SplitterDistance = 250;
         this.splitContainer2.TabIndex = 0;
         // 
         // toolStripContainer1
         // 
         // 
         // toolStripContainer1.ContentPanel
         // 
         this.toolStripContainer1.ContentPanel.Controls.Add(this.splitContainer1);
         this.toolStripContainer1.ContentPanel.Size = new System.Drawing.Size(828, 487);
         this.toolStripContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
         this.toolStripContainer1.Location = new System.Drawing.Point(0, 0);
         this.toolStripContainer1.Name = "toolStripContainer1";
         this.toolStripContainer1.Size = new System.Drawing.Size(828, 536);
         this.toolStripContainer1.TabIndex = 6;
         this.toolStripContainer1.Text = "toolStripContainer1";
         // 
         // toolStripContainer1.TopToolStripPanel
         // 
         this.toolStripContainer1.TopToolStripPanel.Controls.Add(this.menuStrip2);
         this.toolStripContainer1.TopToolStripPanel.Controls.Add(this.toolStrip1);
         // 
         // menuStrip2
         // 
         this.menuStrip2.Dock = System.Windows.Forms.DockStyle.None;
         this.menuStrip2.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.viewToolStripMenuItem});
         this.menuStrip2.Location = new System.Drawing.Point(0, 0);
         this.menuStrip2.Name = "menuStrip2";
         this.menuStrip2.Size = new System.Drawing.Size(828, 24);
         this.menuStrip2.TabIndex = 5;
         this.menuStrip2.Text = "menuStrip2";
         // 
         // fileToolStripMenuItem
         // 
         this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.loadImageToolStripMenuItem,
            this.saveXmlToolStripMenuItem,
            this.toolStripMenuItem1,
            this.exitToolStripMenuItem});
         this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
         this.fileToolStripMenuItem.Size = new System.Drawing.Size(35, 20);
         this.fileToolStripMenuItem.Text = "File";
         // 
         // loadImageToolStripMenuItem
         // 
         this.loadImageToolStripMenuItem.Name = "loadImageToolStripMenuItem";
         this.loadImageToolStripMenuItem.Size = new System.Drawing.Size(143, 22);
         this.loadImageToolStripMenuItem.Text = "Load image ...";
         this.loadImageToolStripMenuItem.Click += new System.EventHandler(this.loadImageToolStripMenuItem_Click);
         // 
         // saveXmlToolStripMenuItem
         // 
         this.saveXmlToolStripMenuItem.Name = "saveXmlToolStripMenuItem";
         this.saveXmlToolStripMenuItem.Size = new System.Drawing.Size(143, 22);
         this.saveXmlToolStripMenuItem.Text = "Save xml ...";
         // 
         // toolStripMenuItem1
         // 
         this.toolStripMenuItem1.Name = "toolStripMenuItem1";
         this.toolStripMenuItem1.Size = new System.Drawing.Size(140, 6);
         // 
         // exitToolStripMenuItem
         // 
         this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
         this.exitToolStripMenuItem.Size = new System.Drawing.Size(143, 22);
         this.exitToolStripMenuItem.Text = "Exit";
         // 
         // viewToolStripMenuItem
         // 
         this.viewToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.allVisibleToolStripMenuItem,
            this.noneVisibleToolStripMenuItem,
            this.invertVisibilityToolStripMenuItem,
            this.toolStripMenuItem2,
            this.generatedXMLToolStripMenuItem});
         this.viewToolStripMenuItem.Name = "viewToolStripMenuItem";
         this.viewToolStripMenuItem.Size = new System.Drawing.Size(41, 20);
         this.viewToolStripMenuItem.Text = "View";
         // 
         // allVisibleToolStripMenuItem
         // 
         this.allVisibleToolStripMenuItem.Name = "allVisibleToolStripMenuItem";
         this.allVisibleToolStripMenuItem.Size = new System.Drawing.Size(147, 22);
         this.allVisibleToolStripMenuItem.Text = "All visible";
         // 
         // noneVisibleToolStripMenuItem
         // 
         this.noneVisibleToolStripMenuItem.Name = "noneVisibleToolStripMenuItem";
         this.noneVisibleToolStripMenuItem.Size = new System.Drawing.Size(147, 22);
         this.noneVisibleToolStripMenuItem.Text = "None visible";
         // 
         // invertVisibilityToolStripMenuItem
         // 
         this.invertVisibilityToolStripMenuItem.Name = "invertVisibilityToolStripMenuItem";
         this.invertVisibilityToolStripMenuItem.Size = new System.Drawing.Size(147, 22);
         this.invertVisibilityToolStripMenuItem.Text = "Invert visibility";
         // 
         // toolStripMenuItem2
         // 
         this.toolStripMenuItem2.Name = "toolStripMenuItem2";
         this.toolStripMenuItem2.Size = new System.Drawing.Size(144, 6);
         // 
         // generatedXMLToolStripMenuItem
         // 
         this.generatedXMLToolStripMenuItem.Name = "generatedXMLToolStripMenuItem";
         this.generatedXMLToolStripMenuItem.Size = new System.Drawing.Size(147, 22);
         this.generatedXMLToolStripMenuItem.Text = "Generated XML";
         // 
         // toolStrip1
         // 
         this.toolStrip1.Dock = System.Windows.Forms.DockStyle.None;
         this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton1,
            this.toolStripButton3,
            this.toolStripSeparator1,
            this.toolStripButton4});
         this.toolStrip1.Location = new System.Drawing.Point(3, 24);
         this.toolStrip1.Name = "toolStrip1";
         this.toolStrip1.Size = new System.Drawing.Size(118, 25);
         this.toolStrip1.TabIndex = 7;
         this.toolStrip1.Text = "toolStrip1";
         // 
         // toolStripButton1
         // 
         this.toolStripButton1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
         this.toolStripButton1.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton1.Image")));
         this.toolStripButton1.ImageTransparentColor = System.Drawing.Color.Magenta;
         this.toolStripButton1.Name = "toolStripButton1";
         this.toolStripButton1.Size = new System.Drawing.Size(23, 22);
         this.toolStripButton1.Text = "toolStripButton1";
         this.toolStripButton1.Click += new System.EventHandler(this.toolStripButton1_Click);
         // 
         // toolStripButton3
         // 
         this.toolStripButton3.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
         this.toolStripButton3.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton3.Image")));
         this.toolStripButton3.ImageTransparentColor = System.Drawing.Color.Magenta;
         this.toolStripButton3.Name = "toolStripButton3";
         this.toolStripButton3.Size = new System.Drawing.Size(23, 22);
         this.toolStripButton3.Text = "toolStripButton3";
         this.toolStripButton3.Click += new System.EventHandler(this.toolStripButton3_Click);
         // 
         // toolStripSeparator1
         // 
         this.toolStripSeparator1.Name = "toolStripSeparator1";
         this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
         // 
         // toolStripButton4
         // 
         this.toolStripButton4.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
         this.toolStripButton4.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton4.Image")));
         this.toolStripButton4.ImageTransparentColor = System.Drawing.Color.Magenta;
         this.toolStripButton4.Name = "toolStripButton4";
         this.toolStripButton4.Size = new System.Drawing.Size(23, 22);
         this.toolStripButton4.Text = "toolStripButton4";
         this.toolStripButton4.Click += new System.EventHandler(this.generatedXMLToolStripMenuItem_Click);
         // 
         // MainWindow
         // 
         this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
         this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
         this.ClientSize = new System.Drawing.Size(828, 536);
         this.Controls.Add(this.toolStripContainer1);
         this.Name = "MainWindow";
         this.Text = "Polukili Editor";
         this.Load += new System.EventHandler(this.Form1_Load);
         ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
         this.splitContainer1.Panel1.ResumeLayout(false);
         this.splitContainer1.Panel2.ResumeLayout(false);
         this.splitContainer1.ResumeLayout(false);
         this.splitContainer2.Panel1.ResumeLayout(false);
         this.splitContainer2.Panel2.ResumeLayout(false);
         this.splitContainer2.ResumeLayout(false);
         this.toolStripContainer1.ContentPanel.ResumeLayout(false);
         this.toolStripContainer1.TopToolStripPanel.ResumeLayout(false);
         this.toolStripContainer1.TopToolStripPanel.PerformLayout();
         this.toolStripContainer1.ResumeLayout(false);
         this.toolStripContainer1.PerformLayout();
         this.menuStrip2.ResumeLayout(false);
         this.menuStrip2.PerformLayout();
         this.toolStrip1.ResumeLayout(false);
         this.toolStrip1.PerformLayout();
         this.ResumeLayout(false);

      }

      #endregion

      private System.Windows.Forms.PictureBox pictureBox1;
      private System.Windows.Forms.PropertyGrid propertyGrid1;
      private System.Windows.Forms.CheckedListBox checkedListBox1;
      private System.Windows.Forms.SplitContainer splitContainer1;
      private System.Windows.Forms.SplitContainer splitContainer2;
      private System.Windows.Forms.ToolStripContainer toolStripContainer1;
      private System.Windows.Forms.MenuStrip menuStrip2;
      private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem loadImageToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem saveXmlToolStripMenuItem;
      private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
      private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem viewToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem allVisibleToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem noneVisibleToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem invertVisibilityToolStripMenuItem;
      private System.Windows.Forms.ToolStripSeparator toolStripMenuItem2;
      private System.Windows.Forms.ToolStripMenuItem generatedXMLToolStripMenuItem;
      private System.Windows.Forms.ToolStrip toolStrip1;
      private System.Windows.Forms.ToolStripButton toolStripButton1;
      private System.Windows.Forms.ToolStripButton toolStripButton3;
      private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
      private System.Windows.Forms.ToolStripButton toolStripButton4;

   }
}

