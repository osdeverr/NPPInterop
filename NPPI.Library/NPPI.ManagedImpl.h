#pragma once
#include "NPPI.Native.h"
#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>
#include <gcroot.h>

using namespace System;
using namespace System::Reflection;
using namespace msclr::interop;

namespace NPPILibrary {
	public class ManagedException : public std::exception
	{
	public:
		ManagedException(System::Object^ exceptionObject)
			: mExceptionObject(exceptionObject) 
		{
			String^ reason = "NPPI - " + mExceptionObject->ToString();
			mExceptionReason = marshal_as<std::string>(reason);
		}

		const char* what() const
		{
			return mExceptionReason.c_str();
		}
	private:
		gcroot<System::Object^> mExceptionObject;
		std::string mExceptionReason;
	};

	public class ObjectImpl : public nppi::object
	{
	public:
		ObjectImpl(System::Object^ hObject)
			: mManagedObject(hObject) {}
	private:
		gcroot<System::Object^> mManagedObject;
	};

	public class AssemblyImpl : public nppi::assembly
	{
	public:
		AssemblyImpl(System::Reflection::Assembly^ hAssembly)
			: mManagedAssembly(hAssembly) { }

		std::unique_ptr<nppi::object> create_instance(const std::string& type, bool ignore_case)
		{
			try {
				auto obj = mManagedAssembly->CreateInstance(marshal_as<String^>(type), ignore_case);
				return std::make_unique<ObjectImpl>(obj);
			}
			catch (Exception^ e)
			{
				throw ManagedException(e);
			}
		}
	private:
		gcroot<System::Reflection::Assembly^> mManagedAssembly;
	};

	public class ContextImpl : public nppi::context
	{
	public:
		std::unique_ptr<nppi::assembly> load_assembly(const std::string& filename)
		{
			try {
				Assembly^ assembly = Assembly::LoadFrom(marshal_as<String^>(filename.c_str()));
				return std::unique_ptr<nppi::assembly>(new AssemblyImpl(assembly));
			}
			catch (Exception^ e)
			{
				throw ManagedException(e);
			}
		}
	};
}
