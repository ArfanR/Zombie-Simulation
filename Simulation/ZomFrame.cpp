//
//  ZomFrame.cpp
//  zombiewx
//
//  Created by Sanjay Madhav on 12/27/14.
//  Copyright (c) 2014 Sanjay Madhav. All rights reserved.
//

#include "ZomFrame.h"
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/log.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/filedlg.h>
#include "ZomDrawPanel.h"
#include "World.hpp"

enum
{
	ID_SImSTART=1000,
	ID_TURN_TIMER,
    ID_LOAD_ZOMBIE,
    ID_LOAD_SURVIVOR,
    ID_RANDOMIZE,
    ID_RESET,
};

wxBEGIN_EVENT_TABLE(ZomFrame, wxFrame)
	EVT_MENU(wxID_EXIT, ZomFrame::OnExit)
	EVT_MENU(wxID_NEW, ZomFrame::OnNew)
    EVT_MENU(ID_LOAD_ZOMBIE, ZomFrame::LoadZombie)
    EVT_MENU(ID_LOAD_SURVIVOR, ZomFrame::LoadSurvivor)
    EVT_MENU(ID_RANDOMIZE, ZomFrame::Randomize)
    EVT_MENU(ID_RESET, ZomFrame::Reset)
	EVT_MENU(ID_SImSTART, ZomFrame::OnSimStart)
	EVT_TIMER(ID_TURN_TIMER, ZomFrame::OnTurnTimer)
wxEND_EVENT_TABLE()

ZomFrame::ZomFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size)
, mIsActive(false)
{
	// File menu
	wxMenu* menuFile = new wxMenu;
	menuFile->Append(wxID_NEW);
	menuFile->Append(wxID_EXIT);
	
	// Simulation menu
	mSimMenu = new wxMenu;
    mSimMenu->Append(ID_LOAD_ZOMBIE, "Load Zombies", "Load Zombies");
    mSimMenu->Append(ID_LOAD_SURVIVOR, "Load Humans", "Load Humans");
    mSimMenu->Append(ID_RESET, "Reset", "Reset Simulation");
    mSimMenu->Append(ID_RANDOMIZE, "Randomize", "Random Zombies");
    mSimMenu->Append(ID_SImSTART, "Start/stop\tSpace", "Start or stop the simulation");
    
    mSimMenu->Enable(ID_SImSTART, false);
    mSimMenu->Enable(ID_RANDOMIZE, false);
    mSimMenu->Enable(ID_RESET, false);
    
    wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(mSimMenu, "&Simulation");
	SetMenuBar(menuBar);
	CreateStatusBar();
	
	// Prepare the draw panel and show this frame
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	mPanel = new ZomDrawPanel(this);
	sizer->Add(mPanel, 1, wxEXPAND);
	
	SetSizer(sizer);
	SetAutoLayout(true);
	Show(true);
	
	mTurnTimer = new wxTimer(this, ID_TURN_TIMER);
    mTurns = 0;

    // 20 zombies
    for (int i = 0; i < 20; i++)
    {
        mZombieStates.push_back(std::make_shared<MachineState>());
    }
    // 10 humans
    for (int i = 0; i < 10; i++)
    {
        mHumanStates.push_back(std::make_shared<MachineState>());
    }
    
}

ZomFrame::~ZomFrame()
{
	delete mTurnTimer;
}

void ZomFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void ZomFrame::OnNew(wxCommandEvent& event)
{
    Reset(event);
    mZombieMachine.clearOps();
    mHumanMachine.clearOps();
    mPanel->SetZombieFile("");
    mPanel->SetHumanFile("");
    mPanel->SetZombies(0);
    mPanel->SetHumans(0);
    mPanel->SetMonths(0);
    mTurns = 0;
    mPanel->PaintNow();
}

