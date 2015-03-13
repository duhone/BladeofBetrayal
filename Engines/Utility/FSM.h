/*
 *  FSM.h
 *  BoB
 *
 *  Created by Eric Duhon on 1/28/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once

#include <vector>
#include <algorithm>
#include "FunctionObjects.h"
#include "Property.h"

namespace CR
{
	namespace Utility
	{
		struct StateHandlerBase
		{
			virtual void operator()() = 0; 
		};
		
		template<class T>
		class StateHandlerImpl : public StateHandlerBase
		{
		public:
			StateHandlerImpl(T *_object,void (T::*_func)()) : m_object(_object), m_func(_func) {}
			virtual void operator()()
			{
				(m_object->*m_func)();
			}
		private:
			T *m_object;
			void (T::*m_func)();
		};
		
		template<class T>
		StateHandlerBase* StateHandler(T *_object,void (T::*_func)())
		{
			return new StateHandlerImpl<T>(_object,_func);
		}
		
		template<int NumStates>
		class SimpleFSM
		{
		public:
			SimpleFSM() : m_state(0)
			{
				std::fill_n(std::back_inserter(m_handlers),NumStates,(StateHandlerBase*)NULL);
				State.Init(this,&SimpleFSM::GetState,&SimpleFSM::SetState);
			}
			~SimpleFSM()
			{
				CR::Utility::ForEach(m_handlers,CR::Utility::DeleteFO());
				m_handlers.clear();
			}
			void operator++(int _postfix)
			{
				if(m_state < (NumStates-1))
					m_state++;
			}
			void operator--(int _postfix)
			{
				if(m_state > 0)
					m_state--;
			}
			void Reset() { m_state = 0;}
			void operator()()
			{
				if(m_handlers[m_state] != NULL)
					(*m_handlers[m_state])();
			}
			void AddStateHandler(int _state,StateHandlerBase *_handler)
			{
				if(_state < (NumStates))
					m_handlers[_state] = _handler;
			}
			Property<int,SimpleFSM> State;
		private:
			int m_state;
			std::vector<StateHandlerBase*> m_handlers;
			int GetState() const {return m_state;}
			void SetState(int _state) {m_state = _state;}
		};
		
		class IState
		{
		public:
			static const int UNCHANGED = -1;
			virtual bool Begin() {return false;}
			virtual void End() {}
			virtual int Process() {return UNCHANGED;}
		};
		
		class FSM
		{
		public:
			FSM() : m_state(-1), m_skipUpdate(false)
			{
				State.Init(this,&FSM::GetState,&FSM::SetState);
			}
			~FSM()
			{
				CR::Utility::ForEach(m_states,CR::Utility::DeleteFO());
				m_states.clear();
			}
			FSM& operator<<(IState *_state) {m_states.push_back(_state); return *this;}
			
			void operator++(int _postfix)
			{
				if(m_state < (m_states.size()-1))
					GoToState(m_state+1);
			}
			void operator--(int _postfix)
			{
				if(m_state > 0)
					GoToState(m_state-1);
			}
			void Reset() { m_state = -1;}
			void operator()()
			{
				if(m_state == -1)
					return;
				int new_state = IState::UNCHANGED;
				if(!m_skipUpdate && m_states[m_state] != NULL)
					new_state = m_states[m_state]->Process();
				m_skipUpdate = false;
				if(new_state != IState::UNCHANGED)
					GoToState(new_state);
			}			
			Property<int,FSM> State;
		private:
			bool m_skipUpdate; 
			int m_state;
			std::vector<IState*> m_states;
			int GetState() const {return m_state;}
			void SetState(int _state) {GoToState(_state);}
			void GoToState(int _state)
			{			
				if(m_state >= 0)
					m_states[m_state]->End();
				m_state = _state;
				m_skipUpdate = m_states[m_state]->Begin();				
			}
		};
	}
}
