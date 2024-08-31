class iappsystem
{
public:
	virtual void filler0() = 0; // 0
	virtual void filler1() = 0; // 1

	// Here's where systems can access other interfaces implemented by this object
	// Returns NULL if it doesn't implement the requested interface
	virtual void filler3() = 0;

	// Init, shutdown
	virtual void filler2() = 0;
	virtual void filler4() = 0;

	// Returns all dependent libraries
	virtual void filler5() = 0;

	// Returns the tier
	virtual void filler6() = 0;

	// Reconnect to a particular interface
	virtual void filler7() = 0;

	// New virtual function added in the 26 MAY 2015 update
	virtual void filler8() = 0;
};