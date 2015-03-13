/*
 *  PathManager.h
 *  BoB
 *
 *  Created by Robert Shoemate on 1/22/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once

class PathManager
	{
	public:
		PathManager();
		virtual ~PathManager();
		
		const char* GetResourcePath(char* resourceName);
		const char* GetResourcePath(char *resourceName, char* type);
		const char* GetDocumentPath(char *fileName);
	};