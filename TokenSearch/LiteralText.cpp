//
//  LiteralText.cpp
//  TokenSearch
//
//  Created by b san on 3/13/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#include "LiteralText.h"

LiteralText::LiteralText(){
    this->typeSegment = LiteralText::LITERAL_TEXT_TYPE;
}

void LiteralText::getSegmentCopy(char** segmentCopy){
    this->getSegmentCopyBase(segmentCopy);
}