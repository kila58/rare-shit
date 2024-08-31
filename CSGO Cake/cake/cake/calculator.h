namespace math
{
	color crandom_color()
	{
		return color(rand() % 255, rand() % 255, rand() % 255, 255);
	}
	bool screen_transform(vector& point, vector& screen)
	{
		matrix worldToScreen = g::ivengine->get_worldtoscreen_matrix();
		screen.x = worldToScreen[0][0] * point.x + worldToScreen[0][1] * point.y + worldToScreen[0][2] * point.z + worldToScreen[0][3];
		screen.y = worldToScreen[1][0] * point.x + worldToScreen[1][1] * point.y + worldToScreen[1][2] * point.z + worldToScreen[1][3];

		float w;
		w = worldToScreen[3][0] * point.x + worldToScreen[3][1] * point.y + worldToScreen[3][2] * point.z + worldToScreen[3][3];
		screen.z = 0.0f;

		bool behind = FALSE;
		if (w < 0.001f)
		{
			behind = TRUE;
			screen.x *= 100000;
			screen.y *= 100000;
		}
		else
		{
			float invw = 1.0f / w;
			screen.x *= invw;
			screen.y *= invw;
		}

		return behind;
	}
	vector to_screen(vector vorigin)
	{
		vector vfinal = vector(0.f, 0.f, 0.f);
		bool breturn = false;
		float fScreenX, fScreenY;

		if (!screen_transform(vorigin, vfinal))
		{
			int iwidth = 1920;
			int iheight = 1080;
			g::ivengine->get_scrnsize(iwidth, iheight);

			fScreenX = iwidth / 2;
			fScreenY = iheight / 2;

			fScreenX += 0.5f * vfinal.x * iwidth + 0.5f;
			fScreenY -= 0.5f * vfinal.y * iheight + 0.5f;

			vfinal.x = fScreenX;
			vfinal.y = fScreenY;
		}

		return vfinal;
	}
}