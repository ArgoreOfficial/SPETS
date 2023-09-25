using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Numerics;
using System.Text;

public static class SMath
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

    public static Vector3 DirectionToAngle(Vector3 direction)
    {
        Vector3 angles = new Vector3();
        //angle_H = atan2(ZD, XD)
        //angle_P=asin(YD)
        angles.X = MathF.Asin(direction.Y);
        angles.Y = MathF.Atan2(direction.X, -direction.Z);
        return angles;
    }

    public static T[,] Make2DArray<T>(T[] input, int height, int width)
    {
        T[,] output = new T[height, width];
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                output[i, j] = input[i * width + j];
            }
        }
        return output;
    }
    /// <summary>
    /// rotates an array clockwise
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="input"></param>
    /// <returns></returns>
    public static T[,] RotateClockwise<T>(T[,] input)
    {
        if (input.GetLength(0) != input.GetLength(1)) return input;

        int arraySize = input.GetLength(0);

        T[,] newArray = new T[arraySize, arraySize];

        for (int i = arraySize - 1; i >= 0; --i)
        {
            for (int j = 0; j < arraySize; ++j)
            {
                newArray[j, (arraySize - 1) - i] = input[i, j];
            }
        }

        return newArray;
    }

    public static T[,] Offset<T>(T[,] input, Point direction)
    {
        T[,] newArray = new T[input.GetLength(0), input.GetLength(1)];

        for (int y = 0; y < input.GetLength(0); y++)
        {
            for (int x = 0; x < input.GetLength(1); x++)
            {
                int newX = (x + direction.X) % input.GetLength(1);
                int newY = (y + direction.Y) % input.GetLength(1);

                newArray[newX, newY] = input[x, y];
            }
        }

        return newArray;
    }
}

