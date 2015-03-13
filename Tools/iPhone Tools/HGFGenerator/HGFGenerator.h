// HGFGenerator.h

#pragma once

#include "IHGFFile.h"
#include "IProgress.h"
#include "..\Utility\BinaryWriter.h"

using namespace System;

namespace HGFGenerator
{

	public ref class Generator
	{
	public:
		static Generator^ Instance()
		{
			if(instance == nullptr)
				instance = gcnew Generator();
			return instance;
		}
		void GenerateImage(IHGFFile^ _hgfFile,IProgress^ _progress);
	private:
		template<int BPP>
		void ConvertSaveImage(Syntax::Utility::BinaryWriter &_file,System::Drawing::Bitmap^ _image,unsigned short _colorKey);
		void ConvertSaveImageHighQuality(Syntax::Utility::BinaryWriter &_file,System::Drawing::Bitmap^ _image);
		void ConvertSaveImageHighQuality24(Syntax::Utility::BinaryWriter &_file,System::Drawing::Bitmap^ _image);
		void SaveImage(Syntax::Utility::BinaryWriter &_file,IHPTImage^ _image);
		static Generator^ instance = nullptr;
	};
}
