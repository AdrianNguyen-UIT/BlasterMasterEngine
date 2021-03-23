#pragma once
#include "Object/Object.h"

class OverworldGate : public Object2D
{
private:
	int gateID;
public:
	OverworldGate(int id, float x = 0, float y = 0);

	int GetGateID() { return gateID; }

	virtual void Start() override;
};