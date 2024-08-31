class LMenu
{
public:
	LMenu();
	void Think();
	void Paint();

	bool Enabled = false;

	LBaseObject* MainFrame = NULL;
	LBaseObject* AddCheckbox(const char*, int*, std::vector<LBaseObject*>*);

	std::vector<LBaseObject*>* ObjectList = new std::vector<LBaseObject*>;
};

LBaseObject* LMenu::AddCheckbox(const char* Name, int* Var, std::vector<LBaseObject*>* Tab)
{
	LCheckbox* NewCheckbox = new LCheckbox;
	NewCheckbox->SetParent(MainFrame);
	NewCheckbox->Text = Name;
	NewCheckbox->Var = Var;
	NewCheckbox->Init(this->ObjectList);
	NewCheckbox->SetPos(10, 70 + Tab->size() * 25);
	Tab->push_back(NewCheckbox);
	return NewCheckbox;
}

LMenu::LMenu()
{

	LOverlayPanel* OverlayPanel = new LOverlayPanel;
	OverlayPanel->Init(this->ObjectList);

	LPanel* Frame = new LPanel;
	Frame->SetSize(512, 256);
	Frame->SetPos(100, 100);
	Frame->SetParent(OverlayPanel);
	Frame->Text = "Fukobot";
	Frame->Init(this->ObjectList);
	this->MainFrame = Frame;

	LTab* TabProperty = new LTab(ObjectList);
	TabProperty->SetSize(Frame->W, Frame->H);
	TabProperty->SetPos(0, 25);
	TabProperty->SetParent(Frame);
	TabProperty->MenuList = this->ObjectList;
	TabProperty->Init(this->ObjectList);

	LTabButton* AimbotTab = new LTabButton;
	std::vector<LBaseObject*> AimbotItems;
	
	AddCheckbox("Aimbot", Vars->AIM_Enabled, &AimbotItems);
	AddCheckbox("Autofire", Vars->AIM_AutoFire, &AimbotItems);
	AddCheckbox("Target Team", Vars->AIM_TargetTeam, &AimbotItems);
	AddCheckbox("Silent Aim", Vars->AIM_SilentAim, &AimbotItems);

	TabProperty->AddTab(FormTab("Aimbot", AimbotItems, AimbotTab));

	LTabButton* VisualTab = new LTabButton;
	std::vector<LBaseObject*> VisualItems;

	AddCheckbox("Players", Vars->ESP_ShowPlayer, &VisualItems);
	AddCheckbox("Entities", Vars->ESP_ShowEntity, &VisualItems);
	AddCheckbox("Dynamic Boxes", Vars->ESP_ShowBones, &VisualItems);
	AddCheckbox("Crosshair", Vars->ESP_ShowCrosshair, &VisualItems);

	TabProperty->AddTab(FormTab("Visuals", VisualItems, VisualTab));

	LTabButton* MiscTab = new LTabButton;
	std::vector<LBaseObject*> MiscItems;

	AddCheckbox("BunnyHop", Vars->MIS_BunnyHop, &MiscItems);
	AddCheckbox("Chat Spam", Vars->MIS_ChatSpam, &MiscItems);
	AddCheckbox("Spread Compensation", Vars->MIS_NoSpread, &MiscItems);
	AddCheckbox("Speed", Vars->MIS_Speed, &MiscItems);

	TabProperty->AddTab(FormTab("Misc", MiscItems, MiscTab));

} LMenu *FukoMenu = new LMenu();


void LMenu::Think()
{
	LoliInput.Think();

	if (!Enabled)
		return;

	for (LBaseObject* Object : *ObjectList)
		Object->DoThink();
}

void LMenu::Paint()
{

	if (!Enabled)
		return;

	for (LBaseObject* Object : *ObjectList)
		Object->DoPaint();
}