#include <intrin.h>
#include <iomanip>
#include <iostream>

using namespace std;

void cpuid(int leaf)
{
	cout << hex << setfill('0') << setw(8) << leaf << ": ";
	int registers[4]{};
	__cpuid(registers, leaf);
	char ascii[17]{};
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			char c = ((char*)&registers[i])[j];
			ascii[i * 4 + j] = c > ' ' ? c : ' ';
		}
		cout << hex << setfill('0') << setw(8) << registers[i] << ' ';
	}
	cout << ascii << endl;
}

void main()
{
	cout << "Leaf      EAX      EBX      ECX      EDX      ASCII" << endl;
	for (int i = 0x00; i <= 0x17; ++i)
		cpuid(i);
	for (int i = 0x80000000; i <= 0x80000008; ++i)
		cpuid(i);
	cin.get();
}