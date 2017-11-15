#ifdef ESSENTIAL_PLATFORM_WIN32

#include "Common/Utilities.h"
#include "windows.h"

namespace NUtilities
{
	void DebugPrintF( const char* pString, ... )
	{
		char pBuffer[ 2048 ];
		va_list pList;
		va_start( pList, pString );
		vsprintf_s( pBuffer, pString, pList );
		va_end( pList );
		OutputDebugStringA( pBuffer );
	}

	void* AlignedMemoryAllocation( u32 uSize, u32 uAlignment )
	{
		return _aligned_malloc( uSize, uAlignment );
	}

	void AlignedFree( void* pMemory )
	{
		_aligned_free( pMemory );
	}

	void WideStringToString( i8* pDestination, wch* pSource )
	{
		size_t oConvertedChars = 0;
		wcstombs_s( &oConvertedChars, pDestination, wcslen( pSource ) + 1, pSource, 
			_TRUNCATE );
	}

	u16 CryptHash( i8* pData, u16 uInputSize, u16 uBufferSize )
	{
		HCRYPTPROV hCryptProv;
		HCRYPTHASH hHash;

		// Get a handle to a cryptography provider context:
		if( !CryptAcquireContext(
		   &hCryptProv,				// handle to the CSP
		   L"EssentialEngineCrypt",	// container name 
		   NULL,					// use the default provider
		   PROV_RSA_FULL,			// provider type
		   0 ) )					// flag values
		{ 
			// An error occurred in acquiring the context. This could mean
			// that the key container requested does not exist. In this case,
			// the function can be called again to attempt to create a new key 
			// container. Error codes are defined in Winerror.h:
			if( GetLastError() == NTE_BAD_KEYSET )
			{
				if( !CryptAcquireContext(
					&hCryptProv, 
					L"EssentialEngineCrypt", 
					NULL, 
					PROV_RSA_FULL, 
					CRYPT_NEWKEYSET ) ) 
				{
					DEBUG_MESSAGE( "Could not create a new key container.\n" );
					assert( false );
				}
			}
			else
			{
				DEBUG_MESSAGE( "A cryptographic service handle could not be "
					"acquired.\n" );
				assert( false );
			}
		}

		// Acquire a hash object handle:
		if( !CryptCreateHash(
			hCryptProv, 
			CALG_MD5, 
			0, 
			0, 
			&hHash ) ) 
		{
			DEBUG_MESSAGE( "Error during CryptBeginHash!\n" );
			assert( false );
		}

		// Hash the Data:
		if( !CryptHashData(
			hHash, 
			reinterpret_cast< BYTE* >( pData ), 
			uInputSize + 1, 
			0 ) ) 
		{
			DEBUG_MESSAGE( "Error during CryptHashData.\n" );
			assert( false );
		}

		DWORD uHashLen;
		DWORD uHashLenSize = sizeof( DWORD );

		// Get the hash data:
		if( CryptGetHashParam(
			hHash,
			HP_HASHSIZE,
			(BYTE *)&uHashLen,
			&uHashLenSize,
			0 ) )
		{
			// It worked. Make sure the buffer is big enough:
			if( uHashLenSize > uBufferSize )
			{
				if( hHash )
				{
					CryptDestroyHash( hHash );
				}
				if( hCryptProv )
				{
					CryptReleaseContext( hCryptProv, 0 );
				}
				return 0;
			}
		}
		else
		{
			DEBUG_MESSAGE( "CryptGetHashParam failed to get size." );
			assert( false );
		}
		if( !CryptGetHashParam(
			hHash,
			HP_HASHVAL,
			reinterpret_cast< BYTE* >( pData ),
			&uHashLen,
			0 ) )
		{
			DEBUG_MESSAGE("Error reading the hash value.");
			assert( false );
		}

		// Clean up:
		if( hHash )
		{
			CryptDestroyHash( hHash );
		}
		if( hCryptProv ) 
		{
			CryptReleaseContext( hCryptProv, 0 );
		}

		return static_cast< u16 >( uHashLen );
	}
}

#endif // ESSENTIAL_PLATFORM_WIN32
