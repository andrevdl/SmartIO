#include "sio_native.h"

#pragma warning(disable : 26812)

SIOData SIONativeFunc::transform(SIOContext* ctx, ffi_arg arg, SIODataType dt)
{
	// for now only strings
	const char* str = (const char*)arg;
	SIODataRef* ref = ctx->store_str(str);

	return define_data_ref(dt, 0, ref);
}

SIONativeFunc::SIONativeFunc(void* func, unsigned int n_args, SIODataType r_type, SIODataType* arg_types):
	SIONativeFuncRaw(func, n_args, get_ffi_type(r_type), get_ffi_types(arg_types, n_args)), vm_r_type(r_type), vm_arg_types(arg_types)
{
	this->arg_types = new ffi_type*[n_args];

	for (size_t i = 0; i < n_args; i++)
	{
		this->arg_types[i] = get_ffi_type(arg_types[i]);
	}
	this->r_type = get_ffi_type(r_type);
}

SIONativeFunc::~SIONativeFunc()
{
	delete[] vm_arg_types;
}

bool SIONativeFunc::invoke(SIOContext* ctx, SIOData* data_args, SIOData& rdata, bool rdicard)
{
	ffi_arg rc = 0;
	bool succ = SIONativeFuncRaw::invoke(ctx, data_args, rc);
	if (succ && !rdicard)
	{
		rdata = transform(ctx, rc, vm_r_type);
	}
	return succ;
}

ffi_type* SIONativeFunc::get_ffi_type(SIODataType dt)
{
	if (dt == SIODataType::STRING)
	{
		return &ffi_type_pointer;
	}
	return &ffi_type_void;
}

ffi_type** SIONativeFunc::get_ffi_types(SIODataType* dt, int size)
{
	ffi_type** r = new ffi_type*[size];
	for (size_t i = 0; i < size; i++)
	{
		r[i] = get_ffi_type(dt[i]);
	}

	return r;
}

const char** SIONativeFuncRaw::get_str_buffer(SIOData* data_args)
{
	unsigned int counter = 0;
	for (size_t i = 0; i < n_args; i++)
	{
		if (data_args[i].datatype == SIODataType::STRING)
		{
			counter++;
		}
	}

	if (counter > 0)
	{
		return new const char*[counter];
	}

	return new const char*[0];
}

SIONativeFuncRaw::SIONativeFuncRaw(void* func, unsigned int n_args, ffi_type* r_type, ffi_type** arg_types):
	func(func), n_args(n_args), arg_types(arg_types), r_type(r_type)
{
}

SIONativeFuncRaw::~SIONativeFuncRaw()
{
	delete[] arg_types;
}

bool SIONativeFuncRaw::invoke(SIOContext* ctx, SIOData* data_args, ffi_arg& rc)
{
	void** values = ALLOC_FFI_ARGS(n_args);

	const char** str_buff = get_str_buffer(data_args);
	unsigned int buff_index = 0;

	for (size_t i = 0; i < n_args; i++)
	{
		switch (data_args[i].datatype)
		{
		case SIODataType::STRING:
			str_buff[i] = ctx->load_str_as_c_char(data_args[i]);
			values[i] = &str_buff[buff_index++];
			break;
		default:
			break;
		}
	}

	bool succ = raw_invoke(values, rc);

	FREE_FFI_ARGS(values);
	delete[] str_buff;

	return succ;
}

bool SIONativeFuncRaw::raw_invoke(void** data_args, ffi_arg& rc)
{
	ffi_cif cif;
	if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, n_args, r_type, arg_types) == FFI_OK)
	{
		ffi_call(&cif, (void (*)()) func, &rc, data_args);
		return true;
	}

	return false;
}

bool SIONativeBridge::validate_name(string name)
{
	// TODO: later validate name pattern (see VM specs)

	// Check if the name is already registered
	NativeFuncFinderRes res;
	return !find_func(name, res);
}

bool SIONativeBridge::find_func(string name, NativeFuncFinderRes& res)
{
	auto r = func_finder.find(name);
	if (r != func_finder.end())
	{
		res = r->second;
		return true;
	}

	return false;
}

bool SIONativeBridge::regiser_func(string name, SIONativeFuncRaw* func)
{
	if (!validate_name(name))
	{
		return false;
	}

	NativeFuncFinderRes res = { NativeFuncType::NATIVE, raw_func.size() };

	raw_func.push_back(func);
	func_finder.insert(make_pair(name, res));

	return true;
}

bool SIONativeBridge::regiser_func(string name, SIONativeFunc* func)
{
	if (!validate_name(name))
	{
		return false;
	}

	NativeFuncFinderRes res = { NativeFuncType::RAW, native_func.size() };

	native_func.push_back(func);
	func_finder.insert(make_pair(name, res));

	return true;
}

bool SIONativeBridge::regiser_func(string name, SIONativeFuncVM* func)
{
	if (!validate_name(name))
	{
		return false;
	}

	NativeFuncFinderRes res = { NativeFuncType::VM, vm_func.size() };

	vm_func.push_back(func);
	func_finder.insert(make_pair(name, res));

	return true;
}

SIONativeFuncRaw* SIONativeBridge::get_raw_func(size_t index)
{
	return raw_func[index];
}

SIONativeFunc* SIONativeBridge::get_native_func(size_t index)
{
	return native_func[index];
}

SIONativeFuncVM* SIONativeBridge::get_vm_func(size_t index)
{
	return vm_func[index];
}

SIONativeFuncVM::SIONativeFuncVM(sio_native_vm_func func, unsigned int n_args, SIODataType r_type, SIODataType* arg_types) :
	func(func), n_args(n_args), r_type(r_type), arg_types(arg_types)
{
}

bool SIONativeFuncVM::invoke(SIOData** data_args, SIOData*& rdata)
{
	rdata = func(data_args, n_args);
	return true; // add checks, like param count etc...
}

void sio_native_testing(SIOContext* ctx)
{
	SIODataRef* ref = ctx->store_str("Hello World! 45");
	SIOData data = define_data_ref(SIODataType::STRING, 0, ref);

	SIODataRef* ref2 = ctx->store_str("Welcome");
	SIOData data2 = define_data_ref(SIODataType::STRING, 0, ref2);

	SIODataType* params = new SIODataType[1];
	params[0] = SIODataType::STRING;
	SIONativeFunc func1(puts, 1, SIODataType::VOID, params); // puts -> std:cout

	//ffi_type* params2 = new ffi_type[1];
	//params2[0] = ffi_type_pointer;
	//SIONativeFunc func2(puts, 1, params2, ffi_type_sint); // puts -> std:cout

	SIODataType* params3 = new SIODataType[2];
	params3[0] = SIODataType::STRING;
	params3[1] = SIODataType::STRING;

	SIONativeFunc func3(dummy, 2, SIODataType::STRING, params3); // puts -> std:cout

	SIOData* args = new SIOData[2];
	args[0] = data;
	args[1] = data2;

	SIOData result;
	//func1.invoke(ctx, args, result, true);
	//func2.invoke(ctx, args);
	func3.invoke(ctx, args, result);
}

char* dummy(char* name, char* xxx)
{
	puts(name);
	return "Hello";
}
