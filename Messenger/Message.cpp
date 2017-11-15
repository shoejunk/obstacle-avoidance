#include "Message.h"
#include <string.h>

CMessage::CMessage( u32 uType )
	: m_uType( uType )
{
}

u32 CMessage::GetType() const
{
	return m_uType;
}

void CMessage::Pack( i8* pBuffer )
{
	memcpy( pBuffer, &m_uType, sizeof( m_uType ) );
}
