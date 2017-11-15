#ifndef MESSAGE_H
#define MESSAGE_H
#include "../Common/Types.h"

class CMessage
{
public:
	static u16	GetMessageDataSize()	{ return sizeof( u32 ); }

public:
					CMessage()	{}
					CMessage( u32 uType );
	virtual			~CMessage()	{}
	u32				GetType() const;
	virtual void	Set( i8* pData )	{ m_uType = *(u32*)pData; }
	virtual void	Pack( i8* pBuffer );
	virtual u16		GetDataSize() const	{ return GetMessageDataSize(); }

protected:
	void	SetType( u32 uType )	{ m_uType = uType; }

private:
	u32		m_uType;
};

#endif
