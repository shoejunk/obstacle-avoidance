#include "Utilities.h"
#include <assert.h>
#include <ctime>
#include <stdlib.h>

namespace NUtilities
{
	//-----------------------------------------------------------------------------
	// MurmurHash2, by Austin Appleby
	// Note - This code makes a few assumptions about how your machine behaves -
	// 1. We can read a 4-byte value from any address without crashing
	// And it has a few limitations -
	// 1. It will not work incrementally.
	// 2. It will not produce the same results on little-endian and big-endian
	//    machines.
	u32 MurmurHash2 ( void const * key, i32 len, u32 seed )
	{
		// 'm' and 'r' are mixing constants generated offline.
		// They're not really 'magic', they just happen to work well.

		const u32 m = 0x5bd1e995;
		const i32 r = 24;

		// Initialize the hash to a 'random' value

		u32 h = seed ^ len;

		// Mix 4 bytes at a time into the hash

		const u8 * data = (const u8*)key;

		while(len >= 4)
		{
			u32 k = *(u32*)data;

			k *= m; 
			k ^= k >> r; 
			k *= m; 
			
			h *= m; 
			h ^= k;

			data += 4;
			len -= 4;
		}

		// Handle the last few bytes of the input array

		switch(len)
		{
			case 3: h ^= data[2] << 16;
			case 2: h ^= data[1] << 8;
			case 1: h ^= data[0];
					h *= m;
		};

		// Do a few final mixes of the hash to ensure the last few
		// bytes are well-incorporated.

		h ^= h >> 13;
		h *= m;
		h ^= h >> 15;

		return h;
	}

	// Check whether two floats are almost equal by checking how many floats
	// it is possible to represent between the given floats.  If too many floats
	// can be represented, return false.  For example, between the floats 0.f and 
	// 0.000977f there are many floats and IsAlmostEqual would treat these numbers as 
	// unequal.  However, between 10000.f and 10000.000977f there are no floats(any number 
	// between 10000 and 10000.000977 would be interpreted as either 10000.f or 
	// 10000.000977.f), so IsAlmostEqual would treat these numbers as equal:
	bool IsAlmostEqual( f32 fNumber1, f32 fNumber2 )
	{
		assert( sizeof( i32 ) == sizeof( f32 ) );
		i32 iNumber1( *reinterpret_cast< i32* >( &fNumber1 ) );
		if( iNumber1 < 0 )
		{
			// Make into two's complement:
			iNumber1 = 0x80000000 - iNumber1;
		}
		i32 iNumber2( *reinterpret_cast< i32* >( &fNumber2 ) );
		if( iNumber2 < 0 )
		{
			// Make into two's complement:
			iNumber2 = 0x80000000 - iNumber2;
		}
		i64 iDifference( iNumber1 - iNumber2 );
		if( iDifference < 0 )
		{
			iDifference = -iDifference;
		}
		if( iDifference <= g_kuFloatTolerance )
		{
			return true;
		}
		return false;
	}

	bool IsAlmostEqual( f64 fNumber1, f64 fNumber2 )
	{
		assert( sizeof( i64 ) == sizeof( f64 ) );
		i64 iNumber1( *reinterpret_cast< i64* >( &fNumber1 ) );
		if( iNumber1 < 0 )
		{
			// Make into two's complement:
			iNumber1 = 0x80000000 - iNumber1;
		}
		i64 iNumber2( *reinterpret_cast< i64* >( &fNumber2 ) );
		if( iNumber2 < 0 )
		{
			// Make into two's complement:
			iNumber2 = 0x80000000 - iNumber2;
		}
		i64 iDifference( iNumber1 - iNumber2 );
		if( iDifference < 0 )
		{
			iDifference = -iDifference;
		}
		if( iDifference <= g_kuFloatTolerance )
		{
			return true;
		}
		return false;
	}

	void SeedRandomNumberGenerator()
	{
		srand( static_cast< u32 >( time( NULL ) ) );
	}

	u32 Random( u32 uNumPossibilities )
	{
		return( rand() % uNumPossibilities );
	}

	u16 RandomU16()
	{
		return( static_cast< u16 >( Random( 0xFF ) | 
			( Random( 0xFF ) << 8 ) ) );
	}

	u32 RandomU32()
	{
		return( Random( 0xFF ) | 
			( Random( 0xFF ) << 8 ) |
			( Random( 0xFF ) << 16 ) |
			( Random( 0xFF ) << 24 ) );
	}

	i32 Round( f32 fNumber )
	{ 
		return static_cast< i32 >( fNumber + 0.5f ); 
	}

	void StringToWideString( wch* pDestination, const i8* pSource, u16 uBufferSize )
	{
		u16 i( 0 );
		for( ; i < ( uBufferSize - 1 ) && pSource[ i ]; ++i )
		{
			pDestination[ i ] = pSource[ i ];
		}
		pDestination[ i ] = NULL;
	}
}
