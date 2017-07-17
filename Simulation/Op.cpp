#include "Op.h"
#include "Machine.h"
#include "World.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>

// Output state information for debugging purposes
void Op::DebugOutput(MachineState& state)
{
	std::cout << state.mProgramCounter << ":" << mOpName << "," << mParam << std::endl;
    std::cout << "x: " << state.GetXPoint() << ", y: " << state.GetYPoint() << std::endl;
}

void OpAttack::Execute(MachineState& state)
{
    DebugOutput(state);
    // attacker is a zombie
    if (state.GetInfect())
    {
        if (state.mFacing == MachineState::UP)
        {
            if (state.GetYPoint()-1 >= 0)
            {
                // find human or zombie to attack
                if ((World::get().mBoard[state.GetYPoint()-1][state.GetXPoint()]) != (nullptr))
                {
                    // Attacked human becomes zombie in world
                    if (!(World::get().mBoard[state.GetYPoint()-1][state.GetXPoint()]->GetInfect()))
                    {
                        int index = 0;
                        // find the zombie in the zombie vector
                        for (auto& z : World::get().mTotalZombies)
                        {
                            if (z->GetXPoint() == state.GetXPoint() && z->GetYPoint() == state.GetYPoint()-1)
                            {
                                World::get().mBoard[state.GetYPoint()-1][state.GetXPoint()] = World::get().mTotalZombies[index];
                                World::get().mTotalZombies.push_back(World::get().mTotalZombies[index]);
                                break;
                            }
                            index++;
                        }
                        index = 0;
                        // find human to erase
                        for (auto& h : World::get().mTotalHumans)
                        {
                            if (h->GetXPoint() == state.GetXPoint() && h->GetYPoint() == state.GetYPoint()-1)
                            {
                                World::get().mTotalHumans.erase(World::get().mTotalHumans.begin() + index);
                                break;
                            }
                            index++;
                        }
                    }
                }
            }
        }
        else if (state.mFacing == MachineState::LEFT)
        {
            if (state.GetXPoint()-1 >= 0)
            {
                // find human or zombie to attack
                if ((World::get().mBoard[state.GetYPoint()][state.GetXPoint()-1]) != (nullptr))
                {
                    // Attacked human becomes zombie in world
                    if (!(World::get().mBoard[state.GetYPoint()][state.GetXPoint()-1]->GetInfect()))
                    {
                        int index = 0;
                        // find the zombie in the zombie vector
                        for (auto& z : World::get().mTotalZombies)
                        {
                            if (z->GetXPoint() == state.GetXPoint()-1 && z->GetYPoint() == state.GetYPoint())
                            {
                                World::get().mBoard[state.GetYPoint()][state.GetXPoint()-1] = World::get().mTotalZombies[index];
                                World::get().mTotalZombies.push_back(World::get().mTotalZombies[index]);
                                break;
                            }
                            index++;
                        }
                        index = 0;
                        // find human to erase
                        for (auto& h : World::get().mTotalHumans)
                        {
                            if (h->GetXPoint() == state.GetXPoint()-1 && h->GetYPoint() == state.GetYPoint())
                            {
                                World::get().mTotalHumans.erase(World::get().mTotalHumans.begin() + index);
                                break;
                            }
                            index++;
                        }
                    }
                }
            }
        }
        else if (state.mFacing == MachineState::RIGHT)
        {
            if (state.GetXPoint()+1 <= 19)
            {
                // find human or zombie to attack
                if ((World::get().mBoard[state.GetYPoint()][state.GetXPoint()+1]) != (nullptr))
                {
                    // Attacked human becomes zombie in world
                    if (!(World::get().mBoard[state.GetYPoint()][state.GetXPoint()+1]->GetInfect()))
                    {
                        int index = 0;
                        // find the zombie in the zombie vector
                        for (auto& z : World::get().mTotalZombies)
                        {
                            if (z->GetXPoint() == state.GetXPoint()+1 && z->GetYPoint() == state.GetYPoint())
                            {
                                World::get().mBoard[state.GetYPoint()][state.GetXPoint()+1] = World::get().mTotalZombies[index];
                                World::get().mTotalZombies.push_back(World::get().mTotalZombies[index]);
                                break;
                            }
                            index++;
                        }
                        index = 0;
                        // find human to erase
                        for (auto& h : World::get().mTotalHumans)
                        {
                            if (h->GetXPoint() == state.GetXPoint()+1 && h->GetYPoint() == state.GetYPoint())
                            {
                                World::get().mTotalHumans.erase(World::get().mTotalHumans.begin() + index);
                                break;
                            }
                            index++;
                        }
                    }
                }
            }
        }
        else if (state.mFacing == MachineState::DOWN)
        {
            if (state.GetYPoint()+1 <= 19)
            {
                // find human or zombie to attack
                if ((World::get().mBoard[state.GetYPoint()+1][state.GetXPoint()]) != (nullptr))
                {
                    // Attacked human becomes zombie in world
                    if (!(World::get().mBoard[state.GetYPoint()+1][state.GetXPoint()]->GetInfect()))
                    {
                        int index = 0;
                        // find the zombie in the zombie vector
                        for (auto& z : World::get().mTotalZombies)
                        {
                            if (z->GetXPoint() == state.GetXPoint() && z->GetYPoint() == state.GetYPoint()+1)
                            {
                                World::get().mBoard[state.GetYPoint()+1][state.GetXPoint()] = World::get().mTotalZombies[index];
                                World::get().mTotalZombies.push_back(World::get().mTotalZombies[index]);
                                break;
                            }
                            index++;
                        }
                        index = 0;
                        // find human to erase
                        for (auto& h : World::get().mTotalHumans)
                        {
                            if (h->GetXPoint() == state.GetXPoint() && h->GetYPoint() == state.GetYPoint()+1)
                            {
                                World::get().mTotalHumans.erase(World::get().mTotalHumans.begin() + index);
                                break;
                            }
                            index++;
                        }
                    }
                }
            }
        }
    }
    // human attacker
    else
    {
        if (state.mFacing == MachineState::UP)
        {
            if (state.GetYPoint()-1 >= 0)
            {
                // find human or zombie to attack
                if ((World::get().mBoard[state.GetYPoint()-1][state.GetXPoint()]) != (nullptr))
                {
                    // Remove attacked human/zombie in world
                    if (World::get().mBoard[state.GetYPoint()-1][state.GetXPoint()]->GetInfect())
                    {
                        int index = 0;
                        // find the zombie in the zombie vector
                        for (auto& z : World::get().mTotalZombies)
                        {
                            if (z->GetXPoint() == state.GetXPoint() && z->GetYPoint() == state.GetYPoint()-1)
                            {
                                World::get().mBoard[state.GetYPoint()-1][state.GetXPoint()] = nullptr;
                                World::get().mTotalZombies.erase(World::get().mTotalZombies.begin() + index);
                                break;
                            }
                            index++;
                        }
                    }
                    else
                    {
                        int index = 0;
                        // find the human in the human vector
                        for (auto& h : World::get().mTotalHumans)
                        {
                            if (h->GetXPoint() == state.GetXPoint() && h->GetYPoint() == state.GetYPoint()-1)
                            {
                                World::get().mBoard[state.GetYPoint()-1][state.GetXPoint()] = nullptr;
                                World::get().mTotalHumans.erase(World::get().mTotalHumans.begin() + index);
                                break;
                            }
                            index++;
                        }
                    }
                }
            }
        }
        else if (state.mFacing == MachineState::LEFT)
        {
            if (state.GetXPoint()-1 >= 0)
            {
                // find human or zombie to attack
                if ((World::get().mBoard[state.GetYPoint()][state.GetXPoint()-1]) != (nullptr))
                {
                    // Remove attacked zombie or human in the world
                    if (World::get().mBoard[state.GetYPoint()][state.GetXPoint()-1]->GetInfect())
                    {
                        int index = 0;
                        // find the zombie in the zombie vector
                        for (auto& z : World::get().mTotalZombies)
                        {
                            if (z->GetXPoint() == state.GetXPoint()-1 && z->GetYPoint() == state.GetYPoint())
                            {
                                World::get().mBoard[state.GetYPoint()][state.GetXPoint()-1] = nullptr;
                                World::get().mTotalZombies.erase(World::get().mTotalZombies.begin() + index);
                                break;
                            }
                            index++;
                        }
                    }
                    else
                    {
                        int index = 0;
                        // find the human in the human vector
                        for (auto& h : World::get().mTotalHumans)
                        {
                            if (h->GetXPoint() == state.GetXPoint()-1 && h->GetYPoint() == state.GetYPoint())
                            {
                                World::get().mBoard[state.GetYPoint()][state.GetXPoint()-1] = nullptr;
                                World::get().mTotalHumans.erase(World::get().mTotalHumans.begin() + index);
                                break;
                            }
                            index++;
                        }
                    }
                }
            }
        }
        else if (state.mFacing == MachineState::RIGHT)
        {
            if (state.GetXPoint()+1 <= 19)
            {
                // find human or zombie to attack
                if ((World::get().mBoard[state.GetYPoint()][state.GetXPoint()+1]) != (nullptr))
                {
                    if (World::get().mBoard[state.GetYPoint()][state.GetXPoint()+1]->GetInfect())
                    {
                        int index = 0;
                        // find the zombie in the zombie vector
                        for (auto& z : World::get().mTotalZombies)
                        {
                            if (z->GetXPoint() == state.GetXPoint()+1 && z->GetYPoint() == state.GetYPoint())
                            {
                                World::get().mBoard[state.GetYPoint()][state.GetXPoint()+1] = nullptr;
                                World::get().mTotalZombies.erase(World::get().mTotalZombies.begin() + index);
                                break;
                            }
                            index++;
                        }
                    }
                    else
                    {
                        int index = 0;
                        // find the human in the human vector
                        for (auto& h : World::get().mTotalHumans)
                        {
                            if (h->GetXPoint() == state.GetXPoint()+1 && h->GetYPoint() == state.GetYPoint())
                            {
                                World::get().mBoard[state.GetYPoint()][state.GetXPoint()+1] = nullptr;
                                World::get().mTotalHumans.erase(World::get().mTotalHumans.begin() + index);
                                break;
                            }
                            index++;
                        }
                    }
                }
            }
        }
        else if (state.mFacing == MachineState::DOWN)
        {
            if (state.GetYPoint()+1 <= 19)
            {
                // find human or zombie to attack
                if ((World::get().mBoard[state.GetYPoint()+1][state.GetXPoint()]) != (nullptr))
                {
                    if (World::get().mBoard[state.GetYPoint()+1][state.GetXPoint()]->GetInfect())
                    {
                        int index = 0;
                        // find the zombie in the zombie vector
                        for (auto& z : World::get().mTotalZombies)
                        {
                            if (z->GetXPoint() == state.GetXPoint() && z->GetYPoint() == state.GetYPoint()+1)
                            {
                                World::get().mBoard[state.GetYPoint()+1][state.GetXPoint()] = nullptr;
                                World::get().mTotalZombies.erase(World::get().mTotalZombies.begin() + index);
                                break;
                            }
                            index++;
                        }
                    }
                    else
                    {
                        int index = 0;
                        // find the human in the human vector
                        for (auto& h : World::get().mTotalHumans)
                        {
                            if (h->GetXPoint() == state.GetXPoint() && h->GetYPoint() == state.GetYPoint()+1)
                            {
                                World::get().mBoard[state.GetYPoint()+1][state.GetXPoint()] = nullptr;
                                World::get().mTotalHumans.erase(World::get().mTotalHumans.begin() + index);
                                break;
                            }
                            index++;
                        }
                    }
                }
            }
        }
    }
    
    state.mProgramCounter++;
    state.mActionsTaken++;
}

