#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <algorithm>
#include "Op.h"
#include "Exceptions.h"

// Defines state data accessible by the machine and ops
struct MachineState
{
	// Friend Machine so BindState works
	template <typename MachineTraits>
	friend class Machine;

	enum Facing { UP, RIGHT, DOWN, LEFT };
	MachineState()
		: mProgramCounter(1)
		, mActionsTaken(0)
		, mFacing(UP)
		, mTest(false)
	{
        //srand(static_cast<unsigned int>(time(NULL)));
        //int rand1 = std::rand();
        //int rand2 = std::rand();
        mXPoint = 0;
        mYPoint = 0;
    }
    
    ~MachineState()
	{
	}

	// Active line number in behavior program
	int mProgramCounter;
	// Number of actions taken this turn
	int mActionsTaken;
	// Current facing of this character
	Facing mFacing;
	// Test flag for branches
	bool mTest;

	int GetActionsPerTurn() const noexcept { return mActionsPerTurn; }
	bool GetInfect() const noexcept { return mInfectOnAttack; }
    
    int GetXPoint() const noexcept { return mXPoint; };
    int GetYPoint() const noexcept { return mYPoint; };
    
    void SetXPoint(int x) { mXPoint = x; };
    void SetYPoint(int y) { mYPoint = y; };
    
private:
	// Data which is set by the traits
	int mActionsPerTurn;
	bool mInfectOnAttack;
    int mXPoint, mYPoint;
};

// Describes the machine which processes ops.
// Different policies dictate behavior possible for machine.
template <typename MachineTraits>
class Machine
{
public:
	// Load in all the ops for this machine from the specified file
	void LoadMachine(const std::string& filename);

	// Given the state, binds the trait parameters to it
	void BindState(MachineState& state);

	// Take a turn using this logic for the passed in state
	void TakeTurn(MachineState& state);

    // Clear vector ops
    void clearOps() { mOps.clear(); };
    
	// Destructor
	~Machine();
private:
	std::vector<std::shared_ptr<Op>> mOps;
};

