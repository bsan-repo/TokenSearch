//
//  Token.cpp
//  TokenSearch
//
//  Created by b san on 3/13/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#include "Token.h"

Token::Token(){
    this->typeSegment = Token::TOKEN_TYPE;
}

void Token::getSegmentCopy(char** segmentCopy){
    this->getSegmentCopyBase(segmentCopy);
}
