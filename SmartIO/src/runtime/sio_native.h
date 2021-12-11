#pragma once

#include <ffi.h>
#include <stdio.h>

#include <unordered_map>
#include <string>

#include <sio_data.h>
#include <sio_context.h>

using namespace std;

#define ALLOC_FFI_ARGS(size) (void**)_malloca(sizeof(void*) * size)
#define FREE_FFI_ARGS(name) _freea(name)

class SIONativeFuncRaw
{
protected:
	void* func;

	unsigned int n_args;
	ffi_type** arg_types;
	ffi_type* r_type;

	const char** get_str_buffer(SIOData* data_args);
public:
	SIONativeFuncRaw(void* func, unsigned int n_args, ffi_type* r_type, ffi_type** arg_types);

	~SIONativeFuncRaw();

	bool invoke(SIOContext* ctx, SIOData* data_args, ffi_arg& rc);
	bool raw_invoke(void** data_args, ffi_arg& rc);
};

class SIONativeFunc: SIONativeFuncRaw
{
private:
	SIODataType* vm_arg_types;
	SIODataType vm_r_type;

	SIOData transform(SIOContext* ctx, ffi_arg arg, SIODataType dt);
public:
	SIONativeFunc(void* func, unsigned int n_args, SIODataType r_type, SIODataType* arg_types);

	~SIONativeFunc();

	bool invoke(SIOContext* ctx, SIOData* data_args, SIOData& rdata, bool rdicard = false);

	static ffi_type* get_ffi_type(SIODataType dt);
	static ffi_type** get_ffi_types(SIODataType* dt, int size);
};

typedef SIOData* (*sio_native_vm_func)(SIOData** args, unsigned int n_args);

class SIONativeFuncVM
{
private:
	sio_native_vm_func func;

	unsigned int n_args;
	SIODataType* arg_types;
	SIODataType r_type;
public:
	SIONativeFuncVM(sio_native_vm_func func, unsigned int n_args, SIODataType r_type, SIODataType* arg_types);

	bool invoke(SIOData** data_args, SIOData*& rdata);
};

enum class NativeFuncType
{
	RAW,
	NATIVE,
	VM
};

struct NativeFuncFinderRes
{
	NativeFuncType type;
	size_t index;
};

class SIONativeBridge
{
private:
	unordered_map<string, NativeFuncFinderRes> func_finder;
	vector<SIONativeFuncRaw*> raw_func;
	vector<SIONativeFunc*> native_func;
	vector<SIONativeFuncVM*> vm_func;

	bool validate_name(string name);
public:
	bool find_func(string name, NativeFuncFinderRes& res);
	// todo: add destroy ...

	bool regiser_func(string name, SIONativeFuncRaw* func);
	bool regiser_func(string name, SIONativeFunc* func);
	bool regiser_func(string name, SIONativeFuncVM* func);

	SIONativeFuncRaw* get_raw_func(size_t index);
	SIONativeFunc* get_native_func(size_t index);
	SIONativeFuncVM* get_vm_func(size_t index);
};

void sio_native_testing(SIOContext* ctx);
char* dummy(char*, char*);