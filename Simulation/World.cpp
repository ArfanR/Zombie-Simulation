//
//  World.cpp
//  zombiewx-mac
//
//  Created by Arfan Rehab on 3/30/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "World.hpp"

World::World()
{
    //mTotalZombies.resize(20);
    //mTotalHumans.resize(10);
    
    mBoard.resize(20);
    for (int i = 0; i < 20; i++)
    {
        mBoard[i].resize(20);
        for (int j = 0; j < 20; j++)
        {
            mBoard[i][j] = nullptr;
        }
    }
    
}
