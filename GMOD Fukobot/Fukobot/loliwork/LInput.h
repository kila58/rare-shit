class LInput
{
public:

    // Mouse control
    int GetMouseX() { return *MouseX; };
    int GetMouseY() { return *MouseY; };
	bool IsMouseDown() { return GetAsyncKeyState(VK_LBUTTON) != 0; };

    void Think();

    int *MouseX      = new int;
    int *MouseY      = new int;
};

void LInput::Think()
{
	//if (Input)
		//Input->GetFullscreenMousePos(this->MouseX, this->MouseY);

	POINT mPoint;
	GetCursorPos(&mPoint);
	ClientToScreen(GetActiveWindow(), &mPoint);
	
	*MouseX = mPoint.x;
	*MouseY = mPoint.y;

}
