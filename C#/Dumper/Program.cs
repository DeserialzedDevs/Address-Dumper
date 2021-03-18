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
        
        // AOBs
        public static string gettop = "55 8B EC 8B 4D 08 8B 41 ?? 2B 41 ?? C1 F8 04 5D"; /*this will never change*/
	    public static string index2adr = "55 8B EC 8B 55 ?? 81 FA F0 D8 FF FF 7E 0F ?? ?? ?? ?? E2 04 03 51 10 8B C2 5D C2 08 00 8B 45 08"; /*may break at some point*/
	    public static string retcheck = "55 8B EC 64 A1 00 00 00 00 6A ?? 68 E8 ?? ?? ?? ?? 64 89 25 00 00 00 00 83 EC ?? 53 56 57 6A ?? E9 ?? ?? ?? ??"; /*may break at some point*/
	    public static string deserialize = "55 8B EC 6A FF 68 70 ?? ?? ?? ?? A1 00 00 00 00 50 64 89 25 00 00 00 00 81 EC 58 01 00 00 56 57"; /*Again not 100% sure about this one's integrity*/
	    public static string getdatamodel = "55 8B EC 64 A1 00 00 00 00 6A FF 68 ?? ?? ?? ?? 50 64 89 25 00 00 00 00 83 EC ?? 80 3D 70 51 5E";
        
        static void Main(string[] args)
        {
            Console.Title = "C# Address Dumper";
            Console.WriteLine("Scanning RBX " + wc.DownloadString("http://setup.roblox.com/version"));
            watch.Start();         
            
            // Scan AOBs
            int gettop_addr = scanner.scan(gettop)[0];
            int index2adr_addr = scanner.scan(index2adr)[0];
            int retcheck_addr = scanner.scan(retcheck)[0];
            int deserialize_addr = scanner.scan(deserialize)[0];
            
            // Log addresses
            LogFunc("deserializer", util.raslr(deserialize_addr));
            LogFunc("lua_gettop", util.raslr(gettop_addr));
            LogFunc("index2adr", util.raslr(index2adr_addr));
            
            // More scanning
            var retcheck_xrefs = scanner.scan_xrefs(retcheck_addr);
            var index2adr_xrefs = scanner.scan_xrefs(index2adr_addr);

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
            Console.Write(": 0x" + addy.ToString("X") + " " + GetConvention(addy) + Environment.NewLine);
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
