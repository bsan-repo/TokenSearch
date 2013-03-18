//
//  Pattern.cpp
//  TokenSearch
//
//  Created by b san on 3/13/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#include "Pattern.h"
#include <ctype.h>
#include <stdlib.h>
#include "SegmentFactory.h"
#include "StrHelper.h"
#include "SToken.h"
#include "GToken.h"

Pattern::Pattern(char* patternStr){
    StrHelper::copyString(&this->pattern, patternStr);
}

Segment* Pattern::extractToken(int offset, int length){
    char character = NULL; // unused part of the token
    int index = 0;
    Segment* segment = NULL;
    
    // skip the first two chars = %{
    int initialOffset = 2;
    // and check if third is a letter or else skip
    if(isdigit(this->pattern[offset+initialOffset]) == false){
        character = this->pattern[offset+initialOffset];
        initialOffset = 3;
        printf("ADDING NON DIGIT DISPLACEMENT\n");
    }
    // Retrieve the index
    index = atoi(this->pattern+offset+initialOffset);
    for(int i = initialOffset; i < length; i++){
        char c = this->pattern[offset+i];
        if(isdigit(c)==false){
            switch (c) {
                case 's': case 'S':
                    segment = SegmentFactory::getSegment(SegmentFactory::STOKEN);
                    ((SToken*)segment)->setSpaces(atoi(this->pattern+offset+i+1));
                    ((Token*)segment)->setIndex(index);
                    break;
                case 'G':
                    segment = SegmentFactory::getSegment(SegmentFactory::GTOKEN);
                    ((Token*)segment)->setIndex(index);
                    break;
                default:
                    segment = SegmentFactory::getSegment(SegmentFactory::TOKEN);
                    ((Token*)segment)->setIndex(index);
                    break;
            }
            break;
        }
    }
    segment->setOffset(offset);
    segment->setLength(length);
    
    return segment;
}

void Pattern::getPattern(char** patternCopy){
    StrHelper::copyString(patternCopy, this->pattern);
}