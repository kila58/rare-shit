#pragma once

#include "main.h"

class Drawing {
public:
	unsigned long font, font2;

	Drawing() {
		font = engine->CreateFont();
		font2 = engine->CreateFont();
		engine->SetFontGlyphSet( font, "Tahoma", 14, 400, 0, 0, 0x200 );
		engine->SetFontGlyphSet( font2, "Comic Sans Ms", 32, 700, 0, 0, 0x200 );
	}

	inline bool w2s( Vector &origin, Vector &screen ) {
		const VMatrix &vmtx = engine->WorldToScreenMatrix();

		float w = vmtx[3][0] * origin.x + vmtx[3][1] * origin[1] + vmtx[3][2] * origin[2] + vmtx[3][3];
		screen.z = 0;

		if( w < 0.001 )
			return false;

		float mw = 1 / w;
		screen.x = (cheat->scrW * 0.5) + ( 0.5 * ((vmtx[0][0] * origin[0] + vmtx[0][1] * origin[1] + vmtx[0][2] * origin[2] + vmtx[0][3]) * mw) * cheat->scrW + 0.5 );
		screen.y = (cheat->scrH * 0.5) - ( 0.5 * ((vmtx[1][0] * origin[0] + vmtx[1][1] * origin[1] + vmtx[1][2] * origin[2] + vmtx[1][3]) * mw) * cheat->scrH + 0.5 );
	
		if( screen.x < -(cheat->scrW * 0.1) || screen.x > cheat->scrW + (cheat->scrW * 0.1) || screen.y < -(cheat->scrH * 0.1) || screen.y > cheat->scrH + (cheat->scrH * 0.1) )
			return false;

		return true;
	}
	
	inline void drawLine( int x, int y, int endx, int endy, Color col ) {
		engine->DrawSetColor( col );
		engine->DrawLine( x, y, endx, endy );
	}

	inline void drawRect( int x, int y, int w, int h, Color col ){
		engine->DrawSetColor( col );
		engine->DrawOutlinedRect( x, y, w + x, h + y );
	}

	inline void drawFilledRect( int x, int y, int w, int h, Color col ) {
		engine->DrawSetColor( col );
		engine->DrawFilledRect( x, y, w + x, h + y );
	}

	inline void drawOutlinedRect( int x, int y, int w, int h, Color col ) {
		engine->DrawSetColor( Color(0, 0, 0, 255) );
		engine->DrawOutlinedRect( x - 1, y - 1, (x - 1) + (w + 2), (h + 2) + (y - 1) );
		engine->DrawOutlinedRect( x + 1, y + 1, (w - 2) + (x + 1), (h - 2) + (y + 1) );
		engine->DrawSetColor( col );
		engine->DrawOutlinedRect( x, y, x + w, h + y );
	}

	inline void drawFilledRectOutlined( int x, int y, int w, int h, Color colinner, Color colouter ) {
		engine->DrawSetColor( colouter );
		engine->DrawOutlinedRect( x - 1, y - 1, (x - 1) + (w + 2), (h + 2) + (y - 1) );
		engine->DrawSetColor( colinner );
		engine->DrawFilledRect( x, y, w + x, h + y );
	}

	inline void drawOutlinedLine( int x, int y, int endx, int endy, Color col ) {
		engine->DrawSetColor( Color(0, 0, 0, 255) );
		engine->DrawLine( x - 1, y - 1, endx - 1, endy - 1 );
		engine->DrawLine( x + 1, y + 1, endx + 1, endy + 1 );
		engine->DrawSetColor( col );
		engine->DrawLine( x, y, endx, endy );
	}

	inline void drawTexture( int id, int x, int y, int w, int h ) {
		engine->DrawSetTexture( id );
		engine->DrawTexturedRect( x, y, x + w, y + h );
	}

	inline void setupTexture( int &id, const char *path, int &w, int &h ) {
		const unsigned char col[] = { 0xFF, 0xFF, 0xFF, 0xF };
		id = engine->CreateNewTextureID( false );
		engine->DrawSetTextureFile( id, path, 1, true );
		engine->DrawGetTextureSize( id, w, h );
		engine->DrawSetTextureRGBA( id, col, w, h );
	}

