//
//  DNAStateMachine.hpp
//  dnawx-mac
//
//  Created by Claudio Landeros on 10/19/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#pragma once
#include <iostream>
#include <unordered_map>
#include <memory>

class FASTATranslator
{
public:
    FASTATranslator();

    void Translate(const std::string& sequence);
    
    const int GetTotal() { return mTotal; }
    
    const std::shared_ptr<std::unordered_map<char, int> > GetAminoAcidCount() const;
    
private:
    const char mStateMachine[17][4] = {
    //  | T | C | A | G |   St
    //------------------------
        { 0,  0,  1,  0},   //0     A in start
        { 2,  0,  1,  0},   //1     T in start
        { 0,  0,  1, 'M'},  //2     G in start
        { 4,  9,  11, 15},  //3     First letter
        { 5,  6,  7,  8},   //4     T**
        {'F','F','L','L'},  //5     TT*
        {'S','S','S','S'},  //6     TC*
        {'Y','Y', 0,  0},   //7     TA*
        {'C','C', 0, 'W'},  //8     TG*
        {'l','p', 10,'r'},  //9     C**
        {'H','H','G','G'},  //10    CA*
        { 12,'t', 13, 14},  //11    A**
        {'I','I','I','M'},  //12    AT*
        {'N','N','K','K'},  //13    AA*
        {'S','S','R','R'},  //14    AG*
        {'v','a', 16,'g'},  //15    G**
        {'D','D','E','E'},  //16    GA*
    };
    /* lower case letters are special cases that represent
    the amino acid and skip the next character because it is
    inconsecuential */
    
    int mState = 0;
    int mTotal = 0;
    std::shared_ptr<std::unordered_map<char, int> > mAminoAcidCount;
};
