//
//  FASTAParser.h
//  dnawx-mac
//
//  Created by Claudio Landeros on 10/18/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#pragma once
#include <iostream>

class FASTAParser
{
public:
    FASTAParser();
    
    void ParseFile(const std::string filePath);
    
    const std::string & GetSequence() const { return mSequence; }
    
    const std::string & GetHeader() const { return mHeader; }
private:
    std::string mHeader;
    std::string mSequence;
};
