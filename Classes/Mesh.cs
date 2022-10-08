using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Numerics;
using System.Text;
using System.Threading;

namespace SPETS.Classes
{
    public class Mesh
    {
        public List<Vector3> Vertices;
        public List<List<int>> Faces;
        public List<Vector3> Normals;

        public Mesh()
        {
            Vertices = new List<Vector3>();
            Faces = new List<List<int>>();
            Normals = new List<Vector3>();
        }
    }

    static class MeshLoader
    {
        public static Mesh LoadOBJ(string filePath)
        {
            Mesh objMesh = new Mesh();
            Thread.CurrentThread.CurrentCulture = new CultureInfo("se-SV");

            string[] file = File.ReadAllLines(filePath);

            for (int i = 0; i < file.Length; i++) // load vertices
            {
                if (file[i][0] == 'v' &&
                    file[i][1] == ' ')
                {
                    // split coords
                    string[] vertexString = file[i].Split(' ');
                    Vector3 vertex = new Vector3(
                            float.Parse(vertexString[1].Replace(".", ",")),
                            float.Parse(vertexString[2].Replace(".", ",")),
                            float.Parse(vertexString[3].Replace(".", ","))
                        );


                    objMesh.Vertices.Add(vertex);
                }
                else if (file[i][0] == 'f' && // load faces
                         file[i][1] == ' ')
                {

                    // split indexes
                    string[] faceString = file[i].Split(' ');
                    List<int> faceIndexes = new List<int>();

                    // get only vertex index
                    for (int f = 1; f < faceString.Length; f++)
                    {
                        faceIndexes.Add(int.Parse(faceString[f].Split('/')[0]));
                    }
                    objMesh.Faces.Add(faceIndexes);
                }
                else if (file[i][0] == 'v' && // load normals
                         file[i][1] == 'n')
                {
                    // split coords
                    string[] normalString = file[i].Split(' ');
                    Vector3 normal = new Vector3(
                            float.Parse(normalString[1].Replace(".", ",")),
                            float.Parse(normalString[2].Replace(".", ",")),
                            float.Parse(normalString[3].Replace(".", ","))
                        );


                    objMesh.Normals.Add(normal);
                }
            }



            return objMesh;
        }
    }
}
