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


#ifndef CMESSAGEQUEUE_H_
#define CMESSAGEQUEUE_H_
///////////////////////////////////////////////////////////////////////////////
#include <queue>
#include <string>
#include <COpenGLDemo.h>
#include <ftgl.h>
#include <FTGLTextureFont.h>
#include <SDL.h>
///////////////////////////////////////////////////////////////////////////////
using namespace std;
///////////////////////////////////////////////////////////////////////////////
class CMessageQueue : public std::list<string>,
					  public IRenderable,
					  public CMutexProtected
{
protected:
	size_t  			m_nSize;
	FTGLTextureFont *	m_pFont;

public:
	CMessageQueue( size_t nSize, FTGLTextureFont *	pFont );
	virtual ~CMessageQueue();
	void push( const string & str);
	void Render();
};
///////////////////////////////////////////////////////////////////////////////
#endif /* CMESSAGEQUEUE_H_ */