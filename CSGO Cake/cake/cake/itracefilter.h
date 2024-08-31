enum TraceType_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,				// NOTE: This does *not* test static props!!!
	TRACE_ENTITIES_ONLY,			// NOTE: This version will *not* test static props
	TRACE_EVERYTHING_FILTER_PROPS,	// NOTE: This version will pass the IHandleEntity for props through the filter, unlike all other filters
};

class tracefilter_interface
{
public:
	virtual bool shouldhitentity(void* pentity, int imask) = 0;
	virtual TraceType_t get_tracetype() = 0;
};

class tracefilter : public tracefilter_interface
{
public:
	bool shouldhitentity(void* pentity, int imask)
	{
		if (pignore == pentity)
			return false;
		return true;
	}

	TraceType_t get_tracetype()
	{
		return TRACE_EVERYTHING;
	}

	void* pignore;
};