void OpRangedAttack::Execute(MachineState& state)
{
    DebugOutput(state);
    
    if (!state.GetInfect()) // must be human attacker
    {
        if (state.mFacing == MachineState::UP)
        {
            if (state.GetYPoint()-2 >= 0)
            {
                // find human or zombie to attack
                if ((World::get().mBoard[state.GetYPoint()-2][state.GetXPoint()]) != (nullptr))
                {
                    // Remove attacked human/zombie in world
                    if (World::get().mBoard[state.GetYPoint()-2][state.GetXPoint()]->GetInfect())
                    {
                        int index = 0;
                        // find the zombie in the zombie vector
                        for (auto& z : World::get().mTotalZombies)
                        {
                            if (z->GetXPoint() == state.GetXPoint() && z->GetYPoint() == state.GetYPoint()-2)
                            {
                                World::get().mBoard[state.GetYPoint()-2][state.GetXPoint()] = nullptr;
                                World::get().mTotalZombies.erase(World::get().mTotalZombies.begin() + index);
                                break;
                            }
                            index++;
                        }
                    }
                    else
                    {
                        int index = 0;
                        // find the human in the human vector
                        for (auto& h : World::get().mTotalHumans)
                        {
                            if (h->GetXPoint() == state.GetXPoint() && h->GetYPoint() == state.GetYPoint()-2)
                            {
                                World::get().mBoard[state.GetYPoint()-2][state.GetXPoint()] = nullptr;
                                World::get().mTotalHumans.erase(World::get().mTotalHumans.begin() + index);
                                break;
                            }
                            index++;
                        }
                    }
                }
            }
        }
        else if (state.mFacing == MachineState::LEFT)
        {
            if (state.GetXPoint()-2 >= 0)
            {
                // find human or zombie to attack
                if ((World::get().mBoard[state.GetYPoint()][state.GetXPoint()-2]) != (nullptr))
                {
                    // Remove attacked zombie or human in the world
                    if (World::get().mBoard[state.GetYPoint()][state.GetXPoint()-2]->GetInfect())
                    {
                        int index = 0;
                        // find the zombie in the zombie vector
                        for (auto& z : World::get().mTotalZombies)
                        {
                            if (z->GetXPoint() == state.GetXPoint()-2 && z->GetYPoint() == state.GetYPoint())
                            {
                                World::get().mBoard[state.GetYPoint()][state.GetXPoint()-2] = nullptr;
                                World::get().mTotalZombies.erase(World::get().mTotalZombies.begin() + index);
                                break;
                            }
                            index++;
                        }
                    }
                    else
                    {
                        int index = 0;
                        // find the human in the human vector
                        for (auto& h : World::get().mTotalHumans)
                        {
                            if (h->GetXPoint() == state.GetXPoint()-2 && h->GetYPoint() == state.GetYPoint())
                            {
                                World::get().mBoard[state.GetYPoint()][state.GetXPoint()-2] = nullptr;
                                World::get().mTotalHumans.erase(World::get().mTotalHumans.begin() + index);
                                break;
                            }
                            index++;
                        }
                    }
                }
            }
        }
        else if (state.mFacing == MachineState::RIGHT)
        {
            if (state.GetXPoint()+2 <= 19)
            {
                // find human or zombie to attack
                if ((World::get().mBoard[state.GetYPoint()][state.GetXPoint()+2]) != (nullptr))
                {
                    if (World::get().mBoard[state.GetYPoint()][state.GetXPoint()+2]->GetInfect())
                    {
                        int index = 0;
                        // find the zombie in the zombie vector
                        for (auto& z : World::get().mTotalZombies)
                        {
                            if (z->GetXPoint() == state.GetXPoint()+2 && z->GetYPoint() == state.GetYPoint())
                            {
                                World::get().mBoard[state.GetYPoint()][state.GetXPoint()+2] = nullptr;
                                World::get().mTotalZombies.erase(World::get().mTotalZombies.begin() + index);
                                break;
                            }
                            index++;
                        }
                    }
                    else
                    {
                        int index = 0;
                        // find the human in the human vector
                        for (auto& h : World::get().mTotalHumans)
                        {
                            if (h->GetXPoint() == state.GetXPoint()+2 && h->GetYPoint() == state.GetYPoint())
                            {
                                World::get().mBoard[state.GetYPoint()][state.GetXPoint()+2] = nullptr;
                                World::get().mTotalHumans.erase(World::get().mTotalHumans.begin() + index);
                                break;
                            }
                            index++;
                        }
                    }
                }
            }
        }
        else if (state.mFacing == MachineState::DOWN)
        {
            if (state.GetYPoint()+2 <= 19)
            {
                // find human or zombie to attack
                if ((World::get().mBoard[state.GetYPoint()+2][state.GetXPoint()]) != (nullptr))
                {
                    if (World::get().mBoard[state.GetYPoint()+2][state.GetXPoint()]->GetInfect())
                    {
                        int index = 0;
                        // find the zombie in the zombie vector
                        for (auto& z : World::get().mTotalZombies)
                        {
                            if (z->GetXPoint() == state.GetXPoint() && z->GetYPoint() == state.GetYPoint()+2)
                            {
                                World::get().mBoard[state.GetYPoint()+2][state.GetXPoint()] = nullptr;
                                World::get().mTotalZombies.erase(World::get().mTotalZombies.begin() + index);
                                break;
                            }
                            index++;
                        }
                    }
                    else
                    {
                        int index = 0;
                        // find the human in the human vector
                        for (auto& h : World::get().mTotalHumans)
                        {
                            if (h->GetXPoint() == state.GetXPoint() && h->GetYPoint() == state.GetYPoint()+2)
                            {
                                World::get().mBoard[state.GetYPoint()+2][state.GetXPoint()] = nullptr;
                                World::get().mTotalHumans.erase(World::get().mTotalHumans.begin() + index);
                                break;
                            }
                            index++;
                        }
                    }
                }
            }
        }
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
            //wxMessageBox("Zombies can't range attack!", "Error", wxOK | wxICON_ERROR);
        }
    }
    
    state.mProgramCounter++;
    state.mActionsTaken++;
}

