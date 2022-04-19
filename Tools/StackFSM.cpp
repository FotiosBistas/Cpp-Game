#include "StackFSM.h"

StackFSM::StackFSM(const int& size)
{
	stack = new EState[size];
}
unsigned int StackFSM::size() const {
	return length;
}
void StackFSM::pushState(const EState state)
{
	if (state == (stack[length - 1])) { return; }
	length++;
	stack[length-1] = state; 
}
EState StackFSM::popState() {
	if (size() == 0) { return EState::EmptyState; }
	EState top = stack[length - 1];
	stack[length - 1] = EState::EmptyState;
	length--;
	return top;
}
EState StackFSM::popStateWithTime() {
	if (!flag) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> pop(600, 1000);
		time = pop(gen);
		flag = true;
		
	}
	else {
		duration += graphics::getDeltaTime();
		if (duration > time) {
			duration = 0;
			flag = false;
			return popState();
		}
	}
}
EState StackFSM::getCurrentState() const
{
	return length > 0 ? stack[length - 1] : EState::EmptyState;
}
void StackFSM::clearStack()
{
	while (length != 1) {
		popState();
	}
}
StackFSM::~StackFSM() {
	delete stack;
}


