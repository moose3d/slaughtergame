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
#ifndef GLOBALS_H_
#define GLOBALS_H_
#include <COpenGLDemo.h>
class CNetworkManager;
class CPlayer;
class Demo;
extern COBJModel g_ShipModel;
extern CTexture  g_ShipTextures[21];
extern CTexture  g_Plasma;
extern CTexture  g_Explosion;
extern CTexture  g_Background;
extern CScreenParams g_ScreenParams;
enum { LEFT, RIGHT, BOTTOM, TOP };
extern Vector4D  g_Planes[4]; // bounding planes for our visible game area
extern Vector3D  g_CornerPoints[2];
extern Vector2D  g_AreaDimensions;
extern const char *g_aszTextureNames[];
extern CNetworkManager g_NetworkManager;
extern bool * 		   g_pAppRunning;
#define g_Application (*Demo::GetInstance())

/*player id for unknown */
#define UNKNOWN_PLAYER    0

#define PLAYER_NAME_LENGTH 25
#define SERVER_PORT 12345
#define MAX_PLAYERS 2
int OnWhichSideOfPlane( const Vector3D & point, const Vector4D & plane );
// Linear interpolation for vectors.
void Lerp( const Vector3D & start, const Vector3D & end, float fRatio, Vector3D & result);
void Lerp( float fStart, float fEnd, float fRatio, float & fResult );
#define TURN_LEFT          1
#define TURN_RIGHT         2
////////////////////
/// Returns a random value between min and max (included).
template <typename Type>
inline Type GetRandom( Type min, Type max )
{
  Type val = max - min ;
  if ( min == max)
	return min;
  return  min + (Type)( val *(rand() / (RAND_MAX+1.0f)));
}
////////////////////
#ifdef WIN32
#pragma warning( disable : 4244 4305 4996 )
#endif

#define SLEEP(T) SDL_Delay(T)

// Fancy tweak to get speed same for Linux and Windows. Blah, it was all about debug output.
#ifdef WIN32
#define SPEED_FUDGE_FACTOR 1.0
#else
#define SPEED_FUDGE_FACTOR 1.0
#endif

#endif /* GLOBALS_H_ */
