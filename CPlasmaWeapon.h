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



#ifndef CPLASMAWEAPON_H_
#define CPLASMAWEAPON_H_
#include <COpenGLDemo.h>
#define NUM_PARTICLES 50
class CShip;
///////////////////////////////////////////////////////////////////////////////
typedef CParticleSystem<NUM_PARTICLES,
	CCompletePolicy< CParticle, CSizeInitializer<CParticle>, CVelocityInitializer<CParticle>,	CEnergyInitializer<CParticle>,CPositionInitializer<CParticle> >,
	CCompletePolicy< CParticle, CNullPolicy<CParticle>,      CMoveAction<CParticle>, CEnergyAction<CParticle>, CNullPolicy<CParticle> >, CParticle> WeaponParticleSystem;
///////////////////////////////////////////////////////////////////////////////
class CPlasmaWeapon : public IRenderable
{
protected:
	WeaponParticleSystem m_PS;
	Vector3D			 m_PointPositions[NUM_PARTICLES];
	CTexture *           m_pTexture;

public:
	float               m_fCharge;
	float               m_fChargeRate;
	float 				m_fSpeed;
	float 				m_fDistance;
	const Vector3D * 	m_pMountPosition;

	CPlasmaWeapon( const Vector3D *pMountPosition ); ///< Attach this position to where your ship position.
	virtual ~CPlasmaWeapon();
	void Fire( const Vector3D & heading, const Vector3D & velocity );
	void FireAbsolute( const Vector3D & position, const Vector3D & velocity );
	void Update( float fSeconds );
	void Render();
	void SetTexture( CTexture *pTex );
	bool CheckHits( CShip *pShip );
};
///////////////////////////////////////////////////////////////////////////////
#endif /* CPLASMAWEAPON_H_ */
