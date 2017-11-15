template< typename DataType, typename KeyType >
THashEntry< DataType, KeyType >::THashEntry( KeyType uKey, const DataType& krData )
	: m_uKey( uKey )
	, m_oData( krData )
{
}
