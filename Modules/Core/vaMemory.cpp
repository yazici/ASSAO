///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016, Intel Corporation
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
// documentation files (the "Software"), to deal in the Software without restriction, including without limitation 
// the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of 
// the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
// SOFTWARE.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File changes (yyyy-mm-dd)
// 2016-09-07: filip.strugar@intel.com: first commit (extracted from VertexAsylum codebase, 2006-2016 by Filip Strugar)
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "vaMemory.h"

using namespace VertexAsylum;

#include "IntegratedExternals/vaAssimpIntegration.h"

namespace
{

	struct TempBufferInstance
	{
		VertexAsylum::byte *    Data;
		int                     Size;
		bool                    InUse;

		TempBufferInstance()		
		{ 
			Data = NULL; 
			Size = 0; 
			InUse = false; 
		}
		~TempBufferInstance()	
		{ 
         Destroy( );
		}
		void Create( int size )
		{
			assert( !InUse ); 
			assert( Data == NULL ); 
			Data = new VertexAsylum::byte[ size ];
			Size = size;
		}
      void Destroy( )
      {
         assert( !InUse );
         if( Data != NULL )
            delete[] Data;
         Data = NULL;
         Size = 0;
         InUse = false;
      }
	};
}

// currently only one, simplest possible implementation
static TempBufferInstance		s_tempBuffer;

_CrtMemState s_memStateStart;


