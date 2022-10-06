using System.Text;
using System.IO;
using Newtonsoft.Json;
using System;
using System.Linq;
using System.Collections.Generic;
using System.Numerics;

namespace SPETS.Classes
{
    static class CompartmentMerger
    {

        public static void MergeAll(string filePath)
        {
            CompartmentRoot newCompartment = new CompartmentRoot("TEST");
            string[] blueprintFile = File.ReadAllLines(filePath);
            List<CompartmentRoot> compartments = new List<CompartmentRoot>();
            List<Vector3> posOffsets = new List<Vector3>();

            // go through file and get all compartments
            for (int i = 0; i < blueprintFile.Length; i++)
            {
                if (blueprintFile[i] == "    \"id\": \"Compartment\"," ||
                    blueprintFile[i] == "      \"id\": \"Compartment\",")
                {

                    // isolate compartment
                    string[] compartmentTest = blueprintFile.Skip(i - 1).Take(5).ToArray();
                    compartmentTest[4] = compartmentTest[4].Trim(',');

                    // deserialize
                    var BaseRoot = JsonConvert.DeserializeObject<CompartmentBaseRoot>(string.Join("", compartmentTest));
                    var DataRoot = JsonConvert.DeserializeObject<CompartmentRoot>(BaseRoot.data);


                    if (DataRoot.compartment != null)
                    {
                        compartments.Add(DataRoot);
                    }
                }
            }

            
            int verticesCount = 0;

            for (int i = 0; i < compartments.Count; i++)
            {

                /*// add rotation
                for (int p = 0; p < compartments[i].compartment.points.Count; p+=3)
                {
                    double radX = compartments[i].rot[0] * Math.PI / 180.0;
                    double radY = compartments[i].rot[1] * Math.PI / 180.0;
                    double radZ = compartments[i].rot[2] * Math.PI / 180.0;

                    compartments[i].compartment.points[p] *= radX;
                    compartments[i].compartment.points[p + 1] *= radY;
                    compartments[i].compartment.points[p + 2] *= radZ;
                }*/

                // add offset
                posOffsets.Add(new Vector3());
                if (compartments[i].parentID != -1)
                {
                    for (int o = compartments[i].parentID; o >= 0; o--)
                    {
                        posOffsets[i] += new Vector3(
                            (float)compartments[o].pos[0],
                            (float)compartments[o].pos[1],
                            (float)compartments[o].pos[2]
                            );
                    }
                }



                // thicknessmap
                newCompartment.compartment.points.AddRange(compartments[i].compartment.points);

                // add vertices
                for (int p = 0; p < compartments[i].compartment.points.Count; p+=3)
                {
                    newCompartment.compartment.points.Add(compartments[i].compartment.points[p] + (double)posOffsets[i].X);
                    newCompartment.compartment.points.Add(compartments[i].compartment.points[p + 1] + (double)posOffsets[i].Y);
                    newCompartment.compartment.points.Add(compartments[i].compartment.points[p + 2] + (double)posOffsets[i].Z);
                }

                newCompartment.compartment.thicknessMap.AddRange(compartments[i].compartment.thicknessMap);

                if (i == 0)
                {
                    newCompartment.compartment.faceMap.AddRange(compartments[i].compartment.faceMap);
                }
                else
                {
                    // go through faces
                    for (int f = 0; f < compartments[i].compartment.faceMap.Count; f++)
                    {
                        List<int> newFace = new List<int>();

                        // a singular face
                        for (int fI = 0; fI < compartments[i].compartment.faceMap[f].Count; fI++)
                        {
                            newFace.Add(compartments[i].compartment.faceMap[f][fI] + verticesCount);
                        }   
                        newCompartment.compartment.faceMap.Add(newFace);
                    }

                    // go through sharedpoints
                    for (int sp = 0; sp < compartments[i].compartment.sharedPoints.Count; sp++)
                    {
                        List<int> newSharedPoint = new List<int>();

                        // a singular sharedPoint
                        for (int spI = 0; spI < compartments[i].compartment.sharedPoints[sp].Count; spI++)
                        {
                            newSharedPoint.Add(compartments[i].compartment.sharedPoints[sp][spI] + verticesCount);
                        }
                        newCompartment.compartment.sharedPoints.Add(newSharedPoint);
                    }
                }

                
                verticesCount += compartments[i].compartment.points.Count / 3;
            }

            CompartmentBaseRoot jsonFile = new CompartmentBaseRoot("Compartment", JsonConvert.SerializeObject(newCompartment), "");

            File.WriteAllText("TEST2.blueprint", JsonConvert.SerializeObject(jsonFile));
        }
    }
}
