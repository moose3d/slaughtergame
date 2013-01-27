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


#ifndef DEMO_H_
#define DEMO_H_

#include <COpenGLDemo.h>
#include "CSingleton.h"
#include <iostream>
#include "CShip.h"
#include "globals.h"
#include <list>
#include <ftgl.h>
#include "CPlayer.h"
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include "CMessageQueue.h"
////////////////////////////////////////////////////////////////////////////////
using namespace std;
////////////////////////////////////////////////////////////////////////////////
typedef list<CShip *> ShipList;
typedef vector<std::string> ServerVector;
struct DeathCountOp
{
	inline bool operator()( CPlayer *pOne, CPlayer *pTwo )
	{
		return (pOne->GetDeathCount() > pTwo->GetDeathCount());
	}
};
////////////////////////////////////////////////////////////////////////////////
typedef priority_queue<CPlayer *, vector<CPlayer *>, DeathCountOp > ScoreQueue;
////////////////////////////////////////////////////////////////////////////////
class Demo : public COpenGLDemo,
			 public CSingleton<Demo>
{
	friend class CSingleton<Demo>;
public:
	CPlayer *  			m_pPlayer;
	ShipList 			m_lstShips;
	FTGLTextureFont *	m_pFont;
	FTGLTextureFont *	m_pFontRegular;
	FTGLTextureFont *   m_pFontSmall;
	CShip *           	m_pShip;
	ServerVector      	m_vecServers;
	ScoreQueue   		m_ScoreQueue;
	CMessageQueue		*m_pMessages;
	//string              m_strNote; ///< Note text before sending.
	CSoundServer       m_SoundServer;
	bool               m_bSounds;
	Demo();

	CShip * CreateShip( unsigned int iTexture );
	void RemoveShip( CShip *pShip );
	CPlayer * GetPlayer();
	void 		SetPlayer( CPlayer *pPlayer );
	void LoadShipsAndTextures();
	void LoadFonts();
	void LoadSounds();
	bool Initialize();
	void PreRender();
	void OnQuit( SDL_QuitEvent & ev );
	void OnKeyUp( SDL_KeyboardEvent & ev );
	void OnKeyDown( SDL_KeyboardEvent & ev );
	void Update( );
	void Render();
	void PostRender();
	void RenderScores();
	ScoreQueue & GetScoreQueue();
	void EnqueueNote( const string & msg );
};
#endif /* DEMO_H_ */
