#include <Windows.h>
#include "SDK.h"
#include "Control Variables.h" // gCvars
#include "File Manager.h" // gFileManager

//===================================================================================

//===================================================================================
void CControlVariables::Initialize( void )
{
	misc_menu_x = 30;
	misc_menu_y = 500;
	misc_menu_w = 200;
	//this->Load();
}
//===================================================================================
void CControlVariables::Save(void)
{
	ALX.pFileManager->WriteFloat("Aimbot", "Aimbot", aimbot);
	ALX.pFileManager->WriteFloat("Aimbot", "RCS", rcs);
	ALX.pFileManager->WriteFloat("Aimbot", "FOV", fov);
	ALX.pFileManager->WriteFloat("Aimbot", "Smooth", smooth);
	ALX.pFileManager->WriteFloat("Aimbot", "Aim key", aimkey);
	ALX.pFileManager->WriteFloat("Aimbot", "Aim bone", aimbone);
	ALX.pFileManager->WriteFloat("Aimbot", "Auto Shoot", autoshoot);

	ALX.pFileManager->WriteFloat("Triggerbot", "Triggerbot", trigger);
	ALX.pFileManager->WriteFloat("Triggerbot", "Trigger Key", triggerkey);

	ALX.pFileManager->WriteFloat("pSilent Trigger", "pSilent Triggerbot", seedtrigger);
	ALX.pFileManager->WriteFloat("pSilent Trigger", "pSilent Trigger key", seedtriggerkey);
	ALX.pFileManager->WriteFloat("pSilent Trigger", "pSilent Bone", seedBone);

	ALX.pFileManager->WriteFloat("Misc", "Dot ESP", esp);
	ALX.pFileManager->WriteFloat("Misc", "Box ESP", boxesp);
	ALX.pFileManager->WriteFloat("Misc", "Health %", Health);
	ALX.pFileManager->WriteFloat("Misc", "Health Bar", Healthbar);
	ALX.pFileManager->WriteFloat("Misc", "Armor Bar", Armor);
	ALX.pFileManager->WriteFloat("Misc", "Weapon ESP", Weapons);
	ALX.pFileManager->WriteFloat("Misc", "Name ESP", Name);
	ALX.pFileManager->WriteFloat("Misc", "Recoil Tracer", Recoil);
	ALX.pFileManager->WriteFloat("Misc", "Bunnyhop", Bunny);
	ALX.pFileManager->WriteFloat("Misc", "Reduce Flash", noflash);
}
//===================================================================================
void CControlVariables::Load( void )
{

	ALX.pFileManager->ReadFloat("Aimbot", "Aimbot", aimbot);
	ALX.pFileManager->ReadFloat("Aimbot", "RCS", rcs);
	ALX.pFileManager->ReadFloat("Aimbot", "FOV", fov);
	ALX.pFileManager->ReadFloat("Aimbot", "Smooth", smooth);
	ALX.pFileManager->ReadFloat("Aimbot", "Aim key", aimkey);
	ALX.pFileManager->ReadFloat("Aimbot", "Aim bone", aimbone);
	ALX.pFileManager->ReadFloat("Aimbot", "Auto Shoot", autoshoot);

	ALX.pFileManager->ReadFloat("Triggerbot", "Triggerbot", trigger);
	ALX.pFileManager->ReadFloat("Triggerbot", "Trigger Key", triggerkey);

	ALX.pFileManager->ReadFloat("pSilent Trigger", "pSilent Triggerbot", seedtrigger);
	ALX.pFileManager->ReadFloat("pSilent Trigger", "pSilent Trigger key", seedtriggerkey);
	ALX.pFileManager->ReadFloat("pSilent Trigger", "pSilent Bone", seedBone);

	ALX.pFileManager->ReadFloat("Misc", "Dot ESP", esp);
	ALX.pFileManager->ReadFloat("Misc", "Box ESP", boxesp);
	ALX.pFileManager->ReadFloat("Misc", "Health %", Health);
	ALX.pFileManager->ReadFloat("Misc", "Health Bar", Healthbar);
	ALX.pFileManager->ReadFloat("Misc", "Armor Bar", Armor);
	ALX.pFileManager->ReadFloat("Misc", "Weapon ESP", Weapons);
	ALX.pFileManager->ReadFloat("Misc", "Name ESP",Name);
	ALX.pFileManager->ReadFloat("Misc", "Recoil Tracer", Recoil);
	ALX.pFileManager->ReadFloat("Misc", "Bunnyhop", Bunny);
	ALX.pFileManager->ReadFloat("Misc", "Reduce Flash", noflash);

}
//===================================================================================
