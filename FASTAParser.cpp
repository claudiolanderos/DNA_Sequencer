//
//  FASTAParser.cpp
//  dnawx-mac
//
//  Created by Claudio Landeros on 10/18/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#include "FASTAParser.h"
#include "Exceptions.h"
#include <fstream>
#include <sstream>

FASTAParser::FASTAParser()
{
}

void FASTAParser::ParseFile(const std::string filePath)
{
    std::ifstream::pos_type size;
    // Open the file for input and start ATE (at the end)
    std::ifstream file (filePath, std::ios::in|std::ios::ate);
    if (file.is_open())
    {
        size = file.tellg(); // Save the size of the file
        double length = size;
        file.seekg (0, std::ios::beg); // Seek back to start of file
        // Reserve space for sequence to avoid resizing
        mSequence.reserve(length);
        
        // Validate header
        char c;
        file.get(c);
        
        if(c != '>'){
            throw FileLoadExcept();
        }
        else{
            file.get(c);
            while(c != '\n')
            {
                mHeader += c;
                file.get(c);
            }
        }
        
        std::cout<<"Header: " << mHeader << '\n';
        while (file.get(c)) {
            if(c == '\xff')  //end of file
            {
                return;
            }
            else if(c == '\n' || c == '\r')
            {
                // Ignore characters
            }
            else if (c != 'T' && c != 'C' && c != 'A' && c != 'G')
            {
                std::cout << "error";
                throw FileLoadExcept();
            }
            else {
                mSequence += c;
            }
        }
        std::cout<<"Sequence: " << mSequence << '\n';
        
        file.close();
        
        file.get();
    }
}
