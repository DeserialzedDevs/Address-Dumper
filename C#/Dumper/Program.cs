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
        // Intialize some sh*t
        public static WebClient wc = new WebClient();
        public static Stopwatch watch = new Stopwatch();
        public static int addycount;

        // Cool functions
        static void LogFunc(string fname, int addy, int conv_args)
        {
            if (!util.isPrologue(addy)) { addy = util.getPrologue(addy); }
            int space = 25 - fname.Length;

            Console.Write(fname);
            for (int i = 0; i < space; i++) { Console.Write(" "); }

            Console.Write(": 0x" + util.raslr(util.getPrologue(addy)).ToString("X8").Remove(0, 1) + " " + GetConvention(addy, conv_args) + Environment.NewLine);
            addycount = addycount + 1;
        }

        static void LogOffset(string name, int off)
        {
            int space = 25 - name.Length;

            Console.Write(name);
            for (int i = 0; i < space; i++) { Console.Write(" "); }
            Console.Write(": 0x" + off + Environment.NewLine);
        }

        static void LogOffNoHex(string name, int off)
        {
            int space = 25 - name.Length;

            Console.Write(name);
            for (int i = 0; i < space; i++) { Console.Write(" "); }
            Console.Write(": " + off + Environment.NewLine);
        }

        static void LogAddr(string fname, int addy) // Cool function
        {
            int space = 25 - fname.Length;

            Console.Write(fname);
            for (int i = 0; i < space; i++) { Console.Write(" "); }

            Console.Write(": 0x" + util.raslr(util.getPrologue(addy)).ToString("X8").Remove(0, 1) + Environment.NewLine);
            addycount = addycount + 1;
        }

        static string GetConvention(int function, int args)
        {
            byte Call = util.getConvention(function, args);
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

        // start dumper
        static void Main(string[] args)
        {
            // AOBs
            string gettop = "55 8B EC 8B 4D 08 8B 41 ?? 2B 41 ?? C1 F8 04 5D"; /*this will never change*/
            string delay = "55 8B EC 6A FF 68 ?? ?? ?? ?? 64 A1 00 00 00 00 50 64 89 25 00 00 00 00 83 EC ?? 53 56 57 F0 FF";
            string print = "55 8B EC 6A FF 68 ?? ?? ?? ?? 64 A1 00 00 00 00 50 64 89 25 00 00 00 00 83 EC 18 8D 45 10 50 FF";
            string checklstring = "55 8B EC FF 75 ?? 8B 55 ?? 8B 4D ?? E8 ?? ?? ?? ?? 85 C0 74 02 5D C3 6A ?? FF 75 ?? FF 75 ?? E8 6C 07 00 00";

            Console.Title = "C# Address Dumper";
            if (Process.GetProcessesByName("RobloxPlayerBeta").Length < 1)
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine("Please open Roblox first!");
                Thread.Sleep(3000);
                Environment.Exit(0);
            }
            EyeStep.open("RobloxPlayerBeta.exe");
            Console.ForegroundColor = ConsoleColor.Red;
            Console.WriteLine("Scanning RBX...");
            Console.ForegroundColor = ConsoleColor.Gray;
            watch.Start();

            // get index2adr
            var tostring = scanner.scan_xrefs("'tostring' must return a string to 'print'")[0];
            var tostring_calls = util.getCalls(util.getPrologue(tostring));

            int getfield_addr = tostring_calls[2];
            var getfield_calls = util.getCalls(getfield_addr);

            // Scan AOBs
            int gettop_addr = scanner.scan(gettop)[0];
            int index2adr_addr = getfield_calls[0];
            int retcheck_addr = getfield_calls[3];
            int deserialize_addr = util.getPrologue(scanner.scan_xrefs(": bytecode")[0]);

            // More scanning
            var retcheck_xrefs = scanner.scan_xrefs(retcheck_addr);
            var index2adr_xrefs = scanner.scan_xrefs(index2adr_addr);

            Console.WriteLine();
            Console.WriteLine("Addresses:");
            // Log addresses
            LogFunc("deserializer", deserialize_addr, 5);
            LogFunc("index2adr", index2adr_addr, 2);

            LogFunc("lua_call", retcheck_xrefs[1], 3);
            LogFunc("lua_checkstack", retcheck_xrefs[32], 2);
            LogFunc("lua_concat", retcheck_xrefs[3], 2);
            LogFunc("lua_createtable", retcheck_xrefs[4], 3);
            LogFunc("lua_gc", retcheck_xrefs[5], 3);
            LogFunc("lua_getargument", retcheck_xrefs[57], 3);
            LogFunc("lua_getfenv", retcheck_xrefs[6], 2);
            LogFunc("lua_getfield", retcheck_xrefs[7], 3);
            LogFunc("lua_getinfo", retcheck_xrefs[58], 3);
            LogFunc("lua_getmetatable", retcheck_xrefs[8], 2);
            LogFunc("lua_gettable", retcheck_xrefs[9], 2);
            LogFunc("lua_gettop", gettop_addr, 1);
            LogFunc("lua_getupvalue", retcheck_xrefs[10], 3);
            LogFunc("lua_insert", retcheck_xrefs[11], 2);
            LogFunc("lua_iscfunction", index2adr_xrefs[8], 2);
            LogFunc("lua_isnumber", index2adr_xrefs[9], 2);
            LogFunc("lua_isstring", index2adr_xrefs[10], 2);
            LogFunc("lua_isuserdata", index2adr_xrefs[7], 2);
            LogFunc("lua_lessthan", retcheck_xrefs[12], 3);
            LogFunc("lua_newthread", retcheck_xrefs[13], 1);
            LogFunc("lua_newuserdata", retcheck_xrefs[14], 3);
            LogFunc("lua_next", retcheck_xrefs[15], 2);
            LogFunc("lua_objlen", retcheck_xrefs[16], 2);
            LogFunc("lua_pcall", retcheck_xrefs[17], 4);
            LogFunc("lua_pushboolean", retcheck_xrefs[18], 2);
            LogFunc("lua_pushcclosure", retcheck_xrefs[19], 5);
            LogFunc("lua_pushfstring", retcheck_xrefs[20], 3);
            LogFunc("lua_pushinteger", retcheck_xrefs[21], 2);
            LogFunc("lua_pushlightuserdata", retcheck_xrefs[22], 2);
            LogFunc("lua_pushlstring", retcheck_xrefs[23], 3);
            LogFunc("lua_pushnil", retcheck_xrefs[24], 1);
            LogFunc("lua_pushnumber", retcheck_xrefs[25], 2);
            LogFunc("lua_pushstring", retcheck_xrefs[26], 2);
            LogFunc("lua_pushthread", retcheck_xrefs[28], 1);
            LogFunc("lua_pushvalue", retcheck_xrefs[30], 2);
            LogFunc("lua_pushvfstring", retcheck_xrefs[31], 3);
            LogFunc("lua_rawget", retcheck_xrefs[33], 2);
            LogFunc("lua_rawgeti", retcheck_xrefs[35], 3);
            LogFunc("lua_rawset", retcheck_xrefs[36], 2);
            LogFunc("lua_rawseti", retcheck_xrefs[37], 3);
            LogFunc("lua_rawvalue", index2adr_xrefs[0], 2);
            LogFunc("lua_remove", retcheck_xrefs[38], 2);
            LogFunc("lua_replace", retcheck_xrefs[39], 2);
            LogFunc("lua_resume", retcheck_xrefs[53], 2);
            LogFunc("lua_setfenv", retcheck_xrefs[40], 2);
            LogFunc("lua_setfield", retcheck_xrefs[41], 3);
            LogFunc("lua_setmetatable", retcheck_xrefs[42], 2);
            LogFunc("lua_setreadonly", retcheck_xrefs[43], 3);
            LogFunc("lua_setsafeenv", retcheck_xrefs[44], 3);
            LogFunc("lua_settable", retcheck_xrefs[45], 2);
            LogFunc("lua_settop", retcheck_xrefs[46], 2);
            LogFunc("lua_setupvalue", retcheck_xrefs[47], 3);
            LogFunc("lua_toboolean", index2adr_xrefs[33], 2);
            LogFunc("lua_tointeger", index2adr_xrefs[34], 3);
            LogFunc("lua_tolstring", retcheck_xrefs[48], 3);
            LogFunc("lua_tonumber", index2adr_xrefs[37], 3);
            LogFunc("lua_topointer", index2adr_xrefs[38], 2);
            LogFunc("lua_tostring", index2adr_xrefs[40], 2);
            LogFunc("lua_tothread", index2adr_xrefs[42], 2);
            LogFunc("lua_tounsignedx", index2adr_xrefs[43], 3);
            LogFunc("lua_touserdata", index2adr_xrefs[44], 2);
            LogFunc("lua_type", index2adr_xrefs[47], 2);
            LogFunc("lua_yield", retcheck_xrefs[54], 2);
            LogFunc("lua_xmove", retcheck_xrefs[50], 3);

            LogFunc("luaU_callhook", retcheck_xrefs[56], 3);

            LogFunc("delay", scanner.scan(delay)[0], 1);
            LogFunc("print", scanner.scan(print)[0], 3);
            LogFunc("f_call", retcheck_xrefs[0], 2);
            LogFunc("resume_error", retcheck_xrefs[55], 2);
            LogAddr("retcheck", getfield_calls[3]);
            LogAddr("RCCServiceDeserializeCall", scanner.scan_xrefs(deserialize_addr)[0]); // Log without ccv

            // log and get offsets
            Console.WriteLine();
            Console.WriteLine("Offsets:");

            int iscfunc_addr = util.getPrologue(index2adr_xrefs[8]);
            for (int i = 0; i < 72; i++) // 72 is all the bytes in lua_iscfunction
            {
                if (util.readByte(iscfunc_addr + i) == 0x80)
                { /*80 is the CMP instruction we're looking for*/
                    LogOffset("IsC", util.readByte(iscfunc_addr + i + 2)); //the offset is the second register of the CMP inst
                    break;
                }
                else if (util.isEpilogue(iscfunc_addr + i))
                {
                    Console.WriteLine("Unable to find IsC offset");
                    break;
                }
            }

            for (int i = 0; i < 16; i++) // gettop is 16 bytes
            {
                if (util.readByte(gettop_addr + i) == 0x2B)
                { /*2B is the sub instruction that uses base*/
                    LogOffset("ls_base", util.readByte(gettop_addr + i + 2)); /*second register*/
                    LogOffset("ls_top", util.readByte(gettop_addr + i - 1)); /*top is just 1 byte back from the sub inst*/
                    break;
                }
                else if (util.isEpilogue(gettop_addr + i))
                {
                    Console.WriteLine("Unable to find top and base");
                    break;
                }
            }
            // the IsC dumping might die at one point but it shouldnt for a long time


            watch.Stop();
            Console.WriteLine();
            Console.ForegroundColor = ConsoleColor.Green;
            Console.WriteLine("Scanned " + addycount + " addresses" + " in " + watch.ElapsedMilliseconds + "ms");
            Thread.Sleep(-1);
        }
    }
}
