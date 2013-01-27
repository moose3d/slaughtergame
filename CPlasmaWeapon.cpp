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

#include "CPlasmaWeapon.h"
#include "CNetworkManager.h"
#include "CShip.h"
#include "globals.h"
#include "Demo.h"
#include <cassert>
///////////////////////////////////////////////////////////////////////////////
CPlasmaWeapon::CPlasmaWeapon( const Vector3D *pMountPosition )
{
	m_PS.m_InitializePolicy.m_SizePolicy.m_fSize = 12.0;
	m_PS.m_InitializePolicy.m_EnergyPolicy.m_fEnergy = 1.0;
	m_fSpeed = 210.0;

	m_pMountPosition = pMountPosition;
	assert(m_pMountPosition != NULL && "Mount position of weapon must not be NULL!!!");
	m_fCharge = 1.0;
	m_fChargeRate = 4.0;
}
///////////////////////////////////////////////////////////////////////////////
CPlasmaWeapon::~CPlasmaWeapon()
{

}
///////////////////////////////////////////////////////////////////////////////
void
CPlasmaWeapon::Fire( const Vector3D & heading, const Vector3D & velocity )
{
	if ( m_fCharge >= 1.0 )
	{

		 FireAbsolute( *m_pMountPosition + heading * 20.0, heading * m_fSpeed + velocity );
		 //if ( g_NetworkManager.IsRunning() )
		 //{
		   // send same information through network
		 //}
	}
}
///////////////////////////////////////////////////////////////////////////////
void
CPlasmaWeapon::FireAbsolute( const Vector3D & pos, const Vector3D & velocity )
{
	if ( m_fCharge >= 1.0 )
	{
		m_PS.m_InitializePolicy.m_VelocityPolicy.m_vVelocity = velocity;
		m_PS.m_InitializePolicy.m_PositionPolicy.m_vPosition = pos;
		m_PS.Init(1);
		m_fCharge = 0.0;
		g_Application.m_SoundServer.Play("fire");
	}
}
///////////////////////////////////////////////////////////////////////////////
void
CPlasmaWeapon::Update( float fSeconds )
{
	m_PS.Update(fSeconds);

	for( size_t i=0;i<m_PS.GetAliveCount();i++ )
	{
		Vector3D & pos = const_cast<Vector3D &>(m_PS.GetParticles()[i].m_vPosition);
		if ( OnWhichSideOfPlane( pos , g_Planes[LEFT] ) == -1 ) pos.x += g_AreaDimensions.x;
		if ( OnWhichSideOfPlane( pos , g_Planes[RIGHT] ) == -1 ) pos.x -= g_AreaDimensions.x;
		if ( OnWhichSideOfPlane( pos , g_Planes[TOP] ) == -1 )    pos.z  += g_AreaDimensions.y;
		if ( OnWhichSideOfPlane( pos , g_Planes[BOTTOM] ) == -1 ) pos.z  -= g_AreaDimensions.y;

		m_PointPositions[i] = pos;

	}
	if (m_fCharge < 1.0 )
		m_fCharge += m_fChargeRate*fSeconds;

}
///////////////////////////////////////////////////////////////////////////////
void
CPlasmaWeapon::Render()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glColor4f(1.0,1.0,1.0,1.0);
	glEnableClientState(GL_VERTEX_ARRAY);
	if ( m_pTexture ) m_pTexture->Apply();
	glEnable(GL_POINT_SPRITE);
	glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
	glPointSize(60.0);

	glVertexPointer(3, GL_FLOAT, 0, reinterpret_cast<const float *>(m_PointPositions));
	glDrawArrays( GL_POINTS, 0, m_PS.GetAliveCount());
	glDisable(GL_POINT_SPRITE);
	glDisableClientState( GL_VERTEX_ARRAY );
	glPointSize(1.0);
	glDepthMask(GL_TRUE);
}
///////////////////////////////////////////////////////////////////////////////
void
CPlasmaWeapon::SetTexture( CTexture *pTex )
{
	m_pTexture = pTex;
}
///////////////////////////////////////////////////////////////////////////////
bool
CPlasmaWeapon::CheckHits( CShip *pShip )
{
	bool retval = false;
	if ( !pShip ) return retval;

	const Vector3D & spherePos= pShip->GetBoundingSphere().GetPosition();
	float radius = pShip->GetBoundingSphere().GetRadius();

	for( size_t i=0;i<m_PS.GetAliveCount();i++ )
	{
		Vector3D & pos = const_cast<Vector3D &>(m_PS.GetParticles()[i].m_vPosition);
		if ( Magnitude(pos - spherePos) < radius )
		{
			retval = true;
			// mark particle dead
			const_cast<CParticle &>(m_PS.GetParticles()[i]).m_fEnergy = 0.0f;
		}

	}
	return retval;
}
