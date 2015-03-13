/*
 *  Event.h
 *  Rewrite using variadic templates once there available. available starting in gcc 4.3, microsoft has not said when they will add support 
 *		for that c++0x feature yet.
 *
 *  Currently only supports up to 3 arguments. Also do not use large arguments, as arguments are passed by value currently. primitives and really small
 *		structs should be ok.
 *
 *  Created by Eric Duhon on 1/25/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include <vector>
#include <algorithm>
#include <functional>

#include "FunctionObjects.h"
//#include <tr1/functional>

class IDelegate
{
public:
	virtual void operator()() = 0;
};

template<typename Arg1>
class IDelegate1
{
public:
	virtual void operator()(Arg1 _arg1) = 0;
};

template<typename Arg1,typename Arg2>
class IDelegate2
{
public:
	virtual void operator()(Arg1 _arg1,Arg2 _arg2) = 0;
};

template<typename Arg1,typename Arg2,typename Arg3>
class IDelegate3
{
public:
	virtual void operator()(Arg1 _arg1,Arg2 _arg2,Arg2 _arg3) = 0;
};

class Event
{
public:
	~Event()
	{
		Clear();
	}
	unsigned int Size() const
	{
		return static_cast<unsigned int>(m_delegates.size());
	}
	void Clear()
	{
		CR::Utility::ForEach(m_delegates,CR::Utility::DeleteFO());
		m_delegates.clear();
	}
	void operator=(IDelegate *_delegate)
	{
		Clear();
		m_delegates.push_back(_delegate);
	}
	void operator+=(IDelegate *_delegate)
	{
		m_delegates.push_back(_delegate);
	}
	void operator()()
	{
		CR::Utility::ForEach(m_delegates,std::mem_fun(&IDelegate::operator()));
	}
private:
	std::vector<IDelegate*> m_delegates;
};
/*
template<typename Arg1>
class Event1
{
public:
	~Event1()
	{
		Clear();
	}
	unsigned int Size() const
	{
		return static_cast<unsigned int>(m_delegates.size());
	}
	void Clear()
	{
		CR::Utility::ForEach(m_delegates,CR::Utility::DeleteFO());
		m_delegates.clear();
	}
	void operator=(IDelegate1<Arg1> *_delegate)
	{
		Clear();
		m_delegates.push_back(_delegate);
	}
	void operator+=(IDelegate1<Arg1> *_delegate)
	{
		m_delegates.push_back(_delegate);
	}
	void operator()(Arg1 _arg1)
	{
		CR::Utility::ForEach(m_delegates,std::tr1::bind(std::tr1::mem_fn(&IDelegate1<Arg1>::operator()),std::tr1::placeholders::_1,_arg1));
	}
private:
	std::vector<IDelegate1<Arg1>*> m_delegates;
};

template<typename Arg1,typename Arg2>
class Event2
{
public:
	~Event2()
	{
		Clear();
	}
	unsigned int Size() const
	{
		return static_cast<unsigned int>(m_delegates.size());
	}
	void Clear()
	{
		CR::Utility::ForEach(m_delegates,CR::Utility::DeleteFO());
		m_delegates.clear();
	}
	void operator=(IDelegate2<Arg1,Arg2> *_delegate)
	{
		Clear();
		m_delegates.push_back(_delegate);
	}
	void operator+=(IDelegate2<Arg1,Arg2> *_delegate)
	{
		m_delegates.push_back(_delegate);
	}
	void operator()(Arg1 _arg1,Arg2 _arg2)
	{
		CR::Utility::ForEach(m_delegates,std::tr1::bind(std::tr1::mem_fn(&IDelegate2<Arg1,Arg2>::operator()),std::tr1::placeholders::_1,_arg1,_arg2));
	}
private:
	std::vector<IDelegate2<Arg1,Arg2>*> m_delegates;
};

template<typename Arg1,typename Arg2,typename Arg3>
class Event3
{
public:
	~Event3()
	{
		Clear();
	}
	unsigned int Size() const
	{
		return static_cast<unsigned int>(m_delegates.size());
	}
	void Clear()
	{
		CR::Utility::ForEach(m_delegates,CR::Utility::DeleteFO());
		m_delegates.clear();
	}
	void operator=(IDelegate3<Arg1,Arg2,Arg3> *_delegate)
	{
		Clear();
		m_delegates.push_back(_delegate);
	}
	void operator+=(IDelegate3<Arg1,Arg2,Arg3> *_delegate)
	{
		m_delegates.push_back(_delegate);
	}
	void operator()(Arg1 _arg1,Arg2 _arg2,Arg3 _arg3)
	{
		CR::Utility::ForEach(m_delegates,std::tr1::bind(std::tr1::mem_fn(&IDelegate3<Arg1,Arg2,Arg3>::operator()),std::tr1::placeholders::_1,_arg1,_arg2,_arg3));
	}
private:
	std::vector<IDelegate3<Arg1,Arg2,Arg3>*> m_delegates;
};*/

