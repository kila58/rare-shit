#include "sdk/structs.h"

class Entity
{
public:
	EntClass* GetClass()
	{
		void* ptr = this + 0x8;
		typedef EntClass* (__thiscall* dfn)(void*);
		return ((dfn)(*(dword**)ptr)[2])(ptr);
	}
	vec3& GetOrigin()
	{
		void* ptr = this + 0x4;
		typedef vec3& (__thiscall* dfn)(void*);
		return ((dfn)(*(dword**)ptr)[1])(ptr);
	}
	void* GetModel()
	{
		void* ptr = this + 0x4;
		typedef void* (__thiscall* dfn)(void*);
		return ((dfn)(*(dword**)ptr)[9])(ptr);
	}

	bool SetupBones(matrix3x4* mtx)
	{
		void* ptr = this + 0x4;
		typedef bool(__thiscall* dfn)(void*, matrix3x4*, int, dword, float);
		return ((dfn)(*(dword**)ptr)[16])(ptr, mtx, 128, 0x100, 0);
	}
	int Health() { return *(int*)(this + 0x90); }
	bool Alive() { return !*(bool*)(this + 0x8F); }
	int Weapon() { return *(int*)(this + 0x2578); }
	int Ammo() { return *(int*)(this + 0x1B7C); }
	int m_iTeamNum() { return *(int*)(this + 0x9C); }
	int m_fFlags() { return *(int*)(this + 0x350); }
	int m_nTickBase() { return *(int*)(this + 0x28F0); }
	vec3 Velocity() { return *(vec3*)(this + 0xF4); }
	vec3 LocalOrigin() { return *(vec3*)(this + 0x338); }
	vec3 ViewOffset() { return *(vec3*)(this + 0xE8); }
	vec3 Maxs() { return *(vec3*)(this + 0x19c + 0x2c); } // m_Collideable + m_vecMaxs
	vec3 Mins() { return *(vec3*)(this + 0x19c + 0x20); } // ok wait
};

class BaseFilter
{
	virtual bool ShouldHitEntity(Entity*,int) = 0;
	virtual int GetTraceType() = 0;
};

class TraceFilter : public BaseFilter
{
public:
	bool ShouldHitEntity(Entity* ent,int)
	{
		if (!ent)
			return false;
		if (ent == local)
			return false;
		if (ent == ignore)
			return false;
		return true;
	}
	int GetTraceType() { return 0; }
	Entity* local;
	Entity* ignore;
};

class ClientEntityList
{
public:
	Entity* GetEntity(int i,bool hnd = false)
	{
		typedef Entity* (__thiscall* dfn)(void*,int);
		return ((dfn)(*(dword**)this)[hnd ? 4 : 3])(this,i);
	}
};

class BaseEngine
{
public:
	void GetScreenSize(int& w, int& h)
	{
		typedef void(__thiscall* dfn)(void*, int&, int&);
		((dfn)(*(dword**)this)[5])(this, w, h);
	}
	void GetPlayerInfo(int index, PlayerInfo& info)
	{
		typedef void(__thiscall* dfn)(void*, int, PlayerInfo&);
		((dfn)(*(dword**)this)[8])(this, index, info);
	}
	int GetLocalPlayer()
	{
		typedef int(__thiscall* dfn)(void*);
		return ((dfn)(*(dword**)this)[12])(this);
	}
	int GetMaxClients()
	{
		typedef int(__thiscall* dfn)(void*);
		return ((dfn)(*(dword**)this)[21])(this);
	}
	void SetViewAngles(vec3& ang)
	{
		typedef void(__thiscall* dfn)(void*, vec3&);
		return ((dfn)(*(dword**)this)[20])(this, ang);
	}
	matrix3x4& GetScreenMatrix()
	{
		typedef matrix3x4& (__thiscall* dfn)(void*);
		return ((dfn)(*(dword**)this)[36])(this);
	}

};
class EngineModel
{
public:
	const char* GetModelName(void* mdl)
	{
		typedef const char* (__thiscall* dfn)(void*,void*);
		return ((dfn)(*(dword**)this)[3])(this,mdl);
	}
	StudioHDR* GetStudioModel(void* mdl)
	{
		typedef StudioHDR* (__thiscall* dfn)(void*,void*);
		return ((dfn)(*(dword**)this)[28])(this,mdl);
	}
};

