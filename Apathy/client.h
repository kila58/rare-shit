#pragma once


#include "Entrypoint.h"
void CL_Speed(void*);


class Client
{
public:
	dword clientbase;
	dword enginebase;
	void* base;
	ClientEntityList* ents;
	void* pred;
	BaseEngine* engine;
	EngineModel* mdl;
	EngineTrace* trace;
	void* panel;
	EngineVGUI* vgui;
	GameSurface* surface;
	void* input;
	void* mode;
	void* helper;
	void* m_mFlags;
	Entity* me;
	Entity* wep;
	vec3 shootpos;
	int local;
	int sw;
	int sh;
};




extern Client cl;

void DoMain(UserCmd*);
void Bhop(UserCmd*);
void Nospread(UserCmd*);
//void Nospread(UserCmd*);