#include <Windows.h>

namespace AOB {
	const char* gettop = "55 8B EC 8B 4D 08 8B 41 ?? 2B 41 ?? C1 F8 04 5D"; /*this will never change*/
	const char* retcheck = "55 8B EC 64 A1 00 00 00 00 6A ?? 68 ?? ?? ?? ?? 50 64 89 25 00 00 00 00 83 EC ?? 53 56 57 6A ?? E9 ?? ?? ?? ??"; /*may break at some point*/
	const char* print = "55 8B EC 6A FF 68 ?? ?? ?? ?? 64 A1 00 00 00 00 50 64 89 25 00 00 00 00 83 EC 18 8D 45 10 50 FF";
	const char* delay = "55 8B EC 6A FF 68 ?? ?? ?? ?? 64 A1 00 00 00 00 50 64 89 25 00 00 00 00 83 EC ?? 53 56 57 F0 FF"; /*sigh, accidentally made this AOB trying to get spawn*/
	const char* lual_checklstring = "55 8B EC FF 75 ?? 8B 55 ?? 8B 4D ?? E8 ?? ?? ?? ?? 85 C0 74 02 5D C3 6A ?? FF 75 ?? FF 75 ?? E8 6C 07 00 00";
}