void OpRotate::Execute(MachineState& state)
{
	DebugOutput(state);
    
	switch (state.mFacing)
	{
	case (MachineState::UP) :
		if (mParam == 0)
		{
			state.mFacing = MachineState::RIGHT;
		}
		else
		{
			state.mFacing = MachineState::LEFT;
		}
		break;
	case (MachineState::RIGHT) :
		if (mParam == 0)
		{
			state.mFacing = MachineState::DOWN;
		}
		else
		{
			state.mFacing = MachineState::UP;
		}
		break;
	case (MachineState::DOWN) :
		if (mParam == 0)
		{
			state.mFacing = MachineState::LEFT;
		}
		else
		{
			state.mFacing = MachineState::RIGHT;
		}
		break;
	default:
	case (MachineState::LEFT) :
		if (mParam == 0)
		{
			state.mFacing = MachineState::UP;
		}
		else
		{
			state.mFacing = MachineState::DOWN;
		}
		break;
	}

	/*std::cout << "Now facing ";
	switch (state.mFacing)
	{
	case (MachineState::UP):
		std::cout << "UP";
		break;
	case (MachineState::RIGHT):
		std::cout << "RIGHT";
		break;
	case (MachineState::DOWN):
		std::cout << "DOWN";
		break;
	case (MachineState::LEFT):
		std::cout << "LEFT";
		break;
	}
	std::cout << std::endl;*/
	state.mProgramCounter++;
	state.mActionsTaken++;
}

