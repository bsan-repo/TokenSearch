//
//  SToken.cpp
//  TokenSearch
//
//  Created by b san on 3/13/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#include "SToken.h"

SToken::SToken(){
    this->typeSegment = SToken::STOKEN_TYPE;
}

void SToken::getSegmentCopy(char** segmentCopy){
    this->getSegmentCopyBase(segmentCopy);
}
