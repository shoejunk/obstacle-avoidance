#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "BaseVector.h"
#include "../Common/Types.h"
#include "../Common/Utilities.h"

template< typename DataType >
class TVector : public TBaseVector< DataType >
{
public:
							TVector();
							TVector( u8 uDimensions );
							TVector( u8 uDimensions, const DataType* aArray );
							TVector( const TVector< DataType >& krVector );
							TVector( DataType oX, DataType oY );
							TVector( DataType oX, DataType oY, DataType oZ );
							TVector( DataType oElement1, DataType oElement2, 
								DataType oElement3, DataType oElement4 );
	virtual					~TVector();
	TVector< DataType >&	operator=( const TVector< DataType >& krRhs );
	TVector< DataType >		operator+( const TVector< DataType >& krRhs ) const;
	TVector< DataType >		operator-( const TVector< DataType >& krRhs ) const;
	TVector< DataType >		operator-() const;
	TVector< DataType >		operator*( DataType fRhs ) const;
	TVector< DataType >&	operator*=( DataType oRhs ); 
	TVector< DataType >&	operator/=( DataType oRhs ); 
	TVector< DataType >&	operator+=( const TVector< DataType >& krRhs ); 
	TVector< DataType >&	operator-=( const TVector< DataType >& krRhs ); 
	void					Initialize( u8 uDimensions );
	virtual DataType		GetElement( u8 uElement ) const;
	virtual void			SetElement( u8 uElement, DataType oElement );
	TVector< DataType >		Cross( const TVector< DataType >& krRhs ) const;
	virtual u8				GetNumDimensions() const;
	void					Normalize();
	void					SafeNormalize();
	void					CopyPartialVector( const TVector< DataType >& krSource,
								u8 uDestinationStart, u8 uSourceStart, u8 uNumElements );
	TVector< DataType >		GetNormal() const;
	DataType				GetAngle( const TVector< DataType >& krRhs ) const;
	DataType				GetDistanceSquared( const TVector< DataType >& krRhs ) const;
	DataType				GetDistance( const TVector< DataType >& krRhs ) const;
	virtual const DataType*	GetArray() const;
	TVector< DataType >		GetResizedVector( u8 uDimensions, 
								DataType oFill = static_cast< DataType >( 0 ) ) const;
private:
	u8			m_uDimensions;
	DataType*	m_aVector;
};

template< typename DataType >
TVector< DataType >::TVector()
	: m_uDimensions( 0 )
	, m_aVector( NULL )
{
}

template< typename DataType >
TVector< DataType >::TVector( u8 uDimensions )
	: m_uDimensions( uDimensions )
{
	assert( uDimensions > 0 );
	m_aVector = new DataType[ uDimensions ];
	for( u8 i( 0 ); i < uDimensions; ++i )
	{
		m_aVector[ i ] = static_cast< DataType >( 0 );
	}
}

template< typename DataType >
TVector< DataType >::TVector( u8 uDimensions, const DataType* aArray )
	: m_uDimensions( uDimensions )
{
	assert( uDimensions > 0 && aArray != NULL );
	m_aVector = new DataType[ uDimensions ];
	for( u8 i( 0 ); i < uDimensions; ++i )
	{
		m_aVector[ i ] = aArray[ i ];
	}
}

template< typename DataType >
TVector< DataType >::TVector( const TVector< DataType >& krVector )
	: m_uDimensions( krVector.m_uDimensions )
{
	assert( m_uDimensions > 0 );
	m_aVector = new DataType[ m_uDimensions ];
	memcpy( m_aVector, krVector.m_aVector, m_uDimensions * sizeof( DataType ) );
}

template< typename DataType >
TVector< DataType >::TVector( DataType oX, DataType oY )
	: m_uDimensions( 2 )
{
	m_aVector = new DataType[ 2 ];
	this->XY( oX, oY );
}

template< typename DataType >
TVector< DataType >::TVector( DataType oX, DataType oY, DataType oZ )
	: m_uDimensions( 3 )
{
	m_aVector = new DataType[ 3 ];
	this->XYZ( oX, oY, oZ );
}

