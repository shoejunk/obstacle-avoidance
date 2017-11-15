#ifndef VECTOR2_H
#define VECTOR2_H

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "BaseVector.h"
#include "Vector.h"
#include "../Common/Types.h"
#include "../Common/Utilities.h"

template< typename DataType >
class TVector2 : public TBaseVector< DataType >
{
public:
							TVector2();
							TVector2( const DataType* aArray );
							TVector2( const TVector2< DataType >& krVector );
							TVector2( DataType oX, DataType oY );
	virtual					~TVector2();
	TVector2< DataType >&	operator=( const TVector2< DataType >& krRhs );
	TVector2< DataType >	operator+( const TVector2< DataType >& krRhs ) const;
	TVector2< DataType >	operator-( const TVector2< DataType >& krRhs ) const;
	TVector2< DataType >	operator-() const;
	TVector2< DataType >	operator/( DataType krRhs ) const;
	TVector2< DataType >	operator*( DataType fRhs ) const;
	TVector2< DataType >&	operator*=( DataType oRhs ); 
	TVector2< DataType >&	operator/=( DataType oRhs ); 
	TVector2< DataType >&	operator+=( const TVector2< DataType >& krRhs ); 
	TVector2< DataType >&	operator-=( const TVector2< DataType >& krRhs ); 
	bool					operator==( const TVector2< DataType >& krRhs ) const; 
	bool					operator!=( const TVector2< DataType >& krRhs ) const; 
	const DataType&			operator[]( u16 uIndex ) const;
	virtual DataType		GetElement( u8 uElement ) const;
	virtual void			SetElement( u8 uElement, DataType oElement );
	TVector2< DataType >	Cross( const TVector2< DataType >& krRhs ) const;
	virtual u8				GetNumDimensions() const;
	void					Normalize();
	void					CopyPartialVector( const TBaseVector< DataType >& krSource, 
								u8 uDestinationStart, u8 uSourceStart, u8 uNumElements );
	TVector2< DataType >	GetNormal() const;
	DataType				GetAngle( const TVector2< DataType >& krRhs ) const;
	DataType				GetDistanceSquared( const TVector2< DataType >& krRhs ) const;
	DataType				GetDistance( const TVector2< DataType >& krRhs ) const;
	virtual const DataType*	GetArray() const;
	TVector2< DataType >	GetResizedVector( u8 uDimensions, 
								DataType oFill = static_cast< DataType >( 0 ) ) const;
	DataType				GetAngle() const;

private:
	DataType	m_akVector[ 2 ];
};

template< typename DataType >
TVector2< DataType >::TVector2()
{
	for( u8 i( 0 ); i < 2; ++i )
	{
		m_akVector[ i ] = static_cast< DataType >( 0 );
	}
}

template< typename DataType >
TVector2< DataType >::TVector2( const DataType* kaArray )
{
	assert( kaArray != NULL );
	for( u8 i( 0 ); i < 2; ++i )
	{
		m_akVector[ i ] = kaArray[ i ];
	}
}

template< typename DataType >
TVector2< DataType >::TVector2( const TVector2< DataType >& krVector )
{
	memcpy( m_akVector, krVector.m_akVector, 2 * sizeof( DataType ) );
}

template< typename DataType >
TVector2< DataType >::TVector2( DataType oX, DataType oY )
{
	m_akVector[ 0 ] = oX;
	m_akVector[ 1 ] = oY;
}

template< typename DataType >
TVector2< DataType >::~TVector2()
{
}

template< typename DataType >
TVector2< DataType >& TVector2< DataType >::operator=( const TVector2< DataType >& krRhs )
{
	memcpy( m_akVector, krRhs.m_akVector, 2 * sizeof( DataType ) );
	return *this;
}

template< typename DataType >
TVector2< DataType > TVector2< DataType >::operator+( const TVector2< DataType >& krRhs ) 
	const
{
	TVector2< DataType > oResult;
	for( u8 i( 0 ); i < 2; ++i )
	{
		oResult.m_akVector[ i ] = m_akVector[ i ] + krRhs.m_akVector[ i ];
	}
	return oResult;
}

template< typename DataType >
TVector2< DataType > TVector2< DataType >::operator-( const TVector2< DataType >& krRhs ) 
	const
{
	TVector2< DataType > oResult;
	for( u8 i( 0 ); i < 2; ++i )
	{
		oResult.m_akVector[ i ] = m_akVector[ i ] - krRhs.m_akVector[ i ];
	}
	return oResult;
}

template< typename DataType >
TVector2< DataType > TVector2< DataType >::operator-() const
{
	TVector2< DataType > oResult;
	for( u8 i( 0 ); i < 2; ++i )
	{
		oResult.m_akVector[ i ] = -m_akVector[ i ];
	}
	return oResult;
}

template< typename DataType >
TVector2< DataType > TVector2< DataType >::operator/( DataType krRhs ) const
{
	return TVector2< DataType >( this->X() / krRhs, this->Y() / krRhs, this->Z() / krRhs );
}

template< typename DataType >
TVector2< DataType > TVector2< DataType >::operator*( DataType oRhs ) const
{
	TVector2< DataType > oResult;
	for( u8 i( 0 ); i < 2; ++i )
	{
		oResult.m_akVector[ i ] = m_akVector[ i ] * oRhs;
	}
	return oResult;
}

template< typename DataType >
TVector2< DataType >& TVector2< DataType >::operator*=( DataType oRhs )
{
	for( u8 i( 0 ); i < 2; ++i )
	{
		m_akVector[ i ] *= oRhs;
	}
	return *this;
}

