class icliententity
{
public:
	inline int iget_hp()
	{
		return *(int*)((dword)this + (dword)0xFC);
	}
	inline vector vget_pos()
	{
		return *(vector*)((dword)this + (dword)0x134);
	}
	inline vector vget_eyepos()
	{
		return this->vget_pos() + *(vector*)((DWORD)this + (DWORD)0x104);
	}
	inline int iget_team()
	{
		return *(int*)((dword)this + (dword)0xF0);
	}
	inline qangle qget_ang()
	{
		return *(qangle*)((dword)this + (dword)0x000023b4);
	}
	inline int iget_movement_state()
	{
		return *(int*)((DWORD)this + (DWORD)0x00000100);
	}
	inline vector vget_punch()
	{
		return *reinterpret_cast<vector*>((DWORD)this + (DWORD)0x13e8);
	}
};