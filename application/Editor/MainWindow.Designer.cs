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
         this.lstPhysics = new System.Windows.Forms.CheckedListBox();
         this.propertyGrid = new System.Windows.Forms.PropertyGrid();
         this.splitContainer1 = new System.Windows.Forms.SplitContainer();
         this.splitContainer2 = new System.Windows.Forms.SplitContainer();
         this.tabControl1 = new System.Windows.Forms.TabControl();
         this.tabPage1 = new System.Windows.Forms.TabPage();
         this.tabPage2 = new System.Windows.Forms.TabPage();
         this.lstActors = new System.Windows.Forms.CheckedListBox();
         this.tabPage3 = new System.Windows.Forms.TabPage();
         this.lstLevel = new System.Windows.Forms.CheckedListBox();
         this.toolStripContainer1 = new System.Windows.Forms.ToolStripContainer();
         this.menuStrip2 = new System.Windows.Forms.MenuStrip();
         this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
         this.newToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
         this.loadXmlToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
         this.saveXmlToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
         this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
         this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
         this.viewToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
         this.allVisibleToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
         this.noneVisibleToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
         this.invertVisibilityToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
         this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripSeparator();
         this.loadImageToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
         this.generatedXMLToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
         this.toolStrip1 = new System.Windows.Forms.ToolStrip();
         this.toolStripButton1 = new System.Windows.Forms.ToolStripButton();
         this.toolStripButton3 = new System.Windows.Forms.ToolStripButton();
         this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
         this.toolStripButton2 = new System.Windows.Forms.ToolStripButton();
         this.toolStripButton4 = new System.Windows.Forms.ToolStripButton();
         ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
         this.splitContainer1.Panel1.SuspendLayout();
         this.splitContainer1.Panel2.SuspendLayout();
         this.splitContainer1.SuspendLayout();
         this.splitContainer2.Panel1.SuspendLayout();
         this.splitContainer2.Panel2.SuspendLayout();
         this.splitContainer2.SuspendLayout();
         this.tabControl1.SuspendLayout();
         this.tabPage1.SuspendLayout();
         this.tabPage2.SuspendLayout();
         this.tabPage3.SuspendLayout();
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
         this.pictureBox1.Size = new System.Drawing.Size(652, 490);
         this.pictureBox1.TabIndex = 0;
         this.pictureBox1.TabStop = false;
         // 
         // lstPhysics
         // 
         this.lstPhysics.CheckOnClick = true;
         this.lstPhysics.Dock = System.Windows.Forms.DockStyle.Fill;
         this.lstPhysics.FormattingEnabled = true;
         this.lstPhysics.Location = new System.Drawing.Point(3, 3);
         this.lstPhysics.Name = "lstPhysics";
         this.lstPhysics.Size = new System.Drawing.Size(197, 214);
         this.lstPhysics.TabIndex = 1;
         this.lstPhysics.SelectedIndexChanged += new System.EventHandler(this.checkedListBox1_SelectedIndexChanged);
         this.lstPhysics.ItemCheck += new System.Windows.Forms.ItemCheckEventHandler(this.checkedListBox1_ItemCheck);
         this.lstPhysics.KeyUp += new System.Windows.Forms.KeyEventHandler(this.deleteItem);
         // 
         // propertyGrid
         // 
         this.propertyGrid.Dock = System.Windows.Forms.DockStyle.Fill;
         this.propertyGrid.Location = new System.Drawing.Point(0, 0);
         this.propertyGrid.Name = "propertyGrid";
         this.propertyGrid.Size = new System.Drawing.Size(211, 235);
         this.propertyGrid.TabIndex = 2;
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
         this.splitContainer1.Size = new System.Drawing.Size(867, 490);
         this.splitContainer1.SplitterDistance = 211;
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
         this.splitContainer2.Panel1.Controls.Add(this.tabControl1);
         // 
         // splitContainer2.Panel2
         // 
         this.splitContainer2.Panel2.Controls.Add(this.propertyGrid);
         this.splitContainer2.Size = new System.Drawing.Size(211, 490);
         this.splitContainer2.SplitterDistance = 251;
         this.splitContainer2.TabIndex = 0;
         // 
         // tabControl1
         // 
         this.tabControl1.Controls.Add(this.tabPage1);
         this.tabControl1.Controls.Add(this.tabPage2);
         this.tabControl1.Controls.Add(this.tabPage3);
         this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
         this.tabControl1.Location = new System.Drawing.Point(0, 0);
         this.tabControl1.Name = "tabControl1";
         this.tabControl1.SelectedIndex = 0;
         this.tabControl1.Size = new System.Drawing.Size(211, 251);
         this.tabControl1.TabIndex = 2;
         this.tabControl1.SelectedIndexChanged += new System.EventHandler(this.tabControl1_SelectedIndexChanged);
         // 
         // tabPage1
         // 
         this.tabPage1.Controls.Add(this.lstPhysics);
         this.tabPage1.Location = new System.Drawing.Point(4, 22);
         this.tabPage1.Name = "tabPage1";
         this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
         this.tabPage1.Size = new System.Drawing.Size(203, 225);
         this.tabPage1.TabIndex = 0;
         this.tabPage1.Text = "Physics";
         this.tabPage1.UseVisualStyleBackColor = true;
         // 
         // tabPage2
         // 
         this.tabPage2.Controls.Add(this.lstActors);
         this.tabPage2.Location = new System.Drawing.Point(4, 22);
         this.tabPage2.Name = "tabPage2";
         this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
         this.tabPage2.Size = new System.Drawing.Size(203, 225);
         this.tabPage2.TabIndex = 1;
         this.tabPage2.Text = "Actors";
         this.tabPage2.UseVisualStyleBackColor = true;
         // 
         // lstActors
         // 
         this.lstActors.CheckOnClick = true;
         this.lstActors.Dock = System.Windows.Forms.DockStyle.Fill;
         this.lstActors.FormattingEnabled = true;
         this.lstActors.Location = new System.Drawing.Point(3, 3);
         this.lstActors.Name = "lstActors";
         this.lstActors.Size = new System.Drawing.Size(197, 214);
         this.lstActors.TabIndex = 0;
         this.lstActors.SelectedIndexChanged += new System.EventHandler(this.checkedListBox1_SelectedIndexChanged);
         this.lstActors.ItemCheck += new System.Windows.Forms.ItemCheckEventHandler(this.checkedListBox1_ItemCheck);
         this.lstActors.KeyUp += new System.Windows.Forms.KeyEventHandler(this.deleteItem);
         // 
         // tabPage3
         // 
         this.tabPage3.Controls.Add(this.lstLevel);
         this.tabPage3.Location = new System.Drawing.Point(4, 22);
         this.tabPage3.Name = "tabPage3";
         this.tabPage3.Padding = new System.Windows.Forms.Padding(3);
         this.tabPage3.Size = new System.Drawing.Size(203, 225);
         this.tabPage3.TabIndex = 2;
         this.tabPage3.Text = "Level";
         this.tabPage3.UseVisualStyleBackColor = true;
         // 
         // lstLevel
         // 
         this.lstLevel.CheckOnClick = true;
         this.lstLevel.Dock = System.Windows.Forms.DockStyle.Fill;
         this.lstLevel.FormattingEnabled = true;
         this.lstLevel.Location = new System.Drawing.Point(3, 3);
         this.lstLevel.Name = "lstLevel";
         this.lstLevel.Size = new System.Drawing.Size(197, 214);
         this.lstLevel.TabIndex = 0;
         this.lstLevel.SelectedIndexChanged += new System.EventHandler(this.checkedListBox1_SelectedIndexChanged);
         this.lstLevel.ItemCheck += new System.Windows.Forms.ItemCheckEventHandler(this.checkedListBox1_ItemCheck);
         // 
         // toolStripContainer1
         // 
         // 
         // toolStripContainer1.ContentPanel
         // 
         this.toolStripContainer1.ContentPanel.Controls.Add(this.splitContainer1);
         this.toolStripContainer1.ContentPanel.Size = new System.Drawing.Size(867, 490);
         this.toolStripContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
         this.toolStripContainer1.Location = new System.Drawing.Point(0, 0);
         this.toolStripContainer1.Name = "toolStripContainer1";
         this.toolStripContainer1.Size = new System.Drawing.Size(867, 539);
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
         this.menuStrip2.Size = new System.Drawing.Size(867, 24);
         this.menuStrip2.TabIndex = 5;
         this.menuStrip2.Text = "menuStrip2";
         // 
         // fileToolStripMenuItem
         // 
         this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripMenuItem,
            this.loadXmlToolStripMenuItem,
            this.saveXmlToolStripMenuItem,
            this.toolStripMenuItem1,
            this.exitToolStripMenuItem});
         this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
         this.fileToolStripMenuItem.Size = new System.Drawing.Size(35, 20);
         this.fileToolStripMenuItem.Text = "File";
         // 
         // newToolStripMenuItem
         // 
         this.newToolStripMenuItem.Name = "newToolStripMenuItem";
         this.newToolStripMenuItem.ShortcutKeyDisplayString = "";
         this.newToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.N)));
         this.newToolStripMenuItem.Size = new System.Drawing.Size(137, 22);
         this.newToolStripMenuItem.Text = "New";
         this.newToolStripMenuItem.Click += new System.EventHandler(this.newToolStripMenuItem_Click);
         // 
         // loadXmlToolStripMenuItem
         // 
         this.loadXmlToolStripMenuItem.Name = "loadXmlToolStripMenuItem";
         this.loadXmlToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
         this.loadXmlToolStripMenuItem.Size = new System.Drawing.Size(137, 22);
         this.loadXmlToolStripMenuItem.Text = "Load";
         this.loadXmlToolStripMenuItem.Click += new System.EventHandler(this.loadXmlToolStripMenuItem_Click);
         // 
         // saveXmlToolStripMenuItem
         // 
         this.saveXmlToolStripMenuItem.Name = "saveXmlToolStripMenuItem";
         this.saveXmlToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
         this.saveXmlToolStripMenuItem.Size = new System.Drawing.Size(137, 22);
         this.saveXmlToolStripMenuItem.Text = "Save";
         this.saveXmlToolStripMenuItem.Click += new System.EventHandler(this.saveXmlToolStripMenuItem_Click);
         // 
         // toolStripMenuItem1
         // 
         this.toolStripMenuItem1.Name = "toolStripMenuItem1";
         this.toolStripMenuItem1.Size = new System.Drawing.Size(134, 6);
         // 
         // exitToolStripMenuItem
         // 
         this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
         this.exitToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Q)));
         this.exitToolStripMenuItem.Size = new System.Drawing.Size(137, 22);
         this.exitToolStripMenuItem.Text = "Exit";
         this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
         // 
         // viewToolStripMenuItem
         // 
         this.viewToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.allVisibleToolStripMenuItem,
            this.noneVisibleToolStripMenuItem,
            this.invertVisibilityToolStripMenuItem,
            this.toolStripMenuItem2,
            this.loadImageToolStripMenuItem,
            this.generatedXMLToolStripMenuItem});
         this.viewToolStripMenuItem.Name = "viewToolStripMenuItem";
         this.viewToolStripMenuItem.Size = new System.Drawing.Size(41, 20);
         this.viewToolStripMenuItem.Text = "View";
         // 
         // allVisibleToolStripMenuItem
         // 
         this.allVisibleToolStripMenuItem.Name = "allVisibleToolStripMenuItem";
         this.allVisibleToolStripMenuItem.Size = new System.Drawing.Size(179, 22);
         this.allVisibleToolStripMenuItem.Text = "All visible";
         this.allVisibleToolStripMenuItem.Click += new System.EventHandler(this.allVisibleToolStripMenuItem_Click);
         // 
         // noneVisibleToolStripMenuItem
         // 
         this.noneVisibleToolStripMenuItem.Name = "noneVisibleToolStripMenuItem";
         this.noneVisibleToolStripMenuItem.Size = new System.Drawing.Size(179, 22);
         this.noneVisibleToolStripMenuItem.Text = "None visible";
         this.noneVisibleToolStripMenuItem.Click += new System.EventHandler(this.noneVisibleToolStripMenuItem_Click);
         // 
         // invertVisibilityToolStripMenuItem
         // 
         this.invertVisibilityToolStripMenuItem.Name = "invertVisibilityToolStripMenuItem";
         this.invertVisibilityToolStripMenuItem.Size = new System.Drawing.Size(179, 22);
         this.invertVisibilityToolStripMenuItem.Text = "Invert visibility";
         this.invertVisibilityToolStripMenuItem.Click += new System.EventHandler(this.invertVisibilityToolStripMenuItem_Click);
         // 
         // toolStripMenuItem2
         // 
         this.toolStripMenuItem2.Name = "toolStripMenuItem2";
         this.toolStripMenuItem2.Size = new System.Drawing.Size(176, 6);
         // 
         // loadImageToolStripMenuItem
         // 
         this.loadImageToolStripMenuItem.Name = "loadImageToolStripMenuItem";
         this.loadImageToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.I)));
         this.loadImageToolStripMenuItem.Size = new System.Drawing.Size(179, 22);
         this.loadImageToolStripMenuItem.Text = "Load image ...";
         this.loadImageToolStripMenuItem.Click += new System.EventHandler(this.loadImageToolStripMenuItem_Click);
         // 
         // generatedXMLToolStripMenuItem
         // 
         this.generatedXMLToolStripMenuItem.Name = "generatedXMLToolStripMenuItem";
         this.generatedXMLToolStripMenuItem.Size = new System.Drawing.Size(179, 22);
         this.generatedXMLToolStripMenuItem.Text = "Generated XML";
         this.generatedXMLToolStripMenuItem.Click += new System.EventHandler(this.generatedXMLToolStripMenuItem_Click);
         // 
         // toolStrip1
         // 
         this.toolStrip1.Dock = System.Windows.Forms.DockStyle.None;
         this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton1,
            this.toolStripButton3,
            this.toolStripSeparator1,
            this.toolStripButton2,
            this.toolStripButton4});
         this.toolStrip1.Location = new System.Drawing.Point(3, 24);
         this.toolStrip1.Name = "toolStrip1";
         this.toolStrip1.Size = new System.Drawing.Size(110, 25);
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
         // toolStripButton2
         // 
         this.toolStripButton2.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
         this.toolStripButton2.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton2.Image")));
         this.toolStripButton2.ImageTransparentColor = System.Drawing.Color.Magenta;
         this.toolStripButton2.Name = "toolStripButton2";
         this.toolStripButton2.Size = new System.Drawing.Size(23, 22);
         this.toolStripButton2.Text = "toolStripButton2";
         this.toolStripButton2.Click += new System.EventHandler(this.toolStripButton2_Click);
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
         this.ClientSize = new System.Drawing.Size(867, 539);
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
         this.tabControl1.ResumeLayout(false);
         this.tabPage1.ResumeLayout(false);
         this.tabPage2.ResumeLayout(false);
         this.tabPage3.ResumeLayout(false);
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
      private System.Windows.Forms.PropertyGrid propertyGrid;
      private System.Windows.Forms.SplitContainer splitContainer1;
      private System.Windows.Forms.SplitContainer splitContainer2;
      private System.Windows.Forms.ToolStripContainer toolStripContainer1;
      private System.Windows.Forms.MenuStrip menuStrip2;
      private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
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
      private System.Windows.Forms.TabControl tabControl1;
      private System.Windows.Forms.TabPage tabPage1;
      private System.Windows.Forms.TabPage tabPage2;
      private System.Windows.Forms.TabPage tabPage3;
      public System.Windows.Forms.CheckedListBox lstPhysics;
      public System.Windows.Forms.CheckedListBox lstActors;
      private System.Windows.Forms.CheckedListBox lstLevel;
      private System.Windows.Forms.ToolStripButton toolStripButton2;
      private System.Windows.Forms.ToolStripMenuItem loadXmlToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem newToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem loadImageToolStripMenuItem;

   }
}

