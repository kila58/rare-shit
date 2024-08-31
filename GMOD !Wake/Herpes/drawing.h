/*
Zeus TF2 Basehook
Copyright (C) 2009 Xeno123

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

int			curX;
int			curY;
Color		CurColor;
vgui::HFont hCurFont;
vgui::HFont Tab;
vgui::HFont weaponFont;
vgui::HFont weaponFont2;

void FontInit()
{
	hCurFont = 9;
	weaponFont = 5;
	weaponFont2 = 5;

	/*
	hCurFont = m_pSurface->CreateFont();
	m_pSurface->SetFontGlyphSet( hCurFont, "Arial Regular", 12, 450, 0, 0, 0x000 );

	//Tab = m_pSurface->CreateFont();
	//m_pSurface->SetFontGlyphSet( hCurFont, "TabLarge", 12, 450, 0, 0, 0x200 );

	weaponFont = m_pSurface->CreateFont();
	m_pSurface->SetFontGlyphSet( weaponFont, "csd", 40, 40, 0, 0, 0x200 );

	weaponFont2 = m_pSurface->CreateFont();
	m_pSurface->SetFontGlyphSet( weaponFont2, "csd", 35, 35, 0, 0, 0x200 );
	*/
}

void DrawString(int x, int y, Color color, const std::string& Text )
{
	std::wstring szTemp = boost::lexical_cast<std::wstring,const char*> (Text.c_str());
	const wchar_t* szConverted = szTemp.c_str();
	
	m_pSurface->DrawSetTextFont( hCurFont );
	m_pSurface->DrawSetTextColor( color );
	m_pSurface->DrawSetTextPos( x, y );
	m_pSurface->DrawPrintText( szConverted, wcslen(szConverted) );
}

void DrawStringA(int x, int y, Color color, const std::string& Text)
{
	std::wstring szTemp = boost::lexical_cast<std::wstring,const char*> (Text.c_str());
	const wchar_t* szConverted = szTemp.c_str();
	
	m_pSurface->DrawSetTextFont( Tab );
	m_pSurface->DrawSetTextColor( color );
	m_pSurface->DrawSetTextPos( x, y );
	m_pSurface->DrawPrintText( szConverted, wcslen(szConverted) );
}

void BeginESPDraw(int x, int y, Color color)
{
	curX = x;
	curY = y;
	CurColor = color;
}

void DrawESPText(const std::string& Text)
{
	DrawString(curX + 4, curY + 1, Color(0, 0, 0, 255), Text);
	DrawString(curX + 3, curY, CurColor, Text);
	curY += 12;
}

void DrawTextCentered(int x, int y, Color color, const std::string& Text)
{
	int W, T;
	std::wstring szTemp = boost::lexical_cast<std::wstring,const char*> (Text.c_str());
	const wchar_t* szConverted = szTemp.c_str();

	m_pSurface->GetTextSize( hCurFont, szConverted, W, T );
	m_pSurface->DrawSetTextFont( hCurFont );
	m_pSurface->DrawSetTextColor( color );
	m_pSurface->DrawSetTextPos( x - ( W / 2 ), y );
	m_pSurface->DrawPrintText( szConverted, wcslen( szConverted )  );
}

void FillRGBA(int x, int y, int w, int h, Color color)
{
	m_pSurface->DrawSetColor( color );
	m_pSurface->DrawFilledRect(x,y,x+w,y+h);
}

void DrawOutlinedRect(int x, int y, int w, int h, Color color)
{
	m_pSurface->DrawSetColor( color );
	m_pSurface->DrawOutlinedRect(x,y,x+w,y+h);
}

void DrawOutlinedRectangle(int x, int y, int w, int h, Color colColor)
{
	m_pSurface->DrawSetColor(Color(10, 10, 10, 255));
	m_pSurface->DrawOutlinedRect(x - 1, y - 1, (x - 1) + (w + 2), (h + 2) + (y - 1));
	m_pSurface->DrawOutlinedRect(x + 1, y + 1, (w - 2) + (x + 1), (h - 2) + (y + 1));
	m_pSurface->DrawSetColor(colColor);
	m_pSurface->DrawOutlinedRect(x, y, x + w, h + y);
}

bool ScreenTransform( const Vector &point, Vector &screen )
{
	float w;
	const VMatrix &worldToScreen = m_pEngine->WorldToScreenMatrix();
		
	screen.x = worldToScreen[0][0] * point[0] + worldToScreen[0][1] * point[1] + worldToScreen[0][2] * point[2] + worldToScreen[0][3];
	screen.y = worldToScreen[1][0] * point[0] + worldToScreen[1][1] * point[1] + worldToScreen[1][2] * point[2] + worldToScreen[1][3];
	w = worldToScreen[3][0] * point[0] + worldToScreen[3][1] * point[1] + worldToScreen[3][2] * point[2] + worldToScreen[3][3];
	screen.z = 0.0f;

	bool behind = false;

	if( w < 0.001f )
	{
		behind = true;
		screen.x *= 100000;
		screen.y *= 100000;
	}
	else
	{
		behind = false;
		float invw = 1.0f / w;
		screen.x *= invw;
		screen.y *= invw;
	}
	return behind;
}

void GetWorldSpaceCenter( CBaseEntity* pBaseEntity, Vector& WorldSpaceCenter )
{
	Vector Min, Max;
	pBaseEntity->GetRenderBounds( Min, Max );
	WorldSpaceCenter = pBaseEntity->GetAbsOrigin();
	WorldSpaceCenter.z += (Min.z + Max.z) / 2.0f;
}

bool WorldToScreen( const Vector &origin, Vector &screen )
{
	if( !ScreenTransform( origin, screen ) )
	{
		int ScreenWidth, ScreenHeight;
		m_pEngine->GetScreenSize( ScreenWidth, ScreenHeight );
		float x = ScreenWidth / 2;
		float y = ScreenHeight / 2;
		x += 0.5 * screen.x * ScreenWidth + 0.5;
		y -= 0.5 * screen.y * ScreenHeight + 0.5;
		screen.x = x;
		screen.y = y;
		return true;
	}

	return false;
}