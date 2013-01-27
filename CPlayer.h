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

#ifndef __CPlayer_h__
#define __CPlayer_h__
#include "globals.h"
#include <SDL_net.h>
class CShip;
////////////////////////////////////////////////////////////////////////////////
class CPlayer
{
public:
	char      m_szName[PLAYER_NAME_LENGTH];
	CShip	  *m_pShip;
	uint8_t   m_Id;
	IPaddress address;
	bool      m_bConnectionAlive; ///< Used to determine if client disconnects abruptly
	size_t    m_nDeaths;
public:
	CPlayer()							{	m_pShip = NULL;	SetConnectionAlive(true); m_nDeaths= 0;}
	virtual ~CPlayer()					{    }
	void SetShip( CShip * pShip )		{	m_pShip = pShip;	}
	CShip * GetShip() 					{ 	return m_pShip; 	}
	void SetName( const char *szName )	{	strncpy( m_szName, szName, PLAYER_NAME_LENGTH);	}
	char * GetName()					{	return m_szName;	}
	void SetID( uint8_t id )			{	m_Id = id;	}
	uint8_t GetID() 					{ return m_Id; }
	IPaddress GetAddress()              { return address; }
	void SetAddress( IPaddress & addr ) { address = addr; }
	void SetConnectionAlive( bool bFlag )         { m_bConnectionAlive = bFlag; }
	bool IsConnectionAlive() const      { return m_bConnectionAlive; }

	void IncreaseDeathCount() { ++m_nDeaths; }
	size_t GetDeathCount()    { return m_nDeaths; }
	void   SetDeathCount( size_t val ) { m_nDeaths = val ; }
	void ResetDeathCount()    { m_nDeaths = 0;}
};
////////////////////////////////////////////////////////////////////////////////
#endif
