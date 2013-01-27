/*******************************************************************************
 * Copyright (c) 2009 Anssi Gröhn / eNtity at iki dot fi.
 *
 * This file is part of Slaughter game.
 *
 *  Slaughter game is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Slaughter game is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Slaughter game.  If not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************/

///////////////////////////////////////////////////////////////////////////////
#include "CCubicSpline.h"
///////////////////////////////////////////////////////////////////////////////
CCubicSpline::CCubicSpline()
{

}
///////////////////////////////////////////////////////////////////////////////
CCubicSpline::CCubicSpline( const Vector3D & p0, const Vector3D & p1,
							const Vector3D & p2, const Vector3D & p3 )
{
	SetPoints(p0,p1,p2,p3);
}
///////////////////////////////////////////////////////////////////////////////
CCubicSpline::~CCubicSpline()
{

}
///////////////////////////////////////////////////////////////////////////////
Vector3D
CCubicSpline::Evaluate( float fT)
{
	//assert(fT >= 0.0f && fT <= 1.0f && "Value of fT not in range [0,1].");
	if ( fT < 0.0f ) fT = 0.0f;
	else if ( fT > 1.0f ) fT = 1.0f;

	float fMul = 1.0f-fT;
	float fMul_2 = fMul*fMul;
	float fMul_3 = fMul_2*fMul;
	float fT_2 = fT*fT;
	float fT_3 = fT_2*fT;
	return (fMul_3 * m_vPoints[0] + 3.0f*fMul_2*fT*m_vPoints[1] + 3.0f*fMul*fT_2*m_vPoints[2] + fT_3*m_vPoints[3]);
}
///////////////////////////////////////////////////////////////////////////////
void
CCubicSpline::SetPoints( const Vector3D & p0, const Vector3D & p1,
						 const Vector3D & p2, const Vector3D & p3 )
{
	m_vPoints[0] = p0;
	m_vPoints[1] = p1;
	m_vPoints[2] = p2;
	m_vPoints[3] = p3;
}
///////////////////////////////////////////////////////////////////////////////