/*template<class T,class FUNCTOR>
class DelegateImpl : public IDelegate
{
public:
	DelegateImpl(T *_classInstance,FUNCTOR _functor) : m_classInstance(_classInstance), m_functor(_functor) {}	
	virtual void operator()()
	{
		(m_classInstance->*m_functor)();
	}
private:
	T *m_classInstance;
	FUNCTOR m_functor;
};*/

template<class T> 
class DelegateImpl : public IDelegate
{ 
public:  
	typedef void (T::*FUNCTOR)(); 
	
	DelegateImpl(T *_classInstance,FUNCTOR _functor) : m_classInstance(_classInstance), m_functor(_functor) {} 
	
	virtual void operator()()  
	{ 
		(m_classInstance->*m_functor)();  
	} 
private:  
	T *m_classInstance;  
	FUNCTOR m_functor; 
}; 

/*
template<class T,class FUNCTOR,typename Arg1>
class DelegateImpl1 : public IDelegate1<Arg1>
{
public:
	DelegateImpl1(T *_classInstance,FUNCTOR _functor) : m_classInstance(_classInstance), m_functor(_functor) {}	
	virtual void operator()(Arg1 _arg1)
	{
		(m_classInstance->*m_functor)(_arg1);
	}
private:
	T *m_classInstance;
	FUNCTOR m_functor;
};
*/

template<class T,typename Arg1> 
class DelegateImpl1 : public IDelegate1<Arg1> 
{ 
public:  
	typedef void (T::*FUNCTOR)(Arg1); 
	
	DelegateImpl1(T *_classInstance,FUNCTOR _functor) : m_classInstance(_classInstance), m_functor(_functor) {} 
	
	virtual void operator()(Arg1 _arg1)  
	{ 
		(m_classInstance->*m_functor)(_arg1);  
	} 
private:  
	T *m_classInstance;  
	FUNCTOR m_functor; 
}; 

/*template<class T,class FUNCTOR,typename Arg1,typename Arg2>
class DelegateImpl2 : public IDelegate2<Arg1,Arg2>
{
public:
	DelegateImpl2(T *_classInstance,FUNCTOR _functor) : m_classInstance(_classInstance), m_functor(_functor) {}	
	virtual void operator()(Arg1 _arg1,Arg2 _arg2)
	{
		(m_classInstance->*m_functor)(_arg1,_arg2);
	}
private:
	T *m_classInstance;
	FUNCTOR m_functor;
};*/

template<class T,typename Arg1,typename Arg2> 
class DelegateImpl2 : public IDelegate2<Arg1,Arg2> 
{ 
public:  
	typedef void (T::*FUNCTOR)(Arg1,Arg2); 
	
	DelegateImpl2(T *_classInstance,FUNCTOR _functor) : m_classInstance(_classInstance), m_functor(_functor) {} 
	
	virtual void operator()(Arg1 _arg1,Arg2 _arg2)  
	{ 
		(m_classInstance->*m_functor)(_arg1,_arg2);  
	} 
private:  
	T *m_classInstance;  
	FUNCTOR m_functor; 
}; 

