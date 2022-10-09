using Newtonsoft.Json;
using SPETS.Classes;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Windows.Forms;

namespace SPETS.forms
{
    public struct VirtualFace
    {
        public List<Vector3> Vertices;
        public Vector3 Position;
        public Vector3 Normal;
        public Vector3 TrueNormal;

        public bool FrontFacing;
        public VirtualFace(List<Vector3> vertices, Matrix4x4 rotationMatrix)
        {
            Position = new Vector3();
            Vertices = new List<Vector3>();
            TrueNormal = Math3D.GetNormal(vertices);

            for (int i = 0; i < vertices.Count; i++)
            {
                Vector3 vert = Vector3.Transform(vertices[i], rotationMatrix);
                Vertices.Add(vert);

                Position.X += vert.X;
                Position.Y += vert.Y;
                Position.Z += vert.Z;
            }
            Position /= vertices.Count;

            Normal = Math3D.GetNormal(Vertices);
            FrontFacing = (Normal.X < 0);
        }
    }
    struct ImportObject
    {
        public string TexturePath;
        public string ModelPath;
        public Image Texture;
        public Mesh Model;
        public List<VirtualFace> PreviewZBuffer; 

        public ImportObject(Image image, Mesh mesh, string texturePath, string modelPath)
        {
            Texture = image;
            Model = mesh;
            TexturePath = texturePath;
            ModelPath = modelPath;
            PreviewZBuffer = new List<VirtualFace>();

            for (int f = 0; f < Model.Faces.Count; f++)
            {
                List<Vector3> points = new List<Vector3>();
                for (int p = 0; p < Model.Faces[f].Count; p++)
                {
                    points.Add(Model.Vertices[Model.Faces[f][p] - 1]);
                }
                VirtualFace vFace = new VirtualFace(
                    points, 
                    Matrix4x4.CreateRotationY(-0.7853982f) * Matrix4x4.CreateRotationZ(0.7853982f));

                
                PreviewZBuffer.Add(vFace);
                
            }
            PreviewZBuffer = PreviewZBuffer.OrderBy(v => v.Position.X).Reverse().ToList();
        }
    }

    public partial class AdvancedEditorForm : Form
    {
        ActionSelectForm asf;
        List<ImportObject> ImportObjects = new List<ImportObject>();
        Pen pen;
        SolidBrush brush;
        int lastSelected;


        Point renderOffset = new Point(125, 125);
        float renderSize = 64;

        Matrix4x4 rotateYMatrix;
        Matrix4x4 rotateZMatrix;
        Matrix4x4 rotationMatrix;
        public AdvancedEditorForm(ActionSelectForm asf)
        {
            InitializeComponent();
            this.asf = asf;
            pen = new Pen(Color.Black, 1);
            brush = new SolidBrush(Color.Gray);

            rotateYMatrix = Matrix4x4.CreateRotationY(-0.7853982f);
            rotateZMatrix = Matrix4x4.CreateRotationZ(0.7853982f);
            rotationMatrix = rotateYMatrix * rotateZMatrix;
        }
        private void AdvancedImportForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            asf.EnableButton();
        }

        #region FILE_LOADING

        private void LoadTextureButton_Click(object sender, EventArgs e)
        {
            if (ImportListView.SelectedIndices.Count > 0)
            {

                OpenFileDialog ofd = new OpenFileDialog();
                ofd.Filter = "Image Files|*.BMP;*.GIF;*.JPG;*.JPEG;*.PNG;*.TIFF";

                DialogResult dr = ofd.ShowDialog();
                if (dr == DialogResult.OK)
                {
                    ImportObjects[lastSelected] = new ImportObject(
                        Image.FromFile(ofd.FileName),
                        ImportObjects[lastSelected].Model,
                        ofd.FileName,
                        ImportObjects[lastSelected].ModelPath
                        );
                    RefreshObjectList();
                }
            }
        }

