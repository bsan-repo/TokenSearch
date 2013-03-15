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
    char character = NULL;
    int index = 0;
    Segment* segment = NULL;
    
    // skip the first two chars = %{
    int initialOffset = 2;
    // and check if third is a letter
    if(isalpha(this->pattern[2]) == true){
        character = this->pattern[2];
        initialOffset = 3;
    }
    index = atoi(this->pattern+offset+initialOffset);
    for(int i = initialOffset; i < length; i++){
        char c = this->pattern[offset+i];
        if(isdigit(c)==false){
            switch (c) {
                case 's': case 'S':
                    segment = SegmentFactory::getSegment(SegmentFactory::STOKEN);
                    ((SToken*)segment)->setSpaces(atoi(this->pattern+offset+i+1));
                    printf("TOKEN__ spaces: %d\n", ((SToken*)segment)->getSpaces());
                    break;
                case 'G':
                    segment = SegmentFactory::getSegment(SegmentFactory::GTOKEN);
                    break;
                default:
                    segment = SegmentFactory::getSegment(SegmentFactory::TOKEN);
                    break;
            }
            break;
        }
    }
    segment->setOffset(offset);
    segment->setLengt(length);
    
    
    printf("TOKEN__ type: %d\n", segment->getType());
    printf("TOKEN__ offset: %d\n", segment->getOffset());
    printf("TOKEN__ length: %d\n", segment->getLength());
    
    return segment;
}