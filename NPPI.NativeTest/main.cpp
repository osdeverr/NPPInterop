#include <iostream>
#include "../NPPI.Library/NPPI.Native.h" // HACK
#pragma comment(lib, "../Debug/NPPI.Library.lib")

int main()
{
	nppi::context& ctx = NPPI_GetContext();
	try {
		auto pAssembly = ctx.current_assembly();
		std::cout << pAssembly->name() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}