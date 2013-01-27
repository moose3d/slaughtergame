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


#ifndef CCUBICSPLINEEVALUATOR_H_
#define CCUBICSPLINEEVALUATOR_H_
#include <Vector3D.h>
class CCubicSpline {
protected:
	Vector3D m_vPoints[4];
public:
	CCubicSpline();
	CCubicSpline(const Vector3D & p0, const Vector3D & p1, const Vector3D & p2, const Vector3D & p3 );
	virtual ~CCubicSpline();
	Vector3D Evaluate(float fT );
	void SetPoints( const Vector3D & p0, const Vector3D & p1, const Vector3D & p2, const Vector3D & p3 );
};

#endif /* CCUBICSPLINEEVALUATOR_H_ */