void OpForward::Execute(MachineState& state)
{
    DebugOutput(state);
    
    if (state.mFacing == MachineState::UP)
    {
        if (state.GetYPoint()-1 >= 0)
        {
            bool openSpaceUp = (World::get().mBoard[state.GetYPoint()-1][state.GetXPoint()]) == (nullptr);
            if (openSpaceUp)
            {
                state.SetYPoint(state.GetYPoint()-1);
            }
        }
    }
    else if (state.mFacing == MachineState::LEFT)
    {
        if (state.GetXPoint()-1 >= 0)
        {
            bool openSpaceLeft = (World::get().mBoard[state.GetYPoint()][state.GetXPoint()-1]) == (nullptr);
            if (openSpaceLeft)
            {
                state.SetXPoint(state.GetXPoint()-1);
            }
        }
        
    }
    else if (state.mFacing == MachineState::RIGHT)
    {
        if (state.GetXPoint()+1 <= 19)
        {
            bool openSpaceRight = (World::get().mBoard[state.GetYPoint()][state.GetXPoint()+1]) == (nullptr);
            if (openSpaceRight)
            {
                state.SetXPoint(state.GetXPoint()+1);
            }
        }
    }
    else if (state.mFacing == MachineState::DOWN)
    {
        if (state.GetYPoint()+1 <= 19)
        {
            bool openSpaceDown = (World::get().mBoard[state.GetYPoint()+1][state.GetXPoint()]) == (nullptr);
            if (openSpaceDown)
            {
                state.SetYPoint(state.GetYPoint()+1);
            } 
        }
    }
    
    state.mProgramCounter++;
    state.mActionsTaken++;
    
}

