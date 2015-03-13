#pragma once

public interface class IHPTImage
{
	property System::String^ FileName;
	property int Width;
	property int Height;
	property int TotalWidth;
	property int TotalHeight;
	property int ColorKeyRed;
	property int ColorKeyGreen;
	property int ColorKeyBlue;
	property float DefaultFrameRate;
	property bool DefaultAutoAnimate;
	property int NumFrameSets;
	property System::Collections::Generic::List<int>^ FramesPerSet;
	property int ImageType;
	property bool HighQuality;
};
