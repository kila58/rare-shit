class usercmd
{
public:
	virtual ~usercmd();
	int		icommand_number;
	int		itick_count;
	vector vviewangles;
	vector	vaimdirection;
	float	fforwardmove;
	float	fsidemove;
	float	fupmove;
	int		ibuttons;
	BYTE    bimpulse;
	int		iweaponselect;
	int		iweaponsubtype;
	int		irandom_seed;
	short	imousedx;
	short	imousedy;
	bool	bhasbeenpredicted;
	vector vheadangles;
	vector	vheadoffset;

	void get_checksum(void) const
	{
		return;
	}
};