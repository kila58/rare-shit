class CVars
{
public:
	void Initialize();
}; CVars Var;

void CVars::Initialize()
{
	InterfaceManager.Cvar->RegisterConCommand((ConCommandBase*)"Hey");
}