namespace wrapper
{
	kui_form* Form(int x, int y, int w, int h, std::string name)
	{
		kui_form* NewForum = new kui_form();
		NewForum->SetDimensions(w, h);
		NewForum->SetPosition(x, y);
		NewForum->SetName(name);

		return NewForum;
	}

	//preset because ik how annoying this would be
	kui_tab* Tab(std::string name, kui_base* parent = nullptr, int x = 0, int y = 7, int w = 68, int h = 15)
	{
		kui_tab* NewTab = new kui_tab();
		NewTab->SetDimensions(w, h);
		NewTab->SetPosition(x, y);
		NewTab->SetName(name);
		NewTab->SetParent(parent);

		return NewTab;
	}

	kui_splitter* Splitter(int x, int y, int w, int h, std::string name, kui_base* parent = nullptr)
	{
		kui_splitter* NewSplitter = new kui_splitter();
		NewSplitter->SetDimensions(w, h);
		NewSplitter->SetPosition(x, y);
		NewSplitter->SetName(name);
		NewSplitter->SetParent(parent);

		return NewSplitter;
	}

	kui_checkbox* CheckBox(bool* var, int x, int y, int w, int h, std::string name, kui_base* parent = nullptr)
	{
		kui_checkbox* NewCheckBox = new kui_checkbox();
		NewCheckBox->SetDimensions(w, h);
		NewCheckBox->SetPosition(x, y);
		NewCheckBox->Variable = var;
		NewCheckBox->SetName(name);
		NewCheckBox->SetParent(parent);

		return NewCheckBox;
	}

	kui_combobox* ComboBox(std::string default, int x, int y, int w, int h, kui_base* parent = nullptr)
	{
		kui_combobox* NewComboBox = new kui_combobox();
		NewComboBox->SetDimensions(w, h);
		NewComboBox->SetPosition(x, y);
		NewComboBox->SetDefaultText(default);
		NewComboBox->SetParent(parent);

		return NewComboBox;
	}

	kui_keytrap* KeyTrap(int* var, int x, int y, int w, int h, kui_base* parent = nullptr)
	{
		kui_keytrap* NewKeyTrap = new kui_keytrap();
		NewKeyTrap->SetDimensions(w, h);
		NewKeyTrap->SetPosition(x, y);
		NewKeyTrap->Variable = var;
		NewKeyTrap->SetParent(parent);

		return NewKeyTrap;
	}

	kui_textbox* TextBox(std::string default, std::string* var, int x, int y, int w, int h, kui_base* parent = nullptr)
	{
		kui_textbox* NewTextBox = new kui_textbox();
		NewTextBox->SetDimensions(w, h);
		NewTextBox->SetPosition(x, y);
		NewTextBox->SetDefaultText(default);
		NewTextBox->Variable = var;
		NewTextBox->SetParent(parent);

		return NewTextBox;
	}

	kui_slider* Slider(float* var, float min, float max, int x, int y, int w, int h, std::string name, kui_base* parent = nullptr)
	{
		kui_slider* NewSlider = new kui_slider();
		NewSlider->SetDimensions(w, h);
		NewSlider->SetPosition(x, y);
		NewSlider->Variable = var;
		NewSlider->Min = min;
		NewSlider->Max = max;
		NewSlider->SetName(name);
		NewSlider->SetParent(parent);

		return NewSlider;
	}
}