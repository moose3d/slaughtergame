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
#include <COpenGLDemo.h>
#include "CNetworkManager.h"
#include "CPlayer.h"
#include "Demo.h"

COBJModel g_ShipModel;
CTexture  g_ShipTextures[21];
CTexture  g_Plasma;
CTexture  g_Background;
CScreenParams g_ScreenParams;
Vector4D  g_Planes[4]; // bounding planes for our visible game area
Vector3D  g_CornerPoints[2];
Vector2D  g_AreaDimensions;
CTexture  g_Explosion;
CNetworkManager g_NetworkManager;
CPlayer         g_Player;
bool *			g_pAppRunning;

const char *g_aszTextureNames[] =
{
		"textures/cinfa.tga",
		"textures/idolknight.tga",
		"textures/krulspeld2.tga",
		"textures/lordshadow.tga",
		"textures/shadee.tga",
		"textures/crono782.tga",
		"textures/jodomatis.tga",
		"textures/krulspeld3.tga",
		"textures/psionic.tga",
		"textures/snaz12.tga",
		"textures/wilko.tga",
		"textures/cubik.tga",
		"textures/kaoskiwi.tga",
		"textures/krulspeld4.tga",
		"textures/pyschicparrot.tga",
		"textures/snazf1.tga",
		"textures/freelancer.tga",
		"textures/krulspeld1.tga",
		"textures/krulspeld5.tga",
		"textures/robin.tga",
		"textures/thor.tga",
		NULL
};
int OnWhichSideOfPlane( const Vector3D & point, const Vector4D & plane )
{
 	  const Vector3D & normal = plane.GetVector3D();
 	  float fDistance = Dot(normal, point) + plane.w;

  	  if      ( fDistance > 0.001  ) return  1;
  	  else if ( fDistance < -0.001 ) return -1;
  	  else return 0;
}

void Lerp( const Vector3D & start, const Vector3D & end, float fRatio, Vector3D & result)
{
	result = start + ((end - start) * fRatio);
}
void Lerp( float fStart, float fEnd, float fRatio, float & fResult )
{
	fResult = fStart + ((fEnd - fStart) * fRatio);
}
