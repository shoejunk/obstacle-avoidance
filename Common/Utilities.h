#ifndef UTILITIES_H
#define UTILITIES_H

#include <assert.h>
#include "stdarg.h"
#ifdef ESSENTIAL_PLATFORM_WIN32
#include "windows.h"
#endif // ESSENTIAL_PLATFORM_WIN32
#include "Types.h"
#include "Macros.h"

// This is a comment that contains the maximum number of characters allowed on a single line ( 100 )

namespace NUtilities
{
	template< typename Type >
	inline Type Min( Type oValue1, Type oValue2 )
	{
		return( oValue1 < oValue2 ? oValue1 : oValue2 );
	}

	template< typename Type >
	inline Type Max( Type oValue1, Type oValue2 )
	{
		return( oValue1 > oValue2 ? oValue1 : oValue2 );
	}

	template< typename Type >
	inline Type AbsoluteValue( Type oValue )
	{
		return( oValue < static_cast< Type >( 0 ) ? -oValue : oValue );
	}

	void	DebugPrintF( const char* pString, ... );

	template< typename Type >
	inline bool IsOdd( Type oValue1 )
	{
		return( oValue1 & 1 );
	}

	template< typename Type >
	inline Type DegreesToRadians( Type oDegrees )
	{
		return( oDegrees * RADIANS_PER_DEGREE );
	}

	template< typename Type >
	inline Type RadiansToDegrees( Type oRadians )
	{
		return( oRadians * DEGREES_PER_RADIAN );
	}

	template< typename DataType >
	DataType RotateWrap( DataType oRotation )
	{
		while( oRotation > static_cast< DataType >( 180 ) )
		{
			oRotation -= static_cast< DataType>( 360 );
		}
		while( oRotation < static_cast< DataType >( -180 ) )
		{
			oRotation += static_cast< DataType >( 360 );
		}
		return oRotation;
	}

	template< typename DataType >
	DataType RotateWrapRadians( DataType oRotation )
	{
		while( oRotation > static_cast< DataType >( PI ) )
		{
			oRotation -= static_cast< DataType>( PI * 2.f );
		}
		while( oRotation < static_cast< DataType >( -PI ) )
		{
			oRotation += static_cast< DataType >( PI * 2.f );
		}
		return oRotation;
	}

	// Scales a coordinate from the range [0,1] to any arbitrary range.
	template< typename DataType >
	DataType ConvertCoordinateFromUnit( DataType oUnitCoordinate, DataType oToMin, DataType oToMax )
	{
		assert( oToMin < oToMax );
		assert( oUnitCoordinate >= static_cast< DataType >( 0 ) );
		assert( oUnitCoordinate <= static_cast< DataType >( 1 ) );
		return ( oUnitCoordinate * ( oToMax - oToMin ) ) + oToMin;
	}
		
	// Scale a single number from one coordinate system to another. For example, to convert a number
	// from a [0,1] coordinate systme to a [-1,1] coordinate system, call:
	// f32 fNumberBetweenNeg1And1( ConvertCoordinate( fNumberBetween0And1, 0.f, 1.f, -1.f, 1.f ) );
	template< typename DataType >
	DataType ConvertCoordinate( DataType oCoordinate, DataType oFromMin, DataType oFromMax,
		DataType oToMin, DataType oToMax )
	{
		assert( oFromMin < oFromMax );
		assert( oToMin < oToMax );
		assert( oCoordinate >= oFromMin );
		assert( oCoordinate <= oFromMax );
		DataType oUnitCoordinate( ( oCoordinate - oFromMin ) / ( oFromMax - oFromMin ) );
		return ConvertFromUnitCoordinate( oUnitCoordinate, oToMin, oToMax );
	}

	template< typename ReturnType, typename Parameter1Type, typename Parameter2Type >
	ReturnType Concatenate( Parameter1Type oParameter1, Parameter2Type oParameter2 )
	{
		assert( sizeof( ReturnType ) >= 
			( sizeof( Parameter1Type ) + sizeof( Parameter2Type ) ) );
		return( ( oParameter1 << ( sizeof( Parameter2Type ) << 3 ) ) | oParameter2 );
	}

	template< typename SourceType, typename Result1Type, typename Result2Type >
	void Split( SourceType oSource, Result1Type& rResult1, Result2Type& rResult2 )
	{
		assert( sizeof( SourceType ) == 
			( sizeof( Result1Type ) + sizeof( Result2Type ) ) );
		rResult1 = static_cast< Result1Type >( oSource >> ( 
			sizeof( Result2Type ) << 3 ) );
		rResult2 = static_cast< Result2Type >( 
			( oSource << ( sizeof( Result1Type ) << 3 ) ) >> ( 
			sizeof( Result1Type ) << 3 ) );
	}

	u32			MurmurHash2 ( const void * key, i32 len, u32 seed );
	bool		IsAlmostEqual( f32 fNumber1, f32 fNumber2 ); 
	bool		IsAlmostEqual( f64 fNumber1, f64 fNumber2 ); 
	void		SeedRandomNumberGenerator();
	u32			Random( u32 uNumPossibilities );
	u16			RandomU16();
	u32			RandomU32();
	i32			Round( f32 fNumber );
	void		WideStringToString( i8* pDestination, wch* pSource );
	void		StringToWideString( wch* pDestination, const i8* pSource, 
					u16 uBufferSize );
	void*		AlignedMemoryAllocation( ptr uSize, ptr uAlignment );
	void		AlignedFree( void* pMemory );
	u16			CryptHash( i8* pData, u16 uInputSize, u16 uBufferSize );
	i8* 		StringCopy( i8* aDestination, const i8* kaSource );
	
	const u32	g_kuFloatTolerance = 5;
};


#endif
