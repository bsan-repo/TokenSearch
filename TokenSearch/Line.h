//
//  Line.h
//  TokenSearch
//
//  Created by b san on 3/13/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#ifndef __TokenSearch__Line__
#define __TokenSearch__Line__

#include <iostream>

class Line{
private:
    char* contents;
    bool patternFoundInLine;
public:
    Line();
    void set(char* contents);
    void clean();
    void getContents(char** contentsCopyPtr);
    inline bool isPatternFoundInLine(){return patternFoundInLine;}
    inline void setPatternFoundInLine(bool found){ patternFoundInLine = found;}
    ~Line();
};

#endif /* defined(__TokenSearch__Line__) */
