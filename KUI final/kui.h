#include <vector>
#include "kui_input.h"
#include "kui_base.h"
#include "kui_form.h"
#include "kui_tab.h"
#include "kui_checkbox.h"
#include "kui_groupbox.h"
#include "kui_slider.h"
#include "kui_combobox.h"
#include "kui_textbox.h"
#include "kui_keytrap.h"
#include "kui_splitter.h"
#include "wrapper.h"

//todo: dynamically place elements like a combobox does with options

class KUIMenu
{
public:
	void Draw();
	void Mouse();

	kui_form* menu;

	KUIMenu();
};

bool testbool1;
bool testbool2;
bool testbool3;
bool testbool4;
bool testbool5;
int testint1;
char* testchar1 = "";

//height inbetween elements (pixels)
//tab = 27
//splitter = 11
//checkbox = 18
//combo/text/keytrap box = 26
//slider = 30

int defaultspacer = 6;
int extendedspacer = 11;
int rightsidespacer = 231;

KUIMenu::KUIMenu()
{
	//form setup
	menu = wrapper::Form(270, 100, 340, 499, "Origin Cheats CS:GO");

	//tab setup
	kui_tab* aimbot_tab = wrapper::Tab("Aimbot", menu);
	kui_tab* visuals_tab = wrapper::Tab("Visuals", menu);
	kui_tab* misc_tab = wrapper::Tab("Misc", menu);
	kui_tab* colors_tab = wrapper::Tab("Colors", menu);
	kui_tab* settings_tab = wrapper::Tab("Settings", menu);

	//element setup

	//aimbot
	kui_splitter* aimbot_splitter = wrapper::Splitter(defaultspacer, 27, menu->w - defaultspacer, 0, "Aimbot", aimbot_tab);

	kui_checkbox* aimbot_enabled = wrapper::CheckBox(&var.aimbot_enabled, 0, 11, 12, 12, "Enabled", aimbot_splitter);

	//kui_checkbox* aimbot_hitscan = wrapper::CheckBox(&testbool5, 0, 18, 12, 12, "Hit scan", aimbot_enabled);

	kui_checkbox* aimbot_autofire = wrapper::CheckBox(&var.aimbot_autoshoot, 0, 18, 12, 12, "Auto shoot", aimbot_enabled);

	kui_checkbox* aimbot_speedrandom = wrapper::CheckBox(&var.aimbot_speedrandom, 0, 18, 12, 12, "Speed randomization", aimbot_autofire);

	kui_checkbox* aimbot_silentaim = wrapper::CheckBox(&var.aimbot_silent, 0, 18, 12, 12, "Silent aim", aimbot_speedrandom);

	//kui_checkbox* aimbot_antismac = wrapper::CheckBox(&var.aimbot_smac, 0, 18, 12, 12, "Anti smac", aimbot_silentaim);

	kui_keytrap* aimbot_key = wrapper::KeyTrap(&var.aimbot_key, rightsidespacer, 11, 100, 16, aimbot_splitter);

	kui_combobox* aimbot_teamselection = wrapper::ComboBox("Team selection...", 0, 26, 100, 15, aimbot_key);
	aimbot_teamselection->AddOption("Both teams", &var.aimbot_aimall);
	aimbot_teamselection->AddOption("Enemies", &var.aimbot_aimenemy);
	aimbot_teamselection->AddOption("Teamates", &var.aimbot_aimteam);

	kui_combobox* aimbot_targeting = wrapper::ComboBox("Targeting...", 0, 26, 100, 15, aimbot_teamselection);
	aimbot_targeting->AddOption("Crosshair", &var.aimbot_targetingcross);
	aimbot_targeting->AddOption("Distance", &var.aimbot_targetingdist);

	kui_combobox* aimbot_hitbox = wrapper::ComboBox("Hitbox...", 0, 26, 100, 15, aimbot_targeting);
	aimbot_hitbox->AddOption("Head", &var.aimbot_head);
	aimbot_hitbox->AddOption("Neck", &var.aimbot_neck);
	aimbot_hitbox->AddOption("Chest", &var.aimbot_chest);
	aimbot_hitbox->AddOption("Stomach", &var.aimbot_stomach);
	aimbot_hitbox->AddOption("Pelvis", &var.aimbot_pelvis);

	kui_slider* aimbot_fov = wrapper::Slider(&var.aimbot_fov, 0, 40, 0, 26, 100, 8, "FoV", aimbot_hitbox);

	kui_slider* aimbot_speed = wrapper::Slider(&var.aimbot_speed, 0, 20, 0, 26, 100, 8, "Speed", aimbot_fov);

	kui_splitter* aimbot_accuracysplitter = wrapper::Splitter(-rightsidespacer, 30, menu->w - defaultspacer, 0, "Accuracy", aimbot_speed);

	kui_checkbox* aimbot_rcs = wrapper::CheckBox(&var.aimbot_rcs, 0, 11, 12, 12, "Recoil control", aimbot_accuracysplitter);

	kui_checkbox* aimbot_autocrouch = wrapper::CheckBox(&var.aimbot_autocrouch, 0, 18, 12, 12, "Auto crouch", aimbot_rcs);



	//misc
	kui_splitter* misc_splitter = wrapper::Splitter(defaultspacer, 27, menu->w - defaultspacer, 0, "Misc", misc_tab);

	kui_checkbox* misc_bhop = wrapper::CheckBox(&var.misc_bhop, 0, 11, 12, 12, "Bunny hop", misc_splitter);

	kui_checkbox* misc_autopistol = wrapper::CheckBox(&var.misc_autopistol, 0, 18, 12, 12, "Auto pistol", misc_bhop);

	kui_checkbox* misc_lag = wrapper::CheckBox(&var.misc_lag, 0, 18, 12, 12, "Server lagger", misc_autopistol);

	//kui_keytrap* misc_airstuck = wrapper::KeyTrap(&var.misc_airstuckkey, rightsidespacer, 11, 100, 16, misc_splitter);


	kui_splitter* chatspam_splitter = wrapper::Splitter(0, 27, menu->w - defaultspacer, 0, "Chat spam", misc_lag);

	kui_checkbox* chatspam_enabled = wrapper::CheckBox(&var.chatspam_enabled, 0, 11, 12, 12, "Enabled", chatspam_splitter);

	kui_checkbox* chatspam_smac = wrapper::CheckBox(&var.chatspam_smac, 0, 18, 12, 12, "Anti smac", chatspam_enabled);

	kui_checkbox* chatspam_radio = wrapper::CheckBox(&var.chatspam_radio, 0, 18, 12, 12, "Radio spam", chatspam_smac);

	kui_textbox* chatspam_textbox = wrapper::TextBox("Spam text...", &var.customspam, rightsidespacer, 11, 100, 16, chatspam_splitter);

	kui_combobox* chatspam_selection = wrapper::ComboBox("Spam selection...", 0, 26, 100, 15, chatspam_textbox);
	chatspam_selection->AddOption("Custom", &var.chatspam_custom);
	chatspam_selection->AddOption("Aimware", &var.chatspam_aimware);
	chatspam_selection->AddOption("Unity", &var.chatspam_unity);
	chatspam_selection->AddOption("Interwebz", &var.chatspam_iwebz);

	//flip the vector for proper rendering
	std::reverse(elements.begin(), elements.end());
}