void vaMemory::Initialize( )
{
#ifdef VA_ASSIMP_INTEGRATION_ENABLED
    {
        Assimp::Importer importer;

        //unsigned char s_simpleCollada [] = {60,63,120,109,108,32,118,101,114,115,105,111,110,61,34,49,46,48,34,63,62,13,10,60,67,79,76,76,65,68,65,32,120,109,108,110,115,61,34,104,116,116,112,58,47,47,119,119,119,46,99,111,108,108,97,100,97,46,111,114,103,47,50,48,48,53,47,49,49,47,67,79,76,76,65,68,65,83,99,104,101,109,97,34,32,118,101,114,115,105,111,110,61,34,49,46,52,46,49,34,62,13,10,32,32,32,32,60,108,105,98,114,97,114,121,95,99,97,109,101,114,97,115,62,13,10,32,32,32,32,60,47,108,105,98,114,97,114,121,95,99,97,109,101,114,97,115,62,13,10,32,32,32,32,60,108,105,98,114,97,114,121,95,108,105,103,104,116,115,47,62,13,10,32,32,32,32,60,108,105,98,114,97,114,121,95,109,97,116,101,114,105,97,108,115,47,62,13,10,32,32,32,32,60,108,105,98,114,97,114,121,95,101,102,102,101,99,116,115,47,62,13,10,32,32,32,32,60,108,105,98,114,97,114,121,95,103,101,111,109,101,116,114,105,101,115,62,13,10,32,32,32,32,32,32,32,32,60,103,101,111,109,101,116,114,121,32,105,100,61,34,98,111,120,45,108,105,98,34,32,110,97,109,101,61,34,98,111,120,34,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,60,109,101,115,104,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,115,111,117,114,99,101,32,105,100,61,34,98,111,120,45,108,105,98,45,112,111,115,105,116,105,111,110,115,34,32,110,97,109,101,61,34,112,111,115,105,116,105,111,110,34,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,102,108,111,97,116,95,97,114,114,97,121,32,105,100,61,34,98,111,120,45,108,105,98,45,112,111,115,105,116,105,111,110,115,45,97,114,114,97,121,34,32,99,111,117,110,116,61,34,50,52,34,62,45,53,48,32,53,48,32,53,48,32,53,48,32,53,48,32,53,48,32,45,53,48,32,45,53,48,32,53,48,32,53,48,32,45,53,48,32,53,48,32,45,53,48,32,53,48,32,45,53,48,32,53,48,32,53,48,32,45,53,48,32,45,53,48,32,45,53,48,32,45,53,48,32,53,48,32,45,53,48,32,45,53,48,60,47,102,108,111,97,116,95,97,114,114,97,121,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,116,101,99,104,110,105,113,117,101,95,99,111,109,109,111,110,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,97,99,99,101,115,115,111,114,32,99,111,117,110,116,61,34,56,34,32,111,102,102,115,101,116,61,34,48,34,32,115,111,117,114,99,101,61,34,35,98,111,120,45,108,105,98,45,112,111,115,105,116,105,111,110,115,45,97,114,114,97,121,34,32,115,116,114,105,100,101,61,34,51,34,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,112,97,114,97,109,32,110,97,109,101,61,34,88,34,32,116,121,112,101,61,34,102,108,111,97,116,34,62,60,47,112,97,114,97,109,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,112,97,114,97,109,32,110,97,109,101,61,34,89,34,32,116,121,112,101,61,34,102,108,111,97,116,34,62,60,47,112,97,114,97,109,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,112,97,114,97,109,32,110,97,109,101,61,34,90,34,32,116,121,112,101,61,34,102,108,111,97,116,34,62,60,47,112,97,114,97,109,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,47,97,99,99,101,115,115,111,114,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,47,116,101,99,104,110,105,113,117,101,95,99,111,109,109,111,110,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,47,115,111,117,114,99,101,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,115,111,117,114,99,101,32,105,100,61,34,98,111,120,45,108,105,98,45,110,111,114,109,97,108,115,34,32,110,97,109,101,61,34,110,111,114,109,97,108,34,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,102,108,111,97,116,95,97,114,114,97,121,32,105,100,61,34,98,111,120,45,108,105,98,45,110,111,114,109,97,108,115,45,97,114,114,97,121,34,32,99,111,117,110,116,61,34,55,50,34,62,48,32,48,32,49,32,48,32,48,32,49,32,48,32,48,32,49,32,48,32,48,32,49,32,48,32,49,32,48,32,48,32,49,32,48,32,48,32,49,32,48,32,48,32,49,32,48,32,48,32,45,49,32,48,32,48,32,45,49,32,48,32,48,32,45,49,32,48,32,48,32,45,49,32,48,32,45,49,32,48,32,48,32,45,49,32,48,32,48,32,45,49,32,48,32,48,32,45,49,32,48,32,48,32,49,32,48,32,48,32,49,32,48,32,48,32,49,32,48,32,48,32,49,32,48,32,48,32,48,32,48,32,45,49,32,48,32,48,32,45,49,32,48,32,48,32,45,49,32,48,32,48,32,45,49,60,47,102,108,111,97,116,95,97,114,114,97,121,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,116,101,99,104,110,105,113,117,101,95,99,111,109,109,111,110,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,97,99,99,101,115,115,111,114,32,99,111,117,110,116,61,34,50,52,34,32,111,102,102,115,101,116,61,34,48,34,32,115,111,117,114,99,101,61,34,35,98,111,120,45,108,105,98,45,110,111,114,109,97,108,115,45,97,114,114,97,121,34,32,115,116,114,105,100,101,61,34,51,34,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,112,97,114,97,109,32,110,97,109,101,61,34,88,34,32,116,121,112,101,61,34,102,108,111,97,116,34,62,60,47,112,97,114,97,109,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,112,97,114,97,109,32,110,97,109,101,61,34,89,34,32,116,121,112,101,61,34,102,108,111,97,116,34,62,60,47,112,97,114,97,109,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,112,97,114,97,109,32,110,97,109,101,61,34,90,34,32,116,121,112,101,61,34,102,108,111,97,116,34,62,60,47,112,97,114,97,109,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,47,97,99,99,101,115,115,111,114,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,47,116,101,99,104,110,105,113,117,101,95,99,111,109,109,111,110,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,47,115,111,117,114,99,101,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,118,101,114,116,105,99,101,115,32,105,100,61,34,98,111,120,45,108,105,98,45,118,101,114,116,105,99,101,115,34,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,105,110,112,117,116,32,115,101,109,97,110,116,105,99,61,34,80,79,83,73,84,73,79,78,34,32,115,111,117,114,99,101,61,34,35,98,111,120,45,108,105,98,45,112,111,115,105,116,105,111,110,115,34,47,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,47,118,101,114,116,105,99,101,115,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,112,111,108,121,108,105,115,116,32,99,111,117,110,116,61,34,54,34,32,109,97,116,101,114,105,97,108,61,34,66,108,117,101,83,71,34,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,105,110,112,117,116,32,111,102,102,115,101,116,61,34,48,34,32,115,101,109,97,110,116,105,99,61,34,86,69,82,84,69,88,34,32,115,111,117,114,99,101,61,34,35,98,111,120,45,108,105,98,45,118,101,114,116,105,99,101,115,34,47,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,105,110,112,117,116,32,111,102,102,115,101,116,61,34,49,34,32,115,101,109,97,110,116,105,99,61,34,78,79,82,77,65,76,34,32,115,111,117,114,99,101,61,34,35,98,111,120,45,108,105,98,45,110,111,114,109,97,108,115,34,47,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,118,99,111,117,110,116,62,52,32,52,32,52,32,52,32,52,32,52,60,47,118,99,111,117,110,116,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,112,62,48,32,48,32,50,32,49,32,51,32,50,32,49,32,51,32,48,32,52,32,49,32,53,32,53,32,54,32,52,32,55,32,54,32,56,32,55,32,57,32,51,32,49,48,32,50,32,49,49,32,48,32,49,50,32,52,32,49,51,32,54,32,49,52,32,50,32,49,53,32,51,32,49,54,32,55,32,49,55,32,53,32,49,56,32,49,32,49,57,32,53,32,50,48,32,55,32,50,49,32,54,32,50,50,32,52,32,50,51,60,47,112,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,47,112,111,108,121,108,105,115,116,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,60,47,109,101,115,104,62,13,10,32,32,32,32,32,32,32,32,60,47,103,101,111,109,101,116,114,121,62,13,10,32,32,32,32,60,47,108,105,98,114,97,114,121,95,103,101,111,109,101,116,114,105,101,115,62,13,10,32,32,32,32,60,108,105,98,114,97,114,121,95,118,105,115,117,97,108,95,115,99,101,110,101,115,62,13,10,32,32,32,32,32,32,32,32,60,118,105,115,117,97,108,95,115,99,101,110,101,32,105,100,61,34,86,105,115,117,97,108,83,99,101,110,101,78,111,100,101,34,32,110,97,109,101,61,34,117,110,116,105,116,108,101,100,34,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,60,110,111,100,101,32,105,100,61,34,67,97,109,101,114,97,34,32,110,97,109,101,61,34,67,97,109,101,114,97,34,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,116,114,97,110,115,108,97,116,101,32,115,105,100,61,34,116,114,97,110,115,108,97,116,101,34,62,45,52,50,55,46,55,52,57,32,51,51,51,46,56,53,53,32,54,53,53,46,48,49,55,60,47,116,114,97,110,115,108,97,116,101,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,114,111,116,97,116,101,32,115,105,100,61,34,114,111,116,97,116,101,89,34,62,48,32,49,32,48,32,45,51,51,60,47,114,111,116,97,116,101,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,114,111,116,97,116,101,32,115,105,100,61,34,114,111,116,97,116,101,88,34,62,49,32,48,32,48,32,45,50,50,46,49,57,53,52,60,47,114,111,116,97,116,101,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,114,111,116,97,116,101,32,115,105,100,61,34,114,111,116,97,116,101,90,34,62,48,32,48,32,49,32,48,60,47,114,111,116,97,116,101,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,105,110,115,116,97,110,99,101,95,99,97,109,101,114,97,32,117,114,108,61,34,35,80,101,114,115,112,67,97,109,101,114,97,34,47,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,60,47,110,111,100,101,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,60,110,111,100,101,32,105,100,61,34,76,105,103,104,116,34,32,110,97,109,101,61,34,76,105,103,104,116,34,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,116,114,97,110,115,108,97,116,101,32,115,105,100,61,34,116,114,97,110,115,108,97,116,101,34,62,45,53,48,48,32,49,48,48,48,32,52,48,48,60,47,116,114,97,110,115,108,97,116,101,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,114,111,116,97,116,101,32,115,105,100,61,34,114,111,116,97,116,101,90,34,62,48,32,48,32,49,32,48,60,47,114,111,116,97,116,101,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,114,111,116,97,116,101,32,115,105,100,61,34,114,111,116,97,116,101,89,34,62,48,32,49,32,48,32,48,60,47,114,111,116,97,116,101,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,114,111,116,97,116,101,32,115,105,100,61,34,114,111,116,97,116,101,88,34,62,49,32,48,32,48,32,48,60,47,114,111,116,97,116,101,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,105,110,115,116,97,110,99,101,95,108,105,103,104,116,32,117,114,108,61,34,35,108,105,103,104,116,45,108,105,98,34,47,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,60,47,110,111,100,101,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,60,110,111,100,101,32,105,100,61,34,66,111,120,34,32,110,97,109,101,61,34,66,111,120,34,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,114,111,116,97,116,101,32,115,105,100,61,34,114,111,116,97,116,101,90,34,62,48,32,48,32,49,32,48,60,47,114,111,116,97,116,101,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,114,111,116,97,116,101,32,115,105,100,61,34,114,111,116,97,116,101,89,34,62,48,32,49,32,48,32,48,60,47,114,111,116,97,116,101,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,114,111,116,97,116,101,32,115,105,100,61,34,114,111,116,97,116,101,88,34,62,49,32,48,32,48,32,48,60,47,114,111,116,97,116,101,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,105,110,115,116,97,110,99,101,95,103,101,111,109,101,116,114,121,32,117,114,108,61,34,35,98,111,120,45,108,105,98,34,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,98,105,110,100,95,109,97,116,101,114,105,97,108,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,116,101,99,104,110,105,113,117,101,95,99,111,109,109,111,110,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,105,110,115,116,97,110,99,101,95,109,97,116,101,114,105,97,108,32,115,121,109,98,111,108,61,34,66,108,117,101,83,71,34,32,116,97,114,103,101,116,61,34,35,66,108,117,101,34,47,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,47,116,101,99,104,110,105,113,117,101,95,99,111,109,109,111,110,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,47,98,105,110,100,95,109,97,116,101,114,105,97,108,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,47,105,110,115,116,97,110,99,101,95,103,101,111,109,101,116,114,121,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,60,47,110,111,100,101,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,60,110,111,100,101,32,105,100,61,34,116,101,115,116,67,97,109,101,114,97,34,32,110,97,109,101,61,34,116,101,115,116,67,97,109,101,114,97,34,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,116,114,97,110,115,108,97,116,101,32,115,105,100,61,34,116,114,97,110,115,108,97,116,101,34,62,45,52,50,55,46,55,52,57,32,51,51,51,46,56,53,53,32,54,53,53,46,48,49,55,60,47,116,114,97,110,115,108,97,116,101,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,114,111,116,97,116,101,32,115,105,100,61,34,114,111,116,97,116,101,89,34,62,48,32,49,32,48,32,45,51,51,60,47,114,111,116,97,116,101,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,114,111,116,97,116,101,32,115,105,100,61,34,114,111,116,97,116,101,88,34,62,49,32,48,32,48,32,45,50,50,46,49,57,53,52,60,47,114,111,116,97,116,101,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,114,111,116,97,116,101,32,115,105,100,61,34,114,111,116,97,116,101,90,34,62,48,32,48,32,49,32,48,60,47,114,111,116,97,116,101,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,105,110,115,116,97,110,99,101,95,99,97,109,101,114,97,32,117,114,108,61,34,35,116,101,115,116,67,97,109,101,114,97,83,104,97,112,101,34,47,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,60,47,110,111,100,101,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,60,110,111,100,101,32,105,100,61,34,112,111,105,110,116,76,105,103,104,116,49,34,32,110,97,109,101,61,34,112,111,105,110,116,76,105,103,104,116,49,34,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,116,114,97,110,115,108,97,116,101,32,115,105,100,61,34,116,114,97,110,115,108,97,116,101,34,62,51,32,52,32,49,48,60,47,116,114,97,110,115,108,97,116,101,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,114,111,116,97,116,101,32,115,105,100,61,34,114,111,116,97,116,101,90,34,62,48,32,48,32,49,32,48,60,47,114,111,116,97,116,101,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,114,111,116,97,116,101,32,115,105,100,61,34,114,111,116,97,116,101,89,34,62,48,32,49,32,48,32,48,60,47,114,111,116,97,116,101,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,114,111,116,97,116,101,32,115,105,100,61,34,114,111,116,97,116,101,88,34,62,49,32,48,32,48,32,48,60,47,114,111,116,97,116,101,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,105,110,115,116,97,110,99,101,95,108,105,103,104,116,32,117,114,108,61,34,35,112,111,105,110,116,76,105,103,104,116,83,104,97,112,101,49,45,108,105,98,34,47,62,13,10,32,32,32,32,32,32,32,32,32,32,32,32,60,47,110,111,100,101,62,13,10,32,32,32,32,32,32,32,32,60,47,118,105,115,117,97,108,95,115,99,101,110,101,62,13,10,32,32,32,32,60,47,108,105,98,114,97,114,121,95,118,105,115,117,97,108,95,115,99,101,110,101,115,62,13,10,32,32,32,32,60,115,99,101,110,101,62,13,10,32,32,32,32,32,32,32,32,60,105,110,115,116,97,110,99,101,95,118,105,115,117,97,108,95,115,99,101,110,101,32,117,114,108,61,34,35,86,105,115,117,97,108,83,99,101,110,101,78,111,100,101,34,47,62,13,10,32,32,32,32,60,47,115,99,101,110,101,62,13,10,60,47,67,79,76,76,65,68,65,62,13,10,};
        //const aiScene * scene = importer.ReadFileFromMemory( s_simpleCollada, _countof(s_simpleCollada), 0, "dae" );
        static unsigned char s_simpleObj [] = {35,9,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,86,101,114,116,105,99,101,115,58,32,56,13,10,35,9,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,80,111,105,110,116,115,58,32,48,13,10,35,9,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,76,105,110,101,115,58,32,48,13,10,35,9,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,70,97,99,101,115,58,32,54,13,10,35,9,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,77,97,116,101,114,105,97,108,115,58,32,49,13,10,13,10,111,32,49,13,10,13,10,35,32,86,101,114,116,101,120,32,108,105,115,116,13,10,13,10,118,32,45,48,46,53,32,45,48,46,53,32,48,46,53,13,10,118,32,45,48,46,53,32,45,48,46,53,32,45,48,46,53,13,10,118,32,45,48,46,53,32,48,46,53,32,45,48,46,53,13,10,118,32,45,48,46,53,32,48,46,53,32,48,46,53,13,10,118,32,48,46,53,32,45,48,46,53,32,48,46,53,13,10,118,32,48,46,53,32,45,48,46,53,32,45,48,46,53,13,10,118,32,48,46,53,32,48,46,53,32,45,48,46,53,13,10,118,32,48,46,53,32,48,46,53,32,48,46,53,13,10,13,10,35,32,80,111,105,110,116,47,76,105,110,101,47,70,97,99,101,32,108,105,115,116,13,10,13,10,117,115,101,109,116,108,32,68,101,102,97,117,108,116,13,10,102,32,52,32,51,32,50,32,49,13,10,102,32,50,32,54,32,53,32,49,13,10,102,32,51,32,55,32,54,32,50,13,10,102,32,56,32,55,32,51,32,52,13,10,102,32,53,32,56,32,52,32,49,13,10,102,32,54,32,55,32,56,32,53,13,10,13,10,35,32,69,110,100,32,111,102,32,102,105,108,101,13,10,};
        const aiScene * scene = importer.ReadFileFromMemory( s_simpleObj, _countof(s_simpleObj), 0, "obj" );
        //const aiScene * scene = importer.ReadFile( "C:\\Work\\Art\\crytek-sponza-other\\banner.obj", 0 );
    }
#endif

    {
    #if defined(DEBUG) || defined(_DEBUG)
    //	_CrtSetDbgFlag( 0
    //		| _CRTDBG_ALLOC_MEM_DF 
    //		|  _CRTDBG_CHECK_CRT_DF
    //		| _CRTDBG_CHECK_EVERY_128_DF
    //		| _CRTDBG_LEAK_CHECK_DF 
    //		);
       _CrtMemCheckpoint( &s_memStateStart );
    //   _CrtSetBreakAlloc( 103 );  // <- if this didn't work, the allocation probably happens before Initialize() or is a global variable
    #endif

	    s_tempBuffer.Create( 2 * 1024 * 1024 );
    }
}

