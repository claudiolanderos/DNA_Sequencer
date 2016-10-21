//
//  PairwiseAlignment.cpp
//  dnawx-mac
//
//  Created by Claudio Landeros on 10/20/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#include "PairwiseAlignment.h"
#include "FASTAParser.h"

PairwiseAlignment::PairwiseAlignment(std::string fileA, std::string fileB)
{
    FASTAParser parser;
    parser.ParseFile(fileA);
    mSequenceA = parser.GetSequence();

    parser.ParseFile(fileB);
    mSequenceB = parser.GetSequence();
}

void PairwiseAlignment::CalculateScore()
{
    // Resize arrays
    int lengthA = (int)mSequenceA.length() +1;
    int lengthB = (int)mSequenceB.length() +1;
    mScoreGrid.resize(lengthA);
    mDirectionGrid.resize(lengthA);
    for(int i = 0; i < lengthA; i++)
    {
        mScoreGrid[i].resize(lengthB);
        mDirectionGrid[i].resize(lengthB);
        
        //Initialize arrays
        mScoreGrid[0][i] = -i;
        if(i != 0)
        {
            mDirectionGrid[0][i] = Direction::left;
        }
        
        if(i < lengthB)
        {
            mScoreGrid[i][0] = -i;
            
            if(i != 0)
            {
                mDirectionGrid[i][0] = Direction::above;
            }
        }
        
    }
    
    for (int i = 1; i < lengthB; i++) {
        for(int x = 1; x < lengthA; x++)
        {
            SetMaximum(i, x);
        }
    }
    
    for (int i = 0; i < lengthB; i++) {
        for(int x = 0; x < lengthA; x++)
        {
            if(mDirectionGrid[i][x] == Direction::above)
            {
                std::cout<<"^" <<"\t";
            }
            else if(mDirectionGrid[i][x] == Direction::left)
            {
                std::cout<< "<" << "\t";
            }
            else if(mDirectionGrid[i][x] == Direction::aboveLeft)
            {
                std::cout<<"\\" << "\t";
            }
        }
        std::cout<<std::endl;
    }
    
    for (int i = 0; i < lengthB; i++) {
        for(int x = 0; x < lengthA; x++)
        {
            std::cout<< mScoreGrid[i][x] << "\t";
        }
        std::cout<<std::endl;
    }
}

void PairwiseAlignment::SetMaximum(int indexA, int indexB)
{
    int aboveLeftScore;
    int leftScore;
    int aboveScore;
    
    aboveLeftScore = mScoreGrid[indexA-1][indexB-1];
    if(mSequenceA.at(indexA-1) == mSequenceB.at(indexB-1))
    {
        aboveLeftScore += 1;
    }
    else{
        aboveLeftScore -= 1;
    }
    
    leftScore = mScoreGrid[indexA-1][indexB];
    leftScore -= 1;
    
    aboveScore = mScoreGrid[indexA][indexB-1];
    aboveScore -= 1;
    
    if(aboveScore > leftScore && aboveScore > aboveLeftScore)
    {
        mScoreGrid[indexA][indexB] = aboveScore;
        mDirectionGrid[indexA][indexB] = Direction::above;
    }
    else if(leftScore > aboveLeftScore)
    {
        mScoreGrid[indexA][indexB] = leftScore;
        mDirectionGrid[indexA][indexB] = Direction::left;
    }
    else
    {
        mScoreGrid[indexA][indexB] = aboveLeftScore;
        mDirectionGrid[indexA][indexB] = Direction::aboveLeft;
    }
}
