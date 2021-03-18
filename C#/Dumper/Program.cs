using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using EyeStepPackage;

namespace Dumper
{
    class Program
    {
        public static WebClient wc = new WebClient();
        public static Stopwatch watch = new Stopwatch();
        public static int addycount;
        static void Main(string[] args)
        {
            Console.Title = "C# Address Dumper";
            Console.WriteLine("Scanning RBX " + wc.DownloadString("http://setup.roblox.com/version"));
            watch.Start();
            // do scanning and stuff

            watch.Stop();
            Console.WriteLine();
            Console.WriteLine("Scanned " + addycount + " addresses" + " in " + watch.ElapsedMilliseconds + "ms");
        }

        static void LogFunc(string fname, int addy)
        {
            int space = 20 - fname.Length;

            Console.Write(fname);
            for (int i = 0; i < space; i++)
            {
                Console.Write(" ");
            }
            Console.Write(": 0x" + addy.ToString("X8").Remove(0, 1) + " " + GetConvention(addy) + Environment.NewLine);
            Console.WriteLine("Pseudocode: " + util.getAnalysis(addy));
            Console.WriteLine();
            addycount = addycount + 1;
        }
        static string GetConvention(int Function)
        {
            byte Call = util.getConvention(Function);
            if (Call == 0)
            {
                return "__cdecl";
            }
            else if (Call == 1)
            {
                return "__stdcall";
            }
            else if (Call == 2)
            {
                return "__fastcall";
            }
            else if (Call == 3)
            {
                return "__thiscall";
            }
            else if (Call == 4)
            {
                return "[auto-generated]";
            }
            else
            {
                return "";
            }
        }
    }
}
