#ifndef __C_ESP_H_
#define __C_ESP_H_

#include "sdk.h"
#include "cDrawing.h"

class CEsp
{
public:
	void DrawWatermark(void);
	void DrawPlayerESP(int iIndex);
	void DrawCrosshair(void);
	void DrawEntityESP(int iIndex);
private:
};

extern CEsp gEsp;

#endif