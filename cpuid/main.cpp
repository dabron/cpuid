#include <intrin.h>
#include <iomanip>
#include <iostream>

using namespace std;

void print_header()
{
	cout << "    LEAF REG ";
	for (int i = 31; i >= 0; --i)
		cout << dec << setfill(' ') << setw(2) << i;
	cout << " HEX      ASCII" << endl;
}

void print_register(const char* name, int value)
{
	cout << name << ' ';
	for (int i = 31; i >= 0; --i)
	{
		bool bit = (1 << i) & value;
		cout << ' ' << bit ? 1 : 0;
	}
	cout << ' ' << hex << setfill('0') << setw(8) << value << ' ';
	for (int i = 0; i < 4; ++i)
	{
		char c = reinterpret_cast<char*>(&value)[i];
		cout << (c > ' ' ? c : ' ');
	}
	cout << endl;
}

void print_cpuid(int leaf)
{
	print_header();
	char name[4]{ "eax" };
	int regs[4]{};
	__cpuid(regs, leaf);
	for (int i = 0; i < 4; ++i)
	{
		if (i == 0)
			cout << hex << setfill(' ') << setw(8) << leaf << ' ';
		else
			cout << "         ";
		print_register(name, regs[i]);
		++name[1];
	}
	cout << endl;
}

int cpuid(int leaf, int reg)
{
	if (reg < 0 || reg >= 4)
		return 0;

	int regs[4]{};
	__cpuid(regs, leaf);
	return regs[reg];
}

void main()
{
	int start = 0x00000000;
	int end = cpuid(start, 0);
	for (int i = start; i <= end; ++i)
		print_cpuid(i);

	start = 0x40000000;
	end = cpuid(start, 0);
	for (int i = start; i <= end; ++i)
		print_cpuid(i);

	start = 0x80000000;
	end = cpuid(start, 0);
	for (int i = start; i <= end; ++i)
		print_cpuid(i);

#ifdef _DEBUG
	cin.get();
#endif
}