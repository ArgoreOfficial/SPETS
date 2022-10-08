
namespace SPETS.forms
{
    partial class BlueprintEditorForm
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
            this.components = new System.ComponentModel.Container();
            this.frameTimer = new System.Windows.Forms.Timer(this.components);
            this.panel1 = new System.Windows.Forms.Panel();
            this.panel2 = new System.Windows.Forms.Panel();
            this.panel3 = new System.Windows.Forms.Panel();
            this.panel4 = new System.Windows.Forms.Panel();
            this.SuspendLayout();
            // 
            // frameTimer
            // 
            this.frameTimer.Enabled = true;
            // 
            // panel1
            // 
            this.panel1.Location = new System.Drawing.Point(12, 12);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(321, 196);
            this.panel1.TabIndex = 0;
            // 
            // panel2
            // 
            this.panel2.Location = new System.Drawing.Point(339, 12);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(401, 196);
            this.panel2.TabIndex = 1;
            // 
            // panel3
            // 
            this.panel3.Location = new System.Drawing.Point(339, 214);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(401, 281);
            this.panel3.TabIndex = 2;
            // 
            // panel4
            // 
            this.panel4.Location = new System.Drawing.Point(12, 214);
            this.panel4.Name = "panel4";
            this.panel4.Size = new System.Drawing.Size(321, 281);
            this.panel4.TabIndex = 3;
            // 
            // BlueprintEditorForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(752, 507);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panel4);
            this.Controls.Add(this.panel3);
            this.Controls.Add(this.panel1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "BlueprintEditorForm";
            this.Text = "BlueprintEditorForm";
            this.Load += new System.EventHandler(this.BlueprintEditorForm_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Timer frameTimer;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Panel panel4;
    }
}