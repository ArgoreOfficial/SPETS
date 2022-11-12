using SPETS.Classes;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Numerics;
using System.Text;

static class Form3DRenderer
{

    public static void RenderMesh(Graphics g, SolidBrush brush, Pen pen, List<VirtualFace> faces, float RenderSize, Vector2 RenderOffset)
    {
        for (int f = 0; f < faces.Count; f++)
        {
            //int zColor = (int)((float)f / (float)faces.Count * 255f);
            int zColor = (int)((-faces[f].TrueNormal.X + 1f) / 2f * 255f);

            if (zColor > 255) { zColor = 255; }
            else if (zColor < 0) { zColor = 0; }

            Color faceColor = Color.FromArgb(zColor, zColor, zColor);
            DrawTriangle(g, brush, pen, faces[f].Vertices, RenderSize, RenderOffset + new Vector2(128, 128), faceColor, true, faces[f].FrontFacing, true, true, false);
        }
    }

    public static void DrawTriangle(Graphics g, SolidBrush brush, Pen pen, List<Vector3> triangle, float size, Vector2 offset, Color faceColor, bool useBackfaceCulling, bool frontFacing, bool drawFaces, bool drawWireframe, bool drawVertices)
    {

        PointF[] tri = new PointF[triangle.Count + 1];
        for (int i = 0; i < triangle.Count; i++)
        {
            tri[i].X = triangle[i].Z * size + offset.X;
            tri[i].Y = -triangle[i].Y * size + offset.Y;
        }
        tri[tri.Length - 1] = tri[0];

        if (drawFaces && (frontFacing || !useBackfaceCulling))
        {
            brush.Color = faceColor;
            g.FillPolygon(brush, tri);
        }

        if (drawWireframe)
        {
            if (frontFacing || !useBackfaceCulling)
            {
                g.DrawPolygon(pen, tri);
            }
        }

        if (drawVertices)
        {
            if (frontFacing || !useBackfaceCulling)
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

}

