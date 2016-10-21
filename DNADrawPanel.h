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
    
    void SetAminoAcidCount(std::shared_ptr<std::unordered_map<char, int> > aminoAcidCount){ mAminoAcidCount = aminoAcidCount; }
    void SetTotal(int total) { mTotal = total; }
    void SetHeader(std::string& header) { mHeader = header; }

protected:
	void PaintEvent(wxPaintEvent & evt);
	void Render(wxDC& dc);
 
	DECLARE_EVENT_TABLE()
	
public:
    std::shared_ptr<std::unordered_map<char, int>> mAminoAcidCount;
    int mTotal;
    std::string mHeader;
};

