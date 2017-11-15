#ifndef VECTOR3_H
#define VECTOR3_H

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "BaseVector.h"
#include "Vector.h"
#include "../Common/Types.h"
#include "../Common/Utilities.h"

template< typename DataType >
class TVector3 : public TBaseVector< DataType >
{
public:
							TVector3();
							TVector3( const DataType* aArray );
							TVector3( const TVector3< DataType >& krVector );
							TVector3( DataType oX, DataType oY, DataType oZ );
	virtual					~TVector3();
	TVector3< DataType >&	operator=( const TVector3< DataType >& krRhs );
	TVector3< DataType >	operator+( const TVector3< DataType >& krRhs ) const;
	TVector3< DataType >	operator-( const TVector3< DataType >& krRhs ) const;
	TVector3< DataType >	operator-() const;
	TVector3< DataType >	operator/( DataType krRhs ) const;
	TVector3< DataType >	operator*( DataType fRhs ) const;
	TVector3< DataType >&	operator*=( DataType oRhs ); 
	TVector3< DataType >&	operator/=( DataType oRhs ); 
	TVector3< DataType >&	operator+=( const TVector3< DataType >& krRhs ); 
	TVector3< DataType >&	operator-=( const TVector3< DataType >& krRhs ); 
	bool					operator==( const TVector3< DataType >& krRhs ) const; 
	bool					operator!=( const TVector3< DataType >& krRhs ) const; 
	const DataType&			operator[]( u16 uIndex ) const;
	virtual DataType		GetElement( u8 uElement ) const;
	virtual void			SetElement( u8 uElement, DataType oElement );
	TVector3< DataType >	Cross( const TVector3< DataType >& krRhs ) const;
	virtual u8				GetNumDimensions() const;
	void					Normalize();
	void					CopyPartialVector( const TBaseVector< DataType >& krSource, 
								u8 uDestinationStart, u8 uSourceStart, u8 uNumElements );
	TVector3< DataType >	GetNormal() const;
	DataType				GetAngle( const TVector3< DataType >& krRhs ) const;
	DataType				GetDistanceSquared( const TVector3< DataType >& krRhs ) const;
	DataType				GetDistance( const TVector3< DataType >& krRhs ) const;
	virtual const DataType*	GetArray() const;
	TVector3< DataType >	GetResizedVector( u8 uDimensions, 
								DataType oFill = static_cast< DataType >( 0 ) ) const;
	DataType				GetXAngle() const;
	DataType				GetYAngle() const;
	DataType				GetZAngle() const;

private:
	DataType	m_akVector[ 3 ];
};

template< typename DataType >
TVector3< DataType >::TVector3()
{
	for( u8 i( 0 ); i < 3; ++i )
	{
		m_akVector[ i ] = static_cast< DataType >( 0 );
	}
}

template< typename DataType >
TVector3< DataType >::TVector3( const DataType* aArray )
{
	assert( aArray != NULL );
	for( u8 i( 0 ); i < 3; ++i )
	{
		m_akVector[ i ] = aArray[ i ];
	}
}

template< typename DataType >
TVector3< DataType >::TVector3( const TVector3< DataType >& krVector )
{
	memcpy( m_akVector, krVector.m_akVector, 3 * sizeof( DataType ) );
}

template< typename DataType >
TVector3< DataType >::TVector3( DataType oX, DataType oY, DataType oZ )
{
	m_akVector[ 0 ] = oX;
	m_akVector[ 1 ] = oY;
	m_akVector[ 2 ] = oZ;
}

template< typename DataType >
TVector3< DataType >::~TVector3()
{
}

template< typename DataType >
TVector3< DataType >& TVector3< DataType >::operator=( const TVector3< DataType >& krRhs )
{
	memcpy( m_akVector, krRhs.m_akVector, 3 * sizeof( DataType ) );
	return *this;
}

template< typename DataType >
TVector3< DataType > TVector3< DataType >::operator+( const TVector3< DataType >& krRhs ) 
	const
{
	TVector3< DataType > oResult;
	for( u8 i( 0 ); i < 3; ++i )
	{
		oResult.m_akVector[ i ] = m_akVector[ i ] + krRhs.m_akVector[ i ];
	}
	return oResult;
}

template< typename DataType >
TVector3< DataType > TVector3< DataType >::operator-( const TVector3< DataType >& krRhs ) 
	const
{
	TVector3< DataType > oResult;
	for( u8 i( 0 ); i < 3; ++i )
	{
		oResult.m_akVector[ i ] = m_akVector[ i ] - krRhs.m_akVector[ i ];
	}
	return oResult;
}

