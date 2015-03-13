#include "AppConfig.h"
#include "S3e.h"
#include "string.h"

AppConfigSingleton::AppConfigSingleton()
{
	char value[S3E_CONFIG_STRING_MAX];
	s3eConfigGetString("crconfig","platform",value);

	if(strcmp(value,"ipad") == 0)
		m_platformType = IPAD;
	else if(strcmp(value,"iad") == 0)
		m_platformType = IAD;
	else if(strcmp(value,"android") == 0)
		m_platformType = ANDROID;
	else
		m_platformType = PHONE;
}