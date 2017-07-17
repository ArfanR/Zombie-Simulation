//
//  ZomDrawPanel.cpp
//  zombiewx
//
//  Created by Sanjay Madhav on 12/27/14.
//  Copyright (c) 2014 Sanjay Madhav. All rights reserved.
//

#include "ZomDrawPanel.h"
#include <wx/dcclient.h>
#include <wx/sizer.h>
#include "Machine.h"
#include "World.hpp"

BEGIN_EVENT_TABLE(ZomDrawPanel, wxPanel)
	EVT_PAINT(ZomDrawPanel::PaintEvent)
END_EVENT_TABLE()

ZomDrawPanel::ZomDrawPanel(wxFrame* parent)
: wxPanel(parent)
{
	mZombieFile = "";
    mHumanFile = "";
    mZombies = 0;
    mHumans = 0;
}

void ZomDrawPanel::PaintEvent(wxPaintEvent & evt)
{
	wxPaintDC dc(this);
	Render(dc);
}

void ZomDrawPanel::PaintNow()
{
	wxClientDC dc(this);
	Render(dc);
}

void ZomDrawPanel::Render(wxDC& dc)
{
	// Clear
	dc.SetBackground(*wxWHITE_BRUSH);
	dc.Clear();
	
	// Draw the grid
	DrawGrid(dc);
    // Draw the text
    DrawText(dc);
}

void ZomDrawPanel::DrawGrid(wxDC& dc)
{
	dc.SetPen(*wxBLACK_PEN);
    dc.SetBrush(*wxWHITE_BRUSH);
	dc.DrawRectangle(0, 0, 600, 600);
   
    wxPoint horizontalLine1(0, 0);
    wxPoint horizontalLine2(600, 0);
    wxPoint verticalLine1(0, 0);
    wxPoint verticalLine2(0, 600);
    
    // draw lines in the grid
    // 30 pixel squares
    while (horizontalLine1.y < 570)
    {
        horizontalLine1.y += 30;
        horizontalLine2.y += 30;
        dc.DrawLine(horizontalLine1, horizontalLine2);
    
        verticalLine1.x += 30;
        verticalLine2.x += 30;
        dc.DrawLine(verticalLine1, verticalLine2);
    }

    for (auto& inner : World::get().mBoard)
    {
        for (auto& j : inner)
        {
            if (j != nullptr)
            {
                // set brush for zombies/humans
                if (j->GetInfect())
                {
                    dc.SetBrush(*wxRED_BRUSH);
                }
                else
                {
                    dc.SetBrush(*wxGREEN_BRUSH);
                }
                
                // draw the triangle
                int x = j->GetXPoint();
                int y = j->GetYPoint();
                
                wxPoint pt1(0, 0);
                wxPoint pt2(0, 0);
                wxPoint pt3(0, 0);
                
                if (j->mFacing == MachineState::UP) // up
                {
                    pt1.x = x*30;
                    pt1.y = y*30 + 30;
                    
                    pt2.x = x*30 + 30;
                    pt2.y = y*30 + 30;
                    
                    pt3.x = x*30 + 15;
                    pt3.y = y*30;
                    
                    wxPoint ptArr[3]{ pt1, pt2, pt3 };
                    dc.DrawPolygon(3, ptArr);
                }
                else if (j->mFacing == MachineState::RIGHT) // right
                {
                    pt1.x = x*30;
                    pt1.y = y*30;
                    
                    pt2.x = x*30;
                    pt2.y = y*30 + 30;
                    
                    pt3.x = x*30 + 30;
                    pt3.y = y*30 + 15;
                    
                    wxPoint ptArr[3]{ pt1, pt2, pt3 };
                    dc.DrawPolygon(3, ptArr);
                }
                else if (j->mFacing == MachineState::DOWN) // down
                {
                    pt1.x = x*30;
                    pt1.y = y*30;
                    
                    pt2.x = x*30 + 30;
                    pt2.y = y*30;
                    
                    pt3.x = x*30 + 15;
                    pt3.y = y*30 + 30;
                    
                    wxPoint ptArr[3]{ pt1, pt2, pt3 };
                    dc.DrawPolygon(3, ptArr);
                }
                else if (j->mFacing == MachineState::LEFT) // left
                {
                    pt1.x = x*30 + 30;
                    pt1.y = y*30;
                    
                    pt2.x = x*30 + 30;
                    pt2.y = y*30 + 30;
                    
                    pt3.x = x*30;
                    pt3.y = y*30 + 15;
                    
                    wxPoint ptArr[3]{ pt1, pt2, pt3 };
                    dc.DrawPolygon(3, ptArr);
                }
                
            }
        }
    }
    
}

void ZomDrawPanel::SetZombieFile(std::string file)
{
    mZombieFile = file;
}

void ZomDrawPanel::SetHumanFile(std::string file)
{
    mHumanFile = file;
}

void ZomDrawPanel::SetZombies(int zombies)
{
    mZombies = zombies;
}

void ZomDrawPanel::SetHumans(int humans)
{
    mHumans = humans;
}

void ZomDrawPanel::SetMonths(int months)
{
    mMonths = months;
}

void ZomDrawPanel::DrawText(wxDC& dc)
{
    wxString zomString("Zombies");
    wxString zomFileString("Program: " + mZombieFile);
    wxString zomAlive("Alive: " + std::to_string(mZombies));
    dc.SetTextForeground(*wxRED);
    dc.DrawText(zomString, 630, 10);
    dc.DrawText(zomFileString, 630, 30);
    dc.DrawText(zomAlive, 630, 50);
    
    wxString humanString("Humans");
    wxString humanFileString("Program: " + mHumanFile);
    wxString humanAlive("Alive: " + std::to_string(mHumans));
    dc.SetTextForeground(*wxGREEN);
    dc.DrawText(humanString, 630, 110);
    dc.DrawText(humanFileString, 630, 130);
    dc.DrawText(humanAlive, 630, 150);
    
    wxString monthString("Months: " + std::to_string(mMonths));
    dc.SetTextForeground(*wxBLACK);
    dc.DrawText(monthString, 630, 210);
}
