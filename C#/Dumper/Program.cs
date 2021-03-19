using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using EyeStepPackage;
using System.Threading;

namespace Dumper
{
    class Program
    {
        public static WebClient wc = new WebClient();
        public static Stopwatch watch = new Stopwatch();
        public static int addycount;

        static void Main(string[] args)
        {
            // AOBs
            string gettop = "55 8B EC 8B 4D 08 8B 41 ?? 2B 41 ?? C1 F8 04 5D"; /*this will never change*/
            string index2adr = "55 8B EC 8B 55 ?? 81 FA F0 D8 FF FF 7E 0F ?? ?? ?? ?? E2 04 03 51 10 8B C2 5D C2 08 00 8B 45 08"; /*may break at some point*/
            string retcheck = "55 8B EC 64 A1 00 00 00 00 6A ?? 68 E8 ?? ?? ?? ?? 64 89 25 00 00 00 00 83 EC ?? 53 56 57 6A ?? E9 ?? ?? ?? ??"; /*may break at some point*/
            string deserialize = "55 8B EC 6A FF 68 70 ?? ?? ?? ?? A1 00 00 00 00 50 64 89 25 00 00 00 00 81 EC 58 01 00 00 56 57"; /*Again not 100% sure about this one's integrity*/
            string getdatamodel = "55 8B EC 64 A1 00 00 00 00 6A FF 68 ?? ?? ?? ?? 50 64 89 25 00 00 00 00 83 EC ?? 80 3D 70 51 5E";

            Console.Title = "C# Address Dumper";
            if (Process.GetProcessesByName("RobloxPlayerBeta").Length < 1)
            {
                Console.ForegroundColor = ConsoleColor.Red;
;               Console.WriteLine("Please open Roblox first!");
                Thread.Sleep(3000);
                Environment.Exit(0);
            }
            EyeStep.open("RobloxPlayerBeta.exe");
            Console.WriteLine("Scanning RBX...");
            watch.Start();

            // Scan AOBs
            int gettop_addr = scanner.scan(gettop)[0];
            int index2adr_addr = scanner.scan(index2adr)[0];
            int retcheck_addr = scanner.scan(retcheck)[0];
            int deserialize_addr = scanner.scan(deserialize)[0];

            // Log addresses
            LogFunc("deserializer", util.raslr(deserialize_addr));
            LogFunc("index2adr", util.raslr(index2adr_addr));

            // More scanning
            var retcheck_xrefs = scanner.scan_xrefs(retcheck_addr);
            var index2adr_xrefs = scanner.scan_xrefs(index2adr_addr);

            // retcheck addresses
            LogFunc("lua_call", util.raslr(util.getPrologue(retcheck_xrefs[1])));
            LogFunc("lua_concat", util.raslr(util.getPrologue(retcheck_xrefs[3])));
            LogFunc("lua_createtable", util.raslr(util.getPrologue(retcheck_xrefs[4])));
            LogFunc("lua_gc", util.raslr(util.getPrologue(retcheck_xrefs[5])));
            LogFunc("lua_getargument", util.raslr(util.getPrologue(retcheck_xrefs[57])));
            LogFunc("lua_getfenv", util.raslr(util.getPrologue(retcheck_xrefs[6])));
            LogFunc("lua_getfield", util.raslr(util.getPrologue(retcheck_xrefs[7])));
            LogFunc("lua_getinfo", util.raslr(util.getPrologue(retcheck_xrefs[58])));
            LogFunc("lua_getmetatable", util.raslr(util.getPrologue(retcheck_xrefs[8])));
            LogFunc("lua_gettable", util.raslr(util.getPrologue(retcheck_xrefs[9])));
            LogFunc("lua_gettop", util.raslr(gettop_addr));
            LogFunc("lua_getupvalue", util.raslr(util.getPrologue(retcheck_xrefs[10])));
            LogFunc("lua_insert", util.raslr(util.getPrologue(retcheck_xrefs[11])));
            LogFunc("lua_lessthan", util.raslr(util.getPrologue(retcheck_xrefs[12])));
            LogFunc("lua_newthread", util.raslr(util.getPrologue(retcheck_xrefs[13])));
            LogFunc("lua_newuserdata", util.raslr(util.getPrologue(retcheck_xrefs[14])));
            LogFunc("lua_next", util.raslr(util.getPrologue(retcheck_xrefs[15])));
            LogFunc("lua_objlen", util.raslr(util.getPrologue(retcheck_xrefs[16])));
            LogFunc("lua_pcall", util.raslr(util.getPrologue(retcheck_xrefs[17])));
            LogFunc("lua_pushboolean", util.raslr(util.getPrologue(retcheck_xrefs[18])));
            LogFunc("lua_pushcclosure", util.raslr(util.getPrologue(retcheck_xrefs[19])));
            LogFunc("lua_pushfstring", util.raslr(util.getPrologue(retcheck_xrefs[20])));
            LogFunc("lua_pushinteger", util.raslr(util.getPrologue(retcheck_xrefs[21])));
            LogFunc("lua_pushlightuserdata", util.raslr(util.getPrologue(retcheck_xrefs[22])));
            LogFunc("lua_pushlstring", util.raslr(util.getPrologue(retcheck_xrefs[23])));
            LogFunc("lua_pushnil", util.raslr(util.getPrologue(retcheck_xrefs[24])));
            LogFunc("lua_pushnumber", util.raslr(util.getPrologue(retcheck_xrefs[25])));
            LogFunc("lua_pushstring", util.raslr(util.getPrologue(retcheck_xrefs[26])));
            LogFunc("lua_pushthread", util.raslr(util.getPrologue(retcheck_xrefs[28])));
            LogFunc("lua_pushvalue", util.raslr(util.getPrologue(retcheck_xrefs[30])));
            LogFunc("lua_pushvfstring", util.raslr(util.getPrologue(retcheck_xrefs[31])));
            LogFunc("lua_checkstack", util.raslr(util.getPrologue(retcheck_xrefs[32])));
            LogFunc("lua_rawget", util.raslr(util.getPrologue(retcheck_xrefs[33])));
            LogFunc("lua_rawgeti", util.raslr(util.getPrologue(retcheck_xrefs[35])));
            LogFunc("lua_rawset", util.raslr(util.getPrologue(retcheck_xrefs[36])));
            LogFunc("lua_rawseti", util.raslr(util.getPrologue(retcheck_xrefs[37])));
            LogFunc("lua_remove", util.raslr(util.getPrologue(retcheck_xrefs[38])));
            LogFunc("lua_replace", util.raslr(util.getPrologue(retcheck_xrefs[39])));
            LogFunc("lua_resume", util.raslr(util.getPrologue(retcheck_xrefs[53])));
            LogFunc("lua_setfenv", util.raslr(util.getPrologue(retcheck_xrefs[40])));
            LogFunc("lua_setfield", util.raslr(util.getPrologue(retcheck_xrefs[41])));
            LogFunc("lua_setlocal", util.raslr(util.getPrologue(retcheck_xrefs[60])));
            LogFunc("lua_setmetatable", util.raslr(util.getPrologue(retcheck_xrefs[42])));
            LogFunc("lua_setreadonly", util.raslr(util.getPrologue(retcheck_xrefs[43])));
            LogFunc("lua_setsafeenv", util.raslr(util.getPrologue(retcheck_xrefs[44])));
            LogFunc("lua_settable", util.raslr(util.getPrologue(retcheck_xrefs[45])));
            LogFunc("lua_settop", util.raslr(util.getPrologue(retcheck_xrefs[46])));
            LogFunc("lua_setupvalue", util.raslr(util.getPrologue(retcheck_xrefs[47])));
            LogFunc("lua_tolstring", util.raslr(util.getPrologue(retcheck_xrefs[48])));
            LogFunc("lua_yield", util.raslr(util.getPrologue(retcheck_xrefs[54])));
            LogFunc("lua_xmove", util.raslr(util.getPrologue(retcheck_xrefs[50])));

            LogFunc("luaU_callhook", util.raslr(util.getPrologue(retcheck_xrefs[56])));

            LogFunc("f_call", util.raslr(util.getPrologue(retcheck_xrefs[0])));
            LogFunc("resume_error", util.raslr(util.getPrologue(retcheck_xrefs[55])));

            watch.Stop();
            Console.WriteLine();
            Console.ForegroundColor = ConsoleColor.Green;
            Console.WriteLine("Scanned " + addycount + " addresses" + " in " + watch.ElapsedMilliseconds + "ms");
            Thread.Sleep(-1);
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