void OpEndTurn::Execute(MachineState& state)
{
    DebugOutput(state);
    
    state.mProgramCounter++;
    state.mActionsTaken = state.GetActionsPerTurn();
}

void OpTestHuman::Execute(MachineState &state)
{
    DebugOutput(state);
    
    if (state.mFacing == MachineState::UP)
    {
        if (state.GetYPoint()-1 >= 0 && mParam == 1)
        {
            bool humanFoundUp = false;
            if ((World::get().mBoard[state.GetYPoint()-1][state.GetXPoint()]) != (nullptr))
            {
                if (!World::get().mBoard[state.GetYPoint()-1][state.GetXPoint()]->GetInfect())
                {
                    humanFoundUp = true;
                }
            }
            if (humanFoundUp)
            {
                state.mTest = true;
            }
            else
            {
                state.mTest = false;
            }
        }
        else if (state.GetYPoint()-2 >= 0 && mParam == 2)
        {
            bool humanFoundUp = false;
            if ((World::get().mBoard[state.GetYPoint()-2][state.GetXPoint()]) != (nullptr))
            {
                if (!World::get().mBoard[state.GetYPoint()-2][state.GetXPoint()]->GetInfect())
                {
                    humanFoundUp = true;
                }
            }
            if (humanFoundUp)
            {
                state.mTest = true;
            }
            else
            {
                state.mTest = false;
            }
        }
        else
        {
            state.mTest = false;
        }
    }
    else if (state.mFacing == MachineState::LEFT)
    {
        if (state.GetXPoint()-1 >= 0 && mParam == 1)
        {
            bool humanFoundLeft = false;
            if ((World::get().mBoard[state.GetYPoint()][state.GetXPoint()-1]) != (nullptr))
            {
                if (!World::get().mBoard[state.GetYPoint()][state.GetXPoint()-1]->GetInfect())
                {
                    humanFoundLeft = true;
                }
            }
            if (humanFoundLeft)
            {
                state.mTest = true;
            }
            else
            {
                state.mTest = false;
            }
        }
        else if (state.GetXPoint()-2 >= 0 && mParam == 2)
        {
            bool humanFoundLeft = false;
            if ((World::get().mBoard[state.GetYPoint()][state.GetXPoint()-2]) != (nullptr))
            {
                if (!World::get().mBoard[state.GetYPoint()][state.GetXPoint()-2]->GetInfect())
                {
                    humanFoundLeft = true;
                }
            }
            if (humanFoundLeft)
            {
                state.mTest = true;
            }
            else
            {
                state.mTest = false;
            }
        }
        else
        {
            state.mTest = false;
        }
    }
    else if (state.mFacing == MachineState::RIGHT)
    {
        if (state.GetXPoint()+1 <= 19 && mParam == 1)
        {
            bool humanFoundRight = false;
            if ((World::get().mBoard[state.GetYPoint()][state.GetXPoint()+1]) != (nullptr))
            {
                if (!World::get().mBoard[state.GetYPoint()][state.GetXPoint()+1]->GetInfect())
                {
                    humanFoundRight = true;
                }
            }
            if (humanFoundRight)
            {
                state.mTest = true;
            }
            else
            {
                state.mTest = false;
            }
        }
        else if (state.GetXPoint()+2 <= 19 && mParam == 2)
        {
            bool humanFoundRight = false;
            if ((World::get().mBoard[state.GetYPoint()][state.GetXPoint()+2]) != (nullptr))
            {
                if (!World::get().mBoard[state.GetYPoint()][state.GetXPoint()+2]->GetInfect())
                {
                    humanFoundRight = true;
                }
            }
            if (humanFoundRight)
            {
                state.mTest = true;
            }
            else
            {
                state.mTest = false;
            }
        }
        else
        {
            state.mTest = false;
        }
    }
    else if (state.mFacing == MachineState::DOWN)
    {
        if (state.GetYPoint()+1 <= 19 && mParam == 1)
        {
            bool humanFoundDown = false;
            if ((World::get().mBoard[state.GetYPoint()+1][state.GetXPoint()]) != (nullptr))
            {
                if (!World::get().mBoard[state.GetYPoint()+1][state.GetXPoint()]->GetInfect())
                {
                    humanFoundDown = true;
                }
            }
            if (humanFoundDown)
            {
                state.mTest = true;
            }
            else
            {
                state.mTest = false;
            }
        }
        else if (state.GetYPoint()+2 <= 19 && mParam == 2)
        {
            bool humanFoundDown = false;
            if ((World::get().mBoard[state.GetYPoint()+2][state.GetXPoint()]) != (nullptr))
            {
                if (!World::get().mBoard[state.GetYPoint()+2][state.GetXPoint()]->GetInfect())
                {
                    humanFoundDown = true;
                }
            }
            if (humanFoundDown)
            {
                state.mTest = true;
            }
            else
            {
                state.mTest = false;
            }
        }
        else
        {
            state.mTest = false;
        }
    }
    
    state.mProgramCounter++;
    
}