template< typename DataType >
TVector3< DataType > TVector3< DataType >::operator-() const
{
	TVector3< DataType > oResult;
	for( u8 i( 0 ); i < 3; ++i )
	{
		oResult.m_akVector[ i ] = -m_akVector[ i ];
	}
	return oResult;
}

template< typename DataType >
TVector3< DataType > TVector3< DataType >::operator/( DataType krRhs ) const
{
	return TVector3< DataType >( this->X() / krRhs, this->Y() / krRhs, this->Z() / krRhs );
}

template< typename DataType >
TVector3< DataType > TVector3< DataType >::operator*( DataType oRhs ) const
{
	TVector3< DataType > oResult;
	for( u8 i( 0 ); i < 3; ++i )
	{
		oResult.m_akVector[ i ] = m_akVector[ i ] * oRhs;
	}
	return oResult;
}

template< typename DataType >
TVector3< DataType >& TVector3< DataType >::operator*=( DataType oRhs )
{
	for( u8 i( 0 ); i < 3; ++i )
	{
		m_akVector[ i ] *= oRhs;
	}
	return *this;
}

template< typename DataType >
TVector3< DataType >& TVector3< DataType >::operator/=( DataType oRhs )
{
	for( u8 i( 0 ); i < 3; ++i )
	{
		m_akVector[ i ] /= oRhs;
	}
	return *this;
}

template< typename DataType >
TVector3< DataType >& TVector3< DataType >::operator+=( const TVector3< DataType >& krRhs )
{
	for( u8 i( 0 ); i < 3; ++i )
	{
		m_akVector[ i ] += krRhs.m_akVector[ i ];
	}
	return (*this);
}

template< typename DataType >
TVector3< DataType >& TVector3< DataType >::operator-=( const TVector3< DataType >& krRhs )
{
	for( u8 i( 0 ); i < 3; ++i )
	{
		m_akVector[ i ] -= krRhs.m_akVector[ i ];
	}
	return (*this);
}

template< typename DataType >
bool TVector3< DataType >::operator==( const TVector3< DataType >& krRhs ) const
{
	return( this->X() == krRhs.X() && this->Y() == krRhs.Y() && this->Z() == krRhs.Z() );
}

template< typename DataType >
bool TVector3< DataType >::operator!=( const TVector3< DataType >& krRhs ) const
{
	return !( *this == krRhs );
}

template< typename DataType >
const DataType& TVector3< DataType >::operator[]( u16 uIndex ) const
{
	assert( uIndex < 3 );
	return m_akVector[ uIndex ];
}

template< typename DataType >
DataType TVector3< DataType >::GetElement( u8 uElement ) const
{
	assert(	uElement < 3 );
	return m_akVector[ uElement ];
}

template< typename DataType >
void TVector3< DataType >::SetElement( u8 uElement, DataType oElement )
{
	assert( uElement < 3 );
	m_akVector[ uElement ] = oElement;
}

// Compute the cross product between two 3-dimensional vectors:
template< typename DataType >
TVector3< DataType > TVector3< DataType >::Cross( const TVector3< DataType >& krRhs ) const
{
	// Create and compute the cross product:
	return TVector3< DataType >( ( this->Y() * krRhs.Z() ) - ( this->Z() * krRhs.Y() ),
		( this->Z() * krRhs.X() ) - ( this->X() * krRhs.Z() ),
		( this->X() * krRhs.Y() ) - ( this->Y() * krRhs.X() ) );
}

template< typename DataType >
u8 TVector3< DataType >::GetNumDimensions() const
{
	return 3;
}

template< typename DataType >
void TVector3< DataType >::Normalize()
{
	(*this) /= this->GetLength();
}

template< typename DataType >
void TVector3< DataType >::CopyPartialVector( const TBaseVector< DataType >& krSource, 
	u8 uDestinationStart, u8 uSourceStart, u8 uNumElements )
{
	assert( uDestinationStart + uNumElements <= 3 );
	assert( krSource.GetNumDimensions() >= uSourceStart + uNumElements );
	memcpy( &( m_akVector[ uDestinationStart ] ), &( krSource.GetArray()[ uSourceStart ] ),
		sizeof( DataType ) * uNumElements );
}

template< typename DataType >
TVector3< DataType > TVector3< DataType >::GetNormal() const
{
	TVector3< DataType > oNormal( *this );
	oNormal.Normalize();
	return oNormal;
}

