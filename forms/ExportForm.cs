using Newtonsoft.Json;
using SPETS.Classes;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace SPETS.forms
{
    public partial class ExportForm : Form
    {
        ActionSelectForm asf;

        string filePath;
        string fileName;
        bool keepCompartmentPosition;

        public ExportForm(ActionSelectForm asf)
        {
            InitializeComponent();
            this.asf = asf;
        }

        public void LoadModel(string filepath, string name, string fileSize)
        {
            filePath = filepath;
            fileName = name;
            FileNameLabel.Text = name;
            FileSizeLabel.Text = fileSize;
        }



        private void ExportButton_Click(object sender, EventArgs e)
        {
            keepCompartmentPosition = KeepCompPosCheckBox.Checked;
            ExportButton.Enabled = false;
            ExportWorker.RunWorkerAsync();
        }



        private void ExportWorker_DoWork(object sender, DoWorkEventArgs e)
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
                        for (int p = 0; p < DataRoot.compartment.points.Count; p += 3)
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

                            for (int n = 0; n < DataRoot.compartment.faceMap[f].Count; n += 3)
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

                ExportWorker.ReportProgress((int)((float)i / blueprintFile.Length * 100f));
            }


            // create obj file

            string documents = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);
            string sprocketFolder = $"{documents}\\My Games\\Sprocket";

            if (!Directory.Exists($"{sprocketFolder}\\Exports"))
            {
                Directory.CreateDirectory($"{sprocketFolder}\\Exports");
            }
            Directory.CreateDirectory($"{sprocketFolder}\\Exports\\{fileName}");
            File.WriteAllText($"{sprocketFolder}\\Exports\\{fileName}\\{fileName}.obj", saveFileSB.ToString());

            ExportWorker.ReportProgress(100);

            Process.Start(Environment.GetEnvironmentVariable("WINDIR") + @"\explorer.exe", $"{sprocketFolder}\\Exports\\{fileName}");
        }

        private void ExportWorker_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            ExportingProgress.Value = e.ProgressPercentage;
        }

        private void ExportForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            asf.EnableButton();
        }
    }
}
