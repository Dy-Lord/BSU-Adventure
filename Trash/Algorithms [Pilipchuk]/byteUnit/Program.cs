using System;
using System.Collections.Generic;
using System.IO;
using System.Numerics;

namespace byteUnit
{
    class Program
    {
        private static string inputPath = "input.txt";
        private static string outputPath = "output.txt";

        private static long a, b, k;
        private static List<int> onePoz = new List<int>();
        private static List<int> twoPoz = new List<int>();
        public static void initData(string inputPath)
        {
            using (StreamReader reader = new StreamReader(inputPath))
            {
                string str = reader.ReadLine();
                string[] num = str.Split(' ');
                a = long.Parse(num[0]);
                b = long.Parse(num[1]);
                k = long.Parse(num[2]);
            }
        }

        private static void writeData(string outPath, long units)
        {
            using (StreamWriter writer = new StreamWriter(outPath))
            {
                writer.Write(units);
            }
        }

        public static string Reverse(string s)
        {
            char[] charArray = s.ToCharArray();
            Array.Reverse(charArray);
            return new string(charArray);
        }

        public static void getPoz(string binary, List<int> pozVector)
        {
            for (int i = binary.Length - 1; i >= 0; i--)
                if (binary[i].Equals('1'))
                    pozVector.Add(i);
        }

        public static long unitsCount(long unitCount, List<int> pozVector)
        {
            long units = 0;
            for (int i = 0; i < pozVector.Count; i++)
                units += prevUnits(pozVector[i], unitCount - i);

            return units;
        }

        private static long prevUnits(long unitPoz,long iterator)
        {
            if (iterator == unitPoz)
                return 1;
            else if (iterator < 0 || iterator > unitPoz)
                return 0;
            return advanceUnits(unitPoz, iterator);
        }

        private static long advanceUnits(long unitPoz, long iterator)
        {
            long temp = unitPoz - iterator;
            long units = 1;

            for (int i = 1; i <= iterator; i++)
            {
                units *= temp + i;
                units /= i;
            }
            return units;
        }
       /* static void Main(string[] args)
        {
            initData(inputPath);

            getPoz(Reverse(Convert.ToString(a, 2)), onePoz);
            getPoz(Reverse(Convert.ToString(++b, 2)), twoPoz);

            long units;

            if (k == 0)
                units = 0;
            else
                units = unitsCount(k, twoPoz) - unitsCount(k, onePoz);

            writeData(outputPath, units);
        }*/
    }
}
