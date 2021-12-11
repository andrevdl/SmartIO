#pragma once

#include <string>

#include <sio_context.h>
#include <runtime/sio_native.h>

// temp
#include <iostream>

typedef enum
{
	OP_NOOP,
	OP_MOVE,
	OP_LOADK,

	OP_ADD,
	OP_SUB,
	OP_MUL,
	OP_MOD,
	OP_POW, // Python 2**2 | Lua 2^2
	OP_DIV, // Delphi/Pascal: 4 / 3
	OP_IDIV, // Delphi/Pascal: 4 div 3 => lua 4 // 3 ==> may SIO 4 %% 3

	OP_LEN,
	OP_CONCAT,
	OP_JMP,
	OP_EQ,
	OP_LT,
	OP_LE,
	OP_CALL,
	OP_RETURN
} VM_OP_CODE;

std::string get_mnemonic(int opcode)
{
	switch (opcode)
	{
	case OP_NOOP:
		return "noop";
	case OP_MOVE:
		return "move";
	case OP_LOADK:
		return "loadk";
	case OP_ADD:
		return "add";
	case OP_SUB:
		return "sub";
	case OP_MUL:
		return "mul";
	case OP_MOD:
		return "mod";
	case OP_POW:
		return "pow";
	case OP_DIV:
		return "div";
	case OP_IDIV:
		return "idiv";
	case OP_LEN:
		return "len";
	case OP_CONCAT:
		return "concat";
	case OP_JMP:
		return "jmp";
	case OP_EQ:
		return "eq";
	case OP_LT:
		return "lt";
	case OP_LE:
		return "le";
	case OP_CALL:
		return "call";
	case OP_RETURN:
		return "return";
	default:
		return "Unkown";
	}
}

// X => opcode
// 0000_0000 0000_0000 0000_0000 0000_0000 0000_0000 0000_0000 0000_0000 0000_0000 0000_0000 0000_0000 0000_0000 0000_0000 0000_0000 0000_0000 0000_0000 0000_0000
// XXXX_XX00 0000_0000 0000_0000 0000_0000 0000_0000 0000_0000 0000_0000 0000_0000 0000_0000 0000_0000 0000_0000 0000_0000 0000_0000 0000_0000 0000_0000 0000_0000 | 58 bits left

// Lua
// max 64 opcodes
// max 256 registers (accessible)
// max 256 constants (accessible)
// max jmp (25 bits + 1 bit (sign)) => 33.554.432 instructions ==> max file size, by reach everything by a jump (x * 32 bits) => (x * 4 bytes) ==> 134.217.728 bytes => 131.072 kb => 128 mb (compiled code)

// A = always register (8 bits)
// B = register or constant (8 bits + 1 (register/constant))
// C = register or constant (8 bits + 1 (register/constant))

// xxxxxx
// If 6 bit is op_code and 58 is instr => max files for jump ==> 1 exabyte

uint64_t get_instr(VM_OP_CODE opcode, int a);
uint64_t get_instr(VM_OP_CODE opcode, int a, int b);
uint64_t get_instr_signed(VM_OP_CODE opcode, int a, int b);
uint64_t get_instr(VM_OP_CODE opcode, int a, int b, int c);

void sio_vm_exec()
{
	//static void* dispatch[] =
	//{
	//	&& test
	//};

	int opcode = OP_JMP;
	std::cout << get_mnemonic(opcode);

	switch (opcode)
	{
	case OP_NOOP:
		opcode = 3;
	case OP_ADD:
		opcode = 2;
	case OP_SUB:
		opcode = 1;
	case OP_CALL:
		opcode = 1;
	//default:
	//	break;
	}
}

class SIORuntime
{
private:
	SIOContext ctx;
	SIONativeBridge bridge;

	void dummy_load(); // load some dummy stuff, what is needed for building the VM...
public:
	void exec();
};