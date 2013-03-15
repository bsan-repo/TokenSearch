//
//  TokenResult.cpp
//  TokenSearch
//
//  Created by b san on 3/14/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#include "TokenResult.h"
#include "StrHelper.h"

TokenResult::TokenResult(int indexParam, const char* resultParam){
    this->index = indexParam;
    this->result = NULL;
    StrHelper::copyString(&this->result, resultParam);
}
void TokenResult::getResult(char** resultCopy){
    StrHelper::copyString(resultCopy, this->result);
}
TokenResult::~TokenResult(){
    if(this->result != NULL){
        delete[] this->result;
    }
}