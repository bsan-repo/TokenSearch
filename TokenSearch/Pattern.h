//
//  Pattern.h
//  TokenSearch
//
//  Created by b san on 3/13/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#ifndef __TokenSearch__Pattern__
#define __TokenSearch__Pattern__

#include <iostream>
#include <list>
#include "Segment.h"

class Pattern{
private:
    char* pattern;
    char* regEx;
    std::list<Segment*> segments;
public:
    Pattern(char* patternStr);
    virtual void getRegEx() = 0;
};

#endif /* defined(__TokenSearch__Pattern__) */
