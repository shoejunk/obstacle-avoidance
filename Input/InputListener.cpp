#include "InputListener.h"

CInputListener::CInputListener( CInput* pInput )
	: m_pInput( pInput )
{
	assert( m_pInput );
}

bool CInputListener::IsButtonDown( u32 uButton ) const
{
	assert( m_pInput );
	return m_pInput->IsButtonDown( uButton );
}

void CInputListener::SetButton( u32 uButton, bool bDown )
{
	assert( m_pInput );
	m_pInput->SetButton( uButton, bDown );
}

void CInputListener::SetAnalog( u32 uAnalog, f32 fValue )
{
	assert( m_pInput );
	m_pInput->SetAnalog( uAnalog, fValue );
}
