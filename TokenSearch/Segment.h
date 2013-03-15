//
//  Segment.h
//  TokenSearch
//
//  Created by b san on 3/13/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#ifndef __TokenSearch__Segment__
#define __TokenSearch__Segment__

#include <iostream>



class Segment{
protected:
    int type;
    int offset;
    int length;
public:
    Segment();
    inline int getType(){return type;}
    inline int getOffset(){return offset;}
    inline void setOffset(int offsetParam){this->offset = offsetParam;};
    inline int getLength(){return length;}
    inline void setLengt(int lengthParam){this->length = lengthParam;};
    
    static const int SEGMENT_TYPE = 0;
};

#endif /* defined(__TokenSearch__Segment__) */
