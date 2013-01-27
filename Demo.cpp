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
#include "Demo.h"
#include <sstream>
using std::ostringstream;
////////////////////////////////////////////////////////////////////////////////
Demo::Demo()
{
	m_pPlayer = NULL;
    m_pShip = NULL;
    m_bSounds = true;
}
////////////////////////////////////////////////////////////////////////////////
CShip * Demo::CreateShip( unsigned int iTexture )
{
	CShip *pShip = new CShip();
	pShip->SetMesh( &g_ShipModel );
	pShip->SetTexture( &g_ShipTextures[iTexture]);
	pShip->SetPosition( Vector3D(0,0,-5));
	pShip->GetWeapon().SetTexture(&g_Plasma);
	pShip->SetScale( 0.5 );
	GetUpdateables().push_back(pShip);
	return pShip;
}
////////////////////////////////////////////////////////////////////////////////
void Demo::RemoveShip( CShip *pShip )
{
	m_lstShips.remove( pShip );
	GetUpdateables().remove( pShip );
	//remove(GetUpdateables().begin(), GetUpdateables().end(), pShip);
}
////////////////////////////////////////////////////////////////////////////////
CPlayer * Demo::GetPlayer() 				  { return m_pPlayer; 		}
////////////////////////////////////////////////////////////////////////////////
void 		Demo::SetPlayer( CPlayer *pPlayer ) { m_pPlayer = pPlayer; 	}
////////////////////////////////////////////////////////////////////////////////
void Demo::LoadShipsAndTextures()
{
	if ( !g_ShipModel.Load("models/fighter.obj") ) abort();

	for( int i=0; g_aszTextureNames[i];i++ )
	{
		if ( !g_ShipTextures[i].Load(g_aszTextureNames[i]) ) abort();
	}

	
	// before updating
	//GetUpdateables().push_back(m_pShip);

	if ( !g_Plasma.Load("textures/plasma.tga") ) abort();
	if ( !g_Explosion.Load("textures/explosion.tga") ) abort();
	if ( !g_Background.Load("textures/horsehead_nebula.tga") ) abort();
	
	m_pShip = CreateShip(0);

}
////////////////////////////////////////////////////////////////////////////////
void Demo::LoadFonts()
{

  m_pFont = new FTGLTextureFont("HVD_Peace.ttf");
  if ( m_pFont->Error()) abort();
  m_pFont->FaceSize(20);

  m_pFontRegular = new FTGLTextureFont("Vera.ttf");
  if ( m_pFontRegular->Error()) abort();
  m_pFontRegular->FaceSize(18);

  m_pFontSmall= new FTGLTextureFont("Vera.ttf");
  if ( m_pFontSmall->Error()) abort();
  m_pFontSmall->FaceSize(12);
}
////////////////////////////////////////////////////////////////////////////////
void
Demo::LoadSounds()
{
	if ( m_bSounds == false ) return;
	if ( !m_SoundServer.Init() ) abort();
 	if ( !m_SoundServer.LoadMusic( "theme", "music/music.ogg")) abort();
 	if ( !m_SoundServer.Load( "fire", "sounds/laser.wav")) abort();
}
////////////////////////////////////////////////////////////////////////////////
bool Demo::Initialize()
{
  LoadShipsAndTextures();
  LoadFonts();
  m_pMessages = new CMessageQueue( 10, m_pFontSmall );
  g_pAppRunning = &m_bRunning;
  m_Camera.SetProjection(PERSPECTIVE);
  m_Camera.RotateX(-90);
  m_Camera.MoveY(600);
  m_Camera.SetViewport(0,0,g_ScreenParams.width, g_ScreenParams.height);

  // bottom left corner
  g_CornerPoints[0].x = -315.0;
  g_CornerPoints[0].y = 0.0;
  g_CornerPoints[0].z = 235.0f;

  // top right corner
  g_CornerPoints[1].x = 315.0f;
  g_CornerPoints[1].y = 0.0f;
  g_CornerPoints[1].z = -235.0f;

  // compute area dimensions
  g_AreaDimensions.x = g_CornerPoints[1].x - g_CornerPoints[0].x;
  g_AreaDimensions.y = g_CornerPoints[0].z - g_CornerPoints[1].z;

  // compute plane equations
  g_Planes[LEFT]   = Vector4D( 1, 0, 0, -Dot(g_CornerPoints[0], Vector3D( 1, 0, 0)));
  g_Planes[RIGHT]  = Vector4D(-1, 0, 0, -Dot(g_CornerPoints[1], Vector3D(-1, 0, 0)));
  g_Planes[TOP]    = Vector4D( 0, 0, 1, -Dot(g_CornerPoints[1], Vector3D( 0, 0, 1)));
  g_Planes[BOTTOM] = Vector4D( 0, 0,-1, -Dot(g_CornerPoints[0], Vector3D( 0, 0,-1)));
  // disable key repeat initially
  SDL_EnableKeyRepeat( 0, SDL_DEFAULT_REPEAT_INTERVAL);
  m_Timer.Reset();

  SetWindowCaption( "Slaughter" );
  m_pMessages->push("Welcome to Slaughter!");
  m_pMessages->push("Welcome to Slaughter!");
  m_pMessages->push("Welcome to Slaughter!");
  m_pMessages->push("Welcome to Slaughter!");
  LoadSounds();
  m_SoundServer.PlayMusic("theme");
  return true;
}
////////////////////////////////////////////////////////////////////////////////

