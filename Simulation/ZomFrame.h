//
//  ZomFrame.h
//  zombiewx
//
//  Created by Sanjay Madhav on 12/27/14.
//  Copyright (c) 2014 Sanjay Madhav. All rights reserved.
//

#pragma once
#include <wx/frame.h>
#include <wx/timer.h>
#include <wx/menu.h>
#include "Machine.h"
#include "Traits.h"

class ZomFrame : public wxFrame
{
public:
	ZomFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	~ZomFrame();
private:
	void OnExit(wxCommandEvent& event);
	void OnNew(wxCommandEvent& event);
    void LoadZombie(wxCommandEvent& event);
    void LoadSurvivor(wxCommandEvent& event);
    void Randomize(wxCommandEvent& event);
    void Reset(wxCommandEvent& event);
	void OnSimStart(wxCommandEvent& event);
	void OnTurnTimer(wxTimerEvent& event);
	
	wxDECLARE_EVENT_TABLE();
private:
	// Panel for drawing
	class ZomDrawPanel* mPanel;
	
	// Simulation menu
	wxMenu* mSimMenu;
	
	// Turn timer
	wxTimer* mTurnTimer;

	// TEST MACHINES
	Machine<ZombieTraits> mZombieMachine;
    Machine<HumanTraits> mHumanMachine;
    // Vector of all zombies
    std::vector<std::shared_ptr<MachineState>> mZombieStates;
    // Vector of all humans
    std::vector<std::shared_ptr<MachineState>> mHumanStates;
    
    int mTurns;
    bool mIsActive;
};
