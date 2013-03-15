//
//  SegmentFactory.h
//  TokenSearch
//
//  Created by b san on 3/14/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#ifndef __TokenSearch__SegmentFactory__
#define __TokenSearch__SegmentFactory__

#include <iostream>
#include "Segment.h"
#include "LiteralText.h"
#include "Token.h"
#include "SToken.h"
#include "GToken.h"

class SegmentFactory{
public:
    static const int SEGMENT = Segment::SEGMENT_TYPE;
    static const int LITERALTEXT = LiteralText::LITERALTEXT_TYPE;
    static const int TOKEN = Token::TOKEN_TYPE;
    static const int STOKEN = SToken::STOKEN_TYPE;
    static const int GTOKEN = GToken::GTOKEN_TYPE;
    static Segment* getSegment(int type);
};

#endif /* defined(__TokenSearch__SegmentFactory__) */
