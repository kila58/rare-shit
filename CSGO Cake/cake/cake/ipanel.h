typedef unsigned int VPANEL;
class ipanel : public ibaseinterface
{
public:
	virtual void filler1() = 0;

	// methods
	virtual void SetPos(VPANEL vguiPanel, int x, int y) = 0;
	virtual void GetPos(VPANEL vguiPanel, int &x, int &y) = 0;
	virtual void SetSize(VPANEL vguiPanel, int wide, int tall) = 0;
	virtual void GetSize(VPANEL vguiPanel, int &wide, int &tall) = 0;
	virtual void SetMinimumSize(VPANEL vguiPanel, int wide, int tall) = 0;
	virtual void GetMinimumSize(VPANEL vguiPanel, int &wide, int &tall) = 0;
	virtual void SetZPos(VPANEL vguiPanel, int z) = 0;
	virtual int  GetZPos(VPANEL vguiPanel) = 0;

	virtual void GetAbsPos(VPANEL vguiPanel, int &x, int &y) = 0;
	virtual void GetClipRect(VPANEL vguiPanel, int &x0, int &y0, int &x1, int &y1) = 0;
	virtual void SetInset(VPANEL vguiPanel, int left, int top, int right, int bottom) = 0;
	virtual void GetInset(VPANEL vguiPanel, int &left, int &top, int &right, int &bottom) = 0;

	virtual void SetVisible(VPANEL vguiPanel, bool state) = 0;
	virtual bool IsVisible(VPANEL vguiPanel) = 0;
	virtual void SetParent(VPANEL vguiPanel, VPANEL newParent) = 0;
	virtual int GetChildCount(VPANEL vguiPanel) = 0;
	virtual VPANEL GetChild(VPANEL vguiPanel, int index) = 0;
	virtual void filler0() = 0;
	virtual VPANEL GetParent(VPANEL vguiPanel) = 0;
	virtual void MoveToFront(VPANEL vguiPanel) = 0;
	virtual void MoveToBack(VPANEL vguiPanel) = 0;
	virtual bool HasParent(VPANEL vguiPanel, VPANEL potentialParent) = 0;
	virtual bool IsPopup(VPANEL vguiPanel) = 0;
	virtual void SetPopup(VPANEL vguiPanel, bool state) = 0;
	virtual bool IsFullyVisible(VPANEL vguiPanel) = 0;

	// gets the scheme this panel uses
	virtual void filler2() = 0;
	// gets whether or not this panel should scale with screen resolution
	virtual bool IsProportional(VPANEL vguiPanel) = 0;
	// returns true if auto-deletion flag is set
	virtual bool IsAutoDeleteSet(VPANEL vguiPanel) = 0;
	// deletes the Panel * associated with the vpanel
	virtual void DeletePanel(VPANEL vguiPanel) = 0;

	// input interest
	virtual void SetKeyBoardInputEnabled(VPANEL vguiPanel, bool state) = 0;
	virtual void SetMouseInputEnabled(VPANEL vguiPanel, bool state) = 0;
	virtual bool IsKeyBoardInputEnabled(VPANEL vguiPanel) = 0;
	virtual bool IsMouseInputEnabled(VPANEL vguiPanel) = 0;

	// calculates the panels current position within the hierarchy
	virtual void Solve(VPANEL vguiPanel) = 0;

	// gets names of the object (for debugging purposes)
	virtual const char* get_name(VPANEL vguiPanel) = 0;
};