#include "NetVars.h"

using namespace ValveSDK;

FILE* pHurensohn = nullptr;

RecvTable* CNetVars::GetRecvTable( std::string strTableName )
{
	if( m_vpTables.empty( ) )
		return nullptr;

	for each( RecvTable* pRecvTable in m_vpTables )
	{
		if( !pRecvTable )
			continue;

		if( !strTableName.compare( pRecvTable->GetName( ) ) )
			return pRecvTable;
	}

	return nullptr;
}

int CNetVars::GetRecvProp( std::string strTableName, std::string strPropName, RecvProp** ppRecvProp )
{
	RecvTable* pRecvTable = this->GetRecvTable( strTableName );
	if( !pRecvTable )
		return 0;

	return this->GetRecvProp( pRecvTable, strPropName, ppRecvProp );
}

int CNetVars::GetRecvProp( RecvTable* pRecvTable, std::string strPropName, RecvProp** ppRecvProp )
{
	if( strPropName.empty( ) )
		return 0;

	int iExtraOffset = 0;
	for( int i = 0; i < pRecvTable->GetNumProps( ); ++i )
	{
		RecvProp* pRecvProp = pRecvTable->GetProp( i );
		RecvTable* pRecvChlidTable = pRecvProp->GetDataTable( );

		if( pRecvChlidTable && ( pRecvChlidTable->GetNumProps( ) > 0 ) )
		{
			int iTempOffset = this->GetRecvProp( pRecvChlidTable, strPropName );
			if( iTempOffset )
				iExtraOffset += pRecvProp->GetOffset( ) + iTempOffset;
		}

		if( strPropName.compare( pRecvProp->GetName( ) ) )
			continue;

		if( ppRecvProp )
			*ppRecvProp = pRecvProp;

		return pRecvProp->GetOffset( ) + iExtraOffset;
	}

	return iExtraOffset;
}

void CNetVars::DumpTable( RecvTable* pRecvTable )
{
	for( int i = 0; i < pRecvTable->GetNumProps( ); i++ )
	{
		RecvProp* pRecvProp = pRecvTable->GetProp( i );
		if( !pRecvProp )
			continue;

		if( !std::string( "baseclass" ).compare( pRecvProp->GetName( ) ) )
			continue;

		if( isdigit( pRecvProp->GetName( )[ 0 ] ) )
			continue;

		printf( "--> %s [ 0x%X ]\n", pRecvProp->GetName( ), pRecvProp->GetOffset( ) );
		fprintf( pHurensohn, "--> %s [ 0x%X ]\n", pRecvProp->GetName( ), pRecvProp->GetOffset( ) );
		RecvTable* pRecvDataTable = pRecvProp->GetDataTable( );
		if( pRecvDataTable )
			this->DumpTable( pRecvDataTable );
	}
}

CNetVars::CNetVars( ClientClass* pFirstClass )
{
	this->SetFirstClientClass( pFirstClass );
}

bool CNetVars::Setup( void )
{
	m_vpTables.clear( );

	if( !m_pFirstClass )
		return false;

	ClientClass* pClass = m_pFirstClass;

	while( pClass )
	{
		RecvTable* pRecvTable = pClass->GetTable( );
		m_vpTables.push_back( pRecvTable );

		pClass = pClass->GetNextClass( );
	}

	return true;
}

bool CNetVars::HookNetVar( std::string strTableName, std::string strNetVar, RecvVarProxyFn fn )
{
	RecvProp* pRecvProp = 0;
	this->GetRecvProp( strTableName, strNetVar, &pRecvProp );

	if( !pRecvProp )
		return false;

	pRecvProp->SetProxyFn( fn );

	return true;
}

DWORD CNetVars::GetOffset(const char* strTableName, const char* strNetVar)
{
	ValveSDK::ClientClass *pClass = g_pClient->GetAllClasses();

	for (; pClass; pClass = pClass->GetNextClass())
	{
		RecvTable *pTable = pClass->GetTable();

		if (pTable->GetNumProps() <= 1) continue;

		for (int i = 0; i < pTable->GetNumProps(); i++)
		{
			RecvProp *pProp = pTable->GetProp(i);

			if (!pProp) continue;

			if (!strcmp(pTable->GetName(), strTableName) && !strcmp(pProp->GetName(), strNetVar))
				return pProp->GetOffset();

			if (pProp->GetDataTable())
			{
				RecvTable *pTable = pProp->GetDataTable();
				for (int i = 0; i < pTable->GetNumProps(); i++)
				{
					RecvProp *pProp = pTable->GetProp(i);

					if (!pProp) continue;

					if (!strcmp(pTable->GetName(), strTableName) && !strcmp(pProp->GetName(), strNetVar))
						return pProp->GetOffset();
				}
			}
		}
	}
	return 0;
}

void CNetVars::DumpNetVars( void )
{
	fopen_s( &pHurensohn, "D:\\netvarsya.txt", "w" );
	for( ClientClass* pClass = m_pFirstClass; pClass != NULL; pClass = pClass->GetNextClass( ) )
	{
		RecvTable* pRecvTable = pClass->GetTable( );
		if( pRecvTable )
		{
			printf( "---------[ %s ]---------\n", pRecvTable->GetName( ) );
			fprintf( pHurensohn, "---------[ %s ]---------\n", pRecvTable->GetName( ) );
			DumpTable( pRecvTable );
		}
	}
	fclose( pHurensohn );
}

void CNetVars::SetFirstClientClass( ClientClass* pFirstClass )
{
	m_pFirstClass = pFirstClass;
}

ValveSDK::CNetVars* g_pNetVars = nullptr;