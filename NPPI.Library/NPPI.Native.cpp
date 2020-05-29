#include "NPPI.Native.h"
#include "NPPI.ManagedImpl.h"

NPPI_DLL nppi::context& NPPI_GetContext()
{
	static NPPILibrary::ContextImpl instance;
	return instance;
}
