using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Numerics;
using System;
using Newtonsoft.Json;
using SPETS.Classes;

namespace SPETS.Classes
{

    static class MeshImporter
    {
        public static bool ImportJson(string filePath, string savePath, string saveName)
        {
            Mesh loaded = MeshLoader.LoadOBJ(filePath);
            CompartmentRoot compRoot = new CompartmentRoot(saveName);
            List<Vector3> vectorPoints = new List<Vector3>(); // used for checking vertices with x y and z
            /// null check
            if (loaded.Faces.Count == 0 || loaded.Vertices.Count == 0)
            {
                return false;
            }

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

                for (int p2 = p1+1; p2 < vectorPoints.Count; p2++)
                {
                    if(vectorPoints[p1] == vectorPoints[p2])
                    {
                        shared.Add(p2);
                        foundIndexes.Add(p2);
                    }
                }

                compRoot.compartment.sharedPoints.Add(shared);
            }

            if(!Directory.Exists($"{savePath}/Blueprints/Compartments"))
            {
                Directory.CreateDirectory($"{savePath}/Blueprints/Compartments");
            }

            CompartmentBaseRoot cbRoot = new CompartmentBaseRoot("Compartment", JsonConvert.SerializeObject(compRoot), "");
            File.WriteAllText($"{savePath}/Blueprints/Compartments/{saveName}.blueprint", $"[\n{JsonConvert.SerializeObject(cbRoot, Formatting.Indented)},\n]");

            return true;
        }

        static List<int> CreateNGon(int length, int offset)
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
    }
}
