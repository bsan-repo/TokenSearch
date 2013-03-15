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

class Search{
protected:
    File* file;
    Pattern* pattern;
    RegExProcessor* processor;
    std::list<LineResult*> lineResults;
public:
    Search(File* file, Pattern* pattern, RegExProcessor* processor);
    const std::list<LineResult*> getLineResults(){return lineResults;}
    bool isPatternInLine(char* line);
    ~Search();
};

#endif /* defined(__TokenSearch__Search__) */
