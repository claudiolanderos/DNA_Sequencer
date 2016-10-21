//
//  PairwiseAlignment.cpp
//  dnawx-mac
//
//  Created by Claudio Landeros on 10/20/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#include "PairwiseAlignment.h"
#include "FASTAParser.h"
#include <fstream>

PairwiseAlignment::PairwiseAlignment(std::string fileA, std::string fileB)
{
    FASTAParser parser;
    parser.ParseFile(fileA);
    mSequenceA = parser.GetSequence();
    mHeaderA = parser.GetHeader();

    parser.ParseFile(fileB);
    mSequenceB = parser.GetSequence();
    mHeaderB = parser.GetHeader();
}

void PairwiseAlignment::CalculateScore()
{
    // Resize arrays
    int lengthA = (int)mSequenceA.length() +1;
    int lengthB = (int)mSequenceB.length() +1;
    
    mScoreGrid.resize(lengthA);
    mDirectionGrid.resize(lengthA);
    for(int a = 0, b= 0 ; a < lengthA; a++)
    {
        mScoreGrid[a].resize(lengthB);
        mDirectionGrid[a].resize(lengthB);
        
        //Initialize arrays
        mScoreGrid[a][0] = -a;
        if(a != 0)
        {
            mDirectionGrid[a][0] = Direction::left;
        }
       
        if(b < lengthB)
        {
            mScoreGrid[0][b] = -b;
            if(b != 0)
            {
                mDirectionGrid[0][b] = Direction::above;
            }
            b++;
        }
    }
    
    for (int i = 1; i < lengthB; i++) {
        for(int x = 1; x < lengthA; x++)
        {
            SetMaximum(x, i);
        }
    }
    
    mScore = mScoreGrid[lengthA-1][lengthB-1];
    ConstructString();
}

void PairwiseAlignment::SetMaximum(int indexA, int indexB)
{
    int aboveLeftScore;
    int leftScore = -1;
    int aboveScore = -1;
    
    aboveLeftScore = mScoreGrid[indexA-1][indexB-1];
    if(mSequenceA.at(indexA-1) == mSequenceB.at(indexB-1))
    {
        aboveLeftScore += 1;
    }
    else{
        aboveLeftScore -= 1;
    }
    
    leftScore += mScoreGrid[indexA-1][indexB];
    aboveScore += mScoreGrid[indexA][indexB-1];
    
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

void PairwiseAlignment::ConstructString()
{
    // Needleman-Wunsh Algorithm
    mResultA = "";
    mResultB = "";
    
    mResultA.reserve(std::max(mSequenceA.length(), mSequenceB.length()));
    mResultB.reserve(std::max(mSequenceA.length(), mSequenceB.length()));

    int indexA = (int)mSequenceA.length();
    int indexB = (int)mSequenceB.length();
    while(indexA != 0 || indexB != 0)
    {
        char dir = mDirectionGrid[indexA][indexB];
        if(dir == Direction::aboveLeft)
        {
            mResultA += mSequenceA.at(--indexA);
            mResultB += mSequenceB.at(--indexB);
        }
        else if(dir == Direction::left)
        {
            mResultA += mSequenceA.at(--indexA);
            mResultB += "_";
        }
        else
        {
            mResultB += mSequenceB.at(--indexB);
            mResultA += "_";
        }
    }
    
    std::reverse(mResultA.begin(), mResultA.end());
    std::reverse(mResultB.begin(), mResultB.end());
}

void PairwiseAlignment::PrintGraphs()
{
    int lengthA = (int)mSequenceA.length() +1;
    int lengthB = (int)mSequenceB.length() +1;
    for (int i = 0; i < lengthB; i++) {
        for(int x = 0; x < lengthA; x++)
        {
            if(mDirectionGrid[x][i] == Direction::above)
            {
                std::cout<<"^" <<"\t";
            }
            else if(mDirectionGrid[x][i] == Direction::left)
            {
                std::cout<< "<" << "\t";
            }
            else if(mDirectionGrid[x][i] == Direction::aboveLeft)
            {
                std::cout<<"\\" << "\t";
            }
        }
        std::cout<<std::endl;
    }
    
    for (int i = 0; i < lengthB; i++) {
        for(int x = 0; x < lengthA; x++)
        {
            std::cout<< (int)mScoreGrid[x][i] << "\t";
        }
        std::cout<<std::endl;
    }
}

void PairwiseAlignment::OutputResult(std::string outputFile)
{
    std::ofstream file;
    file.open(outputFile, std::ios::out | std::ios::trunc);
    
    file << "A: " << mHeaderA << "\n";
    file << "B: " << mHeaderB << "\n";
    file << "Score: " << mScore << "\n\n";
    
    std::string tempB;
    tempB.reserve(70);
    std::string sameChar;
    sameChar.reserve(70);
    
    for(int i = 0; i < mResultA.length(); i++)
    {
        file << mResultA.at(i);
        tempB += mResultB.at(i);
        
        if(mResultA.at(i) == mResultB.at(i))
        {
            sameChar += "|";
        }
        else
        {
            sameChar += " ";
        }
        
        if(i != 0 && ((i+1) % 70) == 0)
        {
            file << "\n" << sameChar << "\n" << tempB << "\n\n";
            sameChar = "";
            tempB = "";
        }
    }
    if(tempB != "")
    {
        file << "\n" << sameChar << "\n" << tempB << "\n";
    }
    file.close();
}