void KUIMenu::Mouse()
{
	static bool cmdonce;

	var.menu_open = menu->visible;

	if (var.menu_open)
	{
		n_draw::DrawString(symbolfont, false, false, Input.mouse_x, Input.mouse_y, Color(0, 0, 0, 255), "e");
		n_draw::DrawString(symbolfont, false, false, Input.mouse_x + 1, Input.mouse_y + 1, Color(255, 255, 255, 255), "e");
		n_draw::DrawString(symbolfont, false, false, Input.mouse_x + 2, Input.mouse_y + 2, Color(0, 0, 0, 255), "e");

		if (!cmdonce)
		{
			ints.engine->ClientCmd("cl_mouseenable 0");
			cmdonce = true;
		}
	}
	else
	{
		if (cmdonce)
		{
			ints.engine->ClientCmd("cl_mouseenable 1");
			cmdonce = false;
		}
	}
}

void KUIMenu::Draw()
{
	Input.UpdateMousePos();

	//combobox input
	for (int i = 0; i < comboboxes.size(); i++)
		comboboxes[i]->MouseInput();

	//window render
	for (int i = 0; i < windows.size(); i++)
		windows[i]->Draw();

	//element render
	for (int i = 0; i < elements.size(); i++)
		elements[i]->Draw();
}

KUIMenu *KUI = new KUIMenu();