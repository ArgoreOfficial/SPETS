﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;

public static class Math3D
{
    public static Vector3 GetNormal(List<Vector3> face)
    {
        if (face.Count > 2)
        {
            Vector3 line1 = face[1] - face[0];
            Vector3 line2 = face.Last() - face[0];
            Vector3 normal = Vector3.Cross(line1, line2);
            return Vector3.Normalize(normal);
        }

        return Vector3.Zero;
    }
}