template< typename DataType >
TVector< DataType >::TVector( DataType oElement1, DataType oElement2, DataType oElement3,
	DataType oElement4 )
	: m_uDimensions( 4 )
{
	m_aVector = new DataType[ 4 ];
	m_aVector[ 0 ] = oElement1;
	m_aVector[ 1 ] = oElement2;
	m_aVector[ 2 ] = oElement3;
	m_aVector[ 3 ] = oElement4;
}

template< typename DataType >
TVector< DataType >::~TVector()
{
	assert( m_aVector );
	delete[] m_aVector;
}

template< typename DataType >
TVector< DataType >& TVector< DataType >::operator=( const TVector< DataType >& krRhs )
{
	if( m_aVector && m_uDimensions != krRhs.m_uDimensions )
	{
		delete[] m_aVector;
		m_uDimensions = krRhs.m_uDimensions;
		m_aVector = new DataType[ m_uDimensions ];
	}
	else if( !m_aVector )
	{
		m_uDimensions = krRhs.m_uDimensions;
		m_aVector = new DataType[ m_uDimensions ];
	}
	memcpy( m_aVector, krRhs.m_aVector, m_uDimensions * sizeof( DataType ) );
	return *this;
}

template< typename DataType >
TVector< DataType > TVector< DataType >::operator+( const TVector< DataType >& krRhs ) 
	const
{
	assert( m_uDimensions == krRhs.m_uDimensions );
	TVector< DataType > oResult( m_uDimensions );
	for( u8 i( 0 ); i < m_uDimensions; ++i )
	{
		oResult.SetElement( i, GetElement( i ) + krRhs.GetElement( i ) );
	}
	return oResult;
}

template< typename DataType >
TVector< DataType > TVector< DataType >::operator-( const TVector< DataType >& krRhs ) 
	const
{
	assert( m_uDimensions == krRhs.m_uDimensions );
	TVector< DataType > oResult( m_uDimensions );
	for( u8 i( 0 ); i < m_uDimensions; ++i )
	{
		oResult.SetElement( i, GetElement( i ) - krRhs.GetElement( i ) );
	}
	return oResult;
}

template< typename DataType >
TVector< DataType > TVector< DataType >::operator-() const
{
	TVector< DataType > oResult( m_uDimensions );
	for( u8 i( 0 ); i < m_uDimensions; ++i )
	{
		oResult.SetElement( i, -m_aVector[ i ] );
	}
	return oResult;
}

template< typename DataType >
TVector< DataType > TVector< DataType >::operator*( DataType oRhs ) const
{
	TVector< DataType > oResult( m_uDimensions );
	for( u8 i( 0 ); i < m_uDimensions; ++i )
	{
		oResult.SetElement( i, m_aVector[ i ] * oRhs );
	}
	return oResult;
}

template< typename DataType >
TVector< DataType >& TVector< DataType >::operator*=( DataType oRhs )
{
	for( u8 i( 0 ); i < m_uDimensions; ++i )
	{
		m_aVector[ i ] *= oRhs;
	}
	return *this;
}

template< typename DataType >
TVector< DataType >& TVector< DataType >::operator/=( DataType oRhs )
{
	for( u8 i( 0 ); i < m_uDimensions; ++i )
	{
		m_aVector[ i ] /= oRhs;
	}
	return *this;
}

template< typename DataType >
TVector< DataType >& TVector< DataType >::operator+=( const TVector< DataType >& krRhs )
{
	assert( krRhs.m_uDimensions == m_uDimensions );
	for( u8 i( 0 ); i < m_uDimensions; ++i )
	{
		m_aVector[ i ] += krRhs.m_aVector[ i ];
	}
	return (*this);
}

template< typename DataType >
TVector< DataType >& TVector< DataType >::operator-=( const TVector< DataType >& krRhs )
{
	assert( krRhs.m_uDimensions == m_uDimensions );
	for( u8 i( 0 ); i < m_uDimensions; ++i )
	{
		m_aVector[ i ] -= krRhs.m_aVector[ i ];
	}
	return (*this);
}

template< typename DataType >
void TVector< DataType >::Initialize( u8 uDimensions )
{
	assert( uDimensions > 0 && m_uDimensions == 0 && !m_aVector );
	m_uDimensions = uDimensions;
	m_aVector = new DataType[ uDimensions ];
	for( u8 i( 0 ); i < uDimensions; ++i )
	{
		m_aVector[ i ] = static_cast< DataType >( 0 );
	}
}

