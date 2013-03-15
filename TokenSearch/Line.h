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
    int number;
    char* contents;
public:
    Line(int numberParam,char* contents);
    void getContents(char** contentsCopyPtr);
    inline int getNumber(){return number;}
    ~Line();
};

#endif /* defined(__TokenSearch__Line__) */
