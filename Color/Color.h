//
//  Color.h
//  Color
//
//  Created by Me on 5/9/12.
//  Copyright (c) 2012 Shoejunk Industries. All rights reserved.
//

#ifndef COLOR_H
#define COLOR_H

#include "Common/Types.h"

class CColor
{
public:
			CColor( f32 fRed, f32 fGreen, f32 fBlue );
	f32		Red() const								{ return m_fRed; }
	f32 	Green() const 							{ return m_fGreen; }
	f32 	Blue() const							{ return m_fBlue; }
	f32 	R() const								{ return Red(); }	
	f32 	G() const								{ return Green(); }	
	f32 	B() const								{ return Blue(); }
	void	Red( f32 fRed );
	void	Green( f32 fGreen );
	void	Blue( f32 fBlue );
	void	R( f32 fRed )							{ Red( fRed ); }
	void	G( f32 fGreen )							{ Green( fGreen ); }
	void	B( f32 fBlue )							{ Blue( fBlue ); }
	void	RedGreenBlue( f32 fR, f32 fG, f32 fB )	{ Red( fR ); Green( fG ); Blue( fB ); }

private:
	CColor();
	
	f32 m_fRed;
	f32 m_fGreen;
	f32 m_fBlue;
};

#endif
