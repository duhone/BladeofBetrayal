/*
 *  FilePaths.h
 *  BoB
 *
 *  Created by Eric Duhon on 2/12/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once
#include "../Engines/Utility/Singleton.h"
#include <string>
#include <vector>

class FilePaths : public CR::Utility::Singleton<FilePaths>
{
	friend class CR::Utility::Singleton<FilePaths>;
public:
	const std::string& GetAILevelPath(int _level) const { return m_aiStrings[_level];}
	void SetAILevelPath(int _level,const std::string &_path)
	{
		if(m_aiStrings.size() <= _level)
			m_aiStrings.resize(_level+1);
		m_aiStrings[_level] = _path;
	}	
	
protected:
	FilePaths() {}
	virtual ~FilePaths() {}
private:
	std::vector<std::string> m_aiStrings;
};
