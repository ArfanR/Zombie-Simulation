// zompiler.cpp : Defines the entry point for the console application.
//

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include "node.h"
#include <fstream>

extern int g_LineNumber;
extern NBlock* g_MainBlock;

extern int zompilerparse();
extern FILE* zompilerin;

int main(int argc, char* argv[])
{
	// Read input from the first command line parameter
	zompilerin = fopen(argv[1], "r");
	
	// Start the parse
	zompilerparse();
	
	// CodeGen from g_MainBlock
    if (g_MainBlock)
    {
        CodeContext currentContext;
        g_MainBlock->CodeGen(currentContext);
        
        // locate goto chains
        auto pair = currentContext.mGoto.begin();
        auto jump = currentContext.mGoto.begin()->second;
        pair++;
        // iterate through the chain
        for (; jump == (pair->first); pair++)
        {
            jump = pair->second;
            if (jump == 1) { break; }
        }
    
        // replace all goto lines
        for (const auto& it: currentContext.mGoto)
        {
            currentContext.mOps[it.first-1] = "goto,1";
        }
        
        // create output file
        std::ofstream outFile("out.zom");
        // open file
        if (!outFile.is_open())
        {
            std::cout << "Cannot create out.zom." << std::endl;
        }
        else
        {
            // print each op to file
            for (const auto& singleOp: currentContext.mOps)
            {
                outFile << singleOp << std::endl;
            }
        }
    }
    
    // Close the file stream
	fclose(zompilerin);

	return 0;
}

void zompilererror(const char* s)
{
	std::cout << s << " on line " << g_LineNumber << std::endl;
}
