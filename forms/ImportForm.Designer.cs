
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
            this.PolygonsLabel = new System.Windows.Forms.Label();
            this.SharedPointsLabel = new System.Windows.Forms.Label();
            this.PolygonProgress = new System.Windows.Forms.ProgressBar();
            this.SharedPointsProgress = new System.Windows.Forms.ProgressBar();
            this.ThicknessMapProgress = new System.Windows.Forms.ProgressBar();
            this.ThicknessMapLabel = new System.Windows.Forms.Label();
            this.faceWorker = new System.ComponentModel.BackgroundWorker();
            this.sharedPointWorker = new System.ComponentModel.BackgroundWorker();
            this.thicknessWorker = new System.ComponentModel.BackgroundWorker();
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
            // PolygonsLabel
            // 
            this.PolygonsLabel.AutoSize = true;
            this.PolygonsLabel.Location = new System.Drawing.Point(12, 101);
            this.PolygonsLabel.Name = "PolygonsLabel";
            this.PolygonsLabel.Size = new System.Drawing.Size(56, 15);
            this.PolygonsLabel.TabIndex = 10;
            this.PolygonsLabel.Text = "Polygons";
            // 
            // SharedPointsLabel
            // 
            this.SharedPointsLabel.AutoSize = true;
            this.SharedPointsLabel.Location = new System.Drawing.Point(12, 145);
            this.SharedPointsLabel.Name = "SharedPointsLabel";
            this.SharedPointsLabel.Size = new System.Drawing.Size(76, 15);
            this.SharedPointsLabel.TabIndex = 11;
            this.SharedPointsLabel.Text = "SharedPoints";
            // 
            // PolygonProgress
            // 
            this.PolygonProgress.Location = new System.Drawing.Point(12, 119);
            this.PolygonProgress.Name = "PolygonProgress";
            this.PolygonProgress.Size = new System.Drawing.Size(248, 23);
            this.PolygonProgress.TabIndex = 12;
            // 
            // SharedPointsProgress
            // 
            this.SharedPointsProgress.Location = new System.Drawing.Point(12, 163);
            this.SharedPointsProgress.Name = "SharedPointsProgress";
            this.SharedPointsProgress.Size = new System.Drawing.Size(248, 23);
            this.SharedPointsProgress.TabIndex = 13;
            // 
            // ThicknessMapProgress
            // 
            this.ThicknessMapProgress.Location = new System.Drawing.Point(12, 207);
            this.ThicknessMapProgress.Name = "ThicknessMapProgress";
            this.ThicknessMapProgress.Size = new System.Drawing.Size(248, 23);
            this.ThicknessMapProgress.TabIndex = 15;
            // 
            // ThicknessMapLabel
            // 
            this.ThicknessMapLabel.AutoSize = true;
            this.ThicknessMapLabel.Location = new System.Drawing.Point(12, 189);
            this.ThicknessMapLabel.Name = "ThicknessMapLabel";
            this.ThicknessMapLabel.Size = new System.Drawing.Size(82, 15);
            this.ThicknessMapLabel.TabIndex = 14;
            this.ThicknessMapLabel.Text = "ThicknessMap";
            // 
            // faceWorker
            // 
            this.faceWorker.WorkerReportsProgress = true;
            this.faceWorker.DoWork += new System.ComponentModel.DoWorkEventHandler(this.faceWorker_DoWork);
            this.faceWorker.ProgressChanged += new System.ComponentModel.ProgressChangedEventHandler(this.faceWorker_ProgressChanged);
            this.faceWorker.RunWorkerCompleted += new System.ComponentModel.RunWorkerCompletedEventHandler(this.faceWorker_RunWorkerCompleted);
            // 
            // sharedPointWorker
            // 
            this.sharedPointWorker.WorkerReportsProgress = true;
            this.sharedPointWorker.DoWork += new System.ComponentModel.DoWorkEventHandler(this.sharedPointWorker_DoWork);
            this.sharedPointWorker.ProgressChanged += new System.ComponentModel.ProgressChangedEventHandler(this.sharedPointWorker_ProgressChanged);
            this.sharedPointWorker.RunWorkerCompleted += new System.ComponentModel.RunWorkerCompletedEventHandler(this.sharedPointWorker_RunWorkerCompleted);
            // 
            // thicknessWorker
            // 
            this.thicknessWorker.WorkerReportsProgress = true;
            this.thicknessWorker.DoWork += new System.ComponentModel.DoWorkEventHandler(this.thicknessWorker_DoWork);
            this.thicknessWorker.ProgressChanged += new System.ComponentModel.ProgressChangedEventHandler(this.thicknessWorker_ProgressChanged);
            this.thicknessWorker.RunWorkerCompleted += new System.ComponentModel.RunWorkerCompletedEventHandler(this.thicknessWorker_RunWorkerCompleted);
            // 
            // ImportForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(272, 242);
            this.Controls.Add(this.ThicknessMapProgress);
            this.Controls.Add(this.ThicknessMapLabel);
            this.Controls.Add(this.SharedPointsProgress);
            this.Controls.Add(this.PolygonProgress);
            this.Controls.Add(this.SharedPointsLabel);
            this.Controls.Add(this.PolygonsLabel);
            this.Controls.Add(this.FactionsCombobox);
            this.Controls.Add(this.ImportButton);
            this.Controls.Add(this.FileSizeLabel);
            this.Controls.Add(this.FileNameLabel);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "ImportForm";
            this.Text = "Import Model";
            this.Load += new System.EventHandler(this.ImportForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label FileNameLabel;
        private System.Windows.Forms.Label FileSizeLabel;
        private System.Windows.Forms.Button ImportButton;
        private System.Windows.Forms.ComboBox FactionsCombobox;
        private System.Windows.Forms.Label PolygonsLabel;
        private System.Windows.Forms.Label SharedPointsLabel;
        private System.Windows.Forms.ProgressBar PolygonProgress;
        private System.Windows.Forms.ProgressBar SharedPointsProgress;
        private System.Windows.Forms.ProgressBar ThicknessMapProgress;
        private System.Windows.Forms.Label ThicknessMapLabel;
        private System.ComponentModel.BackgroundWorker faceWorker;
        private System.ComponentModel.BackgroundWorker sharedPointWorker;
        private System.ComponentModel.BackgroundWorker thicknessWorker;
    }
}