/*
 *  DecompressorFactory.h
 *  AudioTest
 *
 *  Created by Eric Duhon on 10/11/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once

#include "Singleton.h"
#include "ClassFactory.h"

namespace CR
{
	namespace Sound
	{
		typedef CR::Utility::Singleton<CR::Utility::ClassFactory<IDecompressor,int> > DecompressorFactory;		
	}
}
