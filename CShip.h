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

#ifndef __CShip_h__
#define __CShip_h__
#include <COpenGLDemo.h>
#include "CPlasmaWeapon.h"
#include "CCubicSpline.h"
////////////////////////////////////////////////////////////////////////////////
#include "globals.h"
////////////////////////////////////////////////////////////////////////////////
class CShip : public CObject3D, public CMutexProtected
{
public:

	Vector3D m_vVelocity;
	bool m_bTurningLeft;
	bool m_bTurningRight;
	bool m_bAccelerating;
	bool m_bDeaccelerating;
	bool m_bFiring;
	float  m_fTurningSpeed;
	float  m_fAcceleration;
	CPlasmaWeapon m_Weapon;

	bool 			m_bAlive;
	float           m_fExplosionScale;
	float           m_fExplosionScaleRate;
	float 			m_fExplosionAlpha;
	float 			m_fExplosionActive;
	bool            m_bEnemyControlled; ///< Is this ship controlled by enemy
	uint8_t			m_PlayerId;

	Vector3D m_vDisplayPosition;
	Vector3D m_vSlideToDestination;
	Vector3D m_vDisplayRotation;
	Vector3D m_vDisplayVelocity;
	CCubicSpline  m_Spline;
	bool     m_bSliding;
	float    m_fRemainingSlideTime;
	float    m_fSlideTime; ///< Time to finish sliding in seconds

  CShip();
  virtual ~CShip();


  void SetEnemyControlled( bool bFlag );


  CPlasmaWeapon & GetWeapon();


  void Update( float fSeconds );


  void RenderShip( float xOffset, float zOffset );

  void Render();

  void ApplyForce( const Vector3D & vForce );


  void Accelerate();
  void Deacclerate();
  void StopAccelerating();

  void SetTurningLeft(bool value );
  void SetTurningRight(bool value );

  bool IsTurningLeft() const;
  bool IsTurningRight() const;

  void StartShooting();
  void StopShooting();

  void Die();
  void Respawn();
  bool IsAlive() const;

  Vector3D & GetVelocity();
  void 		 SetVelocity( const Vector3D & vel );

  Vector3D & GetDisplayPosition();
  void SetDisplayPosition(const Vector3D & pos);

  Vector3D & GetDisplayRotation();
  void SetDisplayRotation(const Vector3D & rot);

  void SetRemainingSlideTime(float fSeconds);
float GetRemainingSlideTime();
  void SetSlideTime( float fSeconds );
  float GetSlideTime();

};
////////////////////////////////////////////////////////////////////////////////
#endif
