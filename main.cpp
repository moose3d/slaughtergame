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
////////////////////////////////////////////////////////////////////////////////
void PrintUsage( const char *prog)
{
	cout << "Usage: \n" << prog << " [networkrole] [playername] <sfx>\n\n";
	cout << "OPTIONS:\n\t networkrole\t\t either 'server' or 'client'\n";
	cout << "\t playername\t\t " << "player name, max length " << PLAYER_NAME_LENGTH << " characters" << endl;
	cout << "\t sfx\t\t " << "(optional) nosound" << endl;
}
////////////////////////////////////////////////////////////////////////////////
int main( int argc, char **argv )
{
	if ( argc < 3 )
	{
	    PrintUsage(argv[0]);
	    return -1;
	}

	if ( argc >= 4 )
	{
	 	g_Application.m_bSounds = !(strcmp("nosound", argv[3]) == 0);
	}

	g_Application.OpenScreen();
	g_Application.Initialize();







  while( g_Application.IsRunning() )
  {
    
	g_Application.GetTimer().Update();
    g_Application.HandleEvents();
	g_Application.RenderScene();
	g_Application.Update();
    g_Application.GetTimer().Reset();
	SLEEP(1); 
    
  }
  return 0;
}
////////////////////////////////////////////////////////////////////////////////
