using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Management;
using System.Windows.Forms;

namespace BetcherSortApp
{
    public class Sort : Form1
    {
        private static int[] temparray;
        private static MTH Method; 
        public static void sort(int[] arr, MTH method)
        {
            Method = method;

            if (CheckPowTwo(arr.Length) == true)
            {              
                temparray = arr;
                main_Sort(0, arr.Length);
            }
            else
            {
                int dop = 0;
                int adv = 0;

                while (dop < arr.Length)
                    dop = (int)Math.Pow(2, ++adv);

                int count = dop - arr.Length;

                temparray = new int[dop];

                for (int i = 0; i < dop; i++)
                {
                    if (i < arr.Length)
                        temparray[i] = arr[i];
                    else
                        temparray[i] = 0;
                }
              
                main_Sort(0, temparray.Length);

                int g = 0;
                foreach (int el in temparray)
                {
                    if (el == 0 && count != 0)
                    {
                        count--;
                        continue;
                    }
                    else
                        arr[g++] = el;

                }                
            }
        }

        private static bool CheckPowTwo(int n)
        {
            return (n & (n - 1)) == 0;
        }
        private static void main_Sort(int caud, int len)
        {
            if (len > 1)
            {
                int one = len / 2;

                main_Sort(caud, one);
                main_Sort(caud + one, one);

                advance_Sort(caud, len, 1);
            }
        }
        private static void advance_Sort(int caud, int len, int dist)
        {
            int one = dist * 2;

            if (one < len)
            {
                advance_Sort(caud, len, one);      
                advance_Sort(caud + dist, len, one);  
                
                for (int i = caud + dist; i + dist < caud + len; i += one)
                    Collate(i, i + dist);
            }
            else
                Collate(caud, caud + dist);
        }

        private static void Swap(ref int one, ref int two)
        {
            int temp = one;
            one = two;
            two = temp;
        }
        private static void Collate(int i, int j)
        {
            if (Method == MTH.up)
            {
                if (temparray[i] > temparray[j])
                    Swap(ref temparray[i], ref temparray[j]);
            }
            else
                    if (temparray[i] < temparray[j])
                Swap(ref temparray[i], ref temparray[j]);
        }
    }
}
