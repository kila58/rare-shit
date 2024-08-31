class ienginetrace
{
public:
	// Returns the contents mask + entity at a particular world-space position
	virtual void filler0() = 0;

	// Returns the contents mask of the world only @ the world-space position (static props are ignored)
	virtual void filler1() = 0;

	// Get the point contents, but only test the specific entity. This works
	// on static props and brush models.
	//
	// If the entity isn't a static prop or a brush model, it returns CONTENTS_EMPTY and sets
	// bFailed to true if bFailed is non-null.
	virtual void filler2() = 0;

	// Traces a ray against a particular entity
	virtual void filler3() = 0;

	// Traces a ray against a particular entity

	// A version that simply accepts a ray (can work as a traceline or tracehull)
	virtual void filler4();
	virtual void	TraceRay(const Ray_t &ray, unsigned int fMask, tracefilter_interface *pTraceFilter, trace_t *pTrace) = 0;
};