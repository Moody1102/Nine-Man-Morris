#pragma once

#include <memory>
#include <stack>
// States will be based on top layer of stack

#include "State.h"


typedef std::unique_ptr<State> StateRef;

class StateMachine {
	public:
		StateMachine() {}
		~StateMachine() {}

		void AddState(StateRef newState, bool isReplacing = true);
		void RemoveState();
		void ProcessState();

		StateRef& GetActiveState();

	private:
		std::stack<StateRef> states;
		StateRef newState;

		bool isRemoving;
		bool isAdding;
		bool isReplacing;

};