class EngineTrace
{
public:
	void TraceRay(TraceResult* tr,RayData& ray,TraceFilter* filter)
	{
		typedef void (__thiscall* dfn)(void*,RayData&,dword,TraceFilter*,TraceResult*);
		((dfn)(*(dword**)this)[4])(this,ray,0x4600400B,filter,tr);
	}
};

class EngineVGUI
{
public:
	int GetPanel(int panel)
	{
		typedef int (__thiscall* dfn)(void*,int);
		return ((dfn)(*(dword**)this)[1])(this,panel);
	}
};

class GameSurface // if thoses ones crash, do +1 like if it is 75 then it's 76
{
public:
	void GetTextSize(unsigned long arg1, wchar_t const* arg2, int &width, int &height)
	{
		typedef void(__thiscall* dfn)(void*, unsigned long, wchar_t  const*, int &, int &);
		((dfn)(*(dword**)this)[75])(this, arg1, arg2, width, height); // might crash
	}
	void DrawLine(int x, int y, int xx, int yy)
	{
		typedef void(__thiscall* dfn)(void*, int, int, int, int);
		((dfn)(*(dword**)this)[15])(this, x, y, xx, yy); // might crash
	}
	void SetDrawColor(int r, int g, int b)
	{
		typedef void(__thiscall* dfn)(void*, int, int, int, int);
		((dfn)(*(dword**)this)[11])(this, r, g, b, 255); // if it's styles who made this, he's dumb since he forces alpha to 255 ya styler wearing made it
	}
	void SetDrawColor(Color colColor)
	{
		typedef void(__thiscall* dfn)(void*, int, int, int, int);
		((dfn)(*(dword**)this)[11])(this, colColor.r, colColor.g, colColor.b, colColor.a);
	}
	void DrawRect(int x, int y, int w, int h)
	{
		typedef void(__thiscall* dfn)(void*, int, int, int, int);
		((dfn)(*(dword**)this)[12])(this, x, y, x + w, y + h);
	}
	void DrawOutlined(int x, int y, int w, int h)
	{
		typedef void(__thiscall* dfn)(void*, int, int, int, int);
		((dfn)(*(dword**)this)[14])(this, x, y, x + w, y + h);
	}
	void SetFont(int font)
	{
		typedef void(__thiscall* dfn)(void*, int);
		((dfn)(*(dword**)this)[17])(this, font);
	}
	void SetTextColor(int r, int g, int b)
	{
		typedef void(__thiscall* dfn)(void*, int, int, int, int);
		((dfn)(*(dword**)this)[19])(this, r, g, b, 255);
	}
	void SetTextColor(Color colColor)
	{
		typedef void(__thiscall* dfn)(void*, int, int, int, int);
		((dfn)(*(dword**)this)[19])(this, colColor.r, colColor.g, colColor.b, colColor.a);
	}
	void SetTextPos(int x, int y)
	{
		typedef void(__thiscall* dfn)(void*, int, int);
		((dfn)(*(dword**)this)[20])(this, x, y);
	}
	void DrawText(const char* string)
	{
		typedef void(__thiscall* dfn)(void*, const wchar_t*, int, int);
		wchar_t result[128];
		wsprintfW(result, L"%S", string);
		((dfn)(*(dword**)this)[22])(this, result, wcslen(result), 0);
	}
	void DrawCircle(int x, int y, int size, int vertices)
	{
		typedef void(__thiscall* dfn)(void*, int, int, int, int);
		((dfn)(*(dword**)this)[99])(this, x, y, size, vertices);
	}


};