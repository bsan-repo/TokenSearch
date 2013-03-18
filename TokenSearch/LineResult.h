//
//  LineResult.h
//  TokenSearch
//
//  Created by b san on 3/14/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#ifndef __TokenSearch__LineResult__
#define __TokenSearch__LineResult__

#include <iostream>
#include <list>
#include "TokenResult.h"

// The toeken results for a search in a string of characters. The line number
// correspond to the one in a line of a file given for a search.
class LineResult{
protected:
    int lineNumber;
    std::list<TokenResult*> tokenResults;
public:
    LineResult(int lineNumberParam);
    void addTokenResult(TokenResult* tokenResultParam);
    inline int getLineNumber(){return lineNumber;}
    const std::list<TokenResult*> getTokenResults(){return tokenResults;}
    ~LineResult();
};

#endif /* defined(__TokenSearch__LineResult__) */
