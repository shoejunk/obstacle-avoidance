#include "WindowsInputListener.h"
#include "WindowsInputMessage.h"
#include "Common/Macros.h"
#include "MouseMessage.h"

CWindowsInputListener::CWindowsInputListener( CInput* pInput, CWindow& rWindow )
	: CInputListener( pInput )
	, m_rWindow( rWindow )
{
	CMessenger::GlobalListen( *this, CWindowsInputMessage::GetWindowsInputMessageType() );
}

CWindowsInputListener::~CWindowsInputListener()
{
	CMessenger::GlobalStopListening( 
		*this, CWindowsInputMessage::GetWindowsInputMessageType() );
}

void CWindowsInputListener::Push( CMessage& rMessage )
{
	assert( rMessage.GetType() == CWindowsInputMessage::GetWindowsInputMessageType() );
	CWindowsInputMessage& rWindowsMessage( 
		static_cast< CWindowsInputMessage& >( rMessage ) );
	if( rWindowsMessage.GetWindow() != &m_rWindow )
	{
		return;
	}
	switch( rWindowsMessage.GetMessage() )
	{
		case WM_KEYDOWN:
		{
			SetButton( rWindowsMessage.GetParameter1(), true );
			break;
		}
		case WM_KEYUP:
		{
			SetButton( rWindowsMessage.GetParameter1(), false );
			break;
		}
		case WM_DESTROY:
		{
			SetButton( 0, true );
			break;
		}
		case WM_SIZE:
		{
			m_rWindow.Resize( static_cast< f32 >( 
				( rWindowsMessage.GetParameter2() << 16 ) >> 16 ), 
				static_cast< f32 >( rWindowsMessage.GetParameter2() >> 16 ) );
			break;
		}
		case WM_LBUTTONDBLCLK:
		{
			u32 uX( ( rWindowsMessage.GetParameter2() << 16 ) >> 16 );
			u32 uY( rWindowsMessage.GetParameter2() >> 16 );
			f32 fNormalX( m_rWindow.GetWidth() > 0 ? 
				(f32)uX / (f32)m_rWindow.GetWidth() : 0.f );
			f32 fNormalY( m_rWindow.GetHeight() > 0 ? 
				(f32)uY / (f32)m_rWindow.GetHeight() : 0.f );
			CMouseMessage oMouseMessage( CMouseMessage::LEFT_BUTTON_DOUBLE_CLICK, 
				uX, uY, fNormalX, fNormalY );
			CMessenger::GlobalPush( oMouseMessage ); 
			break;
		}
		case WM_RBUTTONDBLCLK:
		{
			u32 uX( ( rWindowsMessage.GetParameter2() << 16 ) >> 16 );
			u32 uY( rWindowsMessage.GetParameter2() >> 16 );
			f32 fNormalX( m_rWindow.GetWidth() > 0 ? 
				(f32)uX / (f32)m_rWindow.GetWidth() : 0.f );
			f32 fNormalY( m_rWindow.GetHeight() > 0 ? 
				(f32)uY / (f32)m_rWindow.GetHeight() : 0.f );
			CMouseMessage oMouseMessage( CMouseMessage::RIGHT_BUTTON_DOUBLE_CLICK, 
				uX, uY, fNormalX, fNormalY );
			CMessenger::GlobalPush( oMouseMessage ); 
			break;
		}
		case WM_LBUTTONDOWN:
		{
			u32 uX( ( rWindowsMessage.GetParameter2() << 16 ) >> 16 );
			u32 uY( rWindowsMessage.GetParameter2() >> 16 );
			f32 fNormalX( m_rWindow.GetWidth() > 0 ? 
				(f32)uX / (f32)m_rWindow.GetWidth() : 0.f );
			f32 fNormalY( m_rWindow.GetHeight() > 0 ? 
				(f32)uY / (f32)m_rWindow.GetHeight() : 0.f );
			CMouseMessage oMouseMessage( CMouseMessage::LEFT_BUTTON_DOWN, 
				uX, uY, fNormalX, fNormalY );
			CMessenger::GlobalPush( oMouseMessage ); 
			break;
		}
		case WM_RBUTTONDOWN:
		{
			u32 uX( ( rWindowsMessage.GetParameter2() << 16 ) >> 16 );
			u32 uY( rWindowsMessage.GetParameter2() >> 16 );
			f32 fNormalX( m_rWindow.GetWidth() > 0 ? 
				(f32)uX / (f32)m_rWindow.GetWidth() : 0.f );
			f32 fNormalY( m_rWindow.GetHeight() > 0 ? 
				(f32)uY / (f32)m_rWindow.GetHeight() : 0.f );
			CMouseMessage oMouseMessage( CMouseMessage::RIGHT_BUTTON_DOWN, 
				uX, uY, fNormalX, fNormalY );
			CMessenger::GlobalPush( oMouseMessage ); 
			break;
		}
		case WM_LBUTTONUP:
		{
			u32 uX( ( rWindowsMessage.GetParameter2() << 16 ) >> 16 );
			u32 uY( rWindowsMessage.GetParameter2() >> 16 );
			f32 fNormalX( m_rWindow.GetWidth() > 0 ? 
				(f32)uX / (f32)m_rWindow.GetWidth() : 0.f );
			f32 fNormalY( m_rWindow.GetHeight() > 0 ? 
				(f32)uY / (f32)m_rWindow.GetHeight() : 0.f );
			CMouseMessage oMouseMessage( CMouseMessage::LEFT_BUTTON_UP, 
				uX, uY, fNormalX, fNormalY );
			CMessenger::GlobalPush( oMouseMessage ); 
			break;
		}
		case WM_RBUTTONUP:
		{
			u32 uX( ( rWindowsMessage.GetParameter2() << 16 ) >> 16 );
			u32 uY( rWindowsMessage.GetParameter2() >> 16 );
			f32 fNormalX( m_rWindow.GetWidth() > 0 ? 
				(f32)uX / (f32)m_rWindow.GetWidth() : 0.f );
			f32 fNormalY( m_rWindow.GetHeight() > 0 ? 
				(f32)uY / (f32)m_rWindow.GetHeight() : 0.f );
			CMouseMessage oMouseMessage( CMouseMessage::RIGHT_BUTTON_UP, 
				uX, uY, fNormalX, fNormalY );
			CMessenger::GlobalPush( oMouseMessage ); 
			break;
		}
		case WM_MOUSEMOVE:
		{
			i16 iX( ( rWindowsMessage.GetParameter2() << 16 ) >> 16 );
			i16 iY( rWindowsMessage.GetParameter2() >> 16 );
			iX = NUtilities::Max< i16 >( 0, iX );
			iY = NUtilities::Max< i16 >( 0, iY );
			f32 fNormalX( m_rWindow.GetWidth() > 0 ? 
				(f32)iX / (f32)m_rWindow.GetWidth() : 0.f );
			f32 fNormalY( m_rWindow.GetHeight() > 0 ? 
				(f32)iY / (f32)m_rWindow.GetHeight() : 0.f );
			CMouseMessage oMouseMessage( CMouseMessage::DRAG, iX, iY, fNormalX,
				fNormalY );
			CMessenger::GlobalPush( oMouseMessage ); 
			break;
		}
		case WM_CAPTURECHANGED:
		{
			CMouseMessage oMouseMessage( CMouseMessage::LOSE_CONTROL, 0, 0, 0.f, 0.f );
			CMessenger::GlobalPush( oMouseMessage ); 
			break;
		}
		default:
			assert( false );
	}
}

CWindowsInputListener::CWindowsInputListener()
	: CInputListener( new CInput )
	, m_rWindow( *( new CWindow( NULL, 0, 0, 0.f, 0.f, false ) ) )
{
	assert( false );
}

CWindowsInputListener& CWindowsInputListener::operator=( const CWindowsInputListener& )
{
	assert( false );
	return *this;
}
