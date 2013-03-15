//
//  PCREPattern.h
//  TokenSearch
//
//  Created by b san on 3/13/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#ifndef __TokenSearch__PCREPattern__
#define __TokenSearch__PCREPattern__

#include <iostream>
#include "Pattern.h"

class PCREPattern : public Pattern{
protected:
    void constructRegEx();
public:
    PCREPattern(char* patternStr);
    void getRegEx(char** regEx);
};

#endif /* defined(__TokenSearch__PCREPattern__) */
