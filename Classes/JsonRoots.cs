using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SPETS.Classes
{
    #region BASE CLASSES
    public class CompartmentBaseRoot
    {
        public CompartmentBaseRoot(string id, string data, string metaData)
        {
            this.id = id;
            this.data = data;
            this.metaData = metaData;
        }

        public string id { get; set; }
        public string data { get; set; }
        public string metaData { get; set; }
    }

    #endregion

    #region BLUEPRINT ROOT CLASSES

    public class Compartment
    {
        public Version version { get; set; }
        public List<double> points { get; set; }
        public List<List<int>> sharedPoints { get; set; }
        public List<double> thicknessMap { get; set; }
        public List<List<int>> faceMap { get; set; }
        public double smooth { get; set; }


        public Compartment()
        {
            version = new Version();
            points = new List<double>();
            sharedPoints = new List<List<int>>();
            thicknessMap = new List<double>();
            faceMap = new List<List<int>>();
            smooth = 0.0;
        }
    }

    public class CompartmentRoot
    {
        public Version version { get; set; }
        public string name { get; set; }
        public int ID { get; set; }
        public int parentID { get; set; }
        public int flags { get; set; }
        public double displacement { get; set; }
        public double armourVolume { get; set; }
        public List<double> pos { get; set; }
        public List<double> rot { get; set; }
        public object turret { get; set; }
        public object genID { get; set; }
        public object genData { get; set; }
        public Compartment compartment { get; set; }

        public CompartmentRoot(string name)
        {
            version = new Version();
            version.Major = 0;
            version.Minor = 3;

            this.name = name;

            ID = 0;
            parentID = -1;
            flags = 3;
            displacement = 1.0;
            armourVolume = 1.0;
            
            pos = new List<double>() { 0.0, 0.0, 0.0 };
            rot = new List<double>() { 0.0, 0.0, 0.0 };
            
            turret = null;
            genID = null;
            genData = null;
            
            compartment = new Compartment();
        }
    }

    public class Version
    {
        public int Major { get; set; }
        public int Minor { get; set; }
    }

    #endregion

    public class Attachment
    {
        public string REF { get; set; }
        public int CID { get; set; }
        public List<double> T { get; set; }
        public List<CompartmentBaseRoot> DAT { get; set; }
    }

    public class AttachmentRoot
    {
        public List<Attachment> attachments { get; set; }
        public AttachmentRoot(List<Attachment> attachments)
        {
            this.attachments = attachments;
        }
    }
    public class AttatchmentAsset
    {
        public string data { get; set; }
        public int type { get; set; }
        public AttatchmentAsset(string data, int type)
        {
            this.data = data;
            this.type = type;
        }
    }

    public class AttatchmentDecal
    {
        public string data { get; set; }
        public int type { get; set; }
        public AttatchmentDecal(string data, int type)
        {
            this.data = data;
            this.type = type;
        }
    }
}
