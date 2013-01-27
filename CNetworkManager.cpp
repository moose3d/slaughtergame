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
#include "globals.h"
#include "CPlayer.h"
#include <iostream>
#include "CShip.h"
#include "Demo.h"
///////////////////////////////////////////////////////////////////////////////
using namespace std;
///////////////////////////////////////////////////////////////////////////////
// Do not touch these.
const float ROTATION_MIN = -360.0f;
const float ROTATION_MAX =  360.0f;
const float COORD_MIN    = -350.0f;
const float COORD_MAX    =  350.0f;
const float VEL_MIN      = -1000.0;
const float VEL_MAX      = 1000.0;
const float SYNC_TIME    = 0.050;
///////////////////////////////////////////////////////////////////////////////
CNetworkManager::CNetworkManager()
{
}
///////////////////////////////////////////////////////////////////////////////
CNetworkManager::~CNetworkManager()
{
}
///////////////////////////////////////////////////////////////////////////////
