
namespace SPETS.forms
{
    partial class AdvancedEditorForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(AdvancedEditorForm));
            this.ImportListView = new System.Windows.Forms.ListView();
            this.TextureColumnHeader = new System.Windows.Forms.ColumnHeader();
            this.MeshColumbHeader = new System.Windows.Forms.ColumnHeader();
            this.TexturePreview = new System.Windows.Forms.PictureBox();
            this.numericUpDown1 = new System.Windows.Forms.NumericUpDown();
            this.DistanceLabel = new System.Windows.Forms.Label();
            this.ImportButton = new System.Windows.Forms.Button();
            this.LoadMeshButton = new System.Windows.Forms.Button();
            this.DeleteItemButton = new System.Windows.Forms.Button();
            this.MeshPreview = new System.Windows.Forms.PictureBox();
            this.LoadTextureButton = new System.Windows.Forms.Button();
            this.TextureTooltip = new System.Windows.Forms.ToolTip(this.components);
            this.ClearTextureButton = new System.Windows.Forms.Button();
            this.TextureLabel = new System.Windows.Forms.Label();
            this.MeshPreviewLabel = new System.Windows.Forms.Label();
            this.LeftButton = new System.Windows.Forms.Button();
            this.UpButton = new System.Windows.Forms.Button();
            this.DownButton = new System.Windows.Forms.Button();
            this.RightButton = new System.Windows.Forms.Button();
            this.ZoomInButton = new System.Windows.Forms.Button();
            this.ZoomOutButton = new System.Windows.Forms.Button();
            this.ToolDropdown = new System.Windows.Forms.ComboBox();
            this.ShowWireframeCheckbox = new System.Windows.Forms.CheckBox();
            this.LoadBlueprintButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.TexturePreview)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.MeshPreview)).BeginInit();
            this.SuspendLayout();
            // 
            // ImportListView
            // 
            this.ImportListView.Activation = System.Windows.Forms.ItemActivation.OneClick;
            this.ImportListView.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ImportListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.TextureColumnHeader,
            this.MeshColumbHeader});
            this.ImportListView.FullRowSelect = true;
            this.ImportListView.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
            this.ImportListView.HideSelection = false;
            this.ImportListView.LabelWrap = false;
            this.ImportListView.Location = new System.Drawing.Point(12, 289);
            this.ImportListView.MultiSelect = false;
            this.ImportListView.Name = "ImportListView";
            this.ImportListView.Size = new System.Drawing.Size(540, 176);
            this.ImportListView.TabIndex = 0;
            this.ImportListView.UseCompatibleStateImageBehavior = false;
            this.ImportListView.View = System.Windows.Forms.View.Details;
            this.ImportListView.SelectedIndexChanged += new System.EventHandler(this.ImportListView_SelectedIndexChanged);
            // 
            // TextureColumnHeader
            // 
            this.TextureColumnHeader.Text = "Texture";
            this.TextureColumnHeader.Width = 200;
            // 
            // MeshColumbHeader
            // 
            this.MeshColumbHeader.Text = "Mesh";
            this.MeshColumbHeader.Width = 200;
            // 
            // TexturePreview
            // 
            this.TexturePreview.Location = new System.Drawing.Point(12, 27);
            this.TexturePreview.Name = "TexturePreview";
            this.TexturePreview.Size = new System.Drawing.Size(128, 128);
            this.TexturePreview.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.TexturePreview.TabIndex = 1;
            this.TexturePreview.TabStop = false;
            this.TextureTooltip.SetToolTip(this.TexturePreview, "Decal to place on every face.\r\nLeave blank for none (recommended for large models" +
        ")");
            // 
            // numericUpDown1
            // 
            this.numericUpDown1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.numericUpDown1.Location = new System.Drawing.Point(431, 27);
            this.numericUpDown1.Name = "numericUpDown1";
            this.numericUpDown1.Size = new System.Drawing.Size(122, 23);
            this.numericUpDown1.TabIndex = 2;
            // 
            // DistanceLabel
            // 
            this.DistanceLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.DistanceLabel.AutoSize = true;
            this.DistanceLabel.Location = new System.Drawing.Point(432, 9);
            this.DistanceLabel.Name = "DistanceLabel";
            this.DistanceLabel.Size = new System.Drawing.Size(93, 15);
            this.DistanceLabel.TabIndex = 3;
            this.DistanceLabel.Text = "Texture Distance";
            this.DistanceLabel.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // ImportButton
            // 
            this.ImportButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.ImportButton.Location = new System.Drawing.Point(431, 234);
            this.ImportButton.Name = "ImportButton";
            this.ImportButton.Size = new System.Drawing.Size(122, 49);
            this.ImportButton.TabIndex = 4;
            this.ImportButton.Text = "Import";
            this.ImportButton.UseVisualStyleBackColor = true;
            // 
            // LoadMeshButton
            // 
            this.LoadMeshButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.LoadMeshButton.Location = new System.Drawing.Point(12, 471);
            this.LoadMeshButton.Name = "LoadMeshButton";
            this.LoadMeshButton.Size = new System.Drawing.Size(108, 31);
            this.LoadMeshButton.TabIndex = 5;
            this.LoadMeshButton.Text = "Load Mesh";
            this.LoadMeshButton.UseVisualStyleBackColor = true;
            this.LoadMeshButton.Click += new System.EventHandler(this.LoadMeshButton_Click);
            // 
            // DeleteItemButton
            // 
            this.DeleteItemButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.DeleteItemButton.Location = new System.Drawing.Point(501, 471);
            this.DeleteItemButton.Name = "DeleteItemButton";
            this.DeleteItemButton.Size = new System.Drawing.Size(51, 31);
            this.DeleteItemButton.TabIndex = 7;
            this.DeleteItemButton.Text = "Delete";
            this.DeleteItemButton.UseVisualStyleBackColor = true;
            this.DeleteItemButton.Click += new System.EventHandler(this.DeleteItemButton_Click);
            // 
            // MeshPreview
            // 
            this.MeshPreview.Location = new System.Drawing.Point(147, 27);
            this.MeshPreview.Name = "MeshPreview";
            this.MeshPreview.Size = new System.Drawing.Size(256, 256);
            this.MeshPreview.TabIndex = 8;
            this.MeshPreview.TabStop = false;
            this.MeshPreview.Paint += new System.Windows.Forms.PaintEventHandler(this.MeshPreview_Paint);
            // 
            // LoadTextureButton
            // 
            this.LoadTextureButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.LoadTextureButton.Location = new System.Drawing.Point(126, 471);
            this.LoadTextureButton.Name = "LoadTextureButton";
            this.LoadTextureButton.Size = new System.Drawing.Size(108, 31);
            this.LoadTextureButton.TabIndex = 9;
            this.LoadTextureButton.Text = "Load Texture";
            this.LoadTextureButton.UseVisualStyleBackColor = true;
            this.LoadTextureButton.Click += new System.EventHandler(this.LoadTextureButton_Click);
            // 
            // ClearTextureButton
            // 
            this.ClearTextureButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.ClearTextureButton.Location = new System.Drawing.Point(387, 471);
            this.ClearTextureButton.Name = "ClearTextureButton";
            this.ClearTextureButton.Size = new System.Drawing.Size(108, 31);
            this.ClearTextureButton.TabIndex = 10;
            this.ClearTextureButton.Text = "Clear Texture";
            this.ClearTextureButton.UseVisualStyleBackColor = true;
            this.ClearTextureButton.Click += new System.EventHandler(this.ClearTextureButton_Click);
            // 
            // TextureLabel
            // 
            this.TextureLabel.AutoSize = true;
            this.TextureLabel.Location = new System.Drawing.Point(13, 9);
            this.TextureLabel.Name = "TextureLabel";
            this.TextureLabel.Size = new System.Drawing.Size(45, 15);
            this.TextureLabel.TabIndex = 11;
            this.TextureLabel.Text = "Texture";
            // 
            // MeshPreviewLabel
            // 
            this.MeshPreviewLabel.AutoSize = true;
            this.MeshPreviewLabel.Location = new System.Drawing.Point(147, 9);
            this.MeshPreviewLabel.Name = "MeshPreviewLabel";
            this.MeshPreviewLabel.Size = new System.Drawing.Size(80, 15);
            this.MeshPreviewLabel.TabIndex = 12;
            this.MeshPreviewLabel.Text = "Mesh Preview";
            // 
            // LeftButton
            // 
            this.LeftButton.Image = ((System.Drawing.Image)(resources.GetObject("LeftButton.Image")));
            this.LeftButton.Location = new System.Drawing.Point(13, 209);
            this.LeftButton.Name = "LeftButton";
            this.LeftButton.Size = new System.Drawing.Size(32, 48);
            this.LeftButton.TabIndex = 13;
            this.LeftButton.UseVisualStyleBackColor = true;
            this.LeftButton.Click += new System.EventHandler(this.LeftButton_Click);
            // 
            // UpButton
            // 
            this.UpButton.Image = ((System.Drawing.Image)(resources.GetObject("UpButton.Image")));
            this.UpButton.ImageAlign = System.Drawing.ContentAlignment.TopCenter;
            this.UpButton.Location = new System.Drawing.Point(47, 209);
            this.UpButton.Name = "UpButton";
            this.UpButton.Size = new System.Drawing.Size(56, 23);
            this.UpButton.TabIndex = 14;
            this.UpButton.UseVisualStyleBackColor = true;
            this.UpButton.Click += new System.EventHandler(this.UpButton_Click);
            // 
            // DownButton
            // 
            this.DownButton.Image = ((System.Drawing.Image)(resources.GetObject("DownButton.Image")));
            this.DownButton.ImageAlign = System.Drawing.ContentAlignment.BottomCenter;
            this.DownButton.Location = new System.Drawing.Point(47, 234);
            this.DownButton.Name = "DownButton";
            this.DownButton.Size = new System.Drawing.Size(56, 23);
            this.DownButton.TabIndex = 15;
            this.DownButton.UseVisualStyleBackColor = true;
            this.DownButton.Click += new System.EventHandler(this.DownButton_Click);
            // 
            // RightButton
            // 
            this.RightButton.Image = ((System.Drawing.Image)(resources.GetObject("RightButton.Image")));
            this.RightButton.Location = new System.Drawing.Point(109, 209);
            this.RightButton.Name = "RightButton";
            this.RightButton.Size = new System.Drawing.Size(32, 48);
            this.RightButton.TabIndex = 16;
            this.RightButton.UseVisualStyleBackColor = true;
            this.RightButton.Click += new System.EventHandler(this.RightButton_Click);
            // 
            // ZoomInButton
            // 
            this.ZoomInButton.Image = ((System.Drawing.Image)(resources.GetObject("ZoomInButton.Image")));
            this.ZoomInButton.Location = new System.Drawing.Point(13, 259);
            this.ZoomInButton.Name = "ZoomInButton";
            this.ZoomInButton.Size = new System.Drawing.Size(62, 24);
            this.ZoomInButton.TabIndex = 17;
            this.ZoomInButton.UseVisualStyleBackColor = true;
            this.ZoomInButton.Click += new System.EventHandler(this.ZoomInButton_Click);
            // 
            // ZoomOutButton
            // 
            this.ZoomOutButton.Image = ((System.Drawing.Image)(resources.GetObject("ZoomOutButton.Image")));
            this.ZoomOutButton.Location = new System.Drawing.Point(79, 259);
            this.ZoomOutButton.Name = "ZoomOutButton";
            this.ZoomOutButton.Size = new System.Drawing.Size(62, 24);
            this.ZoomOutButton.TabIndex = 18;
            this.ZoomOutButton.UseVisualStyleBackColor = true;
            this.ZoomOutButton.Click += new System.EventHandler(this.ZoomOutButton_Click);
            // 
            // ToolDropdown
            // 
            this.ToolDropdown.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.ToolDropdown.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.ToolDropdown.FormattingEnabled = true;
            this.ToolDropdown.Items.AddRange(new object[] {
            "Import from OBJ",
            "Export to OBJ",
            "Advanced Import"});
            this.ToolDropdown.Location = new System.Drawing.Point(431, 56);
            this.ToolDropdown.Name = "ToolDropdown";
            this.ToolDropdown.Size = new System.Drawing.Size(122, 23);
            this.ToolDropdown.TabIndex = 19;
            // 
            // ShowWireframeCheckbox
            // 
            this.ShowWireframeCheckbox.AutoSize = true;
            this.ShowWireframeCheckbox.Location = new System.Drawing.Point(13, 184);
            this.ShowWireframeCheckbox.Name = "ShowWireframeCheckbox";
            this.ShowWireframeCheckbox.Size = new System.Drawing.Size(113, 19);
            this.ShowWireframeCheckbox.TabIndex = 20;
            this.ShowWireframeCheckbox.Text = "Show Wireframe";
            this.ShowWireframeCheckbox.UseVisualStyleBackColor = true;
            this.ShowWireframeCheckbox.CheckedChanged += new System.EventHandler(this.ShowWireframeCheckbox_CheckedChanged);
            // 
            // LoadBlueprintButton
            // 
            this.LoadBlueprintButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.LoadBlueprintButton.Location = new System.Drawing.Point(240, 471);
            this.LoadBlueprintButton.Name = "LoadBlueprintButton";
            this.LoadBlueprintButton.Size = new System.Drawing.Size(108, 31);
            this.LoadBlueprintButton.TabIndex = 21;
            this.LoadBlueprintButton.Text = "Load Blueprint";
            this.LoadBlueprintButton.UseVisualStyleBackColor = true;
            this.LoadBlueprintButton.Click += new System.EventHandler(this.LoadBlueprintButton_Click);
            // 
            // AdvancedEditorForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(565, 514);
            this.Controls.Add(this.LoadBlueprintButton);
            this.Controls.Add(this.ShowWireframeCheckbox);
            this.Controls.Add(this.ToolDropdown);
            this.Controls.Add(this.ZoomOutButton);
            this.Controls.Add(this.ZoomInButton);
            this.Controls.Add(this.RightButton);
            this.Controls.Add(this.DownButton);
            this.Controls.Add(this.UpButton);
            this.Controls.Add(this.LeftButton);
            this.Controls.Add(this.MeshPreviewLabel);
            this.Controls.Add(this.TextureLabel);
            this.Controls.Add(this.ClearTextureButton);
            this.Controls.Add(this.LoadTextureButton);
            this.Controls.Add(this.MeshPreview);
            this.Controls.Add(this.DeleteItemButton);
            this.Controls.Add(this.LoadMeshButton);
            this.Controls.Add(this.ImportButton);
            this.Controls.Add(this.DistanceLabel);
            this.Controls.Add(this.numericUpDown1);
            this.Controls.Add(this.TexturePreview);
            this.Controls.Add(this.ImportListView);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "AdvancedEditorForm";
            this.Text = "Advanced Editor";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.AdvancedImportForm_FormClosing);
            ((System.ComponentModel.ISupportInitialize)(this.TexturePreview)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.MeshPreview)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListView ImportListView;
        private System.Windows.Forms.ColumnHeader TextureColumnHeader;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.NumericUpDown numericUpDown1;
        private System.Windows.Forms.Label DistanceLabel;
        private System.Windows.Forms.PictureBox TexturePreview;
        private System.Windows.Forms.Button ImportButton;
        private System.Windows.Forms.Button LoadMeshButton;
        private System.Windows.Forms.Button AddItemButton;
        private System.Windows.Forms.Button DeleteItemButton;
        private System.Windows.Forms.PictureBox MeshPreview;
        private System.Windows.Forms.Button LoadTextureButton;
        private System.Windows.Forms.ColumnHeader MeshColumbHeader;
        private System.Windows.Forms.ToolTip TextureTooltip;
        private System.Windows.Forms.Button ClearTextureButton;
        private System.Windows.Forms.Label TextureLabel;
        private System.Windows.Forms.Label MeshPreviewLabel;
        private System.Windows.Forms.Button LeftButton;
        private System.Windows.Forms.Button UpButton;
        private System.Windows.Forms.Button DownButton;
        private System.Windows.Forms.Button RightButton;
        private System.Windows.Forms.Button ZoomInButton;
        private System.Windows.Forms.Button ZoomOutButton;
        private System.Windows.Forms.ComboBox ToolDropdown;
        private System.Windows.Forms.CheckBox ShowWireframeCheckbox;
        private System.Windows.Forms.Button LoadBlueprintButton;
    }
}