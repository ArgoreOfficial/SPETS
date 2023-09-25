using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using Newtonsoft.Json;

public static class ResourceHandler
{
    public static List<List<int>> NGonLookup;

    public static void Load()
    {
        NGonLookup = JsonConvert.DeserializeObject<List<List<int>>>(File.ReadAllText("resources/NGonLookup.txt"));

    }

}

