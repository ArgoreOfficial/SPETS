using SPETS.Classes;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Numerics;
using System.Text;
using System.Windows.Forms;

namespace SPETS.forms
{
    public partial class BlueprintEditorForm : Form
    {
        Mesh loaded;
        int size = 50;
        Pen pen = new Pen(Color.Black, 1);
        int mouseX;
        int mouseY;

        public BlueprintEditorForm()
        {
            InitializeComponent();
            this.DoubleBuffered = true;

            frameTimer.Tick += new EventHandler(Update);
        }

        public void LoadModel(Mesh mesh)
        {
            loaded = mesh;
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            mouseX = Cursor.Position.X;
            mouseY = Cursor.Position.Y;

            for (int i = 0; i < loaded.Faces.Count; i++)
            {
                DrawTriangle(e.Graphics, i);
            }
        }

        public void Update(object sender, EventArgs e)
        {
            Invalidate();
        }


        void DrawTriangle(Graphics g, int faceId)
        {

            PointF[] tri = new PointF[loaded.Faces[faceId].Count];
            for (int i = 0; i < loaded.Faces[faceId].Count; i++)
            {
                tri[i].X = loaded.Vertices[loaded.Faces[faceId][i] - 1].Z * size + mouseX;
                tri[i].Y = -loaded.Vertices[loaded.Faces[faceId][i] - 1].Y * size + mouseY;
            }
            g.DrawLines(pen, tri);
            /*
            for (int f = 0; f < loaded.Faces[faceId].Count; f++)
            {
                Vector3 start;
                Vector3 end;

                if (f == loaded.Faces[faceId].Count - 1)
                {
                    start = loaded.Vertices[loaded.Faces[faceId][f] - 1];
                    end = loaded.Vertices[loaded.Faces[faceId][0] - 1];
                }
                else
                {
                    start = loaded.Vertices[loaded.Faces[faceId][f] - 1];
                    end = loaded.Vertices[loaded.Faces[faceId][f + 1] - 1];
                }

                int mouseX = Cursor.Position.X;
                int mouseY = Cursor.Position.Y;
                g.DrawLine( pen,
                            (int)(start.Z * size) + mouseX,
                            (int)(start.Y * size) + mouseY,
                            (int)(end.Z * size) + mouseX,
                            (int)(end.Y * size) + mouseY);

                
            }*/
        }

        private void BlueprintEditorForm_Load(object sender, EventArgs e)
        {

        }
    }
}
