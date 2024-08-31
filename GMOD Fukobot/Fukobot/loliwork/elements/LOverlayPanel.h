class LOverlayPanel : public LBaseObject
{
public:
	void Paint() {};
	void Think() { this->X = 0; this->Y = 0; Engine->GetScreenSize(this->W, this->H); };
	void Click() {};
};

