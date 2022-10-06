using System;
using System.Collections.Generic;
using System.IO;
using System.Numerics;
using System.Text;

namespace SPETS.Classes
{
    public class Mesh
    {
        public List<Vector3> Vertices;
        public List<List<int>> Faces;

        public Mesh()
        {
            Vertices = new List<Vector3>();
            Faces = new List<List<int>>();
        }
    }

    static class MeshLoader
    {
        public static Mesh LoadOBJ(string filePath)
        {
            Mesh objMesh = new Mesh();

            string[] file = File.ReadAllLines(filePath);

            for (int i = 0; i < file.Length; i++) // vertex
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
                else if (file[i][0] == 'f' && // face
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
            }



            return objMesh;
        }
    }
}
