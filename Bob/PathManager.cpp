/*
 *  PathManager.cpp
 *  BoB
 *
 *  Created by Robert Shoemate on 1/22/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "PathManager.h"
//#include <UIKit/UIKit.h>

PathManager::PathManager()
{
}

PathManager::~PathManager()
{
}

const char* PathManager::GetResourcePath(char* resourceName)
{
}

const char* PathManager::GetResourcePath(char *resourceName, char* type)
{
	//NSString * path1 = [[NSBundle mainBundle] pathForResource:  [[NSString alloc] initWithCString: resourceName] ofType: [[NSString alloc] initWithCString: type]];
	//const char *font1 = [path1 cStringUsingEncoding:1];
	
	//return font1;
	return "";
}

const char* PathManager::GetDocumentPath(char *fileName)
{
}