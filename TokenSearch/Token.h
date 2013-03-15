//
//  Token.h
//  TokenSearch
//
//  Created by b san on 3/13/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#ifndef __TokenSearch__Token__
#define __TokenSearch__Token__

#include <iostream>
#include "Segment.h"

class Token : public Segment{
protected:
    int index;
public:
    Token();
    inline int getIndex(){return index;}
    inline void setIndex(int indexParam){this->index = indexParam;}
    
    static const int TOKEN_TYPE = 2;
};

#endif /* defined(__TokenSearch__Token__) */