void vaMemory::Deinitialize()
{
   s_tempBuffer.Destroy( );

#if defined(DEBUG) || defined(_DEBUG)
   _CrtMemState memStateStop, memStateDiff;
   _CrtMemCheckpoint( &memStateStop );
   if( _CrtMemDifference( &memStateDiff, &s_memStateStart, &memStateStop ) )
   {
      // doesn't play nice with .net runtime
      _CrtDumpMemoryLeaks();

      VA_WARN( L"Memory leaks detected - check debug output; using _CrtSetBreakAlloc( allocationIndex ) in vaMemory::Initialize() might help to track it down. " );
   }
   _CrtMemDumpStatistics( &memStateDiff );
#endif
}

void * vaMemory::AllocTempBuffer( int size )
{
	if( s_tempBuffer.InUse || s_tempBuffer.Size < size )
	{
		return new byte[size];
	}
	else
	{
		s_tempBuffer.InUse = true;
		return s_tempBuffer.Data;
	}
}

void	vaMemory::FreeTempBuffer( void * buffer )
{
	if( buffer == s_tempBuffer.Data )
	{
		assert( s_tempBuffer.InUse );
		s_tempBuffer.InUse = false;
	}
	else
	{
		byte * bytePtr = (byte *)buffer;
		delete[] bytePtr;
	}
}


