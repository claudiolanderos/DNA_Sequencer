//
//  DNAFrame.cpp
//  DNAwx
//
//  Created by Sanjay Madhav on 12/27/14.
//  Copyright (c) 2014 Sanjay Madhav. All rights reserved.
//

#include "DNAFrame.h"
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/log.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/filedlg.h>
#include <wx/busyinfo.h>
#include <wx/wfstream.h>
#include "DNADrawPanel.h"
#include "Exceptions.h"
#include "DNAAlignDlg.h"
#include "FASTAParser.h"
#include "FASTATranslator.h"

enum
{
	ID_AMINO_HIST=1000,
};

wxBEGIN_EVENT_TABLE(DNAFrame, wxFrame)
	EVT_MENU(wxID_EXIT, DNAFrame::OnExit)
	EVT_MENU(wxID_NEW, DNAFrame::OnNew)
	EVT_MENU(ID_AMINO_HIST, DNAFrame::OnAminoHist)
wxEND_EVENT_TABLE()

DNAFrame::DNAFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size)
{
	// File menu
	wxMenu* menuFile = new wxMenu;
	menuFile->Append(wxID_NEW);
	menuFile->Append(ID_AMINO_HIST, "Amino Acid Histogram...",
					 "Create a histogram from a FASTA file.");
	menuFile->Append(wxID_EXIT);
	
	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	SetMenuBar(menuBar);
	CreateStatusBar();
	
	// Prepare the draw panel and show this frame
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	mPanel = new DNADrawPanel(this);
	sizer->Add(mPanel, 1, wxEXPAND);
	
	SetSizer(sizer);
	SetAutoLayout(true);
	Show(true);
	
	SetMinSize(GetSize());
	SetMaxSize(GetSize());
}

void DNAFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void DNAFrame::OnNew(wxCommandEvent& event)
{
	// Doesn't do anything...
}

void DNAFrame::OnAminoHist(wxCommandEvent& event)
{
    wxFileDialog
    openFileDialog(this, _(""), "./data", "",
                   "fasta files (*.fasta)|*.fasta", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;     // the user changed idea...
    }
    
    FASTAParser parser;
    std::string sequence;
    try{
        parser.ParseFile(openFileDialog.GetPath().ToStdString());
    } catch (FileLoadExcept e)
    {
        wxMessageBox("FASTA file is invalid", "Error", wxOK | wxICON_ERROR);
        return;
    }
    
    sequence = parser.GetSequence();
    
    FASTATranslator translator;
    translator.Translate(sequence);
    
    auto aminoAcidCount = translator.GetAminoAcidCount();
    
    for(auto i : *aminoAcidCount)
    {
        std::cout<<i.first << " " << i.second << std::endl;
    }
    
    std::cout<<translator.GetLargest().first << " " << translator.GetLargest().second << std::endl;
    mPanel->SetHistogramVariables(aminoAcidCount, translator.GetTotal(), translator.GetLargest().second, parser.GetHeader());
    
    mPanel->PaintNow();
}
