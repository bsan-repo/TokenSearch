//
//  StrHelper.h
//  TokenSearch
//
//  Created by b san on 3/13/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#ifndef __TokenSearch__StrHelper__
#define __TokenSearch__StrHelper__

#include <iostream>

class StrHelper{
public:
    // Copies a character string.
    // The "copy" argument should be a reference to a
    // char pointer that is not pointing to a used
    // char string. It should be released with delete[]
    // after being used. 
    static void copyString(char** copy, const char* toCopy);
};

#endif /* defined(__TokenSearch__StrHelper__) */
