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

#include <cassert>
#include <sstream>
#include "CMessageQueue.h"
#include "globals.h"
#include "CNetworkManager.h"
///////////////////////////////////////////////////////////////////////////////
CMessageQueue::CMessageQueue(size_t nSize, FTGLTextureFont *pFont  ) : m_nSize(nSize),m_pFont(pFont)
{
	assert(m_pFont != NULL);
}
///////////////////////////////////////////////////////////////////////////////
CMessageQueue::~CMessageQueue()
{

}
///////////////////////////////////////////////////////////////////////////////
void
CMessageQueue::push( const string & str )
{
	Lock();
	ostringstream s;
	//s <<"[ " << g_NetworkManager.GetTicksInServerTime( SDL_GetTicks() ) << " ] " + str;
	push_front( s.str() );
	while ( size() > m_nSize ) pop_back();
	Unlock();
}
///////////////////////////////////////////////////////////////////////////////
void
CMessageQueue::Render()
{
	Lock();
	std::list<string>::iterator it = begin();
	glEnable(GL_BLEND);
	float fAlpha = 1.0;
	float fAlphaDecrement = 1.0f/m_nSize;
	glPushMatrix();
		for( ; it != end(); it++)
		{
			glTranslatef(0, m_pFont->FaceSize(),0);
			glColor4f(1,1,1,fAlpha );
			m_pFont->Render(it->c_str());
			fAlpha -= fAlphaDecrement;
		}
	glPopMatrix();
	Unlock();
	glDisable(GL_BLEND);
}
///////////////////////////////////////////////////////////////////////////////
