#pragma once

namespace CR
{
	namespace Utility
	{
		class BinaryWriter;
		class BinaryReader;

		class ISerializable
		{
		public:
			virtual void Serialize(BinaryWriter &_writer) const = 0;
			virtual void DeSerialize(BinaryReader &_reader) = 0;
		protected:
			ISerializable(void) {}
			~ISerializable(void) {}
		};
	}
}
