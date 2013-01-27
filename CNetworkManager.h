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
///////////////////////////////////////////////////////////////////////////////
#ifndef CNETWORKMANAGER_H_
#define CNETWORKMANAGER_H_
///////////////////////////////////////////////////////////////////////////////
#include <SDL.h>
#include <SDL_net.h>
#include <cassert>
#include <map>
#include <list>
#include <string>
#include "globals.h"
class CPlayer;
class CShip;
///////////////////////////////////////////////////////////////////////////////
#pragma pack(push)
#pragma pack(pop)
///////////////////////////////////////////////////////////////////////////////
class CNetworkManager
{
protected:

public:
	CNetworkManager();
	virtual ~CNetworkManager();
};
#endif /* CNETWORKMANAGER_H_ */
