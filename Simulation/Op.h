// Defines all the classes for different operations
// which can be performed.
#pragma once

struct MachineState;

// Abstract Base Class
class Op
{
public:
	Op(const char* OpName, int parameter)
		: mOpName(OpName)
		, mParam(parameter)
	{ }

	void DebugOutput(MachineState& state);

	virtual void Execute(MachineState& state) = 0;

	MachineState* GetTarget(MachineState& state, int n = 1);
	
	virtual ~Op() { }
protected:
	int mParam;
	const char* mOpName;
};

// Defines the attack operation
// No Parameter
struct OpAttack : Op
{
    OpAttack()
    : Op("OpAttack", -1)
    {}
    
    virtual void Execute(MachineState& state) override;
    
};

// Defines the ranged_attack operation
// No Parameter
struct OpRangedAttack : Op
{
    OpRangedAttack()
    : Op("OpRangedAttack", -1)
    {}
    
    virtual void Execute(MachineState& state) override;
    
};

// Defines the rotate operation
// Param of 0 means rotate clockwise
// Param of 1 means rotate counter-clockwise
struct OpRotate : Op
{
	OpRotate(int parameter)
		: Op("OpRotate", parameter)
	{ }

	virtual void Execute(MachineState& state) override;
};

// Defines the forward operation
// No Parameter
struct OpForward : Op
{
    OpForward()
    : Op("OpForward", -1)
    {}
    
    virtual void Execute(MachineState& state) override;
    
};

// Defines the end turn operation
// No Parameter
struct OpEndTurn : Op
{
    OpEndTurn()
    : Op("OpEndTurn", -1)
    {}
    
    virtual void Execute(MachineState& state) override;
    
};

// Defines the test human operation
// Parameter of 1 or 2 means how many tiles in front
struct OpTestHuman : Op
{
    OpTestHuman(int parameter)
    : Op("OpTestHuman", parameter)
    {}
    
    virtual void Execute(MachineState& state) override;
    
};

// Defines the test wall operation
// No Parameter
struct OpTestWall : Op
{
    OpTestWall()
        : Op("OpTestWall", -1)
    {}
    
    virtual void Execute(MachineState& state) override;
    
};

// Defines the test zombie operation
// Parameter of 1 or 2 means how many tiles in front
struct OpTestZombie : Op
{
    OpTestZombie(int parameter)
    : Op("OpTestZombie", parameter)
    {}
    
    virtual void Execute(MachineState& state) override;
    
};

// Defines the test random operation
// No Parameter
struct OpTestRandom : Op
{
    OpTestRandom()
    : Op("OpTestRandom", -1)
    {}
    
    virtual void Execute(MachineState& state) override;
    
};

// Defines the test passable operation
// No Parameter
struct OpTestPassable : Op
{
    OpTestPassable()
    : Op("OpTestPassable", -1)
    {}
    
    virtual void Execute(MachineState& state) override;
    
};

// Defines the je operation
// Parameter determines the line number
struct OpJe : Op
{
    OpJe(int parameter)
    : Op("OpJe", parameter)
    {}
    
    virtual void Execute(MachineState& state) override;
    
};

// Defines the jne operation
// Parameter determines the line number
struct OpJne : Op
{
    OpJne(int parameter)
    : Op("OpJne", parameter)
    {}
    
    virtual void Execute(MachineState& state) override;
    
};

// Defines the goto operation
// Parameter determines the line number
struct OpGoto : Op
{
    OpGoto(int parameter)
    : Op("OpGoto", parameter)
    { }
    
    virtual void Execute(MachineState& state) override;
};
