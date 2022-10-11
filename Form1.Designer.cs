
namespace SPETS
{
    partial class ActionSelectForm
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ActionSelectForm));
            this.ToolDropdown = new System.Windows.Forms.ComboBox();
            this.StartButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // ToolDropdown
            // 
            this.ToolDropdown.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.ToolDropdown.FormattingEnabled = true;
            this.ToolDropdown.Items.AddRange(new object[] {
            "Import from OBJ",
            "Export to OBJ",
            "Advanced Editor"});
            this.ToolDropdown.Location = new System.Drawing.Point(12, 53);
            this.ToolDropdown.Name = "ToolDropdown";
            this.ToolDropdown.Size = new System.Drawing.Size(176, 23);
            this.ToolDropdown.TabIndex = 0;
            // 
            // StartButton
            // 
            this.StartButton.Location = new System.Drawing.Point(194, 12);
            this.StartButton.Name = "StartButton";
            this.StartButton.Size = new System.Drawing.Size(128, 64);
            this.StartButton.TabIndex = 1;
            this.StartButton.Text = "Load";
            this.StartButton.UseVisualStyleBackColor = true;
            this.StartButton.Click += new System.EventHandler(this.StartButton_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 12);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(169, 15);
            this.label1.TabIndex = 2;
            this.label1.Text = "Select tool from the dropdown";
            // 
            // ActionSelectForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(334, 88);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.StartButton);
            this.Controls.Add(this.ToolDropdown);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "ActionSelectForm";
            this.Text = "Sprocket Editing Tools";
            this.Load += new System.EventHandler(this.ActionSelectForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox ToolDropdown;
        private System.Windows.Forms.Button StartButton;
        private System.Windows.Forms.Label label1;
    }
}

