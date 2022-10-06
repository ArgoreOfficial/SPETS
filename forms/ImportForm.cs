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
using System.Numerics;
using System.Text;
using System.Windows.Forms;

namespace SPETS.forms
{
    public partial class ImportForm : Form
    {
        Mesh loaded;
        CompartmentRoot compRoot;
        List<Vector3> vectorPoints = new List<Vector3>(); // used for checking vertices with x y and z
        string[] factions;
        string saveName;

        public ImportForm()
        {
            InitializeComponent();
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

        public void LoadModel(Mesh mesh, string name, string fileSize)
        {
            loaded = mesh;
            compRoot = new CompartmentRoot(name);
            saveName = name;
            FileNameLabel.Text = name;
            FileSizeLabel.Text = fileSize + " bytes";
        }

        private void ImportButton_Click(object sender, EventArgs e)
        {
            faceWorker.RunWorkerAsync();
            ImportButton.Enabled = false;

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

        private void faceWorker_DoWork(object sender, DoWorkEventArgs e)
        {
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

                faceWorker.ReportProgress((int)(MathF.Ceiling((float)f / (loaded.Faces.Count - 1)) * 100.0f));

            }
        }

       

        private void thicknessWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            // thicknessmap
            for (int i = 0; i < compRoot.compartment.points.Count; i++)
            {
                compRoot.compartment.thicknessMap.Add(1);

                thicknessWorker.ReportProgress((int)(MathF.Ceiling((float)i / (compRoot.compartment.points.Count - 1)) * 100.0f));
            }
        }

        private void sharedPointWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            // sharedpoints
            List<int> foundIndexes = new List<int>();
            for (int p1 = 0; p1 < vectorPoints.Count; p1++)
            {
                
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

                sharedPointWorker.ReportProgress((int)(MathF.Ceiling((float)p1 / (vectorPoints.Count - 1)) * 100.0f));
            }
        }

        private void faceWorker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            sharedPointWorker.RunWorkerAsync();
            thicknessWorker.RunWorkerAsync();
        }
        private void faceWorker_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            PolygonProgress.Value = e.ProgressPercentage;
        }

        private void sharedPointWorker_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            SharedPointsProgress.Value = e.ProgressPercentage;
        }

        private void thicknessWorker_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            ThicknessMapProgress.Value = e.ProgressPercentage;
        }

        private void sharedPointWorker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if(!thicknessWorker.IsBusy)
            {
                SaveFile();
            }
        }

        private void thicknessWorker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (!thicknessWorker.IsBusy)
            {
                SaveFile();
            }
        }

        void SaveFile()
        {
            string savePath = factions[FactionsCombobox.SelectedIndex];

            if (!Directory.Exists($"{savePath}/Blueprints/Compartments"))
            {
                Directory.CreateDirectory($"{savePath}/Blueprints/Compartments");
            }

            CompartmentBaseRoot cbRoot = new CompartmentBaseRoot("Compartment", JsonConvert.SerializeObject(compRoot), "");
            File.WriteAllText($"{savePath}/Blueprints/Compartments/{saveName}.blueprint", $"[\n{JsonConvert.SerializeObject(cbRoot, Formatting.Indented)},\n]");
        }
    }
}
