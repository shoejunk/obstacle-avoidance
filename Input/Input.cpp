#include "Input.h"
#include <assert.h>

u32 CInput::GetMaxNumButtons()
{
	return ms_kuMaxNumButtons;
}

u32 CInput::GetMaxNumAnalogs()
{
	return ms_kuMaxNumAnalogs;
}

u32 CInput::GetButtonMessageType()
{
	return ms_kuButtonMessageType;
}

u32 CInput::GetAnalogMessageType()
{
	return ms_kuAnalogMessageType;
}

CInput::CInput()
{
	// Initialize the buttons and analogs:
	for( i32 i( 0 ); i < ms_kuMaxNumButtons; ++i )
	{
		m_akButtonList[ i ] = false;
	}
	for( i32 i( 0 ); i < ms_kuMaxNumAnalogs; ++i )
	{
		m_akAnalogList[ i ] = 0.0f;
	}
}

CInput::~CInput()
{
}

bool CInput::IsButtonDown( u32 uButton ) const
{
	// Make sure the button number is valid:
	assert( uButton < ms_kuMaxNumButtons );

	// Look up the button's value:
	return m_akButtonList[ uButton ];
}

f32 CInput::GetAnalogState( u32 uAnalog ) const
{
	// Make sure the analog number is valid:
	assert( uAnalog < ms_kuMaxNumAnalogs );

	// Look up the button's value:
	return m_akButtonList[ uAnalog ];
}

void CInput::SetButton( u32 uButton, bool bDown )
{
	// Make sure the button number is valid:
	assert( uButton < ms_kuMaxNumButtons );

	// Set the button:
	m_akButtonList[ uButton ] = bDown;	
}

void CInput::SetAnalog( u32 uAnalog, f32 fValue )
{
	// Make sure the analog number is valid:
	assert( uAnalog < ms_kuMaxNumAnalogs );

	// Set the analog:
	m_akAnalogList[ uAnalog ] = fValue;	
}
