using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OCR
{
    class Program
    {
        static void Main(string[] args)
        {
            int[,] t = newgrid();
            t[2, 2] = 1;
            t[2, 4] = 1;
            t[2, 3] = 1;
            t[3, 3] = 1;
            t[4, 3] = 1;
            t[5, 3] = 1;


            int[,] v = newgrid();
            v[5, 3] = 1;
            v[5, 2] = 1;
            v[4, 4] = 1;
            v[4, 1] = 1;
            v[3, 0] = 1;
            v[3, 5] = 1;
            Console.ReadKey();
        }

        static int[,] newgrid()
        {
            int[,] a = new int[6,6];
       
            for (int i = 0; i < 6; i++)
            {
                for (int j = 0; j < 6; j++)
                {
                    a[i, j] = 0;
                }
            }
            return a;
        }
        static void print(int[,] letter)
        {
            for (int i = 0; i < 6; i++)
            {
                for (int j = 0; j < 6; j++)
                {
                    Console.Write(letter[i,j]);
                }
                Console.WriteLine();
            }
        }



    }
}
