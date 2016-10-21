//
//  DNADrawPanel.h
//  DNAwx
//
//  Created by Sanjay Madhav on 12/27/14.
//  Copyright (c) 2014 Sanjay Madhav. All rights reserved.
//

#pragma once
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <string>
#include <memory>
#include <unordered_map>

class DNADrawPanel : public wxPanel
{
public:
    DNADrawPanel(wxFrame* parent);
	void PaintNow();

    void SetHistogramVariables(std::shared_ptr<std::unordered_map<char, int> > aminoAcidCount, int total, int largest, std::string header);
protected:
	void PaintEvent(wxPaintEvent & evt);
	void Render(wxDC& dc);
 
	DECLARE_EVENT_TABLE()
	
public:
    std::shared_ptr<std::unordered_map<char, int>> mAminoAcidCount;
    std::unordered_map<char, std::string> mAminoAcidNames;
    int mTotal;
    int mLargest;
    std::string mHeader;
};

