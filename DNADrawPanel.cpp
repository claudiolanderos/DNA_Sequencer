//
//  DNADrawPanel.cpp
//  DNAwx
//
//  Created by Sanjay Madhav on 12/27/14.
//  Copyright (c) 2014 Sanjay Madhav. All rights reserved.
//

#include "DNADrawPanel.h"
#include <wx/dcclient.h>
#include <wx/sizer.h>
#include <array>
#include <sstream>
#include <iomanip>

BEGIN_EVENT_TABLE(DNADrawPanel, wxPanel)
	EVT_PAINT(DNADrawPanel::PaintEvent)
END_EVENT_TABLE()

DNADrawPanel::DNADrawPanel(wxFrame* parent)
: wxPanel(parent)
{
	
}

void DNADrawPanel::PaintEvent(wxPaintEvent & evt)
{
	wxPaintDC dc(this);
	Render(dc);
}

void DNADrawPanel::PaintNow()
{
	wxClientDC dc(this);
	Render(dc);
}

void DNADrawPanel::Render(wxDC& dc)
{
	// Clear
	dc.SetBackground(*wxWHITE_BRUSH);
	dc.Clear();
	
	// TODO: Draw histogram, if one has been generated
    dc.SetPen(*wxBLACK_PEN);
    dc.SetTextForeground(*wxBLACK);
    
    // Draw header
    dc.DrawText(mHeader, 5, 5);
    
    // Draw histogram
    if(mAminoAcidCount != nullptr)
    {
        for(auto iter : *mAminoAcidCount)
        {
            
        }
    }
    else {
        // throw exception
    }
    //Draw header with some space
    // for loop to draw all amino acids
        //First part of for loop draw name
        //Second part of for loop draw bar
        
}
