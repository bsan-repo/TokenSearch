//
//  Pattern.h
//  TokenSearch
//
//  Created by b san on 3/13/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#ifndef __TokenSearch__Pattern__
#define __TokenSearch__Pattern__

#include <iostream>
#include <list>
#include "Segment.h"

// A pattern can have different segments:
// - Literal text (LiteralText)
// - Simple tokens (Tokens)
// - Tokens with determined spaces (STokens)
// - Greedy tokens (GTokens)

// Pattern segments are used to construct the regular expression to
// perform the search and later to extract the contents of a token from the text
// in which the search was performeds

class Pattern{
protected:
    char* pattern;
    char* regEx;
    std::list<Segment*> segments;
    
    // Creates a Token object from a part of the pattern
    // string given by offset and length and returns it.
    Segment* extractToken(int offset, int length);
    // Create the segments to determine which kind of
    // regular expression can match for it and construct
    // the whole expression.
    virtual void constructRegEx() = 0;
public:
    Pattern(char* patternStr);
    virtual void getRegEx(char** regEx) = 0;
    inline const std::list<Segment*> getSegments(){return segments;}
    void getPattern(char** patternCopy);
};

#endif /* defined(__TokenSearch__Pattern__) */
