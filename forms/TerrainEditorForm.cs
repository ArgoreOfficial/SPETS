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
using SPETS.Classes;
using System.Drawing.Imaging;
using SharpGL.SceneGraph.Primitives;
using SharpGL.SceneGraph.Assets;
using SharpGL.SceneGraph;
using SharpGL;
using SharpGL.SceneGraph.Lighting;
using SharpGL.Serialization.Wavefront;
using System.Numerics;

namespace SPETS.forms
{

    public partial class TerrainEditorForm : Form
    {
        ActionSelectForm asf;
        List<int> m_Heightmap = new List<int>();
        List<int> m_SplatDatabase = new List<int>();
        int[,] Heightmap2D;
        Vector3 MapScale;
        int MapSize = 0;

        List<float> m_PrecomputedError = new List<float>();

        StringBuilder NewFile;
        string[] file;

        public TerrainEditorForm(ActionSelectForm asf)
        {
            InitializeComponent();
            this.asf = asf;
            TerrainPreview.Scene.RenderBoundingVolumes = false;

            NewFile = new StringBuilder();
        }

        public void LoadTerrainData(string filepath)
        {
            string currentAttribute = "";
            file = File.ReadAllLines(filepath);

            // loop through file
            for (int i = 0; i < file.Length; i++)
            {
                // split lines so individual data can be fetched
                string currentline = file[i];
                string[] splitline = file[i].Trim().Split(" ");
                //int spaceCount = currentline.TakeWhile(Char.IsWhiteSpace).Count(); // indentation count

                // get current attribute
                if (currentline.Contains("m_"))
                {
                    foreach(string line in splitline)
                    {
                        if (!line.Contains("m_")) continue;
                        
                        currentAttribute = line;
                        break;                        
                    }
                }

                // get heightmap data
                if(currentAttribute == "m_Heights")
                {
                    if (!currentline.Contains("data")) continue;
                    
                    int h;
                    if(int.TryParse(splitline.Last(), out h))
                    {
                        m_Heightmap.Add(h * 0 + 1);
                    }
                }
                else if(currentAttribute == "m_PrecomputedError")
                {
                    if (!currentline.Contains("data")) continue;

                    float h;
                    if (float.TryParse(splitline.Last().Replace('.', ','), out h))
                    {
                        m_PrecomputedError.Add(h);
                    }
                }
                else if(currentAttribute == "m_Scale")
                {
                    if (currentline.Contains("float"))
                    {
                        float h;
                        if (float.TryParse(splitline.Last().Replace('.', ','), out h))
                        {
                            if(currentline.Contains("x"))
                            {
                                MapScale.X = h;
                            }
                            else if (currentline.Contains("y"))
                            {
                                MapScale.Y = h;
                            }
                            else if (currentline.Contains("z"))
                            {
                                MapScale.Z = h;
                            }

                        }
                    }
                }
            }

            // make 2d heightmap array
            MapSize = (int)Math.Sqrt(m_Heightmap.Count);
            Heightmap2D = SMath.Make2DArray<int>(m_Heightmap.ToArray(), MapSize, MapSize);
            //Heightmap2D = SMath.Offset<int>(Heightmap2D, new Point(90,0));
        }

        private void TerrainEditorForm_Load(object sender, EventArgs e)
        {
            HeightmapBox.Width = MapSize;
            HeightmapBox.Height = MapSize;
            UpdatePreviews();
        }

        #region MAP_DRAWING

        public void UpdatePreviews()
        {
            // 2d image
            HeightmapBox.Image = new Bitmap(HeightmapBox.Width, HeightmapBox.Height);
            int max = m_Heightmap.Max();

            //int t = 0;
            for (int y = 0; y < HeightmapBox.Width; y++)
            {
                for (int x = 0; x < HeightmapBox.Width; x++)
                {
                    int color = (int)Math.Min(255f * Heightmap2D[x,y] / max, 255f);
                    ((Bitmap)HeightmapBox.Image).SetPixel(x, y, Color.FromArgb(color, color, color));
                    //t++;
                }
            }

            HeightmapBox.Invalidate();
            HeightmapBox.Image.Save("heightmaptemp.png");

            Refresh3D();
        }

        void Refresh3D()
        {
            LoadGLFromFile("mapsquare.obj");

        }

        void LoadGLFromFile(string file)
        {
            // load mesh data (only for obj atm)
            var obj = new ObjFileFormat();
            var objScene = obj.LoadData(file);

            // Get the polygons
            var polygons = objScene.SceneContainer.Traverse<Polygon>().ToList();



            // add polygons

            // texture stream
            byte[] bytes = File.ReadAllBytes("heightmaptemp.png");
            MemoryStream ms = new MemoryStream(bytes);
            Bitmap bm = (Bitmap)Bitmap.FromStream(ms);

            int MaxHeight = m_Heightmap.Max();
            float size = 30f;

            foreach (var polygon in polygons)
            {
                for (int i = 0; i < polygon.Vertices.Count; i++)
                {
                    float x = polygon.Vertices[i].X;
                    float z = polygon.Vertices[i].Z;

                    int hX = (int)((x + 1) / 2 * (MapSize - 1));
                    int hY = (int)((z + 1) / 2 * (MapSize - 1));
                    float y = Heightmap2D[hX, hY] * MapScale.Y / MaxHeight / size;

                    polygon.Vertices[i] = new Vertex(x, y, z);
                }



                polygon.Name = new FileInfo(file).Name.Split(".").First();
                polygon.Transformation.RotateX = 90f;
                polygon.Transformation.ScaleX = MapSize * MapScale.X / size / 2f;
                polygon.Transformation.ScaleZ = MapSize * MapScale.Z / size / 2f;
                //polygon.Transformation.TranslateZ = -MaxHeight / size / 2;
                // textures
                polygon.Material = new Material();
                polygon.Material.Texture = new Texture();
                polygon.Material.Texture.Create(TerrainPreview.OpenGL, bm);
                polygon.Material.Texture.Bind(TerrainPreview.OpenGL);
                polygon.Material.Bind(TerrainPreview.OpenGL);

                polygon.Validate(false);
                polygon.Parent.RemoveChild(polygon);
                polygon.Freeze(TerrainPreview.OpenGL);
                TerrainPreview.Scene.SceneContainer.AddChild(polygon);
            }
        }