void OpTestWall::Execute(MachineState& state)
{
    DebugOutput(state);
    
    if (state.mFacing == MachineState::UP)
    {
        if (state.GetYPoint() == 0)
        {
            state.mTest = true;
        }
        else
        {
            state.mTest = false;
        }
    }
    else if (state.mFacing == MachineState::LEFT)
    {
        if (state.GetXPoint() == 0)
        {
            state.mTest = true;
        }
        else
        {
            state.mTest = false;
        }
    }
    else if (state.mFacing == MachineState::RIGHT)
    {
        if (state.GetXPoint() == 19)
        {
            state.mTest = true;
        }
        else
        {
            state.mTest = false;
        }
    }
    else if (state.mFacing == MachineState::DOWN)
    {
        if (state.GetYPoint() == 19)
        {
            state.mTest = true;
        }
        else
        {
            state.mTest = false;
        }
    }
    
    state.mProgramCounter++;
}

void OpTestZombie::Execute(MachineState &state)
{
    DebugOutput(state);
    
    if (state.mFacing == MachineState::UP)
    {
        if (state.GetYPoint()-1 >= 0 && mParam == 1)
        {
            bool zombieFound = false;
            if ((World::get().mBoard[state.GetYPoint()-1][state.GetXPoint()]) != (nullptr))
            {
                if (World::get().mBoard[state.GetYPoint()-1][state.GetXPoint()]->GetInfect())
                {
                    zombieFound = true;
                }
            }
            if (zombieFound)
            {
                state.mTest = true;
            }
            else
            {
                state.mTest = false;
            }
        }
        else if (state.GetYPoint()-2 >= 0 && mParam == 2)
        {
            bool zombieFound = false;
            if ((World::get().mBoard[state.GetYPoint()-2][state.GetXPoint()]) != (nullptr))
            {
                if (World::get().mBoard[state.GetYPoint()-2][state.GetXPoint()]->GetInfect())
                {
                    zombieFound = true;
                }
            }
            if (zombieFound)
            {
                state.mTest = true;
            }
            else
            {
                state.mTest = false;
            }
        }
        else
        {
            state.mTest = false;
        }
    }
    else if (state.mFacing == MachineState::LEFT)
    {
        if (state.GetXPoint()-1 >= 0 && mParam == 1)
        {
            bool zombieFound = false;
            if ((World::get().mBoard[state.GetYPoint()][state.GetXPoint()-1]) != (nullptr))
            {
                if (World::get().mBoard[state.GetYPoint()][state.GetXPoint()-1]->GetInfect())
                {
                    zombieFound = true;
                }
            }
            if (zombieFound)
            {
                state.mTest = true;
            }
            else
            {
                state.mTest = false;
            }
        }
        else if (state.GetXPoint()-2 >= 0 && mParam == 2)
        {
            bool zombieFound = false;
            if ((World::get().mBoard[state.GetYPoint()][state.GetXPoint()-2]) != (nullptr))
            {
                if (World::get().mBoard[state.GetYPoint()][state.GetXPoint()-2]->GetInfect())
                {
                    zombieFound = true;
                }
            }
            if (zombieFound)
            {
                state.mTest = true;
            }
            else
            {
                state.mTest = false;
            }
        }
        else
        {
            state.mTest = false;
        }
    }
    else if (state.mFacing == MachineState::RIGHT)
    {
        if (state.GetXPoint()+1 <= 19 && mParam == 1)
        {
            bool zombieFound = false;
            if ((World::get().mBoard[state.GetYPoint()][state.GetXPoint()+1]) != (nullptr))
            {
                if (World::get().mBoard[state.GetYPoint()][state.GetXPoint()+1]->GetInfect())
                {
                    zombieFound = true;
                }
            }
            if (zombieFound)
            {
                state.mTest = true;
            }
            else
            {
                state.mTest = false;
            }
        }
        else if (state.GetXPoint()+2 <= 19 && mParam == 2)
        {
            bool zombieFound = false;
            if ((World::get().mBoard[state.GetYPoint()][state.GetXPoint()+2]) != (nullptr))
            {
                if (World::get().mBoard[state.GetYPoint()][state.GetXPoint()+2]->GetInfect())
                {
                    zombieFound = true;
                }
            }
            if (zombieFound)
            {
                state.mTest = true;
            }
            else
            {
                state.mTest = false;
            }
        }
        else
        {
            state.mTest = false;
        }
    }
    else if (state.mFacing == MachineState::DOWN)
    {
        if (state.GetYPoint()+1 <= 19 && mParam == 1)
        {
            bool zombieFound = false;
            if ((World::get().mBoard[state.GetYPoint()+1][state.GetXPoint()]) != (nullptr))
            {
                if (World::get().mBoard[state.GetYPoint()+1][state.GetXPoint()]->GetInfect())
                {
                    zombieFound = true;
                }
            }
            if (zombieFound)
            {
                state.mTest = true;
            }
            else
            {
                state.mTest = false;
            }
        }
        else if (state.GetYPoint()+2 <= 19 && mParam == 2)
        {
            bool zombieFound = false;
            if ((World::get().mBoard[state.GetYPoint()+2][state.GetXPoint()]) != (nullptr))
            {
                if (World::get().mBoard[state.GetYPoint()+2][state.GetXPoint()]->GetInfect())
                {
                    zombieFound = true;
                }
            }
            if (zombieFound)
            {
                state.mTest = true;
            }
            else
            {
                state.mTest = false;
            }
        }
        else
        {
            state.mTest = false;
        }
    }
    
    state.mProgramCounter++;
}

