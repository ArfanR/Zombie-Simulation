//
//  World.hpp
//  zombiewx-mac
//
//  Created by Arfan Rehab on 3/30/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#ifndef World_hpp
#define World_hpp

#define DECLARE_SINGLETON(SingletonClass) friend class Singleton<SingletonClass>;

#include <stdio.h>
#include <vector>
#include "Singleton.h"
#include "Machine.h"

class World: public Singleton<World>
{
    DECLARE_SINGLETON(World)
    
private:
    World();
    
public:
    // store all surviving humans
    std::vector<std::shared_ptr<MachineState>> mTotalHumans;
    // store  all surviving zombies
    std::vector<std::shared_ptr<MachineState>> mTotalZombies;
    // grid of all zombies and humans
    std::vector<std::vector<std::shared_ptr<MachineState>>> mBoard;
    
};

#endif /* World_hpp */
