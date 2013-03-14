//
//  LiteralText.h
//  TokenSearch
//
//  Created by b san on 3/13/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#ifndef __TokenSearch__LiteralText__
#define __TokenSearch__LiteralText__

#include <iostream>
#include "Segment.h"

class LiteralText : public Segment{
public:
    LiteralText();
    void getSegmentCopy(char** segmentCopy);
    const static uint LITERAL_TEXT_TYPE = 1;
};
#endif /* defined(__TokenSearch__LiteralText__) */
