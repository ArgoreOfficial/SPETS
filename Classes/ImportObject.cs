using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Reflection;
using System.Text;

namespace SPETS.Classes
{
    public class ImportObjectSave
    {
        public string Type;
        public string ModelName;
        public string TextureName;
        public float TextureDistance;
        public float TextureSize;
        
        public ImportObject LoadImportObjects()
        {
            string exeRoot = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
            Mesh mesh = null;
            if (Type == "mesh")
            {
                mesh = MeshLoader.FromOBJ(exeRoot + "\\Meshes\\" + ModelName);
            }
            else if (Type == "blueprint")
            {
                List<Mesh> blueprintMeshes = MeshLoader.FromBlueprint(exeRoot + "\\Blueprints\\" + ModelName.Split("/")[0]);

                int i;
                if(int.TryParse(ModelName.Split("/")[1], out i))
                {
                    mesh = blueprintMeshes[i];
                }
            }

            if (mesh != null)
            {
                ImportObject iObj = new ImportObject(mesh, ModelName, Type);

                if(TextureName != "")
                {
                    iObj.SetTexture(Image.FromFile(exeRoot + "\\Images\\" + TextureName), exeRoot + "\\Images\\" + TextureName);
                    iObj.SetTextureDist(TextureDistance);
                    iObj.SetTextureSize(TextureSize);
                }
                return iObj;
            }

            return null;
        }

        public ImportObjectSave LoadFromIObj(ImportObject iObj)
        {
            Type = iObj.Type;
            TextureName = iObj.TextureName; 
            ModelName = iObj.ModelName;
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

        public string ModelName;
        public Mesh Model;
        public List<VirtualFace> PreviewZBuffer;

        public Image Texture;
        public string TextureName;
        public float TextureDistance;
        public float TextureSize;

        public ImportObject(Mesh mesh, string modelName, string modelType)
        {
            Model = mesh;
            ModelName = modelName.Split("\\").Last();
            PreviewZBuffer = new List<VirtualFace>();
            Type = modelType;

            Texture = null;
            TextureName = "";
            TextureDistance = 0.749f;
            TextureSize = 0.999f;


            string[] imageTypes = new string[]
            {
                ".bmp",
                ".gif",
                ".jpg",
                ".jpeg",
                ".png",
                ".tiff"
            };
            for (int i = 0; i < imageTypes.Length; i++)
            {
                string file = modelName.Replace(new FileInfo(modelName).Extension, imageTypes[i]);
                if (File.Exists(file))
                {
                    // copy files to root folders
                    string exePath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
                    FileInfo info = new FileInfo(file);

                    File.Copy(info.FullName, exePath + "\\Images\\" + info.FullName.Split("\\").Last(), true);

                    SetTexture(Image.FromFile(file), file);
                    break;
                }
            }

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
            TextureName = path.Split('\\').Last();

            string documents = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);
            string decalsFolder = $"{documents}\\My Games\\Sprocket\\Decals";
            if(!Directory.Exists(decalsFolder))
            {
                Directory.CreateDirectory(decalsFolder);
            }

            File.Copy(path, decalsFolder + "\\" + TextureName, true);
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