        private void ClearTextureButton_Click(object sender, EventArgs e)
        {
            if (ImportListView.SelectedIndices.Count > 0)
            {
                ImportObjects[lastSelected] = new ImportObject(
                        null,
                        ImportObjects[lastSelected].Model,
                        "",
                        ImportObjects[lastSelected].ModelPath
                        );
            }
        }

        private void LoadMeshButton_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "Wavefront Model (*.OBJ)|*.OBJ";

            DialogResult dr = ofd.ShowDialog();
            if (dr == DialogResult.OK)
            {
                Mesh loadMesh = MeshLoader.LoadOBJ(ofd.FileName);

                if (loadMesh.Faces.Count != 0 && loadMesh.Vertices.Count != 0)
                {
                    if (ImportListView.SelectedIndices.Count > 0)
                    {
                        ImportObjects[lastSelected] = new ImportObject(
                            ImportObjects[lastSelected].Texture,
                            loadMesh,
                            ImportObjects[lastSelected].TexturePath,
                            ofd.FileName
                            );
                    }
                    else
                    {
                        ImportObjects.Add(new ImportObject(
                                null,
                                loadMesh,
                                "",
                                ofd.FileName
                            ));
                    }

                    RefreshObjectList();
                }
            }
            
        }



        private void LoadBlueprintButton_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "Sprocket Blueprint (*.BLUEPRINT)|*.BLUEPRINT";

            DialogResult dr = ofd.ShowDialog();
            if (dr == DialogResult.OK)
            {
                List<Mesh> loadedMeshes = LoadBlueprintToMesh(ofd.FileName);
                
                for (int i = 0; i < loadedMeshes.Count; i++)
                {
                    if(loadedMeshes[i].Faces.Count != 0 && loadedMeshes[i].Vertices.Count != 0)
                    {
                        ImportObjects.Add(new ImportObject(
                                    null,
                                    loadedMeshes[i],
                                    "",
                                    ofd.FileName
                                ));
                    }
                }

                RefreshObjectList();
            }
        }
        #endregion

        #region MESH_RENDERER

        private void MeshPreview_Paint(object sender, PaintEventArgs e)
        {
            if (ImportObjects.Count > 0)
            {
                RenderMeshPreview(e.Graphics, ImportObjects[lastSelected].Model, ImportObjects[lastSelected].PreviewZBuffer);
            }
        }

        public void RenderMeshPreview(Graphics g, Mesh model, List<VirtualFace> faces)
        {
            for (int f = 0; f < faces.Count; f++)
            {
                //int zColor = (int)((float)f / (float)faces.Count * 255f);
                int zColor = (int)((-faces[f].TrueNormal.X + 1f) / 2f * 255f);

                if(zColor > 255) { zColor = 255; }
                else if(zColor < 0) { zColor = 0; }

                Color faceColor = Color.FromArgb(zColor, zColor, zColor);
                DrawTriangle(g, faces[f].Vertices, renderSize, renderOffset, faceColor, faces[f].FrontFacing);
            }
        }

        void DrawTriangle(Graphics g, List<Vector3> triangle, float size, Point offset, Color faceColor, bool frontFacing)
        {
            
            PointF[] tri = new PointF[triangle.Count + 1];
            for (int i = 0; i < triangle.Count; i++)
            {
                tri[i].X = triangle[i].Z * size + offset.X;
                tri[i].Y = -triangle[i].Y * size + offset.Y;
            }
            tri[tri.Length - 1] = tri[0];

            if (ShowFacesCheckbox.Checked && frontFacing)
            {
                brush.Color = faceColor;
                g.FillPolygon(brush, tri);
            }

            if (ShowWireframeCheckbox.Checked)
            {
                if (ShowFacesCheckbox.Checked && frontFacing || !ShowFacesCheckbox.Checked)
                {
                    g.DrawPolygon(pen, tri);
                }
            }

            if(ShowVerticesCheckbox.Checked)
            {
                if(ShowFacesCheckbox.Checked && frontFacing || !ShowFacesCheckbox.Checked)
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

        private void LeftButton_Click(object sender, EventArgs e)
        {
            renderOffset.X += 5;
            MeshPreview.Invalidate();
        }

        private void RightButton_Click(object sender, EventArgs e)
        {
            renderOffset.X -= 5;
            MeshPreview.Invalidate();
        }

        private void UpButton_Click(object sender, EventArgs e)
        {
            renderOffset.Y += 5;
            MeshPreview.Invalidate();
        }

        private void DownButton_Click(object sender, EventArgs e)
        {
            renderOffset.Y -= 5;
            MeshPreview.Invalidate();
        }

        private void ZoomInButton_Click(object sender, EventArgs e)
        {
            renderSize *= 1.2f;
            MeshPreview.Invalidate();
        }

        private void ZoomOutButton_Click(object sender, EventArgs e)
        {
            renderSize /= 1.2f;
            MeshPreview.Invalidate();
        }

        #endregion

        #region ITEM_LIST

        private void AddItemButton_Click(object sender, EventArgs e)
        {
            ImportObjects.Add(new ImportObject(null, null, "", ""));
            RefreshObjectList();
        }

        private void DeleteItemButton_Click(object sender, EventArgs e)
        {
            if(ImportListView.SelectedIndices.Count > 0)
            {
                ImportObjects.RemoveAt(ImportListView.SelectedIndices[0]);
                RefreshObjectList();
            }
        }

        void RefreshObjectList()
        {
            ImportListView.Items.Clear();
            for (int i = 0; i < ImportObjects.Count; i++)
            {
                string model = ImportObjects[i].ModelPath;
                string texture = ImportObjects[i].TexturePath;
                
                if(model == "") { model = "none"; }
                if (texture == "") { texture = "none"; }

                ImportListView.Items.Add(new ListViewItem(new string[] { texture, model }));
            }
        }

        private void ImportListView_SelectedIndexChanged(object sender, EventArgs e)
        {
            if(ImportListView.SelectedIndices.Count > 0) 
            { 
                lastSelected = ImportListView.SelectedIndices[0]; 
            }
            
            MeshPreview.Invalidate();
            TexturePreview.Image = ImportObjects[lastSelected].Texture;
        }


        #endregion


        List<Mesh> LoadBlueprintToMesh(string filePath)
        {
            // get file
            string[] blueprintFile = File.ReadAllLines(filePath);
            List<Mesh> meshes = new List<Mesh>();

            // go through lines
            for (int i = 0; i < blueprintFile.Length; i++)
            {
                if (blueprintFile[i].Trim() == "\"id\": \"Compartment\",")
                {
                    // create mesh
                    Mesh mesh = new Mesh();
                    
                    // isolate compartment
                    string[] compartment = blueprintFile.Skip(i - 1).Take(5).ToArray();
                    compartment[4] = compartment[4].Trim(',');

                    // deserialize
                    var BaseRoot = JsonConvert.DeserializeObject<CompartmentBaseRoot>(string.Join("", compartment));
                    var DataRoot = JsonConvert.DeserializeObject<CompartmentRoot>(BaseRoot.data);

                    if (DataRoot.compartment != null)
                    {
                        // vertices
                        for (int p = 0; p < DataRoot.compartment.points.Count; p += 3)
                        {
                            // add vertex
                            mesh.Vertices.Add(
                                new Vector3((float)-DataRoot.compartment.points[p],
                                            (float)DataRoot.compartment.points[p + 1],
                                            (float)DataRoot.compartment.points[p + 2]));
                        }
                        

                        //faces
                        for (int f = 0; f < DataRoot.compartment.faceMap.Count; f++)
                        {
                            List<int> face = new List<int>();

                            for (int n = 0; n < DataRoot.compartment.faceMap[f].Count; n += 3)
                            {
                                face.Add(DataRoot.compartment.faceMap[f][n] + 1);
                                face.Add(DataRoot.compartment.faceMap[f][n + 1] + 1);
                                face.Add(DataRoot.compartment.faceMap[f][n + 2] + 1);
                            }
                            mesh.Faces.Add(face);

                        }
                    }

                    meshes.Add(mesh);
                }
            }

            return meshes;
        }
    }
}
