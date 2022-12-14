using Newtonsoft.Json;
using SharpGL.SceneGraph.Primitives;
using SPETS.Classes;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Reflection;
using System.Threading;
using System.Windows.Forms;
using SharpGL.Serialization.Wavefront;
using SharpGL.SceneGraph.Effects;
using SharpGL.SceneGraph;
using SharpGL.SceneGraph.Assets;
using SharpGL;
using System.Diagnostics;
using SharpGL.SceneGraph.Cameras;

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
        Vector2 LastRenderOffset = new Vector2(-1, -1);
        Vector2 PreviewMouseOrigin = new Vector2(-1, -1);
        float ZoomSpeed = 0.3f;

        string[] Factions;


        public AdvancedEditorForm(ActionSelectForm asf)
        {
            InitializeComponent();
            InitializeScene();

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


        #region GL

        private void InitializeScene()
        {
            //  grid and axis stuff
            GLMeshPreview.Scene.SceneContainer.AddChild(new Grid());
            GLMeshPreview.Scene.SceneContainer.AddChild(new Axies());
            GLMeshPreview.Scene.RenderBoundingVolumes = false;
            
            // set 
            Camera cam = GLMeshPreview.Scene.CurrentCamera;
            cam.AspectRatio = 1;
            cam.Position = new Vertex(-5, -5, 5);
        }

        void LoadGLFromFile(string file)
        {
            // load mesh data (only for obj atm)
            var obj = new ObjFileFormat();
            var objScene = obj.LoadData(file);
            
            // Get the polygons
            var polygons = objScene.SceneContainer.Traverse<Polygon>().ToList();
            
            // add polygons
            foreach (var polygon in polygons)
            {
                polygon.Name = new FileInfo(file).Name.Split(".").First();
                polygon.Transformation.RotateX = 90f; // So that Ducky appears in the right orientation


                polygon.Parent.RemoveChild(polygon);
                polygon.Freeze(GLMeshPreview.OpenGL);
                GLMeshPreview.Scene.SceneContainer.AddChild(polygon);
                
                // Add effects.
                polygon.AddEffect(new OpenGLAttributesEffect());
            }
        }

        void LoadGLFromMesh(Mesh mesh)
        {
            // Get the polygons
            //var polygons = objScene.SceneContainer.Traverse<Polygon>().ToList();
            var polygons = mesh.GetPolygons();
            
            // Add each polygon (There is only one in ducky.obj)
            foreach (var polygon in polygons)
            {
                polygon.Name = "Mesh";
                polygon.Transformation.RotateX = 90f; // So that Ducky appears in the right orientation


                polygon.Freeze(GLMeshPreview.OpenGL);
                GLMeshPreview.Scene.SceneContainer.AddChild(polygon);

                // Add effects.
                //polygon.AddEffect(new OpenGLAttributesEffect());
            }
        }

        #endregion

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

        void LoadMesh(string fileName)
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
            }

            //LoadGLFromFile(fileName);
            LoadGLFromMesh(loadMesh);
        }

        void LoadBlueprint(string fileName)
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
        }

        private void LoadFileButton_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "Tank File|*.OBJ;*.BLUEPRINT";
            ofd.Multiselect = true;

            DialogResult dr = ofd.ShowDialog();
            if (dr == DialogResult.OK)
            {
                foreach (string fileName in ofd.FileNames)
                {
                    string extension = new FileInfo(fileName).Extension;
                    
                    if (extension == ".obj")
                    {
                        LoadMesh(fileName);
                    }
                    else if(extension == ".blueprint")
                    {
                        LoadBlueprint(fileName);
                    }
                }
            }
            
            RefreshObjectList();

        }

        #endregion

        #region PREVIEW_CONTROLS

        private void ShowFacesCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            
        }

        private void ShowVerticesCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            
        }

        private void ShowWireframeCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            
        }

        private void BFCullingCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            
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
            
        }

        private void MeshPreviewTimer_Tick(object sender, EventArgs e)
        {
            RenderOffset.X = LastRenderOffset.X + MousePosition.X - PreviewMouseOrigin.X;
            RenderOffset.Y = LastRenderOffset.Y + MousePosition.Y - PreviewMouseOrigin.Y;
            
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
            Vertex newPosition = GLMeshPreview.Scene.CurrentCamera.Position;
            newPosition.X += ZoomSpeed;
            newPosition.Y += ZoomSpeed;
            newPosition.Z -= ZoomSpeed;
            
            if (newPosition.Magnitude() < 1f) newPosition.Normalize();

            GLMeshPreview.Scene.CurrentCamera.Position = newPosition;
        }

        private void ZoomOutTimer_Tick(object sender, EventArgs e)
        {
            Vertex newPosition = GLMeshPreview.Scene.CurrentCamera.Position;
            newPosition.X -= ZoomSpeed;
            newPosition.Y -= ZoomSpeed;
            newPosition.Z += ZoomSpeed;

            if (newPosition.Magnitude() < 1f) newPosition.Normalize();

            GLMeshPreview.Scene.CurrentCamera.Position = newPosition;
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
                        Vector3 normal = Vector3.Normalize(SMath.GetNormal(points));
                        Vector3 position = faceCenter + normal * (ImportObjects[i].TextureDistance - 0.001f);
                        Vector3 angle = SMath.DirectionToAngle(normal) * 57.29578f;

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
