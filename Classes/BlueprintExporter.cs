using Newtonsoft.Json;
using System;
using System.Linq;
using System.Text;
using System.IO;
using System.Diagnostics;

namespace SPETS.Classes
{


    static class BlueprintExporter
    {
        //Root blueprint = JsonConvert.DeserializeObject<Root>();

        public static void Export(string filePath, string saveName)
        {
            StringBuilder saveFileSB = new StringBuilder();

            // get file
            string[] blueprintFile = File.ReadAllLines(filePath);
            int totalVertices = 0;


            // go through lines
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
                        // object
                        saveFileSB.Append($"o {DataRoot.name}\n");
                        


                        // vertices
                        for (int p = 0; p < DataRoot.compartment.points.Count; p+=3)
                        {

                            // add compartment position
                            if (Settings.Utility.RetainCompartmentPosition)
                            {
                                DataRoot.compartment.points[p] += DataRoot.pos[0];
                                DataRoot.compartment.points[p + 1] += DataRoot.pos[1];
                                DataRoot.compartment.points[p + 2] += DataRoot.pos[2];
                            }

                            // add vertex
                            saveFileSB.Append(
                            $"v " +
                            $"{(-DataRoot.compartment.points[p]).ToString().Replace(",", ".")} " +
                            $"{DataRoot.compartment.points[p + 1].ToString().Replace(",", ".")} " +
                            $"{DataRoot.compartment.points[p + 2].ToString().Replace(",", ".")}\n");
                            
                        }

                        //faces
                        for (int f = 0; f < DataRoot.compartment.faceMap.Count; f++)
                        {

                            for (int n = 0; n < DataRoot.compartment.faceMap[f].Count; n+=3)
                            {
                                saveFileSB.Append(
                                    $"f " +
                                    $"{DataRoot.compartment.faceMap[f][n] + 1 + totalVertices} " +
                                    $"{DataRoot.compartment.faceMap[f][n + 1] + 1 + totalVertices} " +
                                    $"{DataRoot.compartment.faceMap[f][n + 2] + 1 + totalVertices}\n");     
                            }

                        }


                        totalVertices += DataRoot.compartment.points.Count / 3;
                    }
                }
            }

            if(!Directory.Exists("chache\\exports"))
            {
                Directory.CreateDirectory("chache\\exports");
            }
            File.WriteAllText($"chache\\exports\\{saveName}.obj", saveFileSB.ToString());
            Process.Start("chache\\exports");
        }
    }
}
