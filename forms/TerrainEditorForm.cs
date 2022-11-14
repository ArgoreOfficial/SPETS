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

namespace SPETS.forms
{

    public partial class TerrainEditorForm : Form
    {
        ActionSelectForm asf;
        List<int> Heightmap = new List<int>();
        int[,] Heightmap2D;
        int MapSize = 0;

        StringBuilder NewFile;
        string[] file;

        public TerrainEditorForm(ActionSelectForm asf)
        {
            InitializeComponent();
            TerrainPreview.Scene.RenderBoundingVolumes = false;

            NewFile = new StringBuilder();
            this.asf = asf;
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
                        Heightmap.Add(h);
                    }
                }
            }

            // make 2d heightmap array
            MapSize = (int)Math.Sqrt(Heightmap.Count);
            Heightmap2D = SMath.Make2DArray<int>(Heightmap.ToArray(), MapSize, MapSize);
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
            int max = Heightmap.Max();

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
            HeightmapBox.Image.Save("heightmaptemp", ImageFormat.Bmp);

            Refresh3D();

        }

        void Refresh3D()
        {
            // texture

            OpenGL gl = TerrainPreview.OpenGL;
            Bitmap image = new Bitmap("heightmaptemp");
            uint[] textures = new uint[1];

            gl.Enable(OpenGL.GL_TEXTURE_2D);
            gl.GenTextures(1, textures);

            gl.TexImage2D(
                OpenGL.GL_TEXTURE_2D,
                0,
                3,
                HeightmapBox.Width,
                HeightmapBox.Height,
                0,
                OpenGL.GL_BGR,
                OpenGL.GL_UNSIGNED_BYTE,
                image.LockBits(new Rectangle(0,0, HeightmapBox.Width, HeightmapBox.Height),
                ImageLockMode.ReadOnly,
                PixelFormat.Format24bppRgb).Scan0);

            gl.TexParameter(OpenGL.GL_TEXTURE_2D, OpenGL.GL_TEXTURE_MIN_FILTER, OpenGL.GL_LINEAR);

            


            // 3d model
            List<Polygon> polygons = new List<Polygon>();

            Polygon mapPolygon = new Polygon();
            mapPolygon.Material = new Material();

            mapPolygon.Material.Texture.Create(TerrainPreview.OpenGL, "heightmaptemp");

            mapPolygon.CreateFromMap("heightmaptemp", HeightmapBox.Width, HeightmapBox.Height);
            mapPolygon.Transformation.RotateX = 90f;

            int sizeX = 10;
            int sizeY = 10;

            mapPolygon.Transformation.ScaleX = sizeX;
            mapPolygon.Transformation.ScaleZ = sizeY;

            mapPolygon.Transformation.TranslateX = -(sizeX / 2);
            mapPolygon.Transformation.TranslateY = sizeY / 2;

            polygons.Add(mapPolygon);

            foreach (var polygon in polygons)
            {
                polygon.Name = "Mesh";


                polygon.Freeze(TerrainPreview.OpenGL);
                TerrainPreview.Scene.SceneContainer.AddChild(polygon);

                for (int i = 0; i < polygon.Vertices.Count; i++)
                {
                    polygon.UVs.Add(new UV(polygon.Vertices[i].X, polygon.Vertices[i].Y));
                }
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
            int mapsize = (int)Math.Sqrt(Heightmap.Count);
            //List<int> newHeight = new List<int>();
            StringBuilder heightmapSB = new StringBuilder();
            heightmapSB.AppendLine("  0 vector m_Heights");
            heightmapSB.AppendLine($"   1 Array Array ({Heightmap.Count} items)");
            heightmapSB.AppendLine($"    0 int size = {Heightmap.Count}");
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
                            NewFile.AppendLine(heightmapSB.ToString());


                            Debug.WriteLine("   Flipping");
                            int n = 0;
                            // create new heightmap points
                            for (int y = 0; y < mapsize; y++)
                            {
                                for (int x = 0; x < mapsize; x++)
                                {
                                    int newint = Heightmap[x * mapsize + y];
                                    NewFile.AppendLine($"    [{n}]");
                                    NewFile.AppendLine($"     0 SInt16 data = {newint}");
                                    n++;
                                }
                            }
                            Debug.WriteLine($"   Done. {n}");
                        }

                        break;
                    }
                }

                if (location == "m_Heights") continue;

                NewFile.AppendLine(currentline);

            }
            Debug.WriteLine("Done");
            File.WriteAllText("NewFile.txt", NewFile.ToString());

        }

        private void RotateClockwiseButton_Click(object sender, EventArgs e)
        {
            /*
            int[,] test = new int[,]
            {
                { 1, 2, 3 },
                { 4, 5, 6},
                { 7, 8, 9}
            };

            for (int i = 0; i < test.GetLength(0); i++)
            {
                for (int j = 0; j < test.GetLength(1); j++)
                {
                    Debug.Write(test[i, j] + ", ");
                }
                Debug.WriteLine("");
            }

            test = SMath.RotateClockwise<int>(test);

            for (int i = 0; i < test.GetLength(0); i++)
            {
                for (int j = 0; j < test.GetLength(1); j++)
                {
                    Debug.Write(test[i, j] + ", ");
                }
                Debug.WriteLine("");
            }
            */
            Heightmap2D = SMath.RotateClockwise<int>(Heightmap2D);
            UpdatePreviews();
        }

    }
}