template< typename DataType >
DataType TVector3< DataType >::GetAngle( const TVector3< DataType >& krRhs ) const
{
	TVector3< DataType > oNormalThis( GetNormal() );
	TVector3< DataType > oNormalRhs( krRhs.GetNormal() );
	return oNormalThis.GetAngleAssumeNormal( oNormalRhs );
}

template< typename DataType >
DataType TVector3< DataType >::GetDistanceSquared( const TVector3< DataType >& krRhs ) 
	const
{
	TVector3< DataType> oDifference( krRhs - (*this) );
	return oDifference.GetLengthSquared();
}

template< typename DataType >
DataType TVector3< DataType >::GetDistance( const TVector3< DataType >& krRhs ) const
{
	TVector3< DataType > oDifference( krRhs - (*this) );
	return oDifference.GetLength();
}

template< typename DataType >
const DataType* TVector3< DataType >::GetArray() const
{
	return m_akVector;
}

template< typename DataType >
TVector3< DataType > TVector3< DataType >::GetResizedVector( u8 uDimensions, 
	DataType oFill ) const
{
	assert( uDimensions > 0 );
	TVector< DataType > oVector( uDimensions );
	u8 uCopyCount( NUtilities::Min( static_cast< u8 >( 3 ), uDimensions ) );
	oVector.CopyPartialVector( *this, 0, 0, uCopyCount );
	for( u8 i( uCopyCount ); i < uDimensions; ++i )
	{
		oVector.SetElement( i, oFill );
	}
	return oVector;
}

template< typename DataType >
DataType TVector3< DataType >::GetXAngle() const
{
	// Disregard X component and normalize:
	TVector3< DataType > oUnit( *this );
	oUnit.X( static_cast< DataType >( 0 ) );
	if( NUtilities::IsAlmostEqual( oUnit.Y(), static_cast< DataType >( 0 ) ) &&
		NUtilities::IsAlmostEqual( oUnit.Z(), static_cast< DataType >( 0 ) ) )
	{
		return static_cast< DataType >( 0 );
	}
	oUnit.Normalize();

	// Calculate rotation:
	if( oUnit.Z() > static_cast< DataType >( 0 ) )
	{
		return static_cast< DataType >( asin( static_cast< double >( oUnit.Y() ) ) );
	}
	else if( oUnit.Y() > static_cast< DataType >( 0 ) )
	{
		return static_cast< DataType >( ( PI * 0.5f ) + 
			asin( static_cast< double >( -oUnit.Z() ) ) );
	}
	else
	{
		return static_cast< DataType >( -( PI * 0.5f ) - 
			asin( static_cast< double >( -oUnit.Z() ) ) );
	}
}

template< typename DataType >
DataType TVector3< DataType >::GetYAngle() const
{
	// Disregard Y component and normalize:
	TVector3< DataType > oUnit( *this );
	oUnit.Y( static_cast< DataType >( 0 ) );
	if( NUtilities::IsAlmostEqual( oUnit.X(), static_cast< DataType >( 0 ) ) &&
		NUtilities::IsAlmostEqual( oUnit.Z(), static_cast< DataType >( 0 ) ) )
	{
		return static_cast< DataType >( 0 );
	}
	oUnit.Normalize();

	// Calculate rotation:
	if( oUnit.Z() > 0.f )
	{
		return static_cast< DataType >( asin( static_cast< double >( oUnit.X() ) ) );
	}
	else if( oUnit.X() > 0.f )
	{
		return static_cast< DataType >( ( PI * 0.5f ) + 
			asin( static_cast< double >( -oUnit.Z() ) ) );
	}
	else
	{
		return static_cast< DataType >( -( PI * 0.5f ) - 
			asin( static_cast< double >( -oUnit.Z() ) ) );
	}
}

template< typename DataType >
DataType TVector3< DataType >::GetZAngle() const
{
	// Disregard Z component and normalize:
	TVector3< DataType > oUnit( *this );
	oUnit.Z( static_cast< DataType >( 0 ) );
	if( NUtilities::IsAlmostEqual( oUnit.X(), static_cast< DataType >( 0 ) ) &&
		NUtilities::IsAlmostEqual( oUnit.Y(), static_cast< DataType >( 0 ) ) )
	{
		return static_cast< DataType >( 0 );
	}
	oUnit.Normalize();

	// Calculate rotation:
	return static_cast< DataType >( asin( static_cast< double >( oUnit.X() ) ) );
}

typedef TVector3< f32 > CF32Vector3;
typedef TVector3< f64 > CF64Vector3;
typedef TVector3< u16 > CU16Vector3;

// Scalar multiplied by a vector:
CF32Vector3 operator*( f32 fLhs, const CF32Vector3& krRhs );

#endif
