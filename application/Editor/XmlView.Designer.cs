namespace Editor
{
   partial class XmlView
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
         this.txtXML = new System.Windows.Forms.TextBox();
         this.SuspendLayout();
         // 
         // txtXML
         // 
         this.txtXML.Dock = System.Windows.Forms.DockStyle.Fill;
         this.txtXML.Location = new System.Drawing.Point(0, 0);
         this.txtXML.Multiline = true;
         this.txtXML.Name = "txtXML";
         this.txtXML.ScrollBars = System.Windows.Forms.ScrollBars.Both;
         this.txtXML.Size = new System.Drawing.Size(292, 271);
         this.txtXML.TabIndex = 0;
         // 
         // XmlView
         // 
         this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
         this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
         this.ClientSize = new System.Drawing.Size(292, 271);
         this.Controls.Add(this.txtXML);
         this.Name = "XmlView";
         this.Text = "XmlView";
         this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.XmlView_FormClosing);
         this.ResumeLayout(false);
         this.PerformLayout();

      }

      #endregion

      public System.Windows.Forms.TextBox txtXML;

   }
}