template< typename DataType >
TVector2< DataType >& TVector2< DataType >::operator/=( DataType oRhs )
{
	for( u8 i( 0 ); i < 2; ++i )
	{
		m_akVector[ i ] /= oRhs;
	}
	return *this;
}

template< typename DataType >
TVector2< DataType >& TVector2< DataType >::operator+=( const TVector2< DataType >& krRhs )
{
	for( u8 i( 0 ); i < 2; ++i )
	{
		m_akVector[ i ] += krRhs.m_akVector[ i ];
	}
	return (*this);
}

template< typename DataType >
TVector2< DataType >& TVector2< DataType >::operator-=( const TVector2< DataType >& krRhs )
{
	for( u8 i( 0 ); i < 2; ++i )
	{
		m_akVector[ i ] -= krRhs.m_akVector[ i ];
	}
	return (*this);
}

template< typename DataType >
bool TVector2< DataType >::operator==( const TVector2< DataType >& krRhs ) const
{
	return( this->X() == krRhs.X() && this->Y() == krRhs.Y() && this->Z() == krRhs.Z() );
}

template< typename DataType >
bool TVector2< DataType >::operator!=( const TVector2< DataType >& krRhs ) const
{
	return !( *this == krRhs );
}

template< typename DataType >
const DataType& TVector2< DataType >::operator[]( u16 uIndex ) const
{
	assert( uIndex < 2 );
	return m_akVector[ uIndex ];
}

template< typename DataType >
DataType TVector2< DataType >::GetElement( u8 uElement ) const
{
	assert(	uElement < 2 );
	return m_akVector[ uElement ];
}

template< typename DataType >
void TVector2< DataType >::SetElement( u8 uElement, DataType oElement )
{
	assert( uElement < 2 );
	m_akVector[ uElement ] = oElement;
}

// Compute the cross product between two 3-dimensional vectors:
template< typename DataType >
TVector2< DataType > TVector2< DataType >::Cross( const TVector2< DataType >& krRhs ) const
{
	// Create and compute the cross product:
	return TVector2< DataType >( ( this->Y() * krRhs.Z() ) - ( this->Z() * krRhs.Y() ),
		( this->Z() * krRhs.X() ) - ( this->X() * krRhs.Z() ),
		( this->X() * krRhs.Y() ) - ( this->Y() * krRhs.X() ) );
}

template< typename DataType >
u8 TVector2< DataType >::GetNumDimensions() const
{
	return 2;
}

template< typename DataType >
void TVector2< DataType >::Normalize()
{
	(*this) /= this->GetLength();
}

template< typename DataType >
void TVector2< DataType >::CopyPartialVector( const TBaseVector< DataType >& krSource, 
	u8 uDestinationStart, u8 uSourceStart, u8 uNumElements )
{
	assert( uDestinationStart + uNumElements <= 2 );
	assert( krSource.GetNumDimensions() >= uSourceStart + uNumElements );
	memcpy( &( m_akVector[ uDestinationStart ] ), &( krSource.GetArray()[ uSourceStart ] ),
		sizeof( DataType ) * uNumElements );
}

template< typename DataType >
TVector2< DataType > TVector2< DataType >::GetNormal() const
{
	TVector2< DataType > oNormal( *this );
	oNormal.Normalize();
	return oNormal;
}

template< typename DataType >
DataType TVector2< DataType >::GetAngle( const TVector2< DataType >& krRhs ) const
{
	TVector2< DataType > oNormalThis( GetNormal() );
	TVector2< DataType > oNormalRhs( krRhs.GetNormal() );
	return oNormalThis.GetAngleAssumeNormal( oNormalRhs );
}

template< typename DataType >
DataType TVector2< DataType >::GetDistanceSquared( const TVector2< DataType >& krRhs ) 
	const
{
	TVector2< DataType> oDifference( krRhs - (*this) );
	return oDifference.GetLengthSquared();
}

template< typename DataType >
DataType TVector2< DataType >::GetDistance( const TVector2< DataType >& krRhs ) const
{
	TVector2< DataType > oDifference( krRhs - (*this) );
	return oDifference.GetLength();
}

template< typename DataType >
const DataType* TVector2< DataType >::GetArray() const
{
	return m_akVector;
}

template< typename DataType >
TVector2< DataType > TVector2< DataType >::GetResizedVector( u8 uDimensions, 
	DataType oFill ) const
{
	assert( uDimensions > 0 );
	TVector< DataType > oVector( uDimensions );
	u8 uCopyCount( NUtilities::Min( static_cast< u8 >( 2 ), uDimensions ) );
	oVector.CopyPartialVector( *this, 0, 0, uCopyCount );
	for( u8 i( uCopyCount ); i < uDimensions; ++i )
	{
		oVector.SetElement( i, oFill );
	}
	return oVector;
}

template< typename DataType >
DataType TVector2< DataType >::GetAngle() const
{
	// Normalize:
	TVector2< DataType > oUnit( *this );
	if( NUtilities::IsAlmostEqual( oUnit.X(), static_cast< DataType >( 0 ) ) &&
		NUtilities::IsAlmostEqual( oUnit.Y(), static_cast< DataType >( 0 ) ) )
	{
		return static_cast< DataType >( 0 );
	}
	oUnit.Normalize();

	// Calculate rotation:
	return static_cast< DataType >( asin( static_cast< double >( oUnit.X() ) ) );
}

typedef TVector2< f32 > CF32Vector2;
typedef TVector2< f64 > CF64Vector2;
typedef TVector2< u16 > CU16Vector2;

// Scalar multiplied by a vector:
CF32Vector2 operator*( f32 fLhs, const CF32Vector2& krRhs );

#endif
