#pragma once
#include "graphics.h"
#include <random>
enum class EState {
	EmptyState,
	Idle,
	WalkLeft,
	WalkRight,
	Jump,
	Attack,
	Kick,
	Block,
	Crouch,
	JumpLeft,
	JumpRight,
	JumpAttackLeft,
	JumpAttackRight,
	JumpAttackUp,
	CrouchAttack,
	CrouchBlock
};
class StackFSM
{
private:
	EState* stack;
	int length = 0;
	float duration = 0;
	bool flag = false;
	int time = 0;
	EState* operator=(const EState* copy) {}
	StackFSM(const EState* copy) {}
public:
	StackFSM(const int& size);
	unsigned int size() const;
	EState popState();
	EState popStateWithTime();
	void pushState(const EState state);
	EState getCurrentState() const;
	void clearStack();
	~StackFSM();
};

