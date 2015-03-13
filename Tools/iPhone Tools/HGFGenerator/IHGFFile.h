#pragma once
#include "IHPTImage.h"

public interface class IHGFFile
{
	property System::String^ FileName;
	property System::Collections::Generic::List<IHPTImage^>^ Images;
};