	inline void drawEspBox( int minx, int miny, int maxx, int maxy, Color col ) {
		drawRect( minx - 1, miny - 1, maxx + 2, maxy + 2, Color(0, 0, 0, 255) );
		drawRect( minx + 1, miny + 1, maxx - 2, maxy - 2, Color(0, 0, 0, 255) );
		drawRect( minx, miny, maxx, maxy, col );

		//drawOutlinedLine( minx, miny, maxx, miny, col );
		//drawOutlinedLine( minx, maxy, maxx, maxy, col );
		//drawOutlinedLine( minx, miny, minx, maxy, col );
		//drawOutlinedLine( maxx, miny, maxx, maxy, col );
	}

	inline void draw3DEspBox( Vector s[8], Color col ) {
		// bottom lines
		drawLine( s[0].x, s[0].y, s[2].x, s[2].y, col );
		drawLine( s[0].x, s[0].y, s[4].x, s[4].y, col );
		drawLine( s[2].x, s[2].y, s[6].x, s[6].y, col );
		drawLine( s[6].x, s[6].y, s[4].x, s[4].y, col );
		
		// vertical lines
		drawLine( s[0].x, s[0].y, s[1].x, s[1].y, col );
		drawLine( s[2].x, s[2].y, s[3].x, s[3].y, col );
		drawLine( s[4].x, s[4].y, s[5].x, s[5].y, col );
		drawLine( s[6].x, s[6].y, s[7].x, s[7].y, col );

		// top lines
		drawLine( s[1].x, s[1].y, s[3].x, s[3].y, col );
		drawLine( s[1].x, s[1].y, s[5].x, s[5].y, col );
		drawLine( s[3].x, s[3].y, s[7].x, s[7].y, col );
		drawLine( s[7].x, s[7].y, s[5].x, s[5].y, col );
	}

	inline void drawText( unsigned long font, int x, int y, bool centered, Color col, const char *pszText, ... ) {
		if( !pszText )
			return;

		char buf[ 1024 ] = { '\0' };
		wchar_t txt[ 1024 ] = { '\0' };

		va_list vList;

		va_start( vList, pszText );
		vsprintf_s( buf, pszText, vList );
		va_end( vList );

		if( !buf )
			return;
		
		mbstowcs_s( 0, txt, buf, 1023 );
		if( !txt )
			return;

		int tw = 0, th = 0;
		if( centered )
			engine->GetTextSize( font, txt, tw, th );

		engine->DrawSetTextFont( font );
		engine->DrawSetTextPos( x - (tw * 0.5), y );
		engine->DrawSetTextColor( col );
		engine->DrawPrintText( txt, wcslen(txt) );
	}

	inline void drawHPBar( int hp, int minx, int miny, int maxy, Color col ) {
		clamp<int>( hp, 0, 100 );

		Color hpCol = Color( 255 - hp * 2.55, hp * 2.55, 0, 255 );
		
		int hpBarH = hp * maxy / 100;
		drawOutlinedRect( minx - 6, miny, 3, maxy, col );
		drawFilledRect( minx - 6, miny + maxy - hpBarH, 3, hpBarH, hpCol );
	}

	inline void drawBones( CBaseEntity *ent ) {
		matrix3x4_t matrix[ 128 ];
		if( !ent->SetupBones(matrix) )
			return;

		studiohdr_t *stdHdr = engine->GetStudiomodel( ent->GetModel() );
		if( !stdHdr )
			return;

		mstudiobone_t *bone;
		Vector bonePos, parentBonePos, bonePosScr, parentBonePosScr;
		int parent;

		for( int i = 0; i < stdHdr->numbones; i++ ) {
			bone = stdHdr->getBone( i );
			if( !bone )
				continue;
			
			parent = bone->parent;

			if( parent != -1 && (bone->flags & 0x100) ) {
				MatrixPosition( matrix[i], bonePos );
				MatrixPosition( matrix[parent], parentBonePos );
				
				if( w2s(bonePos, bonePosScr) && w2s(parentBonePos, parentBonePosScr) )
					drawLine( bonePosScr.x, bonePosScr.y, parentBonePosScr.x, parentBonePosScr.y, Color(255, 255, 255, 255) );
			}
		}
	}
}; extern Drawing *draw;