using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Numerics;
using System.Text;

namespace SPETS.Classes
{
    public class ImportObjectSave
    {
        public string Type;
        public string ModelPath;
        public string TexturePath;
        public float TextureDistance;
        public float TextureSize;
        
        public ImportObject LoadImportObjects()
        {
            Mesh mesh = MeshLoader.FromOBJ(ModelPath);
            ImportObject iObj = new ImportObject(mesh, ModelPath, Type);

            if(TexturePath != "")
            {
                iObj.SetTexture(Image.FromFile(TexturePath), TexturePath);
                iObj.SetTextureDist(TextureDistance);
                iObj.SetTextureSize(TextureSize);
            }

            return iObj;
        }

        public ImportObjectSave LoadFromIObj(ImportObject iObj)
        {
            Type = iObj.Type;
            ModelPath = iObj.ModelPath;
            TexturePath = iObj.TexturePath;
            TextureDistance = iObj.TextureDistance;
            TextureSize = iObj.TextureSize;
            return this;
        }
        
    }

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
    public class ImportObject
    {
        public string Type;

        public string ModelPath;
        public string ModelName;
        public Mesh Model;
        public List<VirtualFace> PreviewZBuffer;

        public Image Texture;
        public string TextureName;
        public string TexturePath;
        public float TextureDistance;
        public float TextureSize;

        public ImportObject(Mesh mesh, string modelPath, string modelType)
        {
            Model = mesh;
            ModelPath = modelPath;
            ModelName = modelPath.Split('\\').Last();
            PreviewZBuffer = new List<VirtualFace>();
            Type = modelType;

            Texture = null;
            TexturePath = "";
            TextureName = "";
            TextureDistance = 0.0f;
            TextureSize = 0.0f;

            // create virtualface
            for (int f = 0; f < Model.Faces.Count; f++)
            {
                // go through face vertices
                List<Vector3> points = new List<Vector3>();
                for (int p = 0; p < Model.Faces[f].Count; p++)
                {
                    points.Add(Model.Vertices[Model.Faces[f][p] - 1]);
                }

                // transform into isometric view
                VirtualFace vFace = new VirtualFace(
                    points,
                    Matrix4x4.CreateRotationY(-0.7853982f) * Matrix4x4.CreateRotationZ(0.7853982f));
                PreviewZBuffer.Add(vFace);
            }
            PreviewZBuffer = PreviewZBuffer.OrderBy(v => v.Position.X).Reverse().ToList();
        }

        public void SetTexture(Image image, string path)
        {
            Texture = image;
            TexturePath = path;
            TextureName = path.Split('\\').Last();
        }
        public void SetTextureDist(float distance)
        {
            TextureDistance = distance;
        }
        public void SetTextureSize(float size)
        {
            TextureSize = size;
        }
        public void ClearTexture()
        {
            Texture = null;
            TextureName = "";
        }
    }
}
