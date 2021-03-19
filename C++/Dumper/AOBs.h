#include <Windows.h>

namespace AOB {
	const char* gettop = "55 8B EC 8B 4D 08 8B 41 ?? 2B 41 ?? C1 F8 04 5D"; /*this will never change*/
	const char* index2adr = "55 8B EC 8B 55 ?? 81 FA F0 D8 FF FF 7E ?? ?? ?? ?? ?? E2 04 03 51 10 8B C2 5D C2 08 00 8B 45 08"; /*may break at some point*/
	const char* retcheck = "55 8B EC 64 A1 00 00 00 00 6A ?? 68 ?? ?? ?? ?? 50 64 89 25 00 00 00 00 83 EC ?? 53 56 57 6A ?? E9 ?? ?? ?? ??"; /*may break at some point*/
	const char* deserialize = "55 8B EC 6A FF 68 ?? ?? ?? ?? 64 A1 00 00 00 00 50 64 89 25 00 00 00 00 81 EC 58 01 00 00 56 57"; /*Again not 100% sure about this one's integrity*/
	const char* print = "55 8B EC 6A FF 68 ?? ?? ?? ?? 64 A1 00 00 00 00 50 64 89 25 00 00 00 00 83 EC 18 8D 45 10 50 FF";
	const char* delay = "55 8B EC 6A FF 68 ?? ?? ?? ?? 64 A1 00 00 00 00 50 64 89 25 00 00 00 00 83 EC ?? 53 56 57 F0 FF"; /*sigh, accidentally made this AOB trying to get spawn*/
}