
namespace SPETS.forms
{
    partial class TerrainEditorForm
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
            this.TerrainPreview = new SharpGL.SceneControl();
            this.HeightmapBox = new System.Windows.Forms.PictureBox();
            this.RotateClockwiseButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.TerrainPreview)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.HeightmapBox)).BeginInit();
            this.SuspendLayout();
            // 
            // TerrainPreview
            // 
            this.TerrainPreview.DrawFPS = false;
            this.TerrainPreview.Location = new System.Drawing.Point(13, 12);
            this.TerrainPreview.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.TerrainPreview.Name = "TerrainPreview";
            this.TerrainPreview.OpenGLVersion = SharpGL.Version.OpenGLVersion.OpenGL2_1;
            this.TerrainPreview.RenderContextType = SharpGL.RenderContextType.DIBSection;
            this.TerrainPreview.RenderTrigger = SharpGL.RenderTrigger.TimerBased;
            this.TerrainPreview.Size = new System.Drawing.Size(511, 513);
            this.TerrainPreview.TabIndex = 3;
            this.TerrainPreview.OpenGLDraw += new SharpGL.RenderEventHandler(this.TerrainPreview_OpenGLDraw);
            // 
            // HeightmapBox
            // 
            this.HeightmapBox.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.HeightmapBox.Location = new System.Drawing.Point(531, 12);
            this.HeightmapBox.Name = "HeightmapBox";
            this.HeightmapBox.Size = new System.Drawing.Size(513, 513);
            this.HeightmapBox.TabIndex = 1;
            this.HeightmapBox.TabStop = false;
            // 
            // RotateClockwiseButton
            // 
            this.RotateClockwiseButton.Image = global::SPETS.Properties.Resources.icons8_rotate_right_26;
            this.RotateClockwiseButton.Location = new System.Drawing.Point(531, 531);
            this.RotateClockwiseButton.Name = "RotateClockwiseButton";
            this.RotateClockwiseButton.Size = new System.Drawing.Size(42, 42);
            this.RotateClockwiseButton.TabIndex = 2;
            this.RotateClockwiseButton.UseVisualStyleBackColor = true;
            this.RotateClockwiseButton.Click += new System.EventHandler(this.RotateClockwiseButton_Click);
            // 
            // TerrainEditorForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1056, 585);
            this.Controls.Add(this.TerrainPreview);
            this.Controls.Add(this.RotateClockwiseButton);
            this.Controls.Add(this.HeightmapBox);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "TerrainEditorForm";
            this.Text = "Terrain Editor";
            this.Load += new System.EventHandler(this.TerrainEditorForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.TerrainPreview)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.HeightmapBox)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.PictureBox HeightmapBox;
        private System.Windows.Forms.Button RotateClockwiseButton;
        private SharpGL.SceneControl TerrainPreview;
    }
}