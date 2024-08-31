typedef void* (*msg)(const char* cstr, ...);

namespace debug
{
	msg print;
	void message(const char* cdata)
	{
		MessageBoxA(NULL, cdata, ".cake", NULL);
	}
}