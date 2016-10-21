//
//  DNAStateMachine.cpp
//  dnawx-mac
//
//  Created by Claudio Landeros on 10/19/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#include "FASTATranslator.h"

FASTATranslator::FASTATranslator()
{
}

void FASTATranslator::Translate(const std::string &sequence)
{
    char input = 0;
    char charState = 0;
    
    mAminoAcidCount = std::make_shared<std::unordered_map<char, int>>();
    
    for(int i = 0; i  < sequence.length(); i++)
    {
        input = sequence[i];
        switch (input) {
            case 'T':
                charState = mStateMachine[mState][0];
                break;
            case 'C':
                charState = mStateMachine[mState][1];
                break;
            case 'A':
                charState = mStateMachine[mState][2];
                break;
            case 'G':
                charState = mStateMachine[mState][3];
                break;
            default:
                //Throw exception
                break;
        }
        
        switch (charState) {
            case 'A':
            case 'R':
            case 'N':
            case 'D':
            case 'C':
            case 'Q':
            case 'E':
            case 'G':
            case 'H':
            case 'I':
            case 'L':
            case 'K':
            case 'M':
            case 'F':
            case 'P':
            case 'S':
            case 'T':
            case 'W':
            case 'Y':
            case 'V':
                mAminoAcidCount->operator[](charState)++;
                mTotal++;
                mState = 3;
                break;
            case 'a':
            case 'r':
            case 'n':
            case 'd':
            case 'c':
            case 'q':
            case 'e':
            case 'g':
            case 'h':
            case 'i':
            case 'l':
            case 'k':
            case 'm':
            case 'f':
            case 'p':
            case 's':
            case 't':
            case 'w':
            case 'y':
            case 'v':
                mAminoAcidCount->operator[](charState)++;
                mTotal++;
                mState = 3;
                i++; //make sure to increment to account for shortcut
                break;
            default:
                mState = charState;
                break;
        }
    }
}

const std::shared_ptr<std::unordered_map<char, int> > FASTATranslator::GetAminoAcidCount() const
{
    return mAminoAcidCount;
}
