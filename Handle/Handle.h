#ifndef HANDLE_H
#define HANDLE_H

#include "../Common/Types.h"
#include <unordered_map>

class CHandle
{
public:
	virtual void		Disable() = 0;
};

template< typename DataType >
class THandle : public CHandle
{
public:
					THandle() : m_pMemory( NULL )						{}
					THandle( DataType* pMemory ) : m_pMemory( pMemory )	{}
	DataType*		Get() const											{ return m_pMemory; }
	virtual void	Disable()											{ m_pMemory = NULL; }
	void			Set( DataType* pMemory )							{ m_pMemory = pMemory; }

private:
	DataType*	m_pMemory;
};

class CHandleFactory
{
private:
	static CHandleFactory*	ms_pGlobalHandleFactory;

public:
	static CHandleFactory*	GetGlobalHandleFactory();
	static void				CreateGlobalHandleFactory();
	static void				DestroyGlobalHandleFactory();

public:
									CHandleFactory() {}
									~CHandleFactory();
	template< typename DataType >
	THandle< DataType >&			CreateHandle( DataType& rObj );
	template< typename DataType >
	THandle< DataType >&			GetHandle( const DataType& rObj );
	template< typename DataType >
	void							DeleteHandle( const DataType& rObj );
	template< typename DataType >
	bool							DoesHandleExist( const DataType& rObj );

private:
	std::unordered_map< const void*, CHandle* >	m_oHandleMap;
};

template< typename DataType >
THandle< DataType >& CHandleFactory::CreateHandle( DataType& rObj )
{
	THandle< DataType >* pHandle( new THandle< DataType >( &rObj ) );
	m_oHandleMap.insert( std::make_pair( static_cast<const void*>(&rObj), pHandle ) );
	return *pHandle;
}

template< typename DataType >
THandle< DataType >& CHandleFactory::GetHandle( const DataType& rObj )
{
	return static_cast< THandle< DataType >& >( *m_oHandleMap[ static_cast< const void* >( &rObj ) ] );
}

template< typename DataType >
void CHandleFactory::DeleteHandle( const DataType& rObj )
{
	THandle< DataType >* pHandle( static_cast< THandle< DataType >* >( m_oHandleMap[ static_cast< const void* >( &rObj ) ] ) );
	delete pHandle;
	m_oHandleMap.erase( static_cast< const void* >( &rObj ) );
}

template< typename DataType >
bool CHandleFactory::DoesHandleExist( const DataType& rObj )
{
	return m_oHandleMap.find( &rObj ) != m_oHandleMap.end();
}

#endif // HANDLE_H
