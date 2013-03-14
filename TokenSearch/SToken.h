//
//  SToken.h
//  TokenSearch
//
//  Created by b san on 3/13/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#ifndef __TokenSearch__SToken__
#define __TokenSearch__SToken__

#include <iostream>
#include "Segment.h"

class SToken : public Segment{
public:
    SToken();
    void getSegmentCopy(char** segmentCopy);
    const static uint STOKEN_TYPE = 3;
};

#endif /* defined(__TokenSearch__SToken__) */
