
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
            this.ItemTypeColumnHeader = new System.Windows.Forms.ColumnHeader();
            this.MeshColumbHeader = new System.Windows.Forms.ColumnHeader();
            this.TexturePreview = new System.Windows.Forms.PictureBox();
            this.DecalDistanceNumeric = new System.Windows.Forms.NumericUpDown();
            this.DecalDistanceLabel = new System.Windows.Forms.Label();
            this.ImportButton = new System.Windows.Forms.Button();
            this.LoadMeshButton = new System.Windows.Forms.Button();
            this.DeleteItemButton = new System.Windows.Forms.Button();
            this.MeshPreview = new System.Windows.Forms.PictureBox();
            this.LoadTextureButton = new System.Windows.Forms.Button();
            this.TextureTooltip = new System.Windows.Forms.ToolTip(this.components);
            this.ClearTextureButton = new System.Windows.Forms.Button();
            this.ZoomInButton = new System.Windows.Forms.Button();
            this.ZoomOutButton = new System.Windows.Forms.Button();
            this.FactionsCombobox = new System.Windows.Forms.ComboBox();
            this.ShowWireframeCheckbox = new System.Windows.Forms.CheckBox();
            this.LoadBlueprintButton = new System.Windows.Forms.Button();
            this.PropertiesTabControl = new System.Windows.Forms.TabControl();
            this.DecalPage = new System.Windows.Forms.TabPage();
            this.DecalSizeNumeric = new System.Windows.Forms.NumericUpDown();
            this.DecalSizeLabel = new System.Windows.Forms.Label();
            this.PropertiesPage = new System.Windows.Forms.TabPage();
            this.label1 = new System.Windows.Forms.Label();
            this.ShowVerticesCheckbox = new System.Windows.Forms.CheckBox();
            this.ShowFacesCheckbox = new System.Windows.Forms.CheckBox();
            this.BFCullingCheckbox = new System.Windows.Forms.CheckBox();
            this.MeshPreviewTimer = new System.Windows.Forms.Timer(this.components);
            this.ZoomInTimer = new System.Windows.Forms.Timer(this.components);
            this.ZoomOutTimer = new System.Windows.Forms.Timer(this.components);
            this.LoadPresetButton = new System.Windows.Forms.Button();
            this.SavePresetButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.TexturePreview)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.DecalDistanceNumeric)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.MeshPreview)).BeginInit();
            this.PropertiesTabControl.SuspendLayout();
            this.DecalPage.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.DecalSizeNumeric)).BeginInit();
            this.PropertiesPage.SuspendLayout();
            this.SuspendLayout();
            // 
            // ImportListView
            // 
            this.ImportListView.Activation = System.Windows.Forms.ItemActivation.OneClick;
            this.ImportListView.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ImportListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.ItemTypeColumnHeader,
            this.MeshColumbHeader});
            this.ImportListView.FullRowSelect = true;
            this.ImportListView.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
            this.ImportListView.HideSelection = false;
            this.ImportListView.LabelWrap = false;
            this.ImportListView.Location = new System.Drawing.Point(12, 274);
            this.ImportListView.Name = "ImportListView";
            this.ImportListView.Size = new System.Drawing.Size(394, 191);
            this.ImportListView.TabIndex = 0;
            this.ImportListView.UseCompatibleStateImageBehavior = false;
            this.ImportListView.View = System.Windows.Forms.View.Details;
            this.ImportListView.SelectedIndexChanged += new System.EventHandler(this.ImportListView_SelectedIndexChanged);
            // 
            // ItemTypeColumnHeader
            // 
            this.ItemTypeColumnHeader.Text = "Type";
            this.ItemTypeColumnHeader.Width = 100;
            // 
            // MeshColumbHeader
            // 
            this.MeshColumbHeader.Text = "Mesh";
            this.MeshColumbHeader.Width = 290;
            // 
            // TexturePreview
            // 
            this.TexturePreview.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.TexturePreview.Location = new System.Drawing.Point(6, 10);
            this.TexturePreview.Name = "TexturePreview";
            this.TexturePreview.Size = new System.Drawing.Size(128, 128);
            this.TexturePreview.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.TexturePreview.TabIndex = 1;
            this.TexturePreview.TabStop = false;
            this.TextureTooltip.SetToolTip(this.TexturePreview, "Decal to place on every face.\r\nUnavailable for imported blueprints.");
            // 
            // DecalDistanceNumeric
            // 
            this.DecalDistanceNumeric.DecimalPlaces = 3;
            this.DecalDistanceNumeric.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.DecalDistanceNumeric.Location = new System.Drawing.Point(64, 144);
            this.DecalDistanceNumeric.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.DecalDistanceNumeric.Name = "DecalDistanceNumeric";
            this.DecalDistanceNumeric.Size = new System.Drawing.Size(70, 23);
            this.DecalDistanceNumeric.TabIndex = 2;
            this.DecalDistanceNumeric.Value = new decimal(new int[] {
            75,
            0,
            0,
            131072});
            this.DecalDistanceNumeric.ValueChanged += new System.EventHandler(this.DecalDistanceNumeric_ValueChanged);
            // 
            // DecalDistanceLabel
            // 
            this.DecalDistanceLabel.AutoSize = true;
            this.DecalDistanceLabel.Location = new System.Drawing.Point(6, 146);
            this.DecalDistanceLabel.Name = "DecalDistanceLabel";
            this.DecalDistanceLabel.Size = new System.Drawing.Size(52, 15);
            this.DecalDistanceLabel.TabIndex = 3;
            this.DecalDistanceLabel.Text = "Distance";
            this.DecalDistanceLabel.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // ImportButton
            // 
            this.ImportButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.ImportButton.Location = new System.Drawing.Point(524, 475);
            this.ImportButton.Name = "ImportButton";
            this.ImportButton.Size = new System.Drawing.Size(85, 23);
            this.ImportButton.TabIndex = 4;
            this.ImportButton.Text = "Import";
            this.ImportButton.UseVisualStyleBackColor = true;
            this.ImportButton.Click += new System.EventHandler(this.ImportButton_Click);
            // 
            // LoadMeshButton
            // 
            this.LoadMeshButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.LoadMeshButton.Location = new System.Drawing.Point(12, 471);
            this.LoadMeshButton.Name = "LoadMeshButton";
            this.LoadMeshButton.Size = new System.Drawing.Size(97, 31);
            this.LoadMeshButton.TabIndex = 5;
            this.LoadMeshButton.Text = "Load Mesh";
            this.LoadMeshButton.UseVisualStyleBackColor = true;
            this.LoadMeshButton.Click += new System.EventHandler(this.LoadMeshButton_Click);
            // 
            // DeleteItemButton
            // 
            this.DeleteItemButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.DeleteItemButton.Location = new System.Drawing.Point(357, 471);
            this.DeleteItemButton.Name = "DeleteItemButton";
            this.DeleteItemButton.Size = new System.Drawing.Size(51, 31);
            this.DeleteItemButton.TabIndex = 7;
            this.DeleteItemButton.Text = "Delete";
            this.DeleteItemButton.UseVisualStyleBackColor = true;
            this.DeleteItemButton.Click += new System.EventHandler(this.DeleteItemButton_Click);
            // 
            // MeshPreview
            // 
            this.MeshPreview.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.MeshPreview.Cursor = System.Windows.Forms.Cursors.SizeAll;
            this.MeshPreview.Location = new System.Drawing.Point(147, 12);
            this.MeshPreview.Name = "MeshPreview";
            this.MeshPreview.Size = new System.Drawing.Size(256, 256);
            this.MeshPreview.TabIndex = 8;
            this.MeshPreview.TabStop = false;
            this.MeshPreview.Paint += new System.Windows.Forms.PaintEventHandler(this.MeshPreview_Paint);
            this.MeshPreview.MouseDown += new System.Windows.Forms.MouseEventHandler(this.MeshPreview_MouseDown);
            this.MeshPreview.MouseUp += new System.Windows.Forms.MouseEventHandler(this.MeshPreview_MouseUp);
            // 
            // LoadTextureButton
            // 
            this.LoadTextureButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.LoadTextureButton.Cursor = System.Windows.Forms.Cursors.Default;
            this.LoadTextureButton.Location = new System.Drawing.Point(140, 10);
            this.LoadTextureButton.Name = "LoadTextureButton";
            this.LoadTextureButton.Size = new System.Drawing.Size(46, 31);
            this.LoadTextureButton.TabIndex = 9;
            this.LoadTextureButton.Text = "Load";
            this.LoadTextureButton.UseVisualStyleBackColor = true;
            this.LoadTextureButton.Click += new System.EventHandler(this.LoadTextureButton_Click);
            // 
            // ClearTextureButton
            // 
            this.ClearTextureButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.ClearTextureButton.Location = new System.Drawing.Point(140, 47);
            this.ClearTextureButton.Name = "ClearTextureButton";
            this.ClearTextureButton.Size = new System.Drawing.Size(46, 31);
            this.ClearTextureButton.TabIndex = 10;
            this.ClearTextureButton.Text = "Clear";
            this.ClearTextureButton.UseVisualStyleBackColor = true;
            this.ClearTextureButton.Click += new System.EventHandler(this.ClearTextureButton_Click);
            // 
            // ZoomInButton
            // 
            this.ZoomInButton.Image = ((System.Drawing.Image)(resources.GetObject("ZoomInButton.Image")));
            this.ZoomInButton.Location = new System.Drawing.Point(12, 244);
            this.ZoomInButton.Name = "ZoomInButton";
            this.ZoomInButton.Size = new System.Drawing.Size(62, 24);
            this.ZoomInButton.TabIndex = 17;
            this.ZoomInButton.UseVisualStyleBackColor = true;
            this.ZoomInButton.MouseDown += new System.Windows.Forms.MouseEventHandler(this.ZoomInButton_MouseDown);
            this.ZoomInButton.MouseUp += new System.Windows.Forms.MouseEventHandler(this.ZoomInButton_MouseUp);
            // 
            // ZoomOutButton
            // 
            this.ZoomOutButton.Image = ((System.Drawing.Image)(resources.GetObject("ZoomOutButton.Image")));
            this.ZoomOutButton.Location = new System.Drawing.Point(74, 244);
            this.ZoomOutButton.Name = "ZoomOutButton";
            this.ZoomOutButton.Size = new System.Drawing.Size(62, 24);
            this.ZoomOutButton.TabIndex = 18;
            this.ZoomOutButton.UseVisualStyleBackColor = true;
            this.ZoomOutButton.MouseDown += new System.Windows.Forms.MouseEventHandler(this.ZoomOutButton_MouseDown);
            this.ZoomOutButton.MouseUp += new System.Windows.Forms.MouseEventHandler(this.ZoomOutButton_MouseUp);
            // 
            // FactionsCombobox
            // 
            this.FactionsCombobox.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.FactionsCombobox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.FactionsCombobox.FormattingEnabled = true;
            this.FactionsCombobox.Location = new System.Drawing.Point(418, 475);
            this.FactionsCombobox.Name = "FactionsCombobox";
            this.FactionsCombobox.Size = new System.Drawing.Size(100, 23);
            this.FactionsCombobox.TabIndex = 19;
            // 
            // ShowWireframeCheckbox
            // 
            this.ShowWireframeCheckbox.AutoSize = true;
            this.ShowWireframeCheckbox.Checked = true;
            this.ShowWireframeCheckbox.CheckState = System.Windows.Forms.CheckState.Checked;
            this.ShowWireframeCheckbox.Location = new System.Drawing.Point(12, 169);
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
            this.LoadBlueprintButton.Location = new System.Drawing.Point(115, 471);
            this.LoadBlueprintButton.Name = "LoadBlueprintButton";
            this.LoadBlueprintButton.Size = new System.Drawing.Size(97, 31);
            this.LoadBlueprintButton.TabIndex = 21;
            this.LoadBlueprintButton.Text = "Load Blueprint";
            this.LoadBlueprintButton.UseVisualStyleBackColor = true;
            this.LoadBlueprintButton.Click += new System.EventHandler(this.LoadBlueprintButton_Click);
            // 
            // PropertiesTabControl
            // 
            this.PropertiesTabControl.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.PropertiesTabControl.Controls.Add(this.DecalPage);
            this.PropertiesTabControl.Controls.Add(this.PropertiesPage);
            this.PropertiesTabControl.Location = new System.Drawing.Point(409, 12);
            this.PropertiesTabControl.Name = "PropertiesTabControl";
            this.PropertiesTabControl.SelectedIndex = 0;
            this.PropertiesTabControl.Size = new System.Drawing.Size(200, 453);
            this.PropertiesTabControl.TabIndex = 22;
            // 
            // DecalPage
            // 
            this.DecalPage.Controls.Add(this.DecalSizeNumeric);
            this.DecalPage.Controls.Add(this.DecalSizeLabel);
            this.DecalPage.Controls.Add(this.TexturePreview);
            this.DecalPage.Controls.Add(this.LoadTextureButton);
            this.DecalPage.Controls.Add(this.ClearTextureButton);
            this.DecalPage.Controls.Add(this.DecalDistanceLabel);
            this.DecalPage.Controls.Add(this.DecalDistanceNumeric);
            this.DecalPage.Location = new System.Drawing.Point(4, 24);
            this.DecalPage.Name = "DecalPage";
            this.DecalPage.Padding = new System.Windows.Forms.Padding(3);
            this.DecalPage.Size = new System.Drawing.Size(192, 425);
            this.DecalPage.TabIndex = 1;
            this.DecalPage.Text = "Decal";
            this.DecalPage.UseVisualStyleBackColor = true;
            // 
            // DecalSizeNumeric
            // 
            this.DecalSizeNumeric.DecimalPlaces = 3;
            this.DecalSizeNumeric.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.DecalSizeNumeric.Location = new System.Drawing.Point(64, 173);
            this.DecalSizeNumeric.Maximum = new decimal(new int[] {
            4,
            0,
            0,
            0});
            this.DecalSizeNumeric.Name = "DecalSizeNumeric";
            this.DecalSizeNumeric.Size = new System.Drawing.Size(70, 23);
            this.DecalSizeNumeric.TabIndex = 13;
            this.DecalSizeNumeric.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.DecalSizeNumeric.ValueChanged += new System.EventHandler(this.DecalSizeNumeric_ValueChanged);
            // 
            // DecalSizeLabel
            // 
            this.DecalSizeLabel.AutoSize = true;
            this.DecalSizeLabel.Location = new System.Drawing.Point(6, 175);
            this.DecalSizeLabel.Name = "DecalSizeLabel";
            this.DecalSizeLabel.Size = new System.Drawing.Size(27, 15);
            this.DecalSizeLabel.TabIndex = 12;
            this.DecalSizeLabel.Text = "Size";
            this.DecalSizeLabel.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // PropertiesPage
            // 
            this.PropertiesPage.Controls.Add(this.label1);
            this.PropertiesPage.Location = new System.Drawing.Point(4, 24);
            this.PropertiesPage.Name = "PropertiesPage";
            this.PropertiesPage.Padding = new System.Windows.Forms.Padding(3);
            this.PropertiesPage.Size = new System.Drawing.Size(192, 425);
            this.PropertiesPage.TabIndex = 0;
            this.PropertiesPage.Text = "Properties";
            this.PropertiesPage.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(62, 78);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(73, 15);
            this.label1.TabIndex = 0;
            this.label1.Text = "To Be Added";
            // 
            // ShowVerticesCheckbox
            // 
            this.ShowVerticesCheckbox.AutoSize = true;
            this.ShowVerticesCheckbox.Location = new System.Drawing.Point(12, 194);
            this.ShowVerticesCheckbox.Name = "ShowVerticesCheckbox";
            this.ShowVerticesCheckbox.Size = new System.Drawing.Size(98, 19);
            this.ShowVerticesCheckbox.TabIndex = 23;
            this.ShowVerticesCheckbox.Text = "Show Vertices";
            this.ShowVerticesCheckbox.UseVisualStyleBackColor = true;
            this.ShowVerticesCheckbox.CheckedChanged += new System.EventHandler(this.ShowVerticesCheckbox_CheckedChanged);
            // 
            // ShowFacesCheckbox
            // 
            this.ShowFacesCheckbox.AutoSize = true;
            this.ShowFacesCheckbox.Checked = true;
            this.ShowFacesCheckbox.CheckState = System.Windows.Forms.CheckState.Checked;
            this.ShowFacesCheckbox.Location = new System.Drawing.Point(12, 144);
            this.ShowFacesCheckbox.Name = "ShowFacesCheckbox";
            this.ShowFacesCheckbox.Size = new System.Drawing.Size(87, 19);
            this.ShowFacesCheckbox.TabIndex = 24;
            this.ShowFacesCheckbox.Text = "Show Faces";
            this.ShowFacesCheckbox.UseVisualStyleBackColor = true;
            this.ShowFacesCheckbox.CheckedChanged += new System.EventHandler(this.ShowFacesCheckbox_CheckedChanged);
            // 
            // BFCullingCheckbox
            // 
            this.BFCullingCheckbox.AutoSize = true;
            this.BFCullingCheckbox.Location = new System.Drawing.Point(12, 219);
            this.BFCullingCheckbox.Name = "BFCullingCheckbox";
            this.BFCullingCheckbox.Size = new System.Drawing.Size(114, 19);
            this.BFCullingCheckbox.TabIndex = 25;
            this.BFCullingCheckbox.Text = "Backface Culling";
            this.BFCullingCheckbox.UseVisualStyleBackColor = true;
            this.BFCullingCheckbox.CheckedChanged += new System.EventHandler(this.BFCullingCheckbox_CheckedChanged);
            // 
            // MeshPreviewTimer
            // 
            this.MeshPreviewTimer.Interval = 1;
            this.MeshPreviewTimer.Tick += new System.EventHandler(this.MeshPreviewTimer_Tick);
            // 
            // ZoomInTimer
            // 
            this.ZoomInTimer.Interval = 5;
            this.ZoomInTimer.Tick += new System.EventHandler(this.ZoomInTimer_Tick);
            // 
            // ZoomOutTimer
            // 
            this.ZoomOutTimer.Interval = 5;
            this.ZoomOutTimer.Tick += new System.EventHandler(this.ZoomOutTimer_Tick);
            // 
            // LoadPresetButton
            // 
            this.LoadPresetButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.LoadPresetButton.Location = new System.Drawing.Point(12, 12);
            this.LoadPresetButton.Name = "LoadPresetButton";
            this.LoadPresetButton.Size = new System.Drawing.Size(129, 31);
            this.LoadPresetButton.TabIndex = 26;
            this.LoadPresetButton.Text = "Load Preset";
            this.LoadPresetButton.UseVisualStyleBackColor = true;
            this.LoadPresetButton.Click += new System.EventHandler(this.LoadPresetButton_Click);
            // 
            // SavePresetButton
            // 
            this.SavePresetButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.SavePresetButton.Location = new System.Drawing.Point(12, 49);
            this.SavePresetButton.Name = "SavePresetButton";
            this.SavePresetButton.Size = new System.Drawing.Size(129, 31);
            this.SavePresetButton.TabIndex = 27;
            this.SavePresetButton.Text = "Save Preset";
            this.SavePresetButton.UseVisualStyleBackColor = true;
            this.SavePresetButton.Click += new System.EventHandler(this.SavePresetButton_Click);
            // 
            // AdvancedEditorForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(621, 514);
            this.Controls.Add(this.SavePresetButton);
            this.Controls.Add(this.LoadPresetButton);
            this.Controls.Add(this.BFCullingCheckbox);
            this.Controls.Add(this.ShowFacesCheckbox);
            this.Controls.Add(this.ShowVerticesCheckbox);
            this.Controls.Add(this.PropertiesTabControl);
            this.Controls.Add(this.LoadBlueprintButton);
            this.Controls.Add(this.ShowWireframeCheckbox);
            this.Controls.Add(this.FactionsCombobox);
            this.Controls.Add(this.ZoomOutButton);
            this.Controls.Add(this.ZoomInButton);
            this.Controls.Add(this.MeshPreview);
            this.Controls.Add(this.DeleteItemButton);
            this.Controls.Add(this.LoadMeshButton);
            this.Controls.Add(this.ImportButton);
            this.Controls.Add(this.ImportListView);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "AdvancedEditorForm";
            this.Text = "Advanced Editor (Experimental)";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.AdvancedImportForm_FormClosing);
            this.Load += new System.EventHandler(this.AdvancedEditorForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.TexturePreview)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.DecalDistanceNumeric)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.MeshPreview)).EndInit();
            this.PropertiesTabControl.ResumeLayout(false);
            this.DecalPage.ResumeLayout(false);
            this.DecalPage.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.DecalSizeNumeric)).EndInit();
            this.PropertiesPage.ResumeLayout(false);
            this.PropertiesPage.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListView ImportListView;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.NumericUpDown DecalDistanceNumeric;
        private System.Windows.Forms.Label DecalDistanceLabel;
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
        private System.Windows.Forms.Button ZoomInButton;
        private System.Windows.Forms.Button ZoomOutButton;
        private System.Windows.Forms.ComboBox FactionsCombobox;
        private System.Windows.Forms.CheckBox ShowWireframeCheckbox;
        private System.Windows.Forms.Button LoadBlueprintButton;
        private System.Windows.Forms.TabControl PropertiesTabControl;
        private System.Windows.Forms.TabPage PropertiesPage;
        private System.Windows.Forms.TabPage DecalPage;
        private System.Windows.Forms.ColumnHeader ItemTypeColumnHeader;
        private System.Windows.Forms.CheckBox ShowVerticesCheckbox;
        private System.Windows.Forms.CheckBox ShowFacesCheckbox;
        private System.Windows.Forms.CheckBox BFCullingCheckbox;
        private System.Windows.Forms.Timer MeshPreviewTimer;
        private System.Windows.Forms.Timer ZoomInTimer;
        private System.Windows.Forms.Timer ZoomOutTimer;
        private System.Windows.Forms.Label DecalSizeLabel;
        private System.Windows.Forms.NumericUpDown DecalSizeNumeric;
        private System.Windows.Forms.Button LoadPresetButton;
        private System.Windows.Forms.Button SavePresetButton;
        private System.Windows.Forms.Label label1;
    }
}