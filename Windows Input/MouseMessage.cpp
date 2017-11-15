#include "MouseMessage.h"

u32 CMouseMessage::GetMouseMessageUID()
{
	return ms_kuMouseMessageUID;
}

CMouseMessage::CMouseMessage( EMouseAction eMouseAction, u32 uX, u32 uY,
	f32 fNormalX, f32 fNormalY )
	: CMessage( ms_kuMouseMessageUID )
	, m_eMouseAction( eMouseAction )
	, m_uX( uX )
	, m_uY( uY )
	, m_fNormalX( fNormalX )
	, m_fNormalY( fNormalY )
{
}

CMouseMessage::EMouseAction CMouseMessage::GetMouseAction() const
{
	return m_eMouseAction;
}

u32 CMouseMessage::X() const
{
	return m_uX;
}

u32 CMouseMessage::Y() const
{
	return m_uY;
}