void ZomFrame::Reset(wxCommandEvent& event)
{
    mTurnTimer->Stop();
    
    // Clear all world vectors
    World::get().mTotalZombies.clear();
    World::get().mTotalHumans.clear();
    World::get().mBoard.clear();
    for (int i = 0; i < 20; i++)
    {
        World::get().mBoard[i].clear();
    }
    
    // Resize world vectors
    World::get().mBoard.resize(20);
    for (int i = 0; i < 20; i++)
    {
        World::get().mBoard[i].resize(20);
        for (int j = 0; j < 20; j++)
        {
            World::get().mBoard[i][j] = nullptr;
        }
    }
    
    // Clear member variables
    mZombieStates.clear();
    mHumanStates.clear();
    mTurns = 0;
    
    mPanel->SetZombies(static_cast<unsigned int>(World::get().mTotalZombies.size()));
    mPanel->SetHumans(static_cast<unsigned int>(World::get().mTotalHumans.size()));
    mPanel->SetMonths(0);
    mPanel->PaintNow();
}

void ZomFrame::LoadZombie(wxCommandEvent& event)
{
    wxFileDialog loadDialog(this, _("Load Zombies"), "./zom", "",
                             "ZOM files (*.zom)|*.zom", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    
    mSimMenu->Enable(ID_SImSTART, true);
    mSimMenu->Enable(ID_RANDOMIZE, true);
    mSimMenu->Enable(ID_RESET, true);
    
    if (loadDialog.ShowModal() == wxID_OK)
    {
        std::string path = loadDialog.GetPath().ToStdString();
        
        // loading instructions for zombie
        mZombieMachine.LoadMachine(path);
        
        for (auto& z : mZombieStates)
        {
            mZombieMachine.BindState(*z);
        }
        
        for (int i = 0; i < 20; i++)
        {
            World::get().mTotalZombies.push_back(mZombieStates[i]);
            World::get().mBoard[mZombieStates[i]->GetYPoint()][mZombieStates[i]->GetXPoint()] = mZombieStates[i];
        }
        
        mPanel->SetZombieFile(loadDialog.GetFilename().ToStdString());
        mPanel->SetZombies(static_cast<unsigned int>(World::get().mTotalZombies.size()));
        mPanel->SetHumans(static_cast<unsigned int>(World::get().mTotalHumans.size()));
        mPanel->SetMonths(0);
        mPanel->PaintNow();
    }
}

void ZomFrame::LoadSurvivor(wxCommandEvent& event)
{
    wxFileDialog loadDialog(this, _("Load Humans"), "./zom", "",
                            "ZOM files (*.zom)|*.zom", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    
    mSimMenu->Enable(ID_SImSTART, true);
    mSimMenu->Enable(ID_RANDOMIZE, true);
    mSimMenu->Enable(ID_RESET, true);
    
    if (loadDialog.ShowModal() == wxID_OK)
    {
        std::string path = loadDialog.GetPath().ToStdString();
        
        // loading instructions for human
        mHumanMachine.LoadMachine(path);
        
        for (auto& h : mHumanStates)
        {
            mHumanMachine.BindState(*h);
        }
        
        for (int i = 0; i < 10; i++)
        {
            World::get().mTotalHumans.push_back(mHumanStates[i]);
            World::get().mBoard[mHumanStates[i]->GetYPoint()][mHumanStates[i]->GetXPoint()] = mHumanStates[i];
        }
        
        mPanel->SetHumanFile(loadDialog.GetFilename().ToStdString());
        mPanel->SetZombies(static_cast<unsigned int>(World::get().mTotalZombies.size()));
        mPanel->SetHumans(static_cast<unsigned int>(World::get().mTotalHumans.size()));
        mPanel->SetMonths(0);
        mPanel->PaintNow();
    }

}

void ZomFrame::Randomize(wxCommandEvent& event)
{
    Reset(event);
    std::srand(static_cast<unsigned int>(time(0)));
    // Randomly place zombies
    std::rand(), std::rand(), std::rand();
    for (int i = 0; i < 20; i++)
    {
        int randX = std::rand() % 20;
        int randY = std::rand() % 20;
        std::shared_ptr<MachineState> zombie = std::make_shared<MachineState>();
        zombie->SetXPoint(randX);
        zombie->SetYPoint(randY);
        std::cout << zombie->GetXPoint() << std::endl;
        mZombieStates.push_back(zombie);
    }
    // Bind state zombies
    for (int i = 0; i < 20; i++)
    {
        mZombieMachine.BindState(*mZombieStates[i]);
        World::get().mTotalZombies.push_back(mZombieStates[i]);
        World::get().mBoard[mZombieStates[i]->GetYPoint()][mZombieStates[i]->GetXPoint()] = mZombieStates[i];
    }
    
    // Randomly place humans
    for (int i = 0; i < 10; i++)
    {
        int randX = std::rand() % 20;
        int randY = std::rand() % 20;
        std::shared_ptr<MachineState> human = std::make_shared<MachineState>();
        human->SetXPoint(randX);
        human->SetYPoint(randY);
        mHumanStates.push_back(human);
    }
    // bind state humans
    for (int i = 0; i < 10; i++)
    {
        mHumanMachine.BindState(*mHumanStates[i]);
        World::get().mTotalHumans.push_back(mHumanStates[i]);
        World::get().mBoard[mHumanStates[i]->GetYPoint()][mHumanStates[i]->GetXPoint()] = mHumanStates[i];
    }
    
    mPanel->SetZombies(static_cast<unsigned int>(World::get().mTotalZombies.size()));
    mPanel->SetHumans(static_cast<unsigned int>(World::get().mTotalHumans.size()));
    mPanel->SetMonths(mTurns);
    mPanel->PaintNow();
}

void ZomFrame::OnSimStart(wxCommandEvent& event)
{
	if (!mIsActive)
	{
		// Add timer to run once per second
		mTurnTimer->Start(1000);
		mIsActive = true;
	}
	else
	{
		mTurnTimer->Stop();
		mIsActive = false;
	}
    
    mTurns = 0;
}

void ZomFrame::OnTurnTimer(wxTimerEvent& event)
{
    mTurns += 1;
    
    mPanel->SetZombies(static_cast<unsigned int>(World::get().mTotalZombies.size()));
    mPanel->SetHumans(static_cast<unsigned int>(World::get().mTotalHumans.size()));
    mPanel->SetMonths(mTurns);

    for (int i = 0; i < 20; i++)
    {
        int x = mZombieStates[i]->GetXPoint();
        int y = mZombieStates[i]->GetYPoint();
        
        // Take turn for zombie machine
        mZombieMachine.TakeTurn(*mZombieStates[i]);
        mZombieMachine.BindState(*mZombieStates[i]);
        
        int xNew = mZombieStates[i]->GetXPoint();
        int yNew = mZombieStates[i]->GetYPoint();
        
        // Set new zombie coordinate in the World
        World::get().mBoard[y][x] = nullptr;
        World::get().mBoard[yNew][xNew] = mZombieStates[i];
    }
    
    for (int i = 0; i < 10; i++)
    {
        int x2 = mHumanStates[i]->GetXPoint();
        int y2 = mHumanStates[i]->GetYPoint();
        
        // Take turn for human machine
        mHumanMachine.TakeTurn(*mHumanStates[i]);
        mHumanMachine.BindState(*mHumanStates[i]);
        
        int xNew2 = mHumanStates[i]->GetXPoint();
        int yNew2 = mHumanStates[i]->GetYPoint();
        
        // Set new human coordinate in the World
        World::get().mBoard[y2][x2] = nullptr;
        World::get().mBoard[yNew2][xNew2] = mHumanStates[i];
        
    }
    
    if (static_cast<unsigned int>(World::get().mTotalZombies.size() == 0))
    {
        mTurnTimer->Stop();
        wxMessageBox("Humans won!", "Human win", wxOK | wxICON_INFORMATION);
    }
    else if (static_cast<unsigned int>(World::get().mTotalZombies.size() == 0))
    {
        mTurnTimer->Stop();
        wxMessageBox("Zombies won!", "Zombie win", wxOK | wxICON_INFORMATION);
    }
    
    mPanel->PaintNow();
}
