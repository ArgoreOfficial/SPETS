using SPETS.Classes;
using SPETS.forms;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Reflection;

namespace SPETS
{
    public partial class ActionSelectForm : Form
    {
        ImportForm importForm;
        ExportForm exportForm;
        AdvancedEditorForm advImporterForm;
        TerrainEditorForm terrainForm;

        public ActionSelectForm()
        {
            InitializeComponent();


            // Folder Check
            string exePath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
            string[] folders = new string[]
            {
                "cache\\images",
                "cache\\meshes",
                "cache\\blueprints"
            };
            foreach(string folder in folders)
            {
                if (!Directory.Exists(exePath + "\\" + folder))
                {
                    Directory.CreateDirectory(exePath + "\\" + folder);
                }
            }
        }
        private void ActionSelectForm_Load(object sender, EventArgs e)
        {
            ToolDropdown.SelectedIndex = 0;
        }


        private void StartButton_Click(object sender, EventArgs e)
        {

            if (ToolDropdown.SelectedIndex == 0) // import model
            {
                
                OpenFileDialog ofd = new OpenFileDialog();
                ofd.Filter = "Wavefront Model (*.OBJ)|*.OBJ";

                DialogResult dr = ofd.ShowDialog();
                if (dr == DialogResult.OK)
                {
                    Mesh loadMesh = MeshLoader.FromOBJ(ofd.FileName);
                    
                    /// null check
                    if (loadMesh.Faces.Count != 0 && loadMesh.Vertices.Count != 0)
                    {
                        FileInfo file = new FileInfo(ofd.FileName);
                        
                        importForm = new ImportForm(this);
                        importForm.Show();
                        importForm.LoadModel(loadMesh, ofd.FileName.Split('\\').Last().Replace(file.Extension, ""), GetFileSize(file));
                        StartButton.Enabled = false;
                    }
                }
            }
            else if (ToolDropdown.SelectedIndex == 1) // export model 
            {
                
                OpenFileDialog ofd = new OpenFileDialog();
                ofd.Filter = "Sprocket Blueprint (*.BLUEPRINT)|*.BLUEPRINT";

                DialogResult dr = ofd.ShowDialog();
                if (dr == DialogResult.OK)
                {
                    
                    FileInfo file = new FileInfo(ofd.FileName);
                    
                    exportForm = new ExportForm(this);
                    exportForm.Show();
                    exportForm.LoadModel(ofd.FileName, ofd.FileName.Split('\\').Last().Replace(file.Extension, ""), GetFileSize(file));
                    StartButton.Enabled = false;
                }
            }
            else if (ToolDropdown.SelectedIndex == 2) // advanced editor
            {
                advImporterForm = new AdvancedEditorForm(this);
                advImporterForm.Show();
                StartButton.Enabled = false;
            }
            else if (ToolDropdown.SelectedIndex == 3) // terrain editor NOT PUBLIC YET
            {
                OpenFileDialog ofd = new OpenFileDialog();
                ofd.Filter = "Terrain Dump (*.TXT)|*.TXT";

                DialogResult dr = ofd.ShowDialog();
                if (dr == DialogResult.OK)
                {
                    terrainForm = new TerrainEditorForm(this);
                    terrainForm.LoadTerrainData(ofd.FileName);
                    terrainForm.Show();
                    StartButton.Enabled = false;
                }
            }
        }

        public void EnableButton()
        {
            StartButton.Enabled = true;
        }

        string GetFileSize(FileInfo file)
        {
            long fileSize = file.Length;
            string fileSizeString = fileSize.ToString() + " Bytes";
            if (fileSize > 1000000000) { fileSizeString = (fileSize / 1000000000).ToString() + " GB"; }
            else if (fileSize > 1000000) { fileSizeString = (fileSize / 1000000).ToString() + " MB"; }
            else if (fileSize > 1000) { fileSizeString = (fileSize / 1000).ToString() + " KB"; }

            return fileSizeString;
        }
    }
}
