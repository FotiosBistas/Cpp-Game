#pragma once
#include "Fighter.h"
#include "StackFSM.h"
class AI : public Fighter
{
private:
	EState currentState;
	StackFSM* brain;
public:
	AI(const std::string& file);
	void draw();
	void update();
	//animation maker
	void animation(const std::string& name, unsigned const int& frames, unsigned const int& ms);
	//stack methods
	EState getState() const;
	void push(const EState state);
	EState pop();
	EState popTime();
	void clear();
	~AI();
};