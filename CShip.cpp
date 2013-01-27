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
#include "CShip.h"
#include "Demo.h"
#include <cassert>
///////////////////////////////////////////////////////////////////////////////
CShip::CShip() : m_Weapon(&m_Position)
  {
	  m_vVelocity.x = 0;
	  m_vVelocity.y = 0;
	  m_vVelocity.z = 0;

	  m_bTurningLeft = false;
	  m_bTurningRight = false;
	  m_bAccelerating = false;
	  m_bDeaccelerating = false;
	  m_fTurningSpeed = 400.0f;
	  m_fAcceleration = 100.0f;
	  m_bFiring = false;

	  m_bAlive = true;
	  m_fExplosionScale = 1.0;
	  m_fExplosionScaleRate = 1.1f;
	  m_fExplosionAlpha = 1.0;
	  m_fExplosionActive = 0.0;
	  m_bEnemyControlled = false;
	  m_PlayerId = 0;

	  // for liding ship back to proper position
	  m_fRemainingSlideTime = 0.0f;
	  m_fSlideTime = 0.5f; // seconds
	  m_bSliding = false;

  }
///////////////////////////////////////////////////////////////////////////////
CShip::~CShip()
{

}
///////////////////////////////////////////////////////////////////////////////
void
CShip::SetEnemyControlled( bool bFlag )
{
  m_bEnemyControlled = bFlag;
}
///////////////////////////////////////////////////////////////////////////////
CPlasmaWeapon &
CShip::GetWeapon()
{
  return m_Weapon;
}
///////////////////////////////////////////////////////////////////////////////
void
CShip::Update( float fSeconds )
{
	fSeconds *= SPEED_FUDGE_FACTOR;
	//cout << "Update call" << endl;
	Lock();
	float fMag = Magnitude(m_vVelocity);

	if ( fMag > 200.0f  )
	{
		m_vVelocity /= fMag;
		m_vVelocity *= 200.0f;
	}
	//cout << "Speed: " << Magnitude(m_vVelocity) << endl;
	m_Position += m_vVelocity * fSeconds;

	if ( m_bAccelerating && !m_bDeaccelerating )		 ApplyForce( GetHeading()*m_fAcceleration*fSeconds);
	else if ( !m_bAccelerating && m_bDeaccelerating )	 ApplyForce( GetHeading()*-m_fAcceleration*fSeconds);

	if ( m_bTurningLeft && ! m_bTurningRight )
	{
		Vector3D & rot = GetRotation();
		rot.y += m_fTurningSpeed * fSeconds;

		if ( rot.y >= 360.0f ) rot.y -= 360.0f;
			SetRotation( rot );
	}
	else if ( !m_bTurningLeft&& m_bTurningRight )
	{
		Vector3D & rot = GetRotation();
		rot.y -= m_fTurningSpeed *fSeconds;

		if ( rot.y < 0.0f ) rot.y += 360.0f;
			SetRotation( rot );
	}

	if ( m_bFiring)
	{
	 m_Weapon.Fire( GetHeading(), m_vVelocity);
	}
	Unlock();
	//cout << "ship local velocity : " << GetVelocity() << endl;
	m_Weapon.Update(fSeconds);

	Lock();
	GetBoundingSphere().SetPosition(GetPosition());
	GetBoundingSphere().SetRadius(15.0f);
	// change actual location depending on which border has been crossed
	{
		Vector3D & pos = GetPosition();
		if (      GetBoundingSphere().OnWhichSideOfPlane( g_Planes[LEFT]) == -1) 	 pos.x += g_AreaDimensions.x;
		else if ( GetBoundingSphere().OnWhichSideOfPlane( g_Planes[RIGHT]) == -1 )	 pos.x -= g_AreaDimensions.x;

		if (      GetBoundingSphere().OnWhichSideOfPlane( g_Planes[TOP]) == -1 )	 pos.z += g_AreaDimensions.y;
		else if ( GetBoundingSphere().OnWhichSideOfPlane( g_Planes[BOTTOM]) == -1 ) pos.z -= g_AreaDimensions.y;

		SetPosition(pos);
	}
	{
		Vector3D & pos = GetDisplayPosition();
		if (      GetBoundingSphere().OnWhichSideOfPlane( g_Planes[LEFT]) == -1) 	 pos.x += g_AreaDimensions.x;
		else if ( GetBoundingSphere().OnWhichSideOfPlane( g_Planes[RIGHT]) == -1 )	 pos.x -= g_AreaDimensions.x;

		if (      GetBoundingSphere().OnWhichSideOfPlane( g_Planes[TOP]) == -1 )	 pos.z += g_AreaDimensions.y;
		else if ( GetBoundingSphere().OnWhichSideOfPlane( g_Planes[BOTTOM]) == -1 ) pos.z -= g_AreaDimensions.y;

		SetDisplayPosition(pos);
	}

	if ( m_fRemainingSlideTime <= 0.0f )
	{
		m_vDisplayPosition = m_Position;
		m_vDisplayRotation = m_Rotation;
		m_vDisplayVelocity = GetVelocity();
	}
	else
	{
		Vector3D newpos;
		float fRatio = 1.0-(m_fRemainingSlideTime / m_fSlideTime);
		Lerp( m_vDisplayPosition, m_vSlideToDestination, fRatio, newpos);
		//newpos = m_Spline.Evaluate( fRatio );

		m_vDisplayPosition = newpos;
		m_vDisplayRotation = m_Rotation;
		m_fRemainingSlideTime-= fSeconds;


		//Lerp( m_vDisplayRotation.y, m_Rotation.y, fRatio, m_vDisplayRotation.y );

	}

	if ( !m_bAlive )
	{
		m_fExplosionActive += fSeconds;
		m_fExplosionScale += m_fExplosionScaleRate * m_fExplosionScaleRate * fSeconds;
		m_fExplosionScaleRate += 100.0 * fSeconds;
		if ( m_fExplosionActive > 0.5 )
			m_fExplosionAlpha -= 2*fSeconds;
	}
	Unlock();
}
///////////////////////////////////////////////////////////////////////////////
void CShip::RenderShip( float xOffset, float zOffset )
{
//	  glPushMatrix();
//	        glTranslatef( m_Position.x+xOffset, m_Position.y, m_Position.z+zOffset);
//	        glRotatef( m_Rotation.z, 0, 0, 1 );
//	        glRotatef( m_Rotation.y, 0, 1, 0 );
//	        glRotatef( m_Rotation.x, 1, 0, 0);
//	        glScalef( m_fScale, m_fScale, m_fScale );
//	        if ( m_pMesh ) m_pMesh->Render();
//	  glPopMatrix();
  glPushMatrix();
			glTranslatef( m_vDisplayPosition.x+xOffset, m_vDisplayPosition.y, m_vDisplayPosition.z+zOffset);
			glRotatef( m_vDisplayRotation.z, 0, 0, 1 );
			glRotatef( m_vDisplayRotation.y, 0, 1, 0 );
			glRotatef( m_vDisplayRotation.x, 1, 0, 0);
			glScalef( m_fScale, m_fScale, m_fScale );
			if ( m_pMesh ) m_pMesh->Render();
	  glPopMatrix();
}
///////////////////////////////////////////////////////////////////////////////
void CShip::Render()
{
	//cout << "Render call:" << endl;
  if ( !m_bAlive ) {

	  glEnable(GL_DEPTH_TEST);
	  glDepthMask(GL_FALSE);
	  if ( m_fExplosionAlpha <= 0.0f ) return;
	  Lock();
	  glEnable(GL_BLEND);
	  g_Explosion.Apply();
	glPushMatrix();
		glTranslatef( m_vDisplayPosition.x, m_vDisplayPosition.y, m_vDisplayPosition.z);
		glScalef(m_fExplosionScale,0,m_fExplosionScale*0.5);
		glColor4f( 1,1,1, m_fExplosionAlpha );
		glBegin(GL_QUADS);
			glTexCoord2f(0,0); glVertex3f(-1,0,1);
			glTexCoord2f(1,0); glVertex3f( 1,0,1);
			glTexCoord2f(1,1); glVertex3f( 1,0,-1);
			glTexCoord2f(0,1); glVertex3f(-1,0,-1);
		glEnd();
	glPopMatrix();
	 glDisable(GL_BLEND);
	 Unlock();
	return;
  }
  glColor4f( 1.0,1.0,1.0,1.0 );
  glDisable(GL_BLEND);
  glDepthMask(GL_TRUE);
  if ( m_pTexture ) m_pTexture->Apply();
  if ( m_pShader ) m_pShader->Apply();

  Lock();

	  RenderShip(0,0);

	//      glPushMatrix();
	//              glTranslatef( m_Position.x, m_Position.y, m_Position.z);
	//              glDisable(GL_TEXTURE_2D);
	//              glRotatef(90,1,0,0);
	//              gluDisk(m_pSphere, 0, GetBoundingSphere().GetRadius(), 24,1 );
	//      glPopMatrix();
	//      glEnable(GL_TEXTURE_2D);


	  bool bIntersectsLeft   = GetBoundingSphere().Intersects( g_Planes[LEFT]) ;
	  bool bIntersectsRight  = GetBoundingSphere().Intersects( g_Planes[RIGHT] );
	  bool bIntersectsTop    = GetBoundingSphere().Intersects( g_Planes[TOP]   );
	  bool bIntersectsBottom = GetBoundingSphere().Intersects( g_Planes[BOTTOM]);
	  bool bDrawCorners = false;

	  if      ( bIntersectsLeft  && bIntersectsTop    )	bDrawCorners = true;
	  else if ( bIntersectsLeft  && bIntersectsBottom )	bDrawCorners = true;
	  else if ( bIntersectsRight && bIntersectsTop    )	bDrawCorners = true;
	  else if ( bIntersectsRight && bIntersectsBottom )	bDrawCorners = true;

	  // corners need additional drawing (ship is visible in four points at once)
	  if ( bDrawCorners )
	  {
		  RenderShip(  g_AreaDimensions.x, g_AreaDimensions.y);
		  RenderShip(  g_AreaDimensions.x,-g_AreaDimensions.y);
		  RenderShip( -g_AreaDimensions.x, g_AreaDimensions.y);
		  RenderShip( -g_AreaDimensions.x,-g_AreaDimensions.y);


	  }

	  // Render objects to "other side" when they are crossing the boundary
	  if ( bIntersectsLeft )		RenderShip( g_AreaDimensions.x,0);
	  if ( bIntersectsRight )		RenderShip(-g_AreaDimensions.x,0);
	  if ( bIntersectsTop)		RenderShip( 0, g_AreaDimensions.y);
	  if ( bIntersectsBottom )	RenderShip( 0,-g_AreaDimensions.y);
  //cout << "Ship position " << GetDisplayPosition() << endl;
  Unlock();
  glUseProgram(0);
}
///////////////////////////////////////////////////////////////////////////////
void
CShip::ApplyForce( const Vector3D & vForce )
{
  m_vVelocity += vForce;
}
///////////////////////////////////////////////////////////////////////////////
void
CShip::Accelerate() { m_bAccelerating = true; m_bDeaccelerating = false; }
///////////////////////////////////////////////////////////////////////////////
void
CShip::Deacclerate() { m_bDeaccelerating = true; m_bAccelerating = false;}
///////////////////////////////////////////////////////////////////////////////
void
CShip::StopAccelerating() { m_bDeaccelerating = false; m_bAccelerating = false;}
///////////////////////////////////////////////////////////////////////////////
void
CShip::SetTurningLeft(bool value ) { m_bTurningLeft = value; }
///////////////////////////////////////////////////////////////////////////////
void
CShip::SetTurningRight(bool value ) { m_bTurningRight = value; }
///////////////////////////////////////////////////////////////////////////////
bool
CShip::IsTurningLeft() const { return m_bTurningLeft; }
///////////////////////////////////////////////////////////////////////////////
bool
CShip::IsTurningRight() const { return m_bTurningRight; }
///////////////////////////////////////////////////////////////////////////////
void
CShip::StartShooting() 
{ 
// fixeds bug #0000016
	if ( IsAlive() ) m_bFiring = true; 
}
///////////////////////////////////////////////////////////////////////////////
void
CShip::StopShooting() { m_bFiring = false; }
///////////////////////////////////////////////////////////////////////////////
void
CShip::Die() 
{ 
	
	m_bAlive = false; 
	StopShooting();// fixes bug #0000016 
	m_fExplosionScale = 1.0; 
	m_vVelocity.x = m_vVelocity.y = m_vVelocity.z = 0.0; // fixes bug #0000015
	m_vDisplayVelocity = m_vVelocity;
}
///////////////////////////////////////////////////////////////////////////////
void CShip::Respawn()
{
  m_bAlive = true;
  m_fExplosionActive = 0.0;
  m_fExplosionAlpha = 1.0f;
  m_fExplosionScaleRate = 1.1f;
  GetPosition().x = GetRandom<float>(g_CornerPoints[0].x, g_CornerPoints[1].x);
  GetPosition().y = 0.0f;
  GetPosition().z = GetRandom<float>(g_CornerPoints[0].y, g_CornerPoints[1].y);
  SetDisplayPosition(GetPosition());
}
///////////////////////////////////////////////////////////////////////////////
bool
CShip::IsAlive() const { return m_bAlive; }
///////////////////////////////////////////////////////////////////////////////
Vector3D &
CShip::GetVelocity() { return m_vVelocity; }
///////////////////////////////////////////////////////////////////////////////
void
CShip::SetVelocity( const Vector3D & vel ) { m_vVelocity = vel; }
///////////////////////////////////////////////////////////////////////////////
Vector3D &
CShip::GetDisplayPosition() { return m_vDisplayPosition; }
///////////////////////////////////////////////////////////////////////////////
void
CShip::SetDisplayPosition(const Vector3D & pos) { m_vDisplayPosition = pos; }
///////////////////////////////////////////////////////////////////////////////
Vector3D &
CShip::GetDisplayRotation() { return m_vDisplayRotation; }
///////////////////////////////////////////////////////////////////////////////
void
CShip::SetDisplayRotation(const Vector3D & rot) { m_vDisplayRotation= rot; }
///////////////////////////////////////////////////////////////////////////////
void
CShip::SetRemainingSlideTime(float fSeconds) { m_fRemainingSlideTime = fSeconds; }
///////////////////////////////////////////////////////////////////////////////
float
CShip::GetSlideTime() { return m_fSlideTime; }
///////////////////////////////////////////////////////////////////////////////
void
CShip::SetSlideTime( float fValue ) { m_fSlideTime = fValue; }
///////////////////////////////////////////////////////////////////////////////
float
CShip::GetRemainingSlideTime() { return m_fRemainingSlideTime; }
///////////////////////////////////////////////////////////////////////////////