        #endregion

        #region GL_DRAWING 

        private void TerrainPreview_OpenGLDraw(object sender, RenderEventArgs args)
        {

        }


        #endregion

        public void SaveMap()
        {
            // heightmap
            StringBuilder m_HeightsSB = new StringBuilder();
            m_HeightsSB.AppendLine("  0 vector m_Heights");
            m_HeightsSB.AppendLine($"   1 Array Array ({m_Heightmap.Count} items)");
            m_HeightsSB.Append($"    0 int size = {m_Heightmap.Count}");

            // precompiled, idk what this does yet lol
            StringBuilder m_PrecomputedErrorSB = new StringBuilder();
            m_PrecomputedErrorSB.AppendLine("  0 vector m_PrecomputedError");
            m_PrecomputedErrorSB.AppendLine($"   1 Array Array({m_PrecomputedError.Count} items)");
            m_PrecomputedErrorSB.Append($"    0 int size = {m_PrecomputedError.Count}");

            // detailpatches, grass and trees
            StringBuilder m_Patches = new StringBuilder();
            m_Patches.AppendLine("  0 vector m_Patches");
            m_Patches.AppendLine("   1 Array Array (256 items)");
            m_Patches.Append(    "    0 int size = 256");


            Debug.WriteLine("Saving...");

            string currentAttribute = "";
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

                        currentAttribute = line;
                        if (currentAttribute == "m_Heights")
                        {
                            NewFile.AppendLine(m_HeightsSB.ToString());

                            int n = 0;
                            // create new heightmap points
                            for (int y = 0; y < MapSize; y++)
                            {
                                for (int x = 0; x < MapSize; x++)
                                {
                                    int newint = m_Heightmap[x * MapSize + y];
                                    NewFile.AppendLine($"    [{n}]");
                                    NewFile.AppendLine($"     0 SInt16 data = {newint}");
                                    n++;
                                }
                            }
                        }
                        else if (currentAttribute == "m_PrecomputedError")
                        {
                            NewFile.AppendLine(m_PrecomputedErrorSB.ToString());

                            int n = 0;
                            float highestF = m_PrecomputedError.Min();
                            // create new precomputedError points
                            foreach(float f in m_PrecomputedError)
                            {
                                NewFile.AppendLine($"    [{n}]");
                                NewFile.AppendLine($"     0 float data = {highestF.ToString().Replace(',','.')}");
                                n++;
                            }
                        }
                        else if (currentAttribute == "m_Patches")
                        {
                            NewFile.AppendLine(m_Patches.ToString());

                            // create detailDatabase
                            for (int patch = 0; patch < 256; patch++)
                            {
                                NewFile.AppendLine($"    [{patch}]");
                                NewFile.AppendLine("     0 DetailPatch data");
                                NewFile.AppendLine("      0 vector layerIndices");
                                NewFile.AppendLine("       1 Array Array (0 items)");
                                NewFile.AppendLine("        0 int size = 0");
                                NewFile.AppendLine("      0 vector numberOfObjects");
                                NewFile.AppendLine("       1 Array Array (0 items)");
                                NewFile.AppendLine("        0 int size = 0");
                            }
                        }
                        else if (currentAttribute == "m_MinMaxPatchHeights")
                        {
                            NewFile.AppendLine("  0 vector m_MinMaxPatchHeights");
                            NewFile.AppendLine("   1 Array Array (2730 items)");
                            NewFile.AppendLine("    0 int size = 2730");

                            // create detailDatabase
                            for (int patch = 0; patch < 2730; patch++)
                            {
                                NewFile.AppendLine($"    [{patch}]");
                                NewFile.AppendLine( "     0 float data = 0");
                            }
                        }


                        break;
                    }
                }

                if (currentAttribute == "m_Heights") continue;
                if (currentAttribute == "m_PrecomputedError") continue;
                if (currentAttribute == "m_Patches") continue;
                if (currentAttribute == "m_MinMaxPatchHeights") continue;

                NewFile.AppendLine(currentline);

            }
            Debug.WriteLine("Done");
            File.WriteAllText("NewFile.txt", NewFile.ToString());

        }


        private void RotateClockwiseButton_Click(object sender, EventArgs e)
        {
            Heightmap2D = SMath.RotateClockwise<int>(Heightmap2D);
            TerrainPreview.Scene.SceneContainer.Children.Remove(TerrainPreview.Scene.SceneContainer.Children.Last());
            UpdatePreviews();
        }

        private void SaveButton_Click(object sender, EventArgs e)
        {
            SaveMap();
        }
    }
}
