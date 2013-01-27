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

#ifndef __CSingleton_h__
#define __CSingleton_h__

template <class T>
class CSingleton
{
/// Static pointer to only instance.
static T *m_pSingleton;
////////////////////
/// Copy constructor.
CSingleton( const CSingleton &ref){}
protected:
////////////////////
/// Default constructor.
CSingleton() {}
////////////////////
/// Destructor.
virtual ~CSingleton() {}
public:
////////////////////
/// Returns a pointer to this singleton.
inline static T *GetInstance()
{
if ( m_pSingleton == NULL )
{
m_pSingleton = new T();
}
return m_pSingleton;
}
/// Destroys this singleton.
inline static void DestroyInstance()
{
if ( m_pSingleton != NULL )
{
delete m_pSingleton;
m_pSingleton = NULL;
}
}
/// Checks is this object instantiated
static bool Exists()
{
return (m_pSingleton != NULL);      
}
};
/////////////////////////////////////////////////////////////////
/// Initialize the static member in the derived classes.
template<class T> T *CSingleton<T>::m_pSingleton = NULL;

#endif
