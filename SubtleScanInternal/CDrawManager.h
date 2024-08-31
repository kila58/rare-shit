#pragma once
//===================================================================================
#include "Main.h"

#define RED(COLORCODE)	((int) ( COLORCODE >> 24) )
#define BLUE(COLORCODE)	((int) ( COLORCODE >> 8 ) & 0xFF )
#define GREEN(COLORCODE)	((int) ( COLORCODE >> 16 ) & 0xFF )
#define ALPHA(COLORCODE)	((int) COLORCODE & 0xFF )
#define COLORCODE(r,g,b,a)((DWORD)((((r)&0xff)<<24)|(((g)&0xff)<<16)|(((b)&0xff)<<8)|((a)&0xff)))
#define colWhite Color(255,255,255,255)
//===================================================================================
class CDrawManager
{
public:
	int gScreenWidth;
	int gScreenHeight;
	void Initialize();
	void DrawString(bool centred, bool esp, int x, int y, Color dwColor, const wchar_t *pszText);
	void DrawString(bool centred, bool esp, int x, int y, Color dwColor, const char *pszText, ...);
	byte GetESPHeight();
	int GetPixelTextSize(const char *pszText);
	int GetPixelTextSize(wchar_t *pszText);
	void DrawBox(Vector vOrigin, int r, int g, int b, int alpha, int box_width, int radius);
	void DrawRect(int x, int y, int w, int h, Color dwColor);
	void OutlineRect(int x, int y, int w, int h, Color dwColor);
	bool WorldToScreen(Vector &vOrigin, Vector &vScreen);
	void DrawPlayerBox(CBaseEntityNew *pEnt, Color dwColor, Vector &vTop, Vector &vBot, int &iW, int &iH);
	float flGetDistance(Vector from, Vector to);
	void DrawCrosshair(int iValue);
	bool GetBonePosition(CBaseEntityNew* pPlayer, Vector& Hitbox, int Bone)
	{
		matrix3x4_t MatrixArray[128];

		if (!pPlayer->SetupBones(MatrixArray, 128, BONE_USED_BY_HITBOX, 0))
			return false;

		Hitbox = Vector(MatrixArray[Bone][0][3], MatrixArray[Bone][1][3], MatrixArray[Bone][2][3]);

		return true;
	}
	void Draw3DBox(const Vector &mins, const Vector &maxs, Color c)
	{
		Vector diff = maxs - mins;
		Vector pointsToDraw[24] = {
			// Bottom Horizontal lines
			mins, mins + Vector(diff.x, 0, 0), // 1 - 2
			mins + Vector(diff.x, 0, 0), mins + Vector(diff.x, diff.y, 0), // 2 - 3
			mins + Vector(diff.x, diff.y, 0), mins + Vector(0, diff.y, 0), // 3 - 4
			mins + Vector(0, diff.y, 0), mins, // 4 - 1

			// Vertical Lines

			mins, mins + Vector(0, 0, diff.z), // 1 - 6
			mins + Vector(diff.x, 0, 0), mins + Vector(diff.x, 0, diff.z), // 2 - 7
			mins + Vector(diff.x, diff.y, 0), mins + Vector(diff.x, diff.y, diff.z), // 3 - 8
			mins + Vector(0, diff.y, 0), mins + Vector(0, diff.y, diff.z), // 4 - 5

			// Top Horizontal lines.
			maxs, maxs - Vector(diff.x, 0, 0), // 8 - 5
			maxs - Vector(diff.x, 0, 0), maxs - Vector(diff.x, diff.y, 0), // 5 - 6
			maxs - Vector(diff.x, diff.y, 0), maxs - Vector(0, diff.y, 0), // 6 - 7
			maxs - Vector(0, diff.y, 0), maxs // 7 - 8
		};
		Vector startPos, endPos;
		for (int i = 0; i < 24; i += 2)
		{
			if (WorldToScreen(pointsToDraw[i], startPos))
			{
				if (WorldToScreen(pointsToDraw[i + 1], endPos))
					DrawLine(startPos.x, startPos.y, endPos.x, endPos.y,c);
			}
		}


	}
	void DrawCircle(int x, int y, int radius,Color col)
	{
		Surface->DrawSetColor(col);
		Surface->DrawOutlinedCircle(x, y, radius, 32);
	}
	void DrawBone(int StartBone, int EndBone, CBaseEntityNew* target, Color drawCol)
	{
		Vector StartBonePos, EndBonePos;
		Vector StartDrawPos, EndDrawPos;
		if (!target)
			return;

		GetBonePosition(target, StartBonePos,StartBone);

		GetBonePosition(target, EndBonePos,EndBone);

		if (!WorldToScreen(StartBonePos, StartDrawPos))
			return;

		if (!WorldToScreen(EndBonePos, EndDrawPos))
			return;

		Surface->DrawSetColor(drawCol);
		Surface->DrawLine(StartDrawPos.x, StartDrawPos.y, EndDrawPos.x, EndDrawPos.y);
	}
	void DrawLine(int x, int y, int w, int h, Color c)
	{
		Surface->DrawSetColor(c);
		Surface->DrawLine(x, y, w,h);
	}

	void DrawHealthBar(int x, int y, int w,int h, int hp)
	{
		float red = 255 - (hp*2.55);
		float green = hp*2.55;
		x -= w / 2;
		y -= h / 2;
		DrawRect(x, y, w, h + 1, Color(20,20,20,255));
		UINT hw = (UINT)(((w - 2) * hp) / 100);
		DrawRect(x + 1, y + 1, hw, h - 1, Color(red,green,0,255));		
	}
	void DrawRhombusFill(int x, int y, int w, int h, Color dwColor)
	{
		int W = w / 2;
		Surface->DrawSetColor(dwColor);
		for (int i = 0; i < h; i++)
		{
			this->DrawLine(x + W - i, y + i, x + W + w - i, y + i,dwColor);
		}
	}
	void DrawLineBox(int x, int y, int howfaryo, int w, int h, Color Line, Color bground, const char* Text)
	{
		OutlineRect(x, y, w, h, Line);
		DrawLine(x + 10, y, x + howfaryo, y, bground);
		DrawString(false, true, x + 20, y - 5, colWhite, Text);
	}
	void DrawRhombus(int x, int y, int w, int h, Color dwColor)
	{
		int W = w / 2;

		this->DrawLine(x + W, y, x + W + w, y, dwColor); //top
		this->DrawLine(x + W - h, y + h, x + W, y, dwColor); //left
		this->DrawLine(x + W + w - h, y + h, x + W + w, y, dwColor); //right
		this->DrawLine(x + W - h, y + h, x + W + w - h, y + h, dwColor); //bottom
	}
private:
	unsigned long m_Font;
};
//===================================================================================
extern CDrawManager gDrawManager;
//===================================================================================