using Newtonsoft.Json;
using SharpGL.SceneGraph;
using SharpGL.SceneGraph.Assets;
using SharpGL.SceneGraph.Primitives;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Globalization;
using System.IO;
using System.Linq;
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

        /// <summary>
        /// returns a SharpGL formatted list of polygons
        /// </summary>
        /// <returns></returns>
        public List<Polygon> GetPolygons()
        {
            // create list of polygons
            List<Polygon> polygons = new List<Polygon>();

            // loop through faces
            foreach (List<int> face in Faces)
            {
                // create current polygon and faces
                Polygon p = new Polygon();
                List<Vertex> faceVertices = new List<Vertex>();
                
                // loop through each vertex index
                foreach(int i in face)
                {
                    Vector3 vertex = Vertices[i];
                    faceVertices.Add(new Vertex(vertex.X, vertex.Y, vertex.Z));
                }

                p.Validate(true);
                // add to polyon
                p.AddFaceFromVertexData(faceVertices.ToArray());
                polygons.Add(p);
            }

            return polygons;
        }

    }

    static class MeshLoader
    {
        public static Mesh FromOBJ(string filePath)
        {
            Mesh objMesh = new Mesh();
            Thread.CurrentThread.CurrentCulture = new CultureInfo("se-SV");

            string[] file = File.ReadAllLines(filePath);

            for (int i = 0; i < file.Length; i++) // load vertices
            {
                string[] vertexString = file[i].Split(' ');
                if (file[i][0] == 'v' &&
                    file[i][1] == ' ')
                {
                    // split coords
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

        public static List<Mesh> FromBlueprint(string filePath)
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
