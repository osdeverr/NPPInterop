#pragma once
#include <string>
#include <memory>

#ifdef COMPILING_DLL
#define NPPI_DLL __declspec(dllexport)
#else
#define NPPI_DLL __declspec(dllimport)
#endif

namespace nppi {
	class object
	{
	public:

	};

	class assembly
	{
	public:
		virtual ~assembly() {}

		virtual std::string name() = 0;

		virtual std::unique_ptr<object> create_instance(const std::string& type, bool ignore_case) = 0;
	};

	class context
	{
	public:
		virtual ~context() {}

		virtual std::unique_ptr<assembly> load_assembly(const std::string& filename) = 0;
		virtual std::unique_ptr<assembly> current_assembly() = 0;
	};
}

NPPI_DLL nppi::context& NPPI_GetContext();
