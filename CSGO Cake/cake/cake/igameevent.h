class igameevent
{
public:
	virtual ~igameevent() = 0;
	virtual const char *cget_name() const = 0;

	virtual bool  IsReliable() const = 0;
	virtual bool  IsLocal() const = 0;
	virtual bool  IsEmpty(const char *keyName = NULL) = 0;

	virtual bool  bget(const char *keyName = NULL, bool defaultValue = false) = 0;
	virtual int   iget(const char *keyName = NULL, int defaultValue = 0) = 0;
	virtual unsigned long uget(const char *keyName = NULL, unsigned long defaultValue = 0) = 0;
	virtual float fget(const char *keyName = NULL, float defaultValue = 0.0f) = 0;
	virtual const char* cget(const char *keyName = NULL, const char *defaultValue = "") = 0;
	virtual const wchar_t* wget(const char *keyName, const wchar_t *defaultValue = L"") = 0;

	virtual void SetBool(const char *keyName, bool value) = 0;
	virtual void SetInt(const char *keyName, int value) = 0;
	virtual void SetUint64(const char *keyName, unsigned long value) = 0;
	virtual void SetFloat(const char *keyName, float value) = 0;
	virtual void SetString(const char *keyName, const char *value) = 0;
	virtual void SetWString(const char *keyName, const wchar_t *value) = 0;
};