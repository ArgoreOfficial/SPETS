using SPETS.Classes;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
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

        public VirtualFace(List<Vector3> vertices, Matrix4x4 rotationMatrix)
        {
            Position = new Vector3();
            Vertices = new List<Vector3>();

            for (int i = 0; i < vertices.Count; i++)
            {
                Vector3 vert = Vector3.Transform(vertices[i], rotationMatrix);
                Vertices.Add(vert);

                Position.X += vert.X;
                Position.Y += vert.Y;
                Position.Z += vert.Z;
            }
            Position /= vertices.Count;
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
                PreviewZBuffer.Add(new VirtualFace(points, Matrix4x4.CreateRotationY(-0.7853982f) * Matrix4x4.CreateRotationZ(0.7853982f)));
            }
            PreviewZBuffer = PreviewZBuffer.OrderBy(v => v.Position.X).Reverse().ToList();
        }
    }

    public partial class AdvancedImportForm : Form
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
        public AdvancedImportForm(ActionSelectForm asf)
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


        #region MeshRenderer

        private void MeshPreview_Paint(object sender, PaintEventArgs e)
        {
            if(ImportObjects.Count > 0)
            {
                RenderMeshPreview(e.Graphics, ImportObjects[lastSelected].Model, ImportObjects[lastSelected].PreviewZBuffer);
            }
        }

        public void RenderMeshPreview(Graphics g, Mesh model, List<VirtualFace> faces)
        {
            float far = faces[0].Position.X;
            float near = faces.Last().Position.X;

            for (int f = 0; f < faces.Count; f++)
            {
                int zColor = (int)((float)f / (float)faces.Count * 255.0f);
                if(zColor > 255) { zColor = 255; }
                else if(zColor < 0) { zColor = 0; }

                Color faceColor = Color.FromArgb(zColor, zColor, zColor);
                DrawTriangle(g, faces[f].Vertices, renderSize, renderOffset, faceColor);
            }
        }

        void DrawTriangle(Graphics g, List<Vector3> triangle, float size, Point offset, Color faceColor)
        {

            PointF[] tri = new PointF[triangle.Count + 1];
            for (int i = 0; i < triangle.Count; i++)
            {
                tri[i].X = triangle[i].Z * size + offset.X;
                tri[i].Y = -triangle[i].Y * size + offset.Y;
            }
            tri[tri.Length - 1] = tri[0];

            brush.Color = faceColor;
            g.FillPolygon(brush, tri);
            //g.DrawLines(pen, tri);
        }

        #endregion

        #region PreviewControls

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

        #region ItemList

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
    }
}
