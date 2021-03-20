// ExternalDumper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "eyestep.h";
#include "eyestep_utility.h";
#define getConvention(a) EyeStep::convs[EyeStep::util::getConvention(a)]

void LogFunc(const char* name, int address) {
    if (!EyeStep::util::isPrologue(address)) {
        address = EyeStep::util::getPrologue(address);
    }
    std::cout << name;
    int space = 25 - strlen(name);

    for (int i = 0; i < space; i++)
        std::cout << " ";
    std::cout << ": 0x" << std::hex << EyeStep::util::raslr(address) << " " << getConvention(address) << std::endl;
}

void LogAddr(const char* name, int address) {
    std::cout << name;
    int space = 25 - strlen(name);

    for (int i = 0; i < space; i++)
        std::cout << " ";
    std::cout << ": 0x" << std::hex << EyeStep::util::raslr(address) << std::endl;
}

void LogOff(const char* name, int off) {
    std::cout << name;
    int space = 25 - strlen(name);

    for (int i = 0; i < space; i++)
        std::cout << " ";
    std::cout << ": 0x" << off << std::endl;
}

const char* gettop = "55 8B EC 8B 4D 08 8B 41 ?? 2B 41 ?? C1 F8 04 5D"; /*this will never change*/
const char* index2adr = "55 8B EC 8B 55 ?? 81 FA F0 D8 FF FF 7E ?? ?? ?? ?? ?? E2 04 03 51 10 8B C2 5D C2 08 00 8B 45 08"; /*may break at some point*/
const char* retcheck = "55 8B EC 64 A1 00 00 00 00 6A ?? 68 ?? ?? ?? ?? 50 64 89 25 00 00 00 00 83 EC ?? 53 56 57 6A ?? E9 ?? ?? ?? ??"; /*may break at some point*/
const char* deserialize = "55 8B EC 6A FF 68 70 ?? ?? ?? ?? A1 00 00 00 00 50 64 89 25 00 00 00 00 81 EC 58 01 00 00 56 57"; /*Again not 100% sure about this one's integrity*/
const char* print = "55 8B EC 6A FF 68 ?? ?? ?? ?? 64 A1 00 00 00 00 50 64 89 25 00 00 00 00 83 EC 18 8D 45 10 50 FF";
const char* delay = "55 8B EC 6A FF 68 ?? ?? ?? ?? 64 A1 00 00 00 00 50 64 89 25 00 00 00 00 83 EC ?? 53 56 57 F0 FF"; /*sigh, accidentally made this AOB trying to get spawn*/

