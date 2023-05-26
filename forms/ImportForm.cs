using Newtonsoft.Json;
using SPETS.Classes;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using System.Xml.Linq;

namespace SPETS.forms
{
    public partial class ImportForm : Form
    {
        ActionSelectForm asf;

        Mesh[] loadedMeshes;
        CompartmentRoot compRoot;
        List<Vector3> vectorPoints = new List<Vector3>(); // used for checking vertices with x y and z
        string[] factions;
        string[] saveNames;
        int totalWork;
        int selectedFaction;

        public ImportForm(ActionSelectForm asf)
        {
            InitializeComponent();
            this.asf = asf;
        }

        private void ImportForm_Load(object sender, EventArgs e)
        {
            string documents = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);
            string factionsFolder = $"{documents}/My Games/Sprocket/Factions/";
            factions = Directory.GetDirectories(factionsFolder);

            for (int i = 0; i < factions.Length; i++)
            {
                FactionsCombobox.Items.Add(factions[i].Split('/').Last());
            }
            FactionsCombobox.SelectedIndex = 0;
        }
        
        public void LoadModel(Mesh[] meshes, string[] names)
        {
            loadedMeshes = meshes;
            saveNames = names;
        }

        private void ImportButton_Click(object sender, EventArgs e)
        {
            ImportWorker.RunWorkerAsync();
            ImportButton.Enabled = false;
            selectedFaction = FactionsCombobox.SelectedIndex;
        }


        List<int> CreateNGon(int length, int offset)
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

        private void ImportWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            Thread.CurrentThread.CurrentCulture = new CultureInfo("sv-SE");

            for (int i = 0; i < loadedMeshes.Length; i++)
            {
                totalWork += loadedMeshes[i].Vertices.Count;
            }

            for (int meshI = 0; meshI < loadedMeshes.Length; meshI++)
            {
                Mesh currentMesh = loadedMeshes[meshI];
                compRoot = new CompartmentRoot(saveNames[meshI]);
                string saveName = saveNames[meshI];


                for (int i = 0; i < currentMesh.Faces.Count; i++)
                {
                    for (int f = 0; f < currentMesh.Faces[i].Count; f++)
                    {
                        totalWork += 4;
                    }
                }
                int doneWork = 0;



                for (int f = 0; f < currentMesh.Faces.Count; f++)
                {
                    doneWork++;
                    ImportWorker.ReportProgress((int)((float)doneWork / totalWork * 100f));

                    // null face check
                    if (currentMesh.Faces[f].Count < 3 || currentMesh.Faces[f].Count > ResourceHandler.NGonLookup.Count) continue;

                    // faces
                    compRoot.compartment.faceMap.Add(CreateNGon(currentMesh.Faces[f].Count, compRoot.compartment.points.Count / 3));

                    // vertices
                    for (int fP = 0; fP < currentMesh.Faces[f].Count; fP++)
                    {
                        compRoot.compartment.points.Add(-currentMesh.Vertices[currentMesh.Faces[f][fP] - 1].X);
                        compRoot.compartment.points.Add(currentMesh.Vertices[currentMesh.Faces[f][fP] - 1].Y);
                        compRoot.compartment.points.Add(currentMesh.Vertices[currentMesh.Faces[f][fP] - 1].Z);

                        vectorPoints.Add(currentMesh.Vertices[currentMesh.Faces[f][fP] - 1] * new Vector3(-1, 1, 1));
                    }
                }



                // thicknessmap
                for (int i = 0; i < compRoot.compartment.points.Count; i++)
                {
                    doneWork++;
                    ImportWorker.ReportProgress((int)((float)doneWork / totalWork * 100f));

                    compRoot.compartment.thicknessMap.Add(1);
                }



                // sharedpoints
                List<int> foundIndexes = new List<int>();
                for (int p1 = 0; p1 < vectorPoints.Count; p1++)
                {
                    doneWork++;
                    ImportWorker.ReportProgress((int)((float)doneWork / totalWork * 100f));
                    if (foundIndexes.Contains(p1)) continue;

                    List<int> shared = new List<int>();

                    shared.Add(p1);

                    for (int p2 = p1 + 1; p2 < vectorPoints.Count; p2++)
                    {
                        if (vectorPoints[p1] == vectorPoints[p2])
                        {
                            shared.Add(p2);
                            foundIndexes.Add(p2);
                        }
                    }

                    compRoot.compartment.sharedPoints.Add(shared);
                }



                string savePath = factions[selectedFaction];

                if (!Directory.Exists($"{savePath}/Blueprints/Compartments"))
                {
                    Directory.CreateDirectory($"{savePath}/Blueprints/Compartments");
                }
                string compJson = JsonConvert.SerializeObject(compRoot);

                CompartmentBaseRoot cbRoot = new CompartmentBaseRoot("Compartment", compJson, "");
                File.WriteAllText($"{savePath}/Blueprints/Compartments/{saveName}.blueprint", $"[\n{JsonConvert.SerializeObject(cbRoot, Formatting.Indented)},\n]");
            }

            ImportWorker.ReportProgress(100);
            MessageBox.Show("Import finished", "Import finished", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void ImportWorker_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            if(e.ProgressPercentage <= 100)
            {
                ImportingProgress.Value = e.ProgressPercentage;
            }
            else
            {
                ImportingProgress.Value = 100;
            }
        }

        private void ImportForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            asf.EnableButton();
        }
    }
}
