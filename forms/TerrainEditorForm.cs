using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;
using System.Linq;
using System.Diagnostics;

namespace SPETS.forms
{

    public partial class TerrainEditorForm : Form
    {
        ActionSelectForm asf;
        List<int> heightmap = new List<int>();
        StringBuilder newFile;
        string FilePath;
        string[] file;

        public TerrainEditorForm(ActionSelectForm asf)
        {
            InitializeComponent();
            newFile = new StringBuilder();
            this.asf = asf;
        }

        public void LoadTerrainData(string filepath)
        {
            file = File.ReadAllLines(filepath);
            FilePath = filepath;

            Debug.WriteLine(file.Length);
            
            string location = "";
            for (int i = 0; i < file.Length; i++)
            {
                string currentline = file[i];
                string[] splitline = file[i].Trim().Split(" ");
                
                int spaceCount = currentline.TakeWhile(Char.IsWhiteSpace).Count();
                if(spaceCount <= 2)
                {
                    if (!currentline.Contains("m_")) continue;

                    foreach(string line in splitline)
                    {
                        if(line.Contains("m_"))
                        {
                            location = line;
                            break;
                        }
                    }
                }
                
                if(location == "m_Heights")
                {
                    if (!currentline.Contains("data")) continue;
                    
                    int h;
                    if(int.TryParse(splitline.Last(), out h))
                    {
                        heightmap.Add(h);
                    }
                }
            }

            Debug.WriteLine(heightmap.Count);
            Debug.WriteLine(Math.Sqrt(heightmap.Count));
        }

        private void TerrainEditorForm_Load(object sender, EventArgs e)
        {
            int mapsize = (int)Math.Sqrt(heightmap.Count);
            //List<int> newHeight = new List<int>();
            StringBuilder heightmapSB = new StringBuilder();
            heightmapSB.AppendLine("  0 vector m_Heights");
            heightmapSB.AppendLine($"   1 Array Array ({heightmap.Count} items)");
            heightmapSB.AppendLine($"    0 int size = {heightmap.Count}");
            Debug.WriteLine("Saving...");

            string location = "";
            for (int i = 0; i < file.Length; i++)
            {
                string currentline = file[i];
                string[] splitline = file[i].Trim().Split(" ");

                int spaceCount = currentline.TakeWhile(Char.IsWhiteSpace).Count();
                if (spaceCount <= 2 && currentline.Contains("m_"))
                {
                    foreach (string line in splitline)
                    {
                        if (!line.Contains("m_")) continue;
                        
                        location = line;
                        if (location == "m_Heights")
                        {
                            newFile.AppendLine(heightmapSB.ToString());


                            Debug.WriteLine("   Flipping");
                            int n = 0;
                            // create new heightmap points
                            for (int y = 0; y < mapsize; y++)
                            {
                                for (int x = 0; x < mapsize; x++)
                                {
                                    int newint = heightmap[x * mapsize + y];
                                    newFile.AppendLine($"    [{n}]");
                                    newFile.AppendLine($"     0 SInt16 data = {newint}");
                                    n++;
                                }
                            }
                            Debug.WriteLine($"   Done. {n}");
                        }

                        break;
                    }
                }

                if (location == "m_Heights") continue;

                newFile.AppendLine(currentline);

            }
            Debug.WriteLine("Done");
            File.WriteAllText("NewFile.txt", newFile.ToString());
            
            
            HeightmapBox.Width = (int)Math.Sqrt(heightmap.Count);
            HeightmapBox.Height = (int)Math.Sqrt(heightmap.Count);
            UpdateHeightmapImage();
        }

        public void UpdateHeightmapImage()
        {
            HeightmapBox.Image = new Bitmap(HeightmapBox.Width, HeightmapBox.Height);
            int max = heightmap.Max();

            int t = 0;
            for (int y = 0; y < HeightmapBox.Width; y++)
            {
                for (int x = 0; x < HeightmapBox.Width; x++)
                {
                    int color = (int)Math.Min(255f * heightmap[t] / max, 255f);
                    ((Bitmap)HeightmapBox.Image).SetPixel(x, y, Color.FromArgb(color, color, color));
                    t++;
                }

            }
            HeightmapBox.Invalidate();
        }
    }
}
