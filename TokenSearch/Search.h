//
//  Search.h
//  TokenSearch
//
//  Created by b san on 3/14/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#ifndef __TokenSearch__Search__
#define __TokenSearch__Search__

#include <iostream>
#include <list>
#include "File.h"
#include "Pattern.h"
#include "LineResult.h"
#include "RegExProcessor.h"
#include "PCREProcessor.h"

class Search{
protected:
    File* file;
    Pattern* pattern;
    PCREProcessor* processor;
    std::list<LineResult*> lineResults;
    
    void getTokensForLine(char* lineContents, LineResult* lineResult);
public:
    Search(File* file, Pattern* pattern, PCREProcessor* processor);
    const std::list<LineResult*> getLineResults(){return lineResults;}
    bool isPatternInLine(char* line);
    ~Search();
};

#endif /* defined(__TokenSearch__Search__) */