void Demo::PreRender()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT  );
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,g_ScreenParams.width, 0, g_ScreenParams.height,-1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	g_Background.Apply();
	glBegin(GL_QUADS);
		glTexCoord2f(0,1);glVertex2f(0,0);
		glTexCoord2f(1,1);glVertex2f(g_ScreenParams.width,0);
		glTexCoord2f(1,0);glVertex2f(g_ScreenParams.width,g_ScreenParams.height);
		glTexCoord2f(0,0);glVertex2f(0,g_ScreenParams.height);
	glEnd();

	m_Camera.Apply();
	glDepthMask(GL_TRUE);
	glDisable(GL_TEXTURE_2D);
}
////////////////////////////////////////////////////////////////////////////////
void Demo::OnQuit( SDL_QuitEvent & ev )
{
  SetRunning(false);


}
////////////////////////////////////////////////////////////////////////////////
void Demo::OnKeyUp( SDL_KeyboardEvent & ev )
{
  switch(ev.keysym.sym)
  {
  case SDLK_UP:
  case SDLK_DOWN:
	  m_pShip->StopAccelerating();
	break;
  case SDLK_LEFT:
	  m_pShip->SetTurningLeft(false);
	  break;
  case SDLK_RIGHT:
	  m_pShip->SetTurningRight(false);
	  break;
 case SDLK_SPACE:
	  m_pShip->StopShooting();
	  break;
 case SDLK_RETURN:
	 if ( !m_pShip->IsAlive() )
	 {
	   m_pShip->Respawn();
	 }
	 break;
  default:
	  break;
  }
}
////////////////////////////////////////////////////////////////////////////////
void Demo::OnKeyDown( SDL_KeyboardEvent & ev )
{
  switch(ev.keysym.sym)
  {
  case SDLK_UP:
	  m_pShip->Accelerate();
	  break;
  case SDLK_DOWN:
	  m_pShip->Deacclerate();
	break;
  case SDLK_LEFT:
	  m_pShip->SetTurningLeft(true);
	  break;
  case SDLK_RIGHT:
	  m_pShip->SetTurningRight(true);
	  break;
  case SDLK_SPACE:
	  m_pShip->StartShooting();
	  break;
	  
	  

	  break;
  default:
	  break;
  }
}
////////////////////////////////////////////////////////////////////////////////
void Demo::Update( )
{
	COpenGLDemo::Update();
	ShipList::iterator it = m_lstShips.begin();
	// O(#ships), but assuming that there won't be millions of players, we should be fine.
	for( ; it != m_lstShips.end(); it++)
	{
		if ( (*it)->GetWeapon().CheckHits( m_pShip ) )
		{
			if ( m_pShip->IsAlive() ) // this ensures that only one hit actually counts.
			{
			        GetPlayer()->IncreaseDeathCount();
				ostringstream s;
				s << "Player '" << GetPlayer()->GetName() << " died.";
				m_pShip->Die();
				EnqueueNote(s.str());
			
			}
		}

	}
}
////////////////////////////////////////////////////////////////////////////////
void Demo::Render()
{
  m_pShip->Render();

  ShipList::iterator it = m_lstShips.begin();
  for( ; it != m_lstShips.end(); it++)
  {
	  (*it)->Render();
  }

  m_pShip->GetWeapon().Render();
  it = m_lstShips.begin();
  for( ; it != m_lstShips.end(); it++)
  {
	  (*it)->GetWeapon().Render();
  }

  glDisable(GL_TEXTURE_2D);
  glColor3f(0,1,0);
  glBegin(GL_LINE_LOOP);
	  glVertex3f(g_CornerPoints[0].x, 0, g_CornerPoints[0].z);
	  glVertex3f(g_CornerPoints[1].x, 0, g_CornerPoints[0].z);
	  glVertex3f(g_CornerPoints[1].x, 0, g_CornerPoints[1].z);
	  glVertex3f(g_CornerPoints[0].x, 0, g_CornerPoints[1].z);
  glEnd();
  glColor3f(1,1,1);
}
////////////////////////////////////////////////////////////////////////////////
void Demo::PostRender()
{
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glOrtho(0, g_ScreenParams.width, 0, g_ScreenParams.height, -1, 1);
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  glPushMatrix();
  glTranslatef(g_ScreenParams.width-120,20,0);
  {ostringstream s;
  s << "#Ships: ";
  s << m_lstShips.size() + 1;
  m_pFont->Render(s.str().c_str());
  }
  glPopMatrix();


 

  RenderScores();
  // Render messages
  glPushMatrix();
	  glTranslatef(10,10,0);
	  m_pMessages->Render();
  glPopMatrix();

  glDisable(GL_CLIP_PLANE0);
  SDL_GL_SwapBuffers();
}
////////////////////////////////////////////////////////////////////////////////
ScoreQueue &
Demo::GetScoreQueue()
{
	return m_ScoreQueue;
}
////////////////////////////////////////////////////////////////////////////////
void
Demo::RenderScores()
{
        //Construct score queue
        if ( g_Application.GetPlayer() != NULL )
	  GetScoreQueue().push( g_Application.GetPlayer());
	  // Render sorted scores
	  glPushMatrix();
	  glTranslatef(g_ScreenParams.width-100, g_ScreenParams.height-12,0);
	  while ( !GetScoreQueue().empty() )
	  {
		  glTranslatef(0, -12,0);
		  CPlayer *pPlayer = GetScoreQueue().top(); GetScoreQueue().pop();
		  ostringstream s;
		  s << pPlayer->GetName() << " : " << pPlayer->GetDeathCount();
		  m_pFontSmall->Render(s.str().c_str());
	  }
	  glPopMatrix();
}
////////////////////////////////////////////////////////////////////////////////
void
Demo::EnqueueNote(const  string & msg )
{
	m_pMessages->push( msg );
}
////////////////////////////////////////////////////////////////////////////////
