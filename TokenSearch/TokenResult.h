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

class TokenResult{
protected:
    int character;
    int index;
    char* result;
public:
    TokenResult(int charParam, int indexParam);
    inline int getIndex(){return index;}
    void getResult(char** resultCopy);
    void setResult(const char* resultParam);
    ~TokenResult();
};

#endif /* defined(__TokenSearch__TokenResult__) */
