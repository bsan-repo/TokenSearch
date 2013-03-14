//
//  StrHelper.cpp
//  TokenSearch
//
//  Created by b san on 3/13/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#include "StrHelper.h"

void StrHelper::copyString(char** copy, const char* toCopy){
    int size = (int)strlen(toCopy);
    *copy = new char[size];
    strcpy(*copy, toCopy);
}