template <typename MachineTraits>
void Machine<MachineTraits>::LoadMachine(const std::string& filename)
{
	// Parsing code
    mOps.clear();
    std::ifstream file(filename);
    /*
    if (!file.is_open())
    {
        throw FileLoadExcept();
    }
     */
    if (file.is_open())
    {
        int totalLines = 0;
        
        std::string str;
        // read number of lines
        while(std::getline(file, str))
        {
            totalLines++;
        }
        file.close();
        // reopen to read file again
        file.open(filename);
    
        std::string currentOps;
        while (std::getline(file, currentOps))
        {
            std::size_t commentPos = currentOps.find(';');
            // strip away comments
            if (commentPos != std::string::npos)
            {
                currentOps = currentOps.substr(0, commentPos);
            }
            size_t commaPos = currentOps.find(',');
            
            // ops without parameter
            if (commaPos == std::string::npos)
            {
                std::string::iterator end_pos = std::remove(currentOps.begin(), currentOps.end(), ' ');
                currentOps.erase(end_pos, currentOps.end());
                if (currentOps.compare("attack") == 0)
                {
                    mOps.push_back(std::make_shared<OpAttack>());
                }
                else if (currentOps.compare("ranged_attack") == 0)
                {
                    mOps.push_back(std::make_shared<OpRangedAttack>());
                }
                else if (currentOps.compare("forward") == 0)
                {
                    mOps.push_back(std::make_shared<OpForward>());
                }
                else if (currentOps.compare("endturn") == 0)
                {
                    mOps.push_back(std::make_shared<OpEndTurn>());
                }
                else if (currentOps.compare("test_wall") == 0)
                {
                    mOps.push_back(std::make_shared<OpTestWall>());
                }
                else if (currentOps.compare("test_random") == 0)
                {
                    mOps.push_back(std::make_shared<OpTestRandom>());
                }
                else if (currentOps.compare("test_passable") == 0)
                {
                    mOps.push_back(std::make_shared<OpTestPassable>());
                }
                // op with missing parameter
                else
                {
                    try
                    {
                        throw InvalidOp();
                    }
                    catch (std::exception& e)
                    {
                        std::cout << e.what() << std::endl;
                        std::cout << currentOps << std::endl;
                    }
                }
            }
            // ops with a parameter
            else
            {
                std::string paramOps = currentOps.substr(0, commaPos);
                std::string::iterator end_pos = std::remove(paramOps.begin(), paramOps.end(), ' ');
                paramOps.erase(end_pos, paramOps.end());
                
                std::string param = currentOps.substr(commaPos+1);
                std::stringstream str(param);
                int parameter;
                str >> parameter;
                
                // invalid parameter (not a number)
                if (!str)
                {
                    try
                    {
                        throw InvalidOp();
                    }
                    catch (std::exception& e)
                    {
                        std::cout << e.what() << std::endl;
                        std::cout << paramOps << std::endl;
                    }
                }
                else
                {
                    if (paramOps.compare("rotate") == 0)
                    {
                        mOps.push_back(std::make_shared<OpRotate>(parameter));
                    }
                    else if (paramOps.compare("test_human") == 0)
                    {
                        if (parameter > 0 && parameter <= 2)
                        {
                            mOps.push_back(std::make_shared<OpTestHuman>(parameter));
                        }
                        else
                        {
                            try
                            {
                                throw InvalidOp();
                            }
                            catch (std::exception& e)
                            {
                                std::cout << e.what() << std::endl;
                            }
                        }
                    }
                    else if (paramOps.compare("test_zombie") == 0)
                    {
                        if (parameter > 0 && parameter <= 2)
                        {
                            mOps.push_back(std::make_shared<OpTestZombie>(parameter));
                        }
                        else
                        {
                            try
                            {
                                throw InvalidOp();
                            }
                            catch (std::exception& e)
                            {
                                std::cout << e.what() << std::endl;
                            }
                        }
                    }
                    else if (paramOps.compare("je") == 0)
                    {
                        if (parameter > 0 && parameter <= totalLines)
                        {
                            mOps.push_back(std::make_shared<OpJe>(parameter));
                        }
                        else
                        {
                            try
                            {
                                throw InvalidOp();
                            }
                            catch (std::exception& e)
                            {
                                std::cout << e.what() << std::endl;
                            }
                        }
                    }
                    else if (paramOps.compare("jne") == 0)
                    {
                        if (parameter > 0 && parameter <= totalLines)
                        {
                            mOps.push_back(std::make_shared<OpJne>(parameter));
                        }
                        else
                        {
                            try
                            {
                                throw InvalidOp();
                            }
                            catch (std::exception& e)
                            {
                                std::cout << e.what() << std::endl;
                            }
                        }
                    }
                    else if (paramOps.compare("goto") == 0)
                    {
                        if (parameter > 0 && parameter <= totalLines)
                        {
                            mOps.push_back(std::make_shared<OpGoto>(parameter));
                        }
                        else
                        {
                            try
                            {
                                throw InvalidOp();
                            }
                            catch (std::exception& e)
                            {
                                std::cout << e.what() << std::endl;
                            }
                        }
                    }
                    // op that doesn't need parameter but has one
                    else
                    {
                        try
                        {
                            throw InvalidOp();
                        }
                        catch (std::exception& e)
                        {
                            std::cout << e.what() << std::endl;
                        }
                    }
                }
            }
        }
        
        file.close();
    }

    /*
    mOps.push_back(std::make_shared<OpRotate>(0));
	mOps.push_back(std::make_shared<OpRotate>(0));
	mOps.push_back(std::make_shared<OpRotate>(1));
	mOps.push_back(std::make_shared<OpGoto>(1));
	*/
}

template <typename MachineTraits>
void Machine<MachineTraits>::BindState(MachineState& state)
{
	state.mActionsPerTurn = MachineTraits::ACTIONS_PER_TURN;
	state.mInfectOnAttack = MachineTraits::INFECT_ON_ATTACK;
}

template <typename MachineTraits>
void Machine<MachineTraits>::TakeTurn(MachineState& state)
{
	std::cout << "TAKING TURN" << std::endl;
	state.mActionsTaken = 0;
	while (state.mActionsTaken < MachineTraits::ACTIONS_PER_TURN)
	{
		mOps.at(state.mProgramCounter - 1)->Execute(state);
	}
}

template <typename MachineTraits>
Machine<MachineTraits>::~Machine()
{
	mOps.clear();
}
