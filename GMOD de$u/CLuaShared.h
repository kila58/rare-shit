//Babys first class dump

class cLuaShared {
public:
	virtual void pad00() = 0; // 00 ( init )
	virtual void pad01() = 0; // and so on... to lazy to count ( shutdown )
	virtual void pad02() = 0; // (dumpstatus)
	virtual void *cLuaShared::CreateLuaInterface(unsigned char, bool); // Hook this.
	virtual void pad04() = 0; //this is close lua interface i think
	virtual void pad05() = 0; // some bullshit padding
	virtual void *cLuaShared::GetLuaInterface(unsigned char); // should be getluainterface
	virtual void pad07() = 0;
	virtual void pad08() = 0;
	virtual void pad09() = 0;
	virtual void pad10() = 0;
	virtual void pad11() = 0;
	virtual void pad12() = 0;
	virtual void pad13() = 0;
};