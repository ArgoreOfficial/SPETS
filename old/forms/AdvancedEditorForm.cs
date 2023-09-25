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
using SharpGL.SceneGraph.Core;

namespace SPETS.forms
{

    public partial class AdvancedEditorForm : Form
    {


        ActionSelectForm asf;
        List<ImportObject> ImportObjects = new List<ImportObject>();

        int lastSelected;

        Vector2 GLRotation = new Vector2(0.785f, 0.785f);
        float GLDistance = 4f;

        bool Panning = false;
        Point LastMousePos;
        float ZoomSpeed = 0.3f;

        string[] Factions;


        public AdvancedEditorForm(ActionSelectForm asf)
        {
            InitializeComponent();
            InitializeScene();
            UpdateGLCamera();

            this.asf = asf;

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
            // GL Settings
            OpenGL gl = GLMeshPreview.OpenGL;
            gl.Enable(OpenGL.GL_CULL_FACE);
            gl.Enable(OpenGL.GL_BLEND);

            //gl.Disable(OpenGL.GL_DEPTH_TEST);

            gl.CullFace(OpenGL.GL_BACK);
            gl.BlendFunc(OpenGL.GL_SRC_ALPHA, OpenGL.GL_ONE_MINUS_SRC_ALPHA);

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

        void LoadGLFromMesh(Mesh mesh, string name)
        {
            // Get the polygons
            //var polygons = objScene.SceneContainer.Traverse<Polygon>().ToList();
            var polygons = mesh.GetPolygons();
            var meshroot = new SceneElement();
            meshroot.Name = name;
            GLMeshPreview.Scene.SceneContainer.AddChild(meshroot);

            // Add each polygon (There is only one in ducky.obj)
            foreach (var polygon in polygons)
            {
                polygon.Name = "polygon";
                polygon.Transformation.RotateX = 90f;

                polygon.Freeze(GLMeshPreview.OpenGL);
                GLMeshPreview.Scene.SceneContainer.Children.Last().AddChild(polygon);
                // Add effects.
                //polygon.AddEffect(new OpenGLAttributesEffect());
            }

        }

        void RefreshMeshPreview(bool showall = false)
        {
            for (int i = 0; i < GLMeshPreview.Scene.SceneContainer.Children.Count; i++)
            {
                if (!showall &&
                    GLMeshPreview.Scene.SceneContainer.Children[i].Name.Contains(".obj") &&
                    GLMeshPreview.Scene.SceneContainer.Children[i].Name != ImportObjects[lastSelected].ModelName)
                {
                    GLMeshPreview.Scene.SceneContainer.Children[i].IsEnabled = false;
                }
                else
                {
                    GLMeshPreview.Scene.SceneContainer.Children[i].IsEnabled = true;
                }
            }
        }

        void ReplaceSelectedMaterial(Material mat)
        {
            // replace mesh material
            for (int i = 0; i < GLMeshPreview.Scene.SceneContainer.Children.Count; i++)
            {
                if (GLMeshPreview.Scene.SceneContainer.Children[i].Name == ImportObjects[lastSelected].ModelName)
                {
                    for (int p = 0; p < GLMeshPreview.Scene.SceneContainer.Children[i].Children.Count; p++)
                    {
                        // unfreeze
                        ((Polygon)GLMeshPreview.Scene.SceneContainer.Children[i].Children[p]).Unfreeze(GLMeshPreview.OpenGL);

                        // set material
                        ((Polygon)GLMeshPreview.Scene.SceneContainer.Children[i].Children[p]).Material = mat;

                        // freeze
                        ((Polygon)GLMeshPreview.Scene.SceneContainer.Children[i].Children[p]).Freeze(GLMeshPreview.OpenGL);
                    }

                    // move to last in list, that way it'll be drawn on top of everything else
                    var scenelement = GLMeshPreview.Scene.SceneContainer.Children[i];
                    GLMeshPreview.Scene.SceneContainer.RemoveChild(GLMeshPreview.Scene.SceneContainer.Children[i]);
                    GLMeshPreview.Scene.SceneContainer.AddChild(scenelement);
                    break;
                }
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

                DialogResult dialogResult = MessageBox.Show(
                    "You are about to turn a mesh into a decal mask. This means the mesh will be used as a decal placement template, and won't import any vertices or faces. Proceed?",
                    "Turn mesh into decalmask?",
                    MessageBoxButtons.YesNo,
                    MessageBoxIcon.Warning);

                if (dialogResult == DialogResult.Yes)
                {
                    ImportObjects[lastSelected].SetTexture(Image.FromFile(ofd.FileName), ofd.FileName);
                    ImportObjects[lastSelected].Type = "decalmask";

                    Material m = new Material();
                    m.Diffuse = Color.FromArgb(128, 255, 0, 0);
                    ReplaceSelectedMaterial(m);

                    RefreshTexturePreview();
                    RefreshMeshPreview();
                    RefreshObjectList();

                    // copy files to root folders
                    string exePath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
                    FileInfo info = new FileInfo(ofd.FileName);
                
                    File.Copy(info.FullName, exePath + "\\cache\\images\\" + info.FullName.Split("\\").Last(), true);
                }
            }
        }

        private void ClearTextureButton_Click(object sender, EventArgs e)
        {
            if (ImportListView.SelectedIndices.Count > 0)
            {
                Material m = new Material();
                m.Diffuse = Color.FromArgb(255, 255, 255, 255);
                ReplaceSelectedMaterial(m);

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
                    lastSelected = ImportObjects.Count - 1;
                }

                // copy files to root folders
                string exePath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
                FileInfo info = new FileInfo(fileName);
                File.Copy(info.FullName, exePath + "\\cache\\meshes\\" + info.FullName.Split("\\").Last(), true);
            }

            //LoadGLFromFile(fileName);
            FileInfo fileinfo = new FileInfo(fileName);
            
            LoadGLFromMesh(loadMesh, fileinfo.Name);
            RefreshTexturePreview();
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
            File.Copy(info.FullName, exePath + "\\cache\\blueprints\\" + info.FullName.Split("\\").Last(), true);
        }

