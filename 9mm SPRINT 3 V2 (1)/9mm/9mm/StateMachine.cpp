#include "StateMachine.h"

void StateMachine::AddState(StateRef newState, bool isReplacing) {

	this-> isAdding = true;
	this-> isReplacing = isReplacing;

	this-> newState = std::move(newState);
}

void StateMachine::RemoveState() {

	this-> isRemoving = true;
}

//Checks and changes fed state, based on input
void StateMachine::ProcessState() {

	if (this-> isRemoving && !this-> states.empty())
	{
		this-> states.pop();

		if (!this-> states.empty())
		{
			this-> states.top()->Resume();
		}
		this-> isRemoving = false;
	}

	if (this-> isAdding == true)
	{
		if (!this-> states.empty())
		{
			if (this-> isReplacing)
			{
				this-> states.pop();
			}
			else {
				this-> states.top()->Pause();
			}
		}
		this-> states.push(std::move(this-> newState));
		this-> states.top()->Init();
		this-> isAdding = false;
	}
}

StateRef& StateMachine::GetActiveState() {
	return this-> states.top();
}
