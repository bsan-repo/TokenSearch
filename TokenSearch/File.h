//
//  File.h
//  TokenSearch
//
//  Created by b san on 3/13/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#ifndef __TokenSearch__File__
#define __TokenSearch__File__

#include <iostream>
#include <list>

#include "Line.h"

class File{
private:
    std::list<Line*> lines;
    int numberOfLines;
public:
    File();
    void addLine(char* lineContentsParam);
    inline int getNumberOfLines(){return numberOfLines;}
    const std::list<Line*> getLines(){return lines;}
    ~File();
};

#endif /* defined(__TokenSearch__File__) */
