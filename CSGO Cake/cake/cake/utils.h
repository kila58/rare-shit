typedef void* (*interface_t)(const char* cname, int iid);
typedef DWORD dword;

namespace utils
{
	template<typename vfunc> vfunc virtual_call(PVOID pvtable, DWORD dindex)
	{
		PDWORD* pvtable_pointer = (PDWORD*)pvtable;
		PDWORD pvtable_base = *pvtable_pointer;
		return (vfunc)pvtable_base[dindex];
	}

	interface_t icap_factory(char* cfactory_name)
	{
		return (interface_t)(GetProcAddress(GetModuleHandleA(cfactory_name), "CreateInterface"));
	}

	void* pcap_interface(interface_t iselected, const char* cinterface_name)
	{
		std::string sbrute_name = "";
		std::string sinterfacename = cinterface_name;
		void* iinterface = nullptr;

		for (int iinterface_num = 0; iinterface_num < 99; iinterface_num++)
		{
			std::string sinterface_num = std::to_string(iinterface_num);

			if (sinterface_num.length() == 1)
			{
				sbrute_name = sinterfacename + "00" + sinterface_num;
			}
			else if (sinterface_num.length() == 2)
			{
				sbrute_name = sinterfacename + "0" + sinterface_num;
			}

			iinterface = reinterpret_cast<unsigned long*>(iselected(sbrute_name.c_str(), 0));

			if (iinterface != nullptr)
			{
				return iinterface;
			}
		}
		return nullptr;
	}
	void* pcap_interfacea(interface_t iselected_interface, char* cinterface_name)
	{
		void* iinterface = reinterpret_cast<unsigned long*>(iselected_interface(cinterface_name, NULL));
		return iinterface;
	}

	bool bcompare(const BYTE* pdata, const BYTE* bmask, const char* cmask)
	{
		for (; *cmask; cmask++, pdata++, bmask++)
			if (*cmask == 'x' && *cmask != *bmask)
				return false;
		return *cmask == 0;
	}

	dword dwfind_pattern(dword dwaddy, dword dwlen, BYTE* bmask, char* cmask)
	{
		for (dword i = 0; i < dwlen; i++)
		{
			if (bcompare((BYTE*)(dwaddy + i), bmask, cmask))
			{
				return (dword)(dwaddy + i);
			}
		}
		return 0;
	}
}