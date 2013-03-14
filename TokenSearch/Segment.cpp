//
//  Segment.cpp
//  TokenSearch
//
//  Created by b san on 3/13/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#include "Segment.h"

void Segment::getSegmentCopyBase(char** segmentCopy){
    int size = (int)strlen(this->segmentStr);
    *segmentCopy = new char[size];
    strcpy(*segmentCopy, this->segmentStr);
}