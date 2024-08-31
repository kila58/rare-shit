#define WIN32_LEAN_AND_MEAN
#define CHEAT_COLOR Color(200,0,250,255)

class console{
public:
	void Print(const char* pMsg, int i);
}; console *Console = new console;

void console::Print(const char* pMsg, int i=0){
	ConColorMsg(CHEAT_COLOR, "[FukoBot] ");
	Msg(pMsg, i);
	Msg("\n");
}