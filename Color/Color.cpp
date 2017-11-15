//
//  Color.cpp
//  Color
//
//  Created by Me on 5/9/12.
//  Copyright (c) 2012 Shoejunk Industries. All rights reserved.
//

#include "Color.h"
#include <assert.h>

CColor::CColor( f32 fRed, f32 fGreen, f32 fBlue )
	: m_fRed( fRed )
	, m_fGreen( fGreen )
	, m_fBlue( fBlue )
{
	assert( fRed >= 0.f );
	assert( fRed <= 1.f );
	assert( fGreen >= 0.f );
	assert( fGreen <= 1.f );
	assert( fBlue >= 0.f );
	assert( fBlue <= 1.f );
}

void CColor::Red( f32 fRed )
{
	assert( fRed >= 0.f );
	assert( fRed <= 1.f );
	m_fRed = fRed; 
}

void CColor::Green( f32 fGreen )
{ 
	assert( fGreen >= 0.f );
	assert( fGreen <= 1.f );
	m_fGreen = fGreen; 
}

void CColor::Blue( f32 fBlue )
{ 
	assert( fBlue >= 0.f );
	assert( fBlue <= 1.f );
	m_fBlue = fBlue; 
}

CColor::CColor()
{
	assert( false );
}
