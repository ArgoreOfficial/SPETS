
namespace SPETS.forms
{
    partial class ImportForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ImportForm));
            this.FileNameLabel = new System.Windows.Forms.Label();
            this.FileSizeLabel = new System.Windows.Forms.Label();
            this.ImportButton = new System.Windows.Forms.Button();
            this.FactionsCombobox = new System.Windows.Forms.ComboBox();
            this.ImportingProgress = new System.Windows.Forms.ProgressBar();
            this.ImportWorker = new System.ComponentModel.BackgroundWorker();
            this.SuspendLayout();
            // 
            // FileNameLabel
            // 
            this.FileNameLabel.AutoSize = true;
            this.FileNameLabel.Location = new System.Drawing.Point(12, 9);
            this.FileNameLabel.Name = "FileNameLabel";
            this.FileNameLabel.Size = new System.Drawing.Size(57, 15);
            this.FileNameLabel.TabIndex = 0;
            this.FileNameLabel.Text = "FileName";
            // 
            // FileSizeLabel
            // 
            this.FileSizeLabel.AutoSize = true;
            this.FileSizeLabel.Location = new System.Drawing.Point(12, 24);
            this.FileSizeLabel.Name = "FileSizeLabel";
            this.FileSizeLabel.Size = new System.Drawing.Size(76, 15);
            this.FileSizeLabel.TabIndex = 1;
            this.FileSizeLabel.Text = "FileSize Bytes";
            // 
            // ImportButton
            // 
            this.ImportButton.Location = new System.Drawing.Point(139, 42);
            this.ImportButton.Name = "ImportButton";
            this.ImportButton.Size = new System.Drawing.Size(121, 23);
            this.ImportButton.TabIndex = 5;
            this.ImportButton.Text = "Import";
            this.ImportButton.UseVisualStyleBackColor = true;
            this.ImportButton.Click += new System.EventHandler(this.ImportButton_Click);
            // 
            // FactionsCombobox
            // 
            this.FactionsCombobox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.FactionsCombobox.FormattingEnabled = true;
            this.FactionsCombobox.Location = new System.Drawing.Point(12, 42);
            this.FactionsCombobox.Name = "FactionsCombobox";
            this.FactionsCombobox.Size = new System.Drawing.Size(121, 23);
            this.FactionsCombobox.TabIndex = 7;
            // 
            // ImportingProgress
            // 
            this.ImportingProgress.Location = new System.Drawing.Point(12, 71);
            this.ImportingProgress.Name = "ImportingProgress";
            this.ImportingProgress.Size = new System.Drawing.Size(248, 23);
            this.ImportingProgress.TabIndex = 12;
            // 
            // ImportWorker
            // 
            this.ImportWorker.WorkerReportsProgress = true;
            this.ImportWorker.DoWork += new System.ComponentModel.DoWorkEventHandler(this.ImportWorker_DoWork);
            this.ImportWorker.ProgressChanged += new System.ComponentModel.ProgressChangedEventHandler(this.ImportWorker_ProgressChanged);
            // 
            // ImportForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(272, 106);
            this.Controls.Add(this.ImportingProgress);
            this.Controls.Add(this.FactionsCombobox);
            this.Controls.Add(this.ImportButton);
            this.Controls.Add(this.FileSizeLabel);
            this.Controls.Add(this.FileNameLabel);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "ImportForm";
            this.Text = "Import Model";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.ImportForm_FormClosing);
            this.Load += new System.EventHandler(this.ImportForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label FileNameLabel;
        private System.Windows.Forms.Label FileSizeLabel;
        private System.Windows.Forms.Button ImportButton;
        private System.Windows.Forms.ComboBox FactionsCombobox;
        private System.Windows.Forms.ProgressBar ImportingProgress;
        private System.ComponentModel.BackgroundWorker ImportWorker;
    }
}