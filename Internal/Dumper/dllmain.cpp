#include <Windows.h>
#include <thread>
#include "AOBs.h"
#include "EyeStep/eyestep.h"
#include "EyeStep/eyestep_utility.h"
#include <iostream>
#include <time.h>
#include "retcheck.h"
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

void LogOffNoHex(const char* name, int off) {
    std::cout << name;
    int space = 25 - strlen(name);

    for (int i = 0; i < space; i++)
        std::cout << " ";
    std::cout << ": " << off << std::endl;
}

void main() {
	EyeStep::open(GetCurrentProcess()); /*haha, imagine using external eyestep*/

	/*bypass Roblox's shit ass console check*/
	int FreeConsole_addr = reinterpret_cast<int>(FreeConsole);
	EyeStep::util::setPageProtect(FreeConsole_addr, 0x40, 1);
	EyeStep::util::writeByte(FreeConsole_addr, 0xC3);
	AllocConsole();

	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);
	SetConsoleTitleA("Address Dumper || Deserialized devs");

    time_t begin, end;
    time(&begin);

    auto tostring = EyeStep::scanner::scan_xrefs("'tostring' must return a string to 'print'")[0];
    auto tostring_calls = EyeStep::util::getCalls(EyeStep::util::getPrologue(tostring));

    int getfield_addr = tostring_calls[2];
    auto getfield_calls = EyeStep::util::getCalls(getfield_addr);

	/*scan for shit with the AOBs*/
    int gettop_addr = EyeStep::scanner::scan(AOB::gettop)[0];
    int index2adr_addr = getfield_calls[0];
	int retcheck_addr = getfield_calls[3];
	int deserialize_addr = EyeStep::util::getPrologue(EyeStep::scanner::scan_xrefs(": bytecode")[0]);

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
    //LogFunc("lua_setlocal", retcheck_xrefs[60]); <-- not working
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

    //LogFunc("luaL_checklstring", EyeStep::scanner::scan(AOB::lual_checklstring)[0]); <-- this broke too but ill fix it later... fucking AOBs

    LogFunc("f_call", retcheck_xrefs[0]);
    LogFunc("resume_error", retcheck_xrefs[55]);
    LogFunc("delay", EyeStep::scanner::scan(AOB::delay)[0]);
    LogFunc("print", EyeStep::scanner::scan(AOB::print)[0]);

    LogAddr("RCCServiceDeserializeCall", EyeStep::scanner::scan_xrefs(deserialize_addr)[0]);
    
    std::cout << std::endl << std::endl << "Offsets: " << std::endl;

    int iscfunc_addr = EyeStep::util::getPrologue(index2adr_xrefs[8]);
    int func_size = EyeStep::util::nextPrologue(iscfunc_addr) - iscfunc_addr;

    for (int i = 0; i < func_size; i++)
    {
        auto inst = EyeStep::read(iscfunc_addr + i);
        if (inst.info.code == "80+m7")
        {
            LogOff("IsC", EyeStep::util::readByte(inst.address + 2));
            break;
        }
        else if (i == func_size - 1)
        {
            std::cout << "Unable to find IsC offset" << std::endl;
            break;
        }
    }

    /*gettop is 16 bytes*/
    for (int i = 0; i < 16; i++)
    {
        auto inst = EyeStep::read(gettop_addr + i);
        if (inst.info.code == "2B")
        { /*2B is the sub instruction that uses base*/
            LogOff("ls_base", EyeStep::util::readByte(inst.address + 2)); /*second register*/
            LogOff("ls_top", EyeStep::util::readByte(inst.address - 1)); /*top is just 1 byte back from the sub inst*/
            break;
        }
        else if (i == func_size - 1)
        {
            std::cout << "Unable to find top and base offset" << std::endl;
            break;
        }
    }





    typedef int(__cdecl* T_getfield)(int, int, const char*);
    typedef int(__cdecl* T_pushstring)(int, const char*);
    typedef int(__cdecl* T_type)(int, int);
    typedef int(__cdecl* T_newthread)(int);
    typedef int(__cdecl* T_settop)(int, int);
    typedef int(__cdecl* T_pushlightuserdata)(int, int);
    T_getfield r_lua_getfield = reinterpret_cast<T_getfield>(EyeStep::util::createRoutine(unprotect(EyeStep::util::getPrologue(retcheck_xrefs[7])), 3));
    T_pushstring r_lua_pushstring = reinterpret_cast<T_pushstring>(EyeStep::util::createRoutine(unprotect(EyeStep::util::getPrologue(retcheck_xrefs[26])), 2));
    T_type r_lua_type = reinterpret_cast<T_type>(EyeStep::util::createRoutine(unprotect(EyeStep::util::getPrologue(index2adr_xrefs[47])), 2));
    T_newthread r_lua_newthread = reinterpret_cast<T_newthread>(EyeStep::util::createRoutine(unprotect(EyeStep::util::getPrologue(retcheck_xrefs[13])), 1));
    T_settop r_lua_settop = reinterpret_cast<T_settop>(EyeStep::util::createRoutine(unprotect(EyeStep::util::getPrologue(retcheck_xrefs[46])), 2));
    T_pushlightuserdata r_lua_pushlightuserdata = reinterpret_cast<T_pushlightuserdata>(EyeStep::util::createRoutine(unprotect(EyeStep::util::getPrologue(retcheck_xrefs[22])), 2));

    int rL = EyeStep::util::debug_r32(EyeStep::util::getPrologue(retcheck_xrefs[13]) + 3, EyeStep::R32_EBP, 8)[0];

    r_lua_getfield(rL, -10002, "game");
    LogOffNoHex("R_LUA_TUSERDATA", r_lua_type(rL, -1));

    r_lua_settop(rL, 0);
    r_lua_getfield(rL, -10002, "table");
    LogOffNoHex("R_LUA_TTABLE", r_lua_type(rL, -1));

    r_lua_settop(rL, 0);
    r_lua_getfield(rL, -10002, "print");
    LogOffNoHex("R_LUA_TFUNCTION", r_lua_type(rL, -1));

    r_lua_settop(rL, 0);
    r_lua_pushstring(rL, "e");
    LogOffNoHex("R_LUA_TSTRING", r_lua_type(rL, -1));

    r_lua_getfield(rL, -10002, "game");
    r_lua_getfield(rL, -1, "Workspace");
    r_lua_getfield(rL, -1, "FilteringEnabled");
    LogOffNoHex("R_LUA_TBOOLEAN", r_lua_type(rL, -1));

    r_lua_settop(rL, 0);
    r_lua_getfield(rL, -10002, "game");
    r_lua_getfield(rL, -1, "PlaceId");
    LogOffNoHex("R_LUA_TNUMBER", r_lua_type(rL, -1));

    r_lua_newthread(rL);
    LogOffNoHex("R_LUA_TTHREAD", r_lua_type(rL, -1));

    r_lua_pushlightuserdata(rL, 0);
    LogOffNoHex("R_LUA_TLIGHTUSERDATA", r_lua_type(rL, -1));

    r_lua_getfield(rL, -10002, "asdiohasdiyw");
    LogOffNoHex("R_LUA_TNIL", r_lua_type(rL, -1));

    r_lua_settop(rL, 0);

    /*will add R_LUA_TPROTO at some point*/


    time(&end);

    std::cout << "Time taken: " << end - begin << " second(s)" << std::endl;
}

int __stdcall DllMain(HMODULE, int call, void*) {
	if (call == 1)
		std::thread(main).detach();
	return 1;
}