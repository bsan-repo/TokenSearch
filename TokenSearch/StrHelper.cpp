//
//  StrHelper.cpp
//  TokenSearch
//
//  Created by b san on 3/13/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#include "StrHelper.h"

// It's the responsability of the invoker to release memory before and after
// calling this method
void StrHelper::copyString(char** copy, const char* toCopy){
    if(toCopy != NULL){
        int size = (int)strlen(toCopy);
        if(size>0){
            *copy = new char[size];
            strcpy(*copy, toCopy);
        }
    }
}