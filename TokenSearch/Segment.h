//
//  Segment.h
//  TokenSearch
//
//  Created by b san on 3/13/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#ifndef __TokenSearch__Segment__
#define __TokenSearch__Segment__

#include <iostream>

class Segment{
protected:
    char* segmentStr;
    int typeSegment;
    void getSegmentCopyBase(char** segmentCopy);
public:
    virtual void getSegmentCopy(char** segmentCopy) = 0;
};

#endif /* defined(__TokenSearch__Segment__) */
