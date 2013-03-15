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

class LineResult{
protected:
    int lineNumber;
    std::list<TokenResult*> tokenResults;
public:
    LineResult(int lineNumberParam);
    inline int getLineNumber(){return lineNumber;}
    const std::list<TokenResult*> getTokenResults(){return tokenResults;}
    ~LineResult();
};

#endif /* defined(__TokenSearch__LineResult__) */