int main()
{
    EyeStep::open(L"RobloxPlayerBeta.exe");
	std::cout << "Scanning..." << std::endl;
    time_t begin, end;
    time(&begin);

    int gettop_addr = EyeStep::scanner::scan(gettop)[0];
    int index2adr_addr = EyeStep::scanner::scan(index2adr)[0];
    int retcheck_addr = EyeStep::scanner::scan(retcheck)[0];
    int deserialize_addr = EyeStep::scanner::scan(deserialize)[0];

    auto retcheck_xrefs = EyeStep::scanner::scan_xrefs(retcheck_addr);
    auto index2adr_xrefs = EyeStep::scanner::scan_xrefs(index2adr_addr);

    LogFunc("deserializer", deserialize_addr);
    LogFunc("index2adr", index2adr_addr);

    LogFunc("lua_call", retcheck_xrefs[1]);
    LogFunc("lua_concat", retcheck_xrefs[3]);
    LogFunc("lua_createtable", retcheck_xrefs[4]);
    LogFunc("lua_gc", retcheck_xrefs[5]);
    LogFunc("lua_getargument", retcheck_xrefs[57]);
    LogFunc("lua_getfenv", retcheck_xrefs[6]);
    LogFunc("lua_getfield", retcheck_xrefs[7]);
    LogFunc("lua_getinfo", retcheck_xrefs[58]);
    LogFunc("lua_getmetatable", retcheck_xrefs[8]);
    LogFunc("lua_gettable", retcheck_xrefs[9]);
    LogFunc("lua_gettop", gettop_addr);
    LogFunc("lua_getupvalue", retcheck_xrefs[10]);
    LogFunc("lua_insert", retcheck_xrefs[11]);
    LogFunc("lua_iscfunction", index2adr_xrefs[8]);
    LogFunc("lua_isnumber", index2adr_xrefs[9]);
    LogFunc("lua_isstring", index2adr_xrefs[10]);
    LogFunc("lua_isuserdata", index2adr_xrefs[7]);
    LogFunc("lua_lessthan", retcheck_xrefs[12]);
    LogFunc("lua_newthread", retcheck_xrefs[13]);
    LogFunc("lua_newuserdata", retcheck_xrefs[14]);
    LogFunc("lua_next", retcheck_xrefs[15]);
    LogFunc("lua_objlen", retcheck_xrefs[16]);
    LogFunc("lua_pcall", retcheck_xrefs[17]);
    LogFunc("lua_pushboolean", retcheck_xrefs[18]);
    LogFunc("lua_pushcclosure", retcheck_xrefs[19]);
    LogFunc("lua_pushfstring", retcheck_xrefs[20]);
    LogFunc("lua_pushinteger", retcheck_xrefs[21]);
    LogFunc("lua_pushlightuserdata", retcheck_xrefs[22]);
    LogFunc("lua_pushlstring", retcheck_xrefs[23]);
    LogFunc("lua_pushnil", retcheck_xrefs[24]);
    LogFunc("lua_pushnumber", retcheck_xrefs[25]);
    LogFunc("lua_pushstring", retcheck_xrefs[26]);
    LogFunc("lua_pushthread", retcheck_xrefs[28]);
    LogFunc("lua_pushvalue", retcheck_xrefs[30]);
    LogFunc("lua_pushvfstring", retcheck_xrefs[31]);
    LogFunc("lua_checkstack", retcheck_xrefs[32]);
    LogFunc("lua_rawget", retcheck_xrefs[33]);
    LogFunc("lua_rawgeti", retcheck_xrefs[35]);
    LogFunc("lua_rawset", retcheck_xrefs[36]);
    LogFunc("lua_rawseti", retcheck_xrefs[37]);
    LogFunc("lua_rawvalue", index2adr_xrefs[0]);
    LogFunc("lua_remove", retcheck_xrefs[38]);
    LogFunc("lua_replace", retcheck_xrefs[39]);
    LogFunc("lua_resume", retcheck_xrefs[53]);
    LogFunc("lua_setfenv", retcheck_xrefs[40]);
    LogFunc("lua_setfield", retcheck_xrefs[41]);
    LogFunc("lua_setlocal", retcheck_xrefs[60]);
    LogFunc("lua_setmetatable", retcheck_xrefs[42]);
    LogFunc("lua_setreadonly", retcheck_xrefs[43]);
    LogFunc("lua_setsafeenv", retcheck_xrefs[44]);
    LogFunc("lua_settable", retcheck_xrefs[45]);
    LogFunc("lua_settop", retcheck_xrefs[46]);
    LogFunc("lua_setupvalue", retcheck_xrefs[47]);
    LogFunc("lua_toboolean", index2adr_xrefs[33]);
    LogFunc("lua_tointeger", index2adr_xrefs[34]);
    LogFunc("lua_tolstring", retcheck_xrefs[48]);
    LogFunc("lua_tonumber", index2adr_xrefs[37]);
    LogFunc("lua_topointer", index2adr_xrefs[38]);
    LogFunc("lua_tostring", index2adr_xrefs[40]);
    LogFunc("lua_tothread", index2adr_xrefs[42]);
    LogFunc("lua_tounsignedx", index2adr_xrefs[43]);
    LogFunc("lua_touserdata", index2adr_xrefs[44]);
    LogFunc("lua_type", index2adr_xrefs[47]);
    LogFunc("lua_yield", retcheck_xrefs[54]);
    LogFunc("lua_xmove", retcheck_xrefs[50]);

    LogFunc("luaU_callhook", retcheck_xrefs[56]);

    LogFunc("f_call", retcheck_xrefs[0]);
    LogFunc("resume_error", retcheck_xrefs[55]);
    LogFunc("delay", EyeStep::scanner::scan(delay)[0]);
    LogFunc("print", EyeStep::scanner::scan(print)[0]);

    LogAddr("RCCServiceDeserializeCall", EyeStep::scanner::scan_xrefs(deserialize_addr)[0]);

    std::cout << std::endl << std::endl << "Offsets: " << std::endl;

    int iscfunc_addr = EyeStep::util::getPrologue(index2adr_xrefs[8]);
    /*72 is all the bytes in lua_iscfunction*/
    for (int i = 0; i < 72; i++) {
        if (EyeStep::util::readByte(iscfunc_addr + i) == 0x80) { /*80 is the CMP instruction we're looking for*/
            LogOff("IsC", EyeStep::util::readByte(iscfunc_addr + i + 2)); /*the offset is the second register of the CMP inst*/
            break;
        }
        else if (EyeStep::util::isEpilogue(iscfunc_addr + i)) {
            std::cout << "Unable to find IsC offset" << std::endl;
            break;
        }
    }

    /*gettop is 16 bytes*/
    for (int i = 0; i < 16; i++) {
        if (EyeStep::util::readByte(gettop_addr + i) == 0x2B) { /*2B is the sub instruction that uses base*/
            LogOff("ls_base", EyeStep::util::readByte(gettop_addr + i + 2)); /*second register*/
            LogOff("ls_top", EyeStep::util::readByte(gettop_addr + i - 1)); /*top is just 1 byte back from the sub inst*/
            break;
        }
        else if (EyeStep::util::isEpilogue(gettop_addr + i)) {
            std::cout << "Unable to find top and base" << std::endl;
            break;
        }
    }
    /*the IsC dumping might die at one point but it shouldnt for a long time*/


    time(&end);

    std::cout << "Time taken: " << end - begin << " second(s)" << std::endl;
    Sleep(-1);
    return 0;
}