void OpTestRandom::Execute(MachineState& state)
{
    DebugOutput(state);
    
    srand(static_cast<unsigned>(time(0)));
    
    int random = rand() % 2 + 1;
    if (random == 1)
    {
        state.mTest = true;
    }
    else
    {
        state.mTest = false;
    }
    
    state.mProgramCounter++;
}

void OpTestPassable::Execute(MachineState &state)
{
    DebugOutput(state);
    
    bool validUp = state.GetYPoint()-1 >= 0;
    bool validLeft = state.GetXPoint()-1 >= 0;
    bool validRight = state.GetXPoint()+1 <= 19;
    bool validDown = state.GetYPoint()+1 <= 19;

    if (state.mFacing == MachineState::UP)
    {
        if (validUp)
        {
            bool openSpaceUp = (World::get().mBoard[state.GetYPoint()-1][state.GetXPoint()]) == (nullptr);
            if (openSpaceUp)
            {
                state.mTest = true;
            }
            // facing zombie or human
            // rotate
            else
            {
                if (validLeft)
                {
                    if ((World::get().mBoard[state.GetYPoint()][state.GetXPoint()-1]) == (nullptr))
                    {
                       state.mFacing = MachineState::LEFT;
                    }
                }
                if (validRight)
                {
                    if ((World::get().mBoard[state.GetYPoint()][state.GetXPoint()+1]) == (nullptr))
                    {
                        state.mFacing = MachineState::RIGHT;
                    }
                }
                if (validDown)
                {
                    if ((World::get().mBoard[state.GetYPoint()+1][state.GetXPoint()]) == (nullptr))
                    {
                        state.mFacing = MachineState::DOWN;
                    }
                }
                state.mTest = false;
            }
        }
        // face the wall
        // rotate 
        else
        {
            if (validLeft)
            {
                if ((World::get().mBoard[state.GetYPoint()][state.GetXPoint()-1]) == (nullptr))
                {
                    state.mFacing = MachineState::LEFT;
                }
            }
            if (validRight)
            {
                if ((World::get().mBoard[state.GetYPoint()][state.GetXPoint()+1]) == (nullptr))
                {
                    state.mFacing = MachineState::RIGHT;
                }
            }
            if (validDown)
            {
                if ((World::get().mBoard[state.GetYPoint()+1][state.GetXPoint()]) == (nullptr))
                {
                    state.mFacing = MachineState::DOWN;
                }
            }
            state.mTest = false;
        }
    }
    else if (state.mFacing == MachineState::LEFT)
    {
        if (validLeft)
        {
            bool openSpaceLeft = (World::get().mBoard[state.GetYPoint()][state.GetXPoint()-1]) == (nullptr);
            if (openSpaceLeft)
            {
                state.mTest = true;
            }
            else{
                if (validUp)
                {
                    if ((World::get().mBoard[state.GetYPoint()-1][state.GetXPoint()]) == (nullptr))
                    {
                       state.mFacing = MachineState::UP;
                    }
                }
                if (validRight)
                {
                    if ((World::get().mBoard[state.GetYPoint()][state.GetXPoint()+1]) == (nullptr))
                    {
                        state.mFacing = MachineState::RIGHT;
                    }
                }
                if (validDown)
                {
                    if ((World::get().mBoard[state.GetYPoint()+1][state.GetXPoint()]) == (nullptr))
                    {
                        state.mFacing = MachineState::DOWN;
                    }
                }
                state.mTest = false;
            }
        }
        else
        {
            if (validUp)
            {
                if ((World::get().mBoard[state.GetYPoint()-1][state.GetXPoint()]) == (nullptr))
                {
                    state.mFacing = MachineState::UP;
                }
            }
            if (validRight)
            {
                if ((World::get().mBoard[state.GetYPoint()][state.GetXPoint()+1]) == (nullptr))
                {
                    state.mFacing = MachineState::RIGHT;
                }
            }
            if (validDown)
            {
                if ((World::get().mBoard[state.GetYPoint()+1][state.GetXPoint()]) == (nullptr))
                {
                    state.mFacing = MachineState::DOWN;
                }
            }
            state.mTest = false;
        }
        
    }
    else if (state.mFacing == MachineState::RIGHT)
    {
        if (validRight)
        {
            bool openSpaceRight = (World::get().mBoard[state.GetYPoint()][state.GetXPoint()+1]) == (nullptr);
            if (openSpaceRight)
            {
                state.mTest = true;
            }
            else
            {
                if (validLeft)
                {
                    if ((World::get().mBoard[state.GetYPoint()][state.GetXPoint()-1]) == (nullptr))
                    {
                        state.mFacing = MachineState::LEFT;
                    }
                }
                if (validUp)
                {
                    if ((World::get().mBoard[state.GetYPoint()-1][state.GetXPoint()]) == (nullptr))
                    {
                        state.mFacing = MachineState::UP;
                    }
                }
                if (validDown)
                {
                    if ((World::get().mBoard[state.GetYPoint()+1][state.GetXPoint()]) == (nullptr))
                    {
                        state.mFacing = MachineState::DOWN;
                    }
                }
                state.mTest = false;
            }
        }
        else
        {
            if (validLeft)
            {
                if ((World::get().mBoard[state.GetYPoint()][state.GetXPoint()-1]) == (nullptr))
                {
                    state.mFacing = MachineState::LEFT;
                }
            }
            if (validUp)
            {
                if ((World::get().mBoard[state.GetYPoint()-1][state.GetXPoint()]) == (nullptr))
                {
                    state.mFacing = MachineState::UP;
                }
            }
            if (validDown)
            {
                if ((World::get().mBoard[state.GetYPoint()+1][state.GetXPoint()]) == (nullptr))
                {
                    state.mFacing = MachineState::DOWN;
                }
            }
            state.mTest = false;
        }
    }
    else if (state.mFacing == MachineState::DOWN)
    {
        if (validDown)
        {
            bool openSpaceDown = (World::get().mBoard[state.GetYPoint()+1][state.GetXPoint()]) == (nullptr);
            if (openSpaceDown)
            {
                state.mTest = true;
            }
            else
            {
                if (validLeft)
                {
                    if ((World::get().mBoard[state.GetYPoint()][state.GetXPoint()-1]) == (nullptr))
                    {
                        state.mFacing = MachineState::LEFT;
                    }
                }
                if (validUp)
                {
                    if ((World::get().mBoard[state.GetYPoint()-1][state.GetXPoint()]) == (nullptr))
                    {
                        state.mFacing = MachineState::UP;
                    }
                }
                if (validRight)
                {
                    if ((World::get().mBoard[state.GetYPoint()][state.GetXPoint()+1]) == (nullptr))
                    {
                        state.mFacing = MachineState::RIGHT;
                    }
                }
                state.mTest = false;
            }
        }
        else
        {
            if (validLeft)
            {
                if ((World::get().mBoard[state.GetYPoint()][state.GetXPoint()-1]) == (nullptr))
                {
                    state.mFacing = MachineState::LEFT;
                }
            }
            if (validUp)
            {
                if ((World::get().mBoard[state.GetYPoint()-1][state.GetXPoint()]) == (nullptr))
                {
                    state.mFacing = MachineState::UP;
                }
            }
            if (validRight)
            {
                if ((World::get().mBoard[state.GetYPoint()][state.GetXPoint()+1]) == (nullptr))
                {
                    state.mFacing = MachineState::RIGHT;
                }
            }
            state.mTest = false;
        }
    }
    
    state.mProgramCounter++;
}

void OpJe::Execute(MachineState &state)
{
    DebugOutput(state);
    
    if (state.mTest)
    {
        state.mProgramCounter = mParam;
    }
    else
    {
        state.mProgramCounter++;
    }
}

void OpJne::Execute(MachineState &state)
{
    DebugOutput(state);
    
    if (state.mTest)
    {
        state.mProgramCounter++;
    }
    else
    {
        state.mProgramCounter = mParam;
    }
}

void OpGoto::Execute(MachineState& state)
{
    DebugOutput(state);
    state.mProgramCounter = mParam;
}

