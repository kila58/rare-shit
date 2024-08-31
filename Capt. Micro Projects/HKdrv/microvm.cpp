#ifdef __cplusplus
extern "C" 
{
#endif
#include <ntddk.h>
#include <ntddstor.h>
#include <mountdev.h>
#include <ntddvol.h>
#ifdef __cplusplus
}
#endif

#define MicroVM_StackDepth 32
#define MicroVM_MemorySize 1024 //bytes (must be divisible by 4)
#define MicroVM_MemIntSize (MicroVM_MemorySize / 4)

#define MicroVN_FLAG_EQU 0x00000001
#define MicroVN_FLAG_GT  0x00000002
#define MicroVN_FLAG_LT  0x00000004

typedef struct {
	unsigned int Pc;
	unsigned int Sp;
	unsigned int Flags;
	unsigned int Stack[MicroVM_StackDepth];
	unsigned int *Memory;
} MicroVM_STATE;

void MicroVM_Create(MicroVM_STATE *vm)
{
	RtlZeroMemory(vm, sizeof(MicroVM_STATE));
	vm->Memory = (unsigned int*)ExAllocatePool(NonPagedPool, MicroVM_MemorySize);
	RtlZeroMemory(vm->Memory, MicroVM_MemorySize);
}

void MicroVM_Destory(MicroVM_STATE *vm)
{
	RtlZeroMemory(vm->Memory, MicroVM_MemorySize);
	ExFreePool(vm->Memory);
	RtlZeroMemory(vm, sizeof(MicroVM_STATE));
}

void MicroVM_Step(MicroVM_STATE *vm)
{
	unsigned char Opcode = vm->Memory[vm->Pc];
	unsigned int Arg0 = vm->Memory[vm->Pc + 1];
	unsigned int Arg1 = vm->Memory[vm->Pc + 2];
	unsigned int *Res = &vm->Memory[vm->Pc + 1];

	switch (Opcode)
	{
		case 0x0:
			*Res = Arg0 + Arg1;
			break;
		case 0x1:
			vm->Memory[Arg0] = Arg1;
			break;
		case 0x2:
			vm->Flags = 0;
			if (Arg0 == Arg1) vm->Flags |= MicroVN_FLAG_EQU;
			if (Arg0 > Arg1) vm->Flags |= MicroVN_FLAG_GT;
			if (Arg0 < Arg1) vm->Flags |= MicroVN_FLAG_LT;
			break;
		case 0x3:
			vm->Pc = Arg0;
			break;
		case 0x4:
			if ((vm->Flags&MicroVN_FLAG_EQU)==MicroVN_FLAG_EQU)
				vm->Pc = Arg0;
			break;
		case 0x5:
			if ((vm->Flags&MicroVN_FLAG_GT)==MicroVN_FLAG_GT)
				vm->Pc = Arg0;
			break;
		case 0x6:
			if ((vm->Flags&MicroVN_FLAG_LT)==MicroVN_FLAG_LT)
				vm->Pc = Arg0;
			break;
		case 0x7:
			vm->Stack[vm->Sp] = vm->Pc + 2; //skip this CALL on return
			vm->Pc = Arg0;
			vm->Sp++;
			break;
		case 0x8:
			vm->Sp--;
			vm->Pc = vm->Stack[vm->Sp];
			vm->Stack[vm->Sp] = 0;
			break;
		case 0x9:
			vm->Stack[vm->Sp] = Arg0;
			vm->Sp++;
			break;
		case 0xA:
			vm->Sp--;
			vm->Stack[vm->Sp] = Arg0;
			break;
		case 0xB:
			*Res = ~Arg0;
			break;
		case 0xC:
			*Res = Arg0 ^ Arg1;
			break;
		case 0xD:
			*Res = Arg0 & Arg1;
			break;
		case 0xE:
			*Res = Arg0 + Arg1;
			break;
		case 0xF:
			*Res = Arg0 * Arg1;
			break;
	}
}
