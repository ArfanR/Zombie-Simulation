//
//  ZomDrawPanel.h
//  zombiewx
//
//  Created by Sanjay Madhav on 12/27/14.
//  Copyright (c) 2014 Sanjay Madhav. All rights reserved.
//

#pragma once
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <string>

class ZomDrawPanel : public wxPanel
{
 
public:
	ZomDrawPanel(wxFrame* parent);
	void PaintNow();
 
    std::string GetZombieFile() const noexcept { return mZombieFile; };
    std::string GetHumanFile() const noexcept { return mHumanFile; };
    
    int GetZombies() const noexcept { return mZombies; };
    int GetHumans() const noexcept { return mHumans; };
    int GetMonths() const noexcept { return mMonths; };
    
    void SetZombieFile(std::string file);
    void SetHumanFile(std::string file);
    
    void SetZombies(int zombies);
    void SetHumans(int humans);
    void SetMonths(int months);
    
protected:
	void PaintEvent(wxPaintEvent & evt);
	void Render(wxDC& dc);
	void DrawGrid(wxDC& dc);
    void DrawText(wxDC& dc);
    
	DECLARE_EVENT_TABLE()
	
public:
    std::string mZombieFile, mHumanFile;
    int mZombies, mHumans, mMonths;
};

