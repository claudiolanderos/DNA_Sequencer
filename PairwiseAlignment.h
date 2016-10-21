//
//  PairwiseAlignment.hpp
//  dnawx-mac
//
//  Created by Claudio Landeros on 10/20/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#pragma once
#include <iostream>
#include <vector>

class PairwiseAlignment
{
public:
    explicit PairwiseAlignment(std::string fileA, std::string fileB);
    
    void CalculateScore();
    
    void OutputResult();
    
    void SetMaximum(int indexA, int indexB);
    
private:
    std::string mSequenceA;
    std::string mSequenceB;
    
    std::vector<std::vector<short>> mScoreGrid;
    std::vector<std::vector<char>> mDirectionGrid;
    
    enum Direction : char
    {
        aboveLeft,
        left,
        above,
    };
    
    const short Match = 1;
    const short Mismatch = -1;
    const short Gap = -1;
};