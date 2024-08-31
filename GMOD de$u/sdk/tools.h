typedef void* (_cdecl* FactoryFn)(const char*,void*);
typedef int (_cdecl* PseudoRandomFn)(int);
typedef void (_cdecl* MsgFn)(const char*,...);
typedef void (_cdecl* RandomSeedFn)(int);
typedef int (_cdecl* RandomIntFn)(int,int);
typedef float (_cdecl* RandomFloatFn)(float,float);

extern PseudoRandomFn PseudoRandom;
extern MsgFn Msg;
extern RandomSeedFn RandomSeed;
extern RandomFloatFn RandomFloat;

static dword HookVirtual(dword* vmt,dword* fn,int index)
{
	dword origin = vmt[index];
	dword old;
	VirtualProtect(&vmt[index],4,0x40,&old);
	vmt[index] = (dword)fn;
	VirtualProtect(&vmt[index],4,old,&old);
	return origin;
}

static void* QueryInterface(const char* name,FactoryFn factory)
{
	void* result;
	char version[32];
	int count = 0;
	for (int i=1; i <= 99; i++)
	{
		sprintf_s(version,i > 9 ? "%s0%i" : "%s00%i",name,i);
		result = factory(version,0);
		if (count == -1)
			break;
		if (result)
			count++;
		else if (count > 0)
			i -= 2,count = -1;
	}
	return result;
}