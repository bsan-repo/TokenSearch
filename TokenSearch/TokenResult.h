//
//  TokenResult.h
//  TokenSearch
//
//  Created by b san on 3/14/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#ifndef __TokenSearch__TokenResult__
#define __TokenSearch__TokenResult__

#include <iostream>

// The contents of a token for a search in a string of characters. The index
// correspond to a Token object index for a given Pattern.
class TokenResult{
protected:
    int index;
    char* result;
public:
    TokenResult(int indexParam, const char* resultParam);
    inline int getIndex(){return index;}
    void getResult(char** resultCopy);
    ~TokenResult();
};

#endif /* defined(__TokenSearch__TokenResult__) */
