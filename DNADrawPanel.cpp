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
    mAminoAcidNames.insert(std::make_pair('A', "Alanine"));
    mAminoAcidNames.insert(std::make_pair('R', "Arginine"));
    mAminoAcidNames.insert(std::make_pair('N', "Asparagine"));
    mAminoAcidNames.insert(std::make_pair('D', "Aspartic Acid"));
    mAminoAcidNames.insert(std::make_pair('C', "Cysteine"));
    mAminoAcidNames.insert(std::make_pair('Q', "Glutamine"));
    mAminoAcidNames.insert(std::make_pair('E', "Glutamic Acid"));
    mAminoAcidNames.insert(std::make_pair('G', "Glycine"));
    mAminoAcidNames.insert(std::make_pair('H', "Histidine"));
    mAminoAcidNames.insert(std::make_pair('I', "Isoleucine"));
    mAminoAcidNames.insert(std::make_pair('L', "Leucine"));
    mAminoAcidNames.insert(std::make_pair('K', "Lysine"));
    mAminoAcidNames.insert(std::make_pair('M', "Methionine"));
    mAminoAcidNames.insert(std::make_pair('F', "Phenylalanine"));
    mAminoAcidNames.insert(std::make_pair('P', "Proline"));
    mAminoAcidNames.insert(std::make_pair('S', "Serine"));
    mAminoAcidNames.insert(std::make_pair('T', "Threonine"));
    mAminoAcidNames.insert(std::make_pair('W', "Tryptophan"));
    mAminoAcidNames.insert(std::make_pair('Y', "Tyrosine"));
    mAminoAcidNames.insert(std::make_pair('V', "Valine"));
}

void DNADrawPanel::SetHistogramVariables(std::shared_ptr<std::unordered_map<char, int> > aminoAcidCount, int total, int largest, std::string header)
{
    mAminoAcidCount = aminoAcidCount;
    mTotal = total;
    mLargest = largest;
    mHeader = header;
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
    dc.SetBrush(*wxRED_BRUSH);
    
    // Draw histogram
    if(mAminoAcidCount != nullptr)
    {
        int spacing = 30;
        std::stringstream ss;
        int counter = 1;
        int color = 1;
        for(auto iter : *mAminoAcidCount)
        {
            color = counter % 3;
            if(color == 0)
            {
                dc.SetTextForeground(*wxRED);
                dc.SetBrush(*wxRED_BRUSH);
            }
            else if(color == 1)
            {
                dc.SetTextForeground(*wxGREEN);
                dc.SetBrush(*wxGREEN_BRUSH);
            }
            else if(color == 2)
            {
                dc.SetTextForeground(*wxBLUE);
                dc.SetBrush(*wxBLUE_BRUSH);
            }
            counter++;
            ss.str("");
            ss << mAminoAcidNames[iter.first] << ": "
            << std::fixed << std::setprecision(2) << ((float)iter.second/(float)mTotal)*100
            << "% (" << iter.second << ")";
            dc.DrawText(ss.str(), 10, spacing);
            dc.DrawRectangle(wxPoint(200, spacing), wxSize(((float)iter.second/(float)mLargest)*800, 30));
            spacing += 30;
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
