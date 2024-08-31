class icliententitylist
{
public:
	virtual void padding0() = 0;
	virtual void padding1() = 0;
	virtual void padding2() = 0;
	virtual icliententity* pget_cliententity(int ient_index);
	virtual void padding3() = 0;
	virtual void padding4() = 0;
	virtual int iget_highest_index(void) = 0;
};