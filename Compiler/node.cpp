#include "node.h"
#include <sstream>

void NBlock::AddStatement(NStatement* statement)
{
	mStatements.push_back(statement);
}

void NBlock::CodeGen(CodeContext& context) const
{
	// TODO: Loop through statements in list and code gen them
    for (const auto& it: mStatements)
    {
        (it)->CodeGen(context);
    }
    if (mbMainBlock)
    {
        context.mOps.push_back("goto,1");
        context.mGoto[static_cast<int>(context.mOps.size())] = 1;
    }
}

NNumeric::NNumeric(std::string& value)
{
	mvalue = std::atoi(value.c_str());
}

NRotate::NRotate(NNumeric* dir)
	: mDir(dir)
{
}

void NRotate::CodeGen(CodeContext& context) const
{
	if (mDir->mvalue == 0)
	{
		context.mOps.push_back("rotate,0");
	}
	else if (mDir->mvalue == 1)
	{
		context.mOps.push_back("rotate,1");
	}
}

NForward::NForward()
{
}

void NForward::CodeGen(CodeContext& context) const
{
    context.mOps.push_back("forward");
}

NAttack::NAttack()
{
}

void NAttack::CodeGen(CodeContext& context) const
{
    context.mOps.push_back("attack");
}

NRangedAttack::NRangedAttack()
{
}

void NRangedAttack::CodeGen(CodeContext& context) const
{
    context.mOps.push_back("ranged_attack");
}

NIsHuman::NIsHuman(NNumeric* val)
    : mVal(val)
{
}

void NIsHuman::CodeGen(CodeContext &context) const
{
    if (mVal->mvalue == 1)
    {
        context.mOps.push_back("test_human,1");
    }
    else if (mVal->mvalue == 2)
    {
        context.mOps.push_back("test_human,2");
    }
}

NIsZombie::NIsZombie(NNumeric* val)
    : mVal(val)
{
}

void NIsZombie::CodeGen(CodeContext &context) const
{
    if (mVal->mvalue == 1)
    {
        context.mOps.push_back("test_zombie,1");
    }
    else if (mVal->mvalue == 2)
    {
        context.mOps.push_back("test_zombie,2");
    }
}

NIsPassable::NIsPassable()
{
}

void NIsPassable::CodeGen(CodeContext &context) const
{
    context.mOps.push_back("test_passable");
}

NIsRandom::NIsRandom()
{
}

void NIsRandom::CodeGen(CodeContext &context) const
{
    context.mOps.push_back("test_random");
}

NIf::NIf()
    : mBool(nullptr), mIfBlock(nullptr), mElseBlock(nullptr)
{
}

NIf::NIf(NBoolean* cond, NBlock* ifBlock)
    : mBool(cond), mIfBlock(ifBlock), mElseBlock(nullptr)
{
}

NIf::NIf(NBoolean* cond, NBlock* ifBlock, NBlock* elseBlock)
    : mBool(cond), mIfBlock(ifBlock), mElseBlock(elseBlock)
{
}

void NIf::CodeGen(CodeContext &context) const
{
    // test flag
    mBool->CodeGen(context);
    
    // je to the if block
    context.mOps.push_back("je,rand");
    int posJe = static_cast<int>(context.mOps.size() - 1);
    
    // else block
    if (mElseBlock) { mElseBlock->CodeGen(context); }

    // goto past the if block
    context.mOps.push_back("goto,rand");
    int posGoto = static_cast<int>(context.mOps.size() - 1);
    int startIf = static_cast<int>(context.mOps.size() + 1);
    int goToLine = static_cast<int>(context.mOps.size());
    
    // if block
    mIfBlock->CodeGen(context);
    int endIf = static_cast<int>(context.mOps.size() + 1);
    
    // go back to fill line for je
    context.mOps[posJe] = "je," + std::to_string(startIf);
    // go back to fill goto line
    context.mOps[posGoto] = "goto," + std::to_string(endIf);
    // go to optimization
    context.mGoto[goToLine] = endIf;
}
