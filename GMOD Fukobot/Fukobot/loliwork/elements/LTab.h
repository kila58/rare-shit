class LTabButton : public LBaseObject
{
public:

	void Think(){};
	void Paint();
	void Click();

	bool Selected = false;
	int Index = 0;
	
};

void LTabButton::Paint()
{
	Draw->DrawBox(this->X, this->Y, this->W, this->H, Color( ColorBg.r()*.8, ColorBg.g()*.8, ColorBg.b()*.8, 200 ));
	Draw->DrawBoxOutline(this->X-1, this->Y-1, this->W+2, this->H+2, Color(0, 0, 0, 200));

	if (this->_Hovered)
		Draw->DrawBox(this->X, this->Y, this->W, this->H, ColorBg );

	if (this->Selected)
		Draw->DrawBox(this->X, this->Y, this->W, this->H+2, ColorBg);

	Draw->DrawStringA(FukoFontMenu, this->X + this->W*.5, this->Y + this->H*.5, TextColor, this->Text);
}

struct FormTab
{
	FormTab::FormTab(const char* Text, std::vector<LBaseObject*>Items, LTabButton* Button) { this->Text = Text; this->Items = Items; this->Button = Button; };
	const char* Text;
	std::vector<LBaseObject*> Items;
	LTabButton* Button;
};

class LTab : public LBaseObject
{
public:
	LTab::LTab(std::vector<LBaseObject*> *MList) { MenuList = MList; };

	void Paint();
	void Think(){};
	void Click(){};

	int OpenIndex = 0;

	std::vector<FormTab> Tabs;

	void AddTab(FormTab);
	std::vector<LTabButton*> Buttons;

	std::vector<LBaseObject*> *MenuList;

};

void LTab::AddTab(FormTab Tab)
{
	Tabs.push_back(Tab);
	Tab.Button->Init(this->MenuList);

	Tab.Button->Index = Tabs.size()-1;
	Tab.Button->W = 70;
	Tab.Button->H = 20;
	Tab.Button->SetPos(5 + (Tab.Button->W+4)*Tab.Button->Index, 5);
	Tab.Button->SetParent(this);
	Tab.Button->Text = Tab.Text;

	for (LBaseObject* Object : Tab.Items)
		Object->Enabled = false;

}

void LTab::Paint()
{ 
	Draw->DrawBoxOutline(X + 4, Y + 25, W - 8, H - 55, Color(0,0,0,255));
}

void LTabButton::Click()
{

	LTab* Tab = (LTab*)this->_Parent;
	Tab->OpenIndex = this->Index;

	for (FormTab CurrentTab : Tab->Tabs)
	{

		CurrentTab.Button->Selected = false;

		if (CurrentTab.Button->Index == Tab->OpenIndex)
			CurrentTab.Button->Selected = true;

		for (LBaseObject* CurrentObject : CurrentTab.Items)
		{

			if (CurrentObject == NULL) continue;
	
			CurrentObject->Enabled = false;

			if (Tab->OpenIndex == CurrentTab.Button->Index)
				CurrentObject->Enabled = true;

		}

	}

}
