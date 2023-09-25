
namespace SPETS.forms
{
    partial class ExportForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ExportForm));
            this.KeepCompPosCheckBox = new System.Windows.Forms.CheckBox();
            this.ExportingProgress = new System.Windows.Forms.ProgressBar();
            this.ExportButton = new System.Windows.Forms.Button();
            this.FileSizeLabel = new System.Windows.Forms.Label();
            this.FileNameLabel = new System.Windows.Forms.Label();
            this.ExportWorker = new System.ComponentModel.BackgroundWorker();
            this.SuspendLayout();
            // 
            // KeepCompPosCheckBox
            // 
            this.KeepCompPosCheckBox.AutoSize = true;
            this.KeepCompPosCheckBox.Location = new System.Drawing.Point(12, 42);
            this.KeepCompPosCheckBox.Name = "KeepCompPosCheckBox";
            this.KeepCompPosCheckBox.Size = new System.Drawing.Size(176, 19);
            this.KeepCompPosCheckBox.TabIndex = 0;
            this.KeepCompPosCheckBox.Text = "Keep Compartment Position";
            this.KeepCompPosCheckBox.UseVisualStyleBackColor = true;
            // 
            // ExportingProgress
            // 
            this.ExportingProgress.Location = new System.Drawing.Point(12, 67);
            this.ExportingProgress.Name = "ExportingProgress";
            this.ExportingProgress.Size = new System.Drawing.Size(248, 23);
            this.ExportingProgress.TabIndex = 17;
            // 
            // ExportButton
            // 
            this.ExportButton.Location = new System.Drawing.Point(194, 38);
            this.ExportButton.Name = "ExportButton";
            this.ExportButton.Size = new System.Drawing.Size(66, 23);
            this.ExportButton.TabIndex = 15;
            this.ExportButton.Text = "Export";
            this.ExportButton.UseVisualStyleBackColor = true;
            this.ExportButton.Click += new System.EventHandler(this.ExportButton_Click);
            // 
            // FileSizeLabel
            // 
            this.FileSizeLabel.AutoSize = true;
            this.FileSizeLabel.Location = new System.Drawing.Point(12, 24);
            this.FileSizeLabel.Name = "FileSizeLabel";
            this.FileSizeLabel.Size = new System.Drawing.Size(76, 15);
            this.FileSizeLabel.TabIndex = 14;
            this.FileSizeLabel.Text = "FileSize Bytes";
            // 
            // FileNameLabel
            // 
            this.FileNameLabel.AutoSize = true;
            this.FileNameLabel.Location = new System.Drawing.Point(12, 9);
            this.FileNameLabel.Name = "FileNameLabel";
            this.FileNameLabel.Size = new System.Drawing.Size(57, 15);
            this.FileNameLabel.TabIndex = 13;
            this.FileNameLabel.Text = "FileName";
            // 
            // ExportWorker
            // 
            this.ExportWorker.WorkerReportsProgress = true;
            this.ExportWorker.DoWork += new System.ComponentModel.DoWorkEventHandler(this.ExportWorker_DoWork);
            this.ExportWorker.ProgressChanged += new System.ComponentModel.ProgressChangedEventHandler(this.ExportWorker_ProgressChanged);
            // 
            // ExportForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(279, 102);
            this.Controls.Add(this.ExportingProgress);
            this.Controls.Add(this.ExportButton);
            this.Controls.Add(this.FileSizeLabel);
            this.Controls.Add(this.FileNameLabel);
            this.Controls.Add(this.KeepCompPosCheckBox);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "ExportForm";
            this.Text = "Export Model";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.ExportForm_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.CheckBox KeepCompPosCheckBox;
        private System.Windows.Forms.ProgressBar ExportingProgress;
        private System.Windows.Forms.Button ExportButton;
        private System.Windows.Forms.Label FileSizeLabel;
        private System.Windows.Forms.Label FileNameLabel;
        private System.ComponentModel.BackgroundWorker ExportWorker;
    }
}