//
//  SegmentFactory.cpp
//  TokenSearch
//
//  Created by b san on 3/14/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#include "SegmentFactory.h"

Segment* SegmentFactory::getSegment(int type){
    switch (type) {
        case SegmentFactory::LITERALTEXT:
            return new LiteralText();
            break;
        case SegmentFactory::TOKEN:
            return new Token();
            break;
        case SegmentFactory::STOKEN:
            return new SToken();
            break;
        case SegmentFactory::GTOKEN:
            return new GToken();
            break;
        default:
            return NULL;
    }
}