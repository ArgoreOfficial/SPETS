using Newtonsoft.Json;
using SPETS.Classes;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace SPETS.forms
{

    public partial class AdvancedEditorForm : Form
    {
        ActionSelectForm asf;
        List<ImportObject> ImportObjects = new List<ImportObject>();

        Pen pen;
        SolidBrush brush;
        int lastSelected;

        Vector2 RenderOffset = new Vector2(0, 0);
        float RenderSize = 20;
        Vector2 LastRenderOffset = new Vector2(-1, -1);
        Vector2 PreviewMouseOrigin = new Vector2(-1, -1);

        string[] Factions;


        public AdvancedEditorForm(ActionSelectForm asf)
        {
            InitializeComponent();

            this.asf = asf;
            pen = new Pen(Color.Black, 1);
            brush = new SolidBrush(Color.Gray);
        }
        private void AdvancedEditorForm_Load(object sender, EventArgs e)
        {
            // load factions
            string documents = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);
            string factionsFolder = $"{documents}\\My Games\\Sprocket\\Factions\\";
            Factions = Directory.GetDirectories(factionsFolder);

            for (int i = 0; i < Factions.Length; i++)
            {
                FactionsCombobox.Items.Add(Factions[i].Split('\\').Last());
            }
            FactionsCombobox.SelectedIndex = 0;
        }
        private void AdvancedImportForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            asf.EnableButton();
        }


        #region FILE_LOADING

        private void LoadTextureButton_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "Image Files|*.BMP;*.GIF;*.JPG;*.JPEG;*.PNG;*.TIFF";
            
            DialogResult dr = ofd.ShowDialog();
            if (dr == DialogResult.OK)
            {
                
                ImportObjects[lastSelected].SetTexture(Image.FromFile(ofd.FileName), ofd.FileName);

                RefreshTexturePreview();
                RefreshObjectList();

                // copy files to root folders
                string exePath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
                FileInfo info = new FileInfo(ofd.FileName);
                
                File.Copy(info.FullName, exePath + "\\Images\\" + info.FullName.Split("\\").Last(), true);
                
            }
        }

        private void ClearTextureButton_Click(object sender, EventArgs e)
        {
            if (ImportListView.SelectedIndices.Count > 0)
            {
                ImportObjects[lastSelected].ClearTexture();
                RefreshTexturePreview();
                RefreshObjectList();
            }
        }

        private void LoadMeshButton_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "Wavefront Model (*.OBJ)|*.OBJ";
            ofd.Multiselect = true;

            DialogResult dr = ofd.ShowDialog();
            if (dr == DialogResult.OK)
            {
                foreach (string fileName in ofd.FileNames)
                {
                    Mesh loadMesh = MeshLoader.FromOBJ(fileName);

                    if (loadMesh.Faces.Count != 0 && loadMesh.Vertices.Count != 0)
                    {
                        if (ImportListView.SelectedIndices.Count > 0)
                        {
                            ImportObjects[lastSelected] = new ImportObject(
                                loadMesh,
                                fileName,
                                "mesh"
                                );
                        }
                        else
                        {
                            ImportObjects.Add(new ImportObject(
                                    loadMesh,
                                    fileName,
                                    "mesh"
                                ));
                        }

                        // copy files to root folders
                        string exePath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
                        FileInfo info = new FileInfo(fileName);
                        File.Copy(info.FullName, exePath + "\\Meshes\\" + info.FullName.Split("\\").Last(), true);

                        RefreshObjectList();
                    }
                }
            }
            
        }



        private void LoadBlueprintButton_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "Sprocket Blueprint (*.BLUEPRINT)|*.BLUEPRINT";
            ofd.Multiselect = true;
            
            DialogResult dr = ofd.ShowDialog();
            if (dr == DialogResult.OK)
            {
                foreach (string fileName in ofd.FileNames)
                {
                    List<Mesh> loadedMeshes = MeshLoader.FromBlueprint(fileName);

                    for (int i = 0; i < loadedMeshes.Count; i++)
                    {
                        if (loadedMeshes[i].Faces.Count != 0 && loadedMeshes[i].Vertices.Count != 0)
                        {
                            ImportObjects.Add(new ImportObject(
                                        loadedMeshes[i],
                                        fileName + "/" + i,
                                        "blueprint"
                                    ));
                        }
                    }

                    // copy files to root folders
                    string exePath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
                    FileInfo info = new FileInfo(fileName);
                    File.Copy(info.FullName, exePath + "\\Blueprints\\" + info.FullName.Split("\\").Last(), true);

                    RefreshObjectList();
                }
            }
        }
        #endregion

        #region MESH_RENDERER

        private void MeshPreview_Paint(object sender, PaintEventArgs e)
        {
            if (ImportObjects.Count > 0)
            {
                RenderMeshPreview(e.Graphics, ImportObjects[lastSelected].PreviewZBuffer);
            }
        }

        public void RenderMeshPreview(Graphics g, List<VirtualFace> faces)
        {
            for (int f = 0; f < faces.Count; f++)
            {
                //int zColor = (int)((float)f / (float)faces.Count * 255f);
                int zColor = (int)((-faces[f].TrueNormal.X + 1f) / 2f * 255f);

                if(zColor > 255) { zColor = 255; }
                else if(zColor < 0) { zColor = 0; }

                Color faceColor = Color.FromArgb(zColor, zColor, zColor);
                DrawTriangle(g, faces[f].Vertices, RenderSize, RenderOffset + new Vector2(128,128), faceColor, faces[f].FrontFacing);
            }
        }

        void DrawTriangle(Graphics g, List<Vector3> triangle, float size, Vector2 offset, Color faceColor, bool frontFacing)
        {
            
            PointF[] tri = new PointF[triangle.Count + 1];
            for (int i = 0; i < triangle.Count; i++)
            {
                tri[i].X = triangle[i].Z * size + offset.X;
                tri[i].Y = -triangle[i].Y * size + offset.Y;
            }
            tri[tri.Length - 1] = tri[0];

            if (ShowFacesCheckbox.Checked && (frontFacing || !BFCullingCheckbox.Checked))
            {
                brush.Color = faceColor;
                g.FillPolygon(brush, tri);
            }

            if (ShowWireframeCheckbox.Checked)
            {
                if (frontFacing || !BFCullingCheckbox.Checked)
                {
                    g.DrawPolygon(pen, tri);
                }
            }

            if(ShowVerticesCheckbox.Checked)
            {
                if(frontFacing || !BFCullingCheckbox.Checked)
                {
                    pen.Color = Color.Red;
                    for (int i = 0; i < tri.Length; i++)
                    {
                        g.DrawRectangle(pen, new Rectangle((int)tri[i].X, (int)tri[i].Y, 1, 1));
                    }
                    pen.Color = Color.Black;
                }
            }
        }

        #endregion

        #region PREVIEW_CONTROLS

        private void ShowFacesCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            MeshPreview.Invalidate();
        }

        private void ShowVerticesCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            MeshPreview.Invalidate();
        }

        private void ShowWireframeCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            MeshPreview.Invalidate();
        }

        private void BFCullingCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            MeshPreview.Invalidate();
        }

        // mouse pan
        private void MeshPreview_MouseDown(object sender, MouseEventArgs e)
        {
            if(PreviewMouseOrigin.X < 0 && PreviewMouseOrigin.Y < 0)
            {
                LastRenderOffset = RenderOffset;
                PreviewMouseOrigin = new Vector2(MousePosition.X, MousePosition.Y);

                MeshPreviewTimer.Start();
            }
        }

        private void MeshPreview_MouseUp(object sender, MouseEventArgs e)
        {
            PreviewMouseOrigin.X = -1;
            PreviewMouseOrigin.Y = -1;
            MeshPreviewTimer.Stop();
            MeshPreview.Invalidate();
        }

        private void MeshPreviewTimer_Tick(object sender, EventArgs e)
        {
            RenderOffset.X = LastRenderOffset.X + MousePosition.X - PreviewMouseOrigin.X;
            RenderOffset.Y = LastRenderOffset.Y + MousePosition.Y - PreviewMouseOrigin.Y;
            MeshPreview.Invalidate();
        }

        // zoom

        private void ZoomInButton_MouseDown(object sender, MouseEventArgs e)
        {
            ZoomInTimer.Start();
        }

        private void ZoomInButton_MouseUp(object sender, MouseEventArgs e)
        {
            ZoomInTimer.Stop();
        }

        private void ZoomOutButton_MouseDown(object sender, MouseEventArgs e)
        {
            ZoomOutTimer.Start();
        }

        private void ZoomOutButton_MouseUp(object sender, MouseEventArgs e)
        {
            ZoomOutTimer.Stop();
        }

        private void ZoomInTimer_Tick(object sender, EventArgs e)
        {
            RenderSize *= 1.01f;
            RenderOffset *= 1.01f;
            MeshPreview.Invalidate();
        }

        private void ZoomOutTimer_Tick(object sender, EventArgs e)
        {
            RenderSize /= 1.01f;
            RenderOffset /= 1.01f;
            MeshPreview.Invalidate();
        }

        #endregion

        #region ITEM_LIST_AND_PROPERTIES

        private void DeleteItemButton_Click(object sender, EventArgs e)
        {
            
            for (int i = ImportListView.SelectedIndices.Count - 1; i >= 0; i--)
            {
                ImportObjects.RemoveAt(ImportListView.SelectedIndices[i]);
            }
            RefreshObjectList();
            
        }

        void RefreshObjectList()
        {
            ImportListView.Items.Clear();
            for (int i = 0; i < ImportObjects.Count; i++)
            {
                string model = ImportObjects[i].ModelName;
                string type = ImportObjects[i].Type;
                
                if(model == "") { model = "none"; }

                ImportListView.Items.Add(new ListViewItem(new string[] { type, model }));
            }
        }

        void RefreshTexturePreview()
        {
            if(ImportListView.SelectedIndices.Count > 0)
            {
                TexturePreview.Image = ImportObjects[lastSelected].Texture;
                DecalSizeNumeric.Value = (decimal)ImportObjects[lastSelected].TextureSize;
                DecalDistanceNumeric.Value = (decimal)ImportObjects[lastSelected].TextureDistance;
            }
        }

        private void ImportListView_SelectedIndexChanged(object sender, EventArgs e)
        {
            if(ImportListView.SelectedIndices.Count > 0) 
            { 
                lastSelected = ImportListView.SelectedIndices[0];
            }

            if(ImportObjects[lastSelected].Type == "blueprint")
            {
                LoadTextureButton.Enabled = false;
            }
            else
            {
                LoadTextureButton.Enabled = true;
            }

            MeshPreview.Invalidate();
            RefreshTexturePreview();
        }

        private void DecalDistanceNumeric_ValueChanged(object sender, EventArgs e)
        {
            ImportObjects[lastSelected].TextureDistance = (float)DecalDistanceNumeric.Value;
        }

        private void DecalSizeNumeric_ValueChanged(object sender, EventArgs e)
        {
            ImportObjects[lastSelected].TextureSize = (float)DecalSizeNumeric.Value;
        }

        #endregion
        
        #region IMPORT
        private void ImportButton_Click(object sender, EventArgs e)
        {
            bool hasTexture = false;

            for (int i = 0; i < ImportObjects.Count; i++) {
                if(ImportObjects[i].Texture != null) {
                    hasTexture = true;
                    break;
                }
            }

            if(hasTexture)
            {
                DialogResult dialogResult = MessageBox.Show(
                    "One or more loaded meshes have a texture, this will place a decal on every face of that model. Proceed?", 
                    "Mesh includes textures", 
                    MessageBoxButtons.YesNo, 
                    MessageBoxIcon.Warning);
                if (dialogResult == DialogResult.Yes)
                {
                    DoImport();
                }
            }
            else
            {
                DoImport();
            }
        }
        void DoImport()
        {
            Thread.CurrentThread.CurrentCulture = new CultureInfo("en-US");

            ImportButton.Enabled = false;
            Cursor.Current = Cursors.WaitCursor;

            AdvancedImport(Factions[FactionsCombobox.SelectedIndex], "advanced_import");

            ImportButton.Enabled = true;
            Cursor.Current = Cursors.Default;

            MessageBox.Show("Importing finished", "Importing finished", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }
        void AdvancedImport(string savePath, string saveName)
        {
            List<CompartmentBaseRoot> blueprintFile = new List<CompartmentBaseRoot>();

            // compartment
            
            string name = ImportObjects[0].ModelName.Split('.')[0];

            Mesh loaded = ImportObjects[0].Model;
            CompartmentRoot compRoot = new CompartmentRoot(name);
            List<Vector3> vectorPoints = new List<Vector3>(); // used for checking vertices with x y and z

            /// null check
            if (loaded.Faces.Count == 0 || loaded.Vertices.Count == 0) return;

            for (int f = 0; f < loaded.Faces.Count; f++)
            {
                // null face check
                if (loaded.Faces[f].Count < 3 || loaded.Faces[f].Count > ResourceHandler.NGonLookup.Count) continue;

                // faces
                compRoot.compartment.faceMap.Add(CreateNGon(loaded.Faces[f].Count, compRoot.compartment.points.Count / 3));

                // vertices
                for (int fP = 0; fP < loaded.Faces[f].Count; fP++)
                {
                    compRoot.compartment.points.Add(-loaded.Vertices[loaded.Faces[f][fP] - 1].X);
                    compRoot.compartment.points.Add(loaded.Vertices[loaded.Faces[f][fP] - 1].Y);
                    compRoot.compartment.points.Add(loaded.Vertices[loaded.Faces[f][fP] - 1].Z);

                    vectorPoints.Add(loaded.Vertices[loaded.Faces[f][fP] - 1] * new Vector3(-1, 1, 1));
                }
            }

            // sharedpoints(temp) and thicknessmap
            for (int i = 0; i < compRoot.compartment.points.Count; i++)
            {
                compRoot.compartment.thicknessMap.Add(1);
            }


            // sharedpoints
            List<int> foundIndexes = new List<int>();
            for (int p1 = 0; p1 < vectorPoints.Count; p1++)
            {
                if (foundIndexes.Contains(p1)) continue;

                List<int> shared = new List<int>();

                shared.Add(p1);

                for (int p2 = p1 + 1; p2 < vectorPoints.Count; p2++)
                {
                    if (vectorPoints[p1] == vectorPoints[p2])
                    {
                        shared.Add(p2);
                        foundIndexes.Add(p2);
                    }
                }

                compRoot.compartment.sharedPoints.Add(shared);
            }

            blueprintFile.Add(new CompartmentBaseRoot("Compartment", JsonConvert.SerializeObject(compRoot), ""));


            List<Attachment> Attachments = new List<Attachment>();
            for (int i = 0; i < ImportObjects.Count; i++)
            {
                if(ImportObjects[i].Texture != null)
                {
                    for (int f = 0; f < ImportObjects[i].Model.Faces.Count; f++)
                    {

                        Attachment decalAttachment = new Attachment();
                        decalAttachment.REF = "356f883c9f9bc9344aa34cd4f646d36e";
                        decalAttachment.CID = 0;

                        // decal positions, a lot of maths
                        List<Vector3> points = new List<Vector3>();
                        Vector3 faceCenter = new Vector3();
                        for (int p = 0; p < ImportObjects[i].Model.Faces[f].Count; p++)
                        {
                            points.Add(ImportObjects[i].Model.Vertices[ImportObjects[i].Model.Faces[f][p] - 1]);
                            faceCenter += ImportObjects[i].Model.Vertices[ImportObjects[i].Model.Faces[f][p] - 1];
                        }
                        faceCenter /= ImportObjects[i].Model.Faces[f].Count;
                        Vector3 normal = Vector3.Normalize(Math3D.GetNormal(points));
                        Vector3 position = faceCenter + normal * (ImportObjects[i].TextureDistance - 0.001f);
                        Vector3 angle = Math3D.DirectionToAngle(normal) * 57.29578f;

                        decalAttachment.T = new List<double> {
                            -position.X,
                            position.Y,
                            position.Z,
                            angle.X,
                            angle.Y,
                            angle.Z,
                            ImportObjects[i].TextureSize - 0.001f,
                            ImportObjects[i].TextureSize - 0.001f,
                            ImportObjects[i].TextureSize - 0.001f,
                            0.0
                        };
                        decalAttachment.DAT = new List<CompartmentBaseRoot>
                        {
                            //new CompartmentBaseRoot("decal", "\"data\": \"{\\\"ID\\\":{" + 0 + "}}\",", ""),
                            new CompartmentBaseRoot("asset", JsonConvert.SerializeObject(new AttatchmentAsset(ImportObjects[i].TextureName, 1)), "")
                        };
                        
                        // add to list
                        Attachments.Add(decalAttachment);
                    }
                }
            }
            if(Attachments.Count > 0)
            {
                blueprintFile.Add(new CompartmentBaseRoot("Attachments", JsonConvert.SerializeObject(new AttachmentRoot(Attachments)), ""));
            }


            // saving
            if (!Directory.Exists($"{savePath}/Blueprints/Compartments"))
            {
                Directory.CreateDirectory($"{savePath}/Blueprints/Compartments");
            }


            string file = JsonConvert.SerializeObject(blueprintFile.ToArray(), Formatting.Indented);
            File.WriteAllText($"{savePath}/Blueprints/Compartments/{saveName}.blueprint", file);
        }

        List<int> CreateNGon(int length, int offset)
        {
            // use lookup table
            // replace indexOrder with count
            int[] indexOrder = ResourceHandler.NGonLookup[length - 1].ToArray();
            List<int> face = new List<int>();

            for (int i = 0; i < indexOrder.Length; i++)
            {
                face.Add(indexOrder[i] + offset);
            }

            return face;
        }

        #endregion

        #region PRESET

        private void LoadPresetButton_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "Preset File (*.PRESET)|*.PRESET";
            
            DialogResult dr = ofd.ShowDialog();
            if (dr == DialogResult.OK)
            {
                List<ImportObjectSave> loadedPreset = JsonConvert.DeserializeObject<List<ImportObjectSave>>(File.ReadAllText(ofd.FileName));    
                foreach(ImportObjectSave iObjSave in loadedPreset)
                {
                    ImportObjects.Add(iObjSave.LoadImportObjects());
                }
            }
            
            RefreshObjectList();
        }

        private void SavePresetButton_Click(object sender, EventArgs e)
        {
            if (ImportObjects.Count > 0)
            {
                SaveFileDialog dialog = new SaveFileDialog();

                dialog.Filter = "Preset File (*.PRESET)|*.PRESET|All files (*.*)|*.*";
                dialog.FilterIndex = 0;
                dialog.RestoreDirectory = true;

                if (dialog.ShowDialog() == DialogResult.OK)
                {
                    List<ImportObjectSave> iObjSave = new List<ImportObjectSave>();
                    foreach(ImportObject iObj in ImportObjects)
                    {
                        iObjSave.Add(new ImportObjectSave().LoadFromIObj(iObj));
                    }
                    
                    File.WriteAllText(dialog.FileName, JsonConvert.SerializeObject(iObjSave, Formatting.Indented));
                }
            }
        }

        #endregion
    }
}
