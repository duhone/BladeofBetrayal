/*
 *  Property.h
 *  BoB
 *
 *  Created by Eric Duhon on 1/27/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once

namespace CR
{
	namespace Utility
	{
		template<typename ValueType,typename ThisType>
		struct Property
		{
			typedef ValueType (ThisType::*GetterType)() const;
			typedef void (ThisType::*SetterType)(ValueType);
			
			void Init(ThisType *_this,GetterType _getter,SetterType _setter)
			{
				m_this = _this;
				m_getter = _getter;
				m_setter = _setter;
			}
			operator ValueType()
			{
				return (m_this->*m_getter)();
			}
			void operator=(const ValueType &_value)
			{
				(m_this->*m_setter)(_value);
			}
		private:
			ThisType *m_this;
			GetterType m_getter;
			SetterType m_setter;
		};
	}
}