template< typename DataType >
DataType TVector< DataType >::GetElement( u8 uElement ) const
{
	assert(	m_aVector && uElement < m_uDimensions );
	return m_aVector[ uElement ];
}

template< typename DataType >
void TVector< DataType >::SetElement( u8 uElement, DataType oElement )
{
	assert( uElement < m_uDimensions );
	m_aVector[ uElement ] = oElement;
}

// Compute the cross product between two 3-dimensional vectors:
template< typename DataType >
TVector< DataType > TVector< DataType >::Cross( const TVector< DataType >& krRhs ) const
{
	// Only allow 3-dimensional vectors:
	assert( m_uDimensions == 3 && krRhs.m_uDimensions == 3 );

	// Create and compute the cross product:
	TVector< DataType > oCross( 3 );
	oCross.SetElement( 0, ( this->Y() * krRhs.Z() ) - ( this->Z() * krRhs.Y() ) );
	oCross.SetElement( 1, ( this->Z() * krRhs.X() ) - ( this->X() * krRhs.Z() ) );
	oCross.SetElement( 2, ( this->X() * krRhs.Y() ) - ( this->Y() * krRhs.X() ) );
	return oCross;
}

template< typename DataType >
u8 TVector< DataType >::GetNumDimensions() const
{
	return m_uDimensions;
}

template< typename DataType >
void TVector< DataType >::Normalize()
{
	(*this) /= this->GetLength();
}

template< typename DataType >
void TVector< DataType >::SafeNormalize( )
{
	DataType oLength( this->GetLength() );
	if( oLength == static_cast< DataType >( 0 ) )
	{
		assert( this->GetNumDimensions() > 0 );
		this->SetElement( 0, static_cast< DataType >( 1 ) );
		for( u8 i( 1 ); i < this->GetNumDimensions(); ++i )
		{
			this->SetElement( i, static_cast< DataType >( 0 ) );
 		}
		return;
	}
	( *this ) /= oLength;
}

template< typename DataType >
void TVector< DataType >::CopyPartialVector( const TVector< DataType >& krSource, 
	u8 uDestinationStart, u8 uSourceStart, u8 uNumElements )
{
	assert( m_uDimensions >= uDestinationStart + uNumElements );
	assert( krSource.m_uDimensions >= uSourceStart + uNumElements );
	memcpy( &( m_aVector[ uDestinationStart ] ), &( krSource.m_aVector[ uSourceStart ] ),
		sizeof( DataType ) * uNumElements );
}

template< typename DataType >
TVector< DataType >	TVector< DataType >::GetNormal() const
{
	TVector< DataType > oNormal( *this );
	oNormal.Normalize();
	return oNormal;
}

template< typename DataType >
DataType TVector< DataType >::GetAngle( const TVector< DataType >& krRhs ) 
	const
{
	TVector< DataType > oNormalThis( GetNormal() );
	TVector< DataType > oNormalRhs( krRhs.GetNormal() );
	return oNormalThis.GetAngleAssumeNormal( oNormalRhs );
}

template< typename DataType >
DataType TVector< DataType >::GetDistanceSquared( const TVector< DataType >& krRhs ) const
{
	TVector< DataType> oDifference( krRhs - (*this) );
	return oDifference.GetLengthSquared();
}

template< typename DataType >
DataType TVector< DataType >::GetDistance( const TVector< DataType >& krRhs ) const
{
	TVector< DataType> oDifference( krRhs - (*this) );
	return oDifference.GetLength();
}

template< typename DataType >
const DataType* TVector< DataType >::GetArray() const
{
	return m_aVector;
}

template< typename DataType >
TVector< DataType > TVector< DataType >::GetResizedVector( u8 uDimensions, DataType oFill )
	const
{
	assert( uDimensions > 0 );
	TVector< DataType > oVector( uDimensions );
	u8 uCopyCount( NUtilities::Min( m_uDimensions, uDimensions ) );
	oVector.CopyPartialVector( *this, 0, 0, uCopyCount );
	for( u8 i( uCopyCount ); i < uDimensions; ++i )
	{
		oVector.SetElement( i, oFill );
	}
	return oVector;
}

typedef TVector< f32 > CF32Vector;
typedef TVector< f64 > CF64Vector;

CF32Vector operator*( f32 fLhs, const CF32Vector& krRhs );

#endif
