#ifndef BASEVECTOR_H
#define BASEVECTOR_H

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "../Common/Types.h"
#include "../Common/Utilities.h"

template< typename DataType >
class TBaseVector
{
public:
							TBaseVector();
	virtual					~TBaseVector();
	virtual DataType		GetElement( u8 uElement ) const = 0;
	virtual void			SetElement( u8 uElement, DataType oElement ) = 0;
	DataType				X() const;
	DataType				Y() const;
	DataType				Z() const;
	void					X( DataType oX );
	void					Y( DataType oY );
	void					Z( DataType oZ );
	void					XY( DataType oX, DataType oY );
	void					XZ( DataType oX, DataType oZ );
	void					YZ( DataType oY, DataType oZ );
	void					XYZ( DataType oX, DataType oY, DataType oZ );
	virtual u8				GetNumDimensions() const = 0;
	DataType				GetLength() const;
	DataType				GetLengthSquared() const;
	bool					IsNormal() const;
	DataType				Dot( const TBaseVector< DataType >& krRhs ) const;
	DataType				GetAngleAssumeNormal( const TBaseVector< DataType >& krRhs ) 
								const;
	virtual const DataType*	GetArray() const = 0;
};

template< typename DataType >
TBaseVector< DataType >::TBaseVector()
{
}

template< typename DataType >
TBaseVector< DataType >::~TBaseVector()
{
}

template< typename DataType >
DataType TBaseVector< DataType >::X() const
{
	assert( GetNumDimensions() > 0 );
	return GetElement( 0 );
}

template< typename DataType >
DataType TBaseVector< DataType >::Y() const
{
	assert( GetNumDimensions() > 1 );
	return GetElement( 1 );
}

template< typename DataType >
DataType TBaseVector< DataType >::Z() const
{
	assert( GetNumDimensions() > 2 );
	return GetElement( 2 );
}

template< typename DataType >
void TBaseVector< DataType >::X( DataType oX )
{
	assert( GetNumDimensions() > 0 );
	SetElement( 0, oX );
}

template< typename DataType >
void TBaseVector< DataType >::Y( DataType oY )
{
	assert( GetNumDimensions() > 1 );
	SetElement( 1, oY );
}

template< typename DataType >
void TBaseVector< DataType >::Z( DataType oZ )
{
	assert( GetNumDimensions() > 2 );
	SetElement( 2, oZ );
}

template< typename DataType >
void TBaseVector< DataType >::XY( DataType oX, DataType oY )
{
	assert( GetNumDimensions() > 1 );
	SetElement( 0, oX );
	SetElement( 1, oY );
}

template< typename DataType >
void TBaseVector< DataType >::XZ( DataType oX, DataType oZ )
{
	assert( GetNumDimensions() > 2 );
	SetElement( 0, oX );
	SetElement( 2, oZ );
}

template< typename DataType >
void TBaseVector< DataType >::YZ( DataType oY, DataType oZ )
{
	assert( GetNumDimensions() > 2 );
	SetElement( 1, oY );
	SetElement( 2, oZ );
}

template< typename DataType >
void TBaseVector< DataType >::XYZ( DataType oX, DataType oY, DataType oZ )
{
	assert( GetNumDimensions() > 2 );
	SetElement( 0, oX );
	SetElement( 1, oY );
	SetElement( 2, oZ );
}

template< typename DataType >
DataType TBaseVector< DataType >::GetLength() const
{
	DataType oLength( static_cast< DataType >( 0 ) );
	for( u8 i( 0 ); i < GetNumDimensions(); ++i )
	{
		oLength += ( GetElement( i ) * GetElement( i ) );
	}
	return static_cast< DataType >( sqrt( oLength ) );
}

template< typename DataType >
DataType TBaseVector< DataType >::GetLengthSquared() const
{
	DataType oLengthSquared( static_cast< DataType >( 0 ) );
	for( u8 i( 0 ); i < GetNumDimensions(); ++i )
	{
		oLengthSquared += ( GetElement( i ) * GetElement( i ) );
	}
	return oLengthSquared;
}

template< typename DataType >
bool TBaseVector< DataType >::IsNormal() const
{
	if( NUtilities::IsAlmostEqual( GetLengthSquared(), static_cast< DataType >( 1 ) ) )
	{
		return true;
	}
	return false;
}

template< typename DataType >
DataType TBaseVector< DataType >::Dot( const TBaseVector< DataType >& krRhs ) const
{
	assert( GetNumDimensions() == krRhs.GetNumDimensions() );
	DataType oDot( static_cast< DataType >( 0 ) );
	for( u8 i( 0 ); i < GetNumDimensions(); ++i )
	{
		oDot += ( GetElement( i ) * krRhs.GetElement( i ) );
	}
	return oDot;
}

template< typename DataType >
DataType TBaseVector< DataType >::GetAngleAssumeNormal( 
	const TBaseVector< DataType >& krRhs ) const
{
	assert( IsNormal() && krRhs.IsNormal() );
	DataType oDot( Dot( krRhs ) );
	if( oDot > static_cast< DataType >( 1 ) )
	{
		oDot = static_cast< DataType >( 1 );
	}
	if( oDot < static_cast< DataType >( -1 ) )
	{
		oDot = static_cast< DataType >( -1 );
	}
	return acos( oDot );
}

typedef TBaseVector< f32 >	CF32BaseVector;
typedef TBaseVector< f64 >	CF64BaseVector;

#endif