        private void LoadFileButton_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "Wavefront|*.OBJ";
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
                    /*else if(extension == ".blueprint") // might fix this at some point? we'll see
                    {
                        LoadBlueprint(fileName);
                    }*/
                }
            }
            
            RefreshObjectList();

        }

        #endregion

        #region PREVIEW_CONTROLS

        // mouse pan

        private void GLMeshPreview_MouseDown(object sender, MouseEventArgs e)
        {
            if (!Panning)
            {
                LastMousePos = MousePosition;
                Panning = true;

                MeshPreviewTimer.Start();
                Debug.WriteLine("MouseDown");
            }
        }

        private void GLMeshPreview_MouseUp(object sender, MouseEventArgs e)
        {
            Panning = false;
            MeshPreviewTimer.Stop();
            Debug.WriteLine("MouseUp");
        }

        private void MeshPreviewTimer_Tick(object sender, EventArgs e)
        {
            Point mouseDelta = new Point(MousePosition.X - LastMousePos.X, MousePosition.Y - LastMousePos.Y);

            GLRotation.X -= mouseDelta.X * 0.003f;
            GLRotation.Y += mouseDelta.Y * 0.003f;

            if (GLRotation.Y > 1.5f)
            {
                GLRotation.Y = 1.5f;
            }
            else if (GLRotation.Y < -1.5f)
            {
                GLRotation.Y = -1.5f;
            }

            LastMousePos = MousePosition;
            UpdateGLCamera();
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
            GLDistance -= ZoomSpeed;
            UpdateGLCamera();
        }

        private void ZoomOutTimer_Tick(object sender, EventArgs e)
        {
            GLDistance += ZoomSpeed;
            UpdateGLCamera();
        }

        /// <summary>
        /// updates sharpgl camera position
        /// </summary>
        private void UpdateGLCamera()
        {
            /*
             * x = cos(yaw)*cos(pitch)
               y = sin(yaw)*cos(pitch)
               z = sin(pitch)
             */
            Vertex position = new Vertex(
                MathF.Cos(GLRotation.X) * MathF.Cos(GLRotation.Y) * GLDistance,
                MathF.Sin(GLRotation.X) * MathF.Cos(GLRotation.Y) * GLDistance,
                MathF.Sin(GLRotation.Y) * GLDistance);

            GLMeshPreview.Scene.CurrentCamera.Position = position;
        }

        #endregion

        #region ITEM_LIST_AND_PROPERTIES

        private void DeleteItemButton_Click(object sender, EventArgs e)
        {

            // remove mesh from scene 
            for (int i = 0; i < GLMeshPreview.Scene.SceneContainer.Children.Count; i++)
            {
                if (GLMeshPreview.Scene.SceneContainer.Children[i].Name == ImportObjects[lastSelected].ModelName)
                {
                    GLMeshPreview.Scene.SceneContainer.RemoveChild(GLMeshPreview.Scene.SceneContainer.Children[i]);
                    break;
                }
            }

            // remove from list
            for (int i = ImportListView.SelectedIndices.Count - 1; i >= 0; i--)
            {
                ImportObjects.RemoveAt(ImportListView.SelectedIndices[i]);
            }

            lastSelected = 0;
            ImportListView.SelectedIndices.Clear();

            // refresh stuff
            RefreshObjectList();
            RefreshMeshPreview();
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
            if (ImportListView.SelectedIndices.Count > 0)
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

            // doesn't do anything atm since blueprints can't be imported (for now)
            if(ImportObjects[lastSelected].Type == "blueprint")
            {
                LoadTextureButton.Enabled = false;
            }
            else
            {
                LoadTextureButton.Enabled = true;
            }

            RefreshMeshPreview(ImportListView.SelectedIndices.Count == 0);
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