/*template<class T,class FUNCTOR,typename Arg1,typename Arg2,typename Arg3>
class DelegateImpl3 : public IDelegate3<Arg1,Arg2,Arg3>
{
public:
	DelegateImpl3(T *_classInstance,FUNCTOR _functor) : m_classInstance(_classInstance), m_functor(_functor) {}	
	virtual void operator()(Arg1 _arg1,Arg2 _arg2,Arg3 _arg3)
	{
		(m_classInstance->*m_functor)(_arg1,_arg2,_arg3);
	}
private:
	T *m_classInstance;
	FUNCTOR m_functor;
};*/

template<class T,typename Arg1,typename Arg2,typename Arg3> 
class DelegateImpl3 : public IDelegate3<Arg1,Arg2,Arg3> 
{ 
public:
	typedef void (T::*FUNCTOR)(Arg1,Arg2,Arg3); 
	
	DelegateImpl3(T *_classInstance,FUNCTOR _functor) : m_classInstance(_classInstance), m_functor(_functor) {} 
	
	virtual void operator()(Arg1 _arg1,Arg2 _arg2,Arg3 _arg3)
	{ 
		(m_classInstance->*m_functor)(_arg1,_arg2,_arg3);  
	} 
private:  
	T *m_classInstance;  
	FUNCTOR m_functor; 
}; 

/*template<class T,class FUNCTOR>
DelegateImpl<T,FUNCTOR>* Delegate(T *_classInstance,FUNCTOR _functor)
{
	return new DelegateImpl<T,FUNCTOR>(_classInstance,_functor);
}*/

template<class T> 
DelegateImpl<T>* Delegate(T *_classInstance,typename DelegateImpl<T>::FUNCTOR _functor) 
{  
	return new DelegateImpl<T>(_classInstance,_functor); 
}

/*template<class T,class FUNCTOR,typename Arg1>
DelegateImpl1<T,FUNCTOR,Arg1>* Delegate1(T *_classInstance,FUNCTOR _functor)
{
	return new DelegateImpl1<T,FUNCTOR,Arg1>(_classInstance,_functor);
}*/

template<class T,typename Arg1> 
DelegateImpl1<T,Arg1>* Delegate1(T *_classInstance,typename DelegateImpl1<T,Arg1>::FUNCTOR _functor) 
{  
	return new DelegateImpl1<T,Arg1>(_classInstance,_functor); 
}

/*template<class T,class FUNCTOR,typename Arg1,typename Arg2>
DelegateImpl2<T,FUNCTOR,Arg1,Arg2>* Delegate2(T *_classInstance,FUNCTOR _functor)
{
	return new DelegateImpl2<T,FUNCTOR,Arg1,Arg2>(_classInstance,_functor);
}*/

template<class T,typename Arg1,typename Arg2> 
DelegateImpl2<T,Arg1,Arg2>* Delegate2(T *_classInstance,typename DelegateImpl2<T,Arg1,Arg2>::FUNCTOR _functor) 
{  
	return new DelegateImpl2<T,Arg1,Arg2>(_classInstance,_functor); 
}

/*
template<class T,class FUNCTOR,typename Arg1,typename Arg2,typename Arg3>
DelegateImpl3<T,FUNCTOR,Arg1,Arg2,Arg3>* Delegate3(T *_classInstance,FUNCTOR _functor)
{
	return new DelegateImpl3<T,FUNCTOR,Arg1,Arg2,Arg3>(_classInstance,_functor);
}
*/

template<class T,typename Arg1,typename Arg2,typename Arg3> 
DelegateImpl3<T,Arg1,Arg2,Arg3>* Delegate3(T *_classInstance,typename DelegateImpl3<T,Arg1,Arg2,Arg3>::FUNCTOR _functor) 
{  
	return new DelegateImpl3<T,Arg1,Arg2,Arg3>(_classInstance,_functor); 
}




