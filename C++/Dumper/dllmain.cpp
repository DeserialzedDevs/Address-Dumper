#include <Windows.h>
#include <thread>
#include "AOBs.h"
#include "EyeStep/eyestep.h"
#include "EyeStep/eyestep_utility.h"
#include <iostream>
#define getConvention(a) EyeStep::convs[EyeStep::util::getConvention(a)]

void Log(const char* name, int address) {
	std::cout << name;
	int space = 20 - strlen(name);

	for (int i = 0; i < space; i++)
		std::cout << " ";
	std::cout << ": 0x" << std::hex << EyeStep::util::raslr(address) << " " << getConvention(address) << " " << EyeStep::util::getAnalysis(address) << std::endl;
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

	/*scan for shit with the AOBs*/
	int gettop_addr = EyeStep::scanner::scan(AOB::gettop)[0];
	int index2adr_addr = EyeStep::scanner::scan(AOB::index2adr)[0];
	int retcheck_addr = EyeStep::scanner::scan(AOB::retcheck)[0];
	int deserialize_addr = EyeStep::scanner::scan(AOB::deserialize)[0];

	Log("deserializer", deserialize_addr);
	Log("lua_gettop", gettop_addr);
	Log("index2adr", index2adr_addr);

	auto retcheck_xrefs = EyeStep::scanner::scan_xrefs(retcheck_addr);
	auto index2adr_xrefs = EyeStep::scanner::scan_xrefs(index2adr_addr);

	/*do shit here*/
}

int __stdcall DllMain(HMODULE, int call, void*) {
	if (call == 1)
		std::thread(main).detach();
	return 1;
}