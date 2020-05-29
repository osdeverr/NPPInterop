#include <iostream>
#include "../NPPI.Library/NPPI.Native.h" // HACK
#pragma comment(lib, "../Debug/NPPI.Library.lib")

int main()
{
	auto& ctx = NPPI_GetContext();
	try {
		auto pAssembly = ctx.load_assembly("I_DO_NOT_EXIST.dll");
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}