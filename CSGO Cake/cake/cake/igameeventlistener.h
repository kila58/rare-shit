class igameeventlistener
{
public:
	virtual ~igameeventlistener(void) {};
	virtual void fire_gameevent(igameevent* e) = 0;
	virtual int iget_debugid(void) = 0;
	int badd_listener(igameeventlistener* ilistener, const char* cname, bool bserver_side)
	{
		typedef int(__thiscall* t_addlistener)(PVOID, igameeventlistener*, const char*, bool);
		return utils::virtual_call<t_addlistener>(this, 3)(this, ilistener, cname, bserver_side);
	}
};