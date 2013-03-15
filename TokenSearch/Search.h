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

class Search{
protected:
    File* file;
    Pattern* pattern;
    std::list<LineResult*> lineResults;
public:
    Search(File* file, Pattern* pattern);
    const std::list<LineResult*> getLineResults(){return lineResults;}
    ~Search();
};

#endif /* defined(__TokenSearch__Search__) */
