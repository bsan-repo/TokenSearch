//
//  TokenResult.cpp
//  TokenSearch
//
//  Created by b san on 3/14/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#include "TokenResult.h"
#include "StrHelper.h"

TokenResult::TokenResult(int charParam, int indexParam){
    this->character = charParam;
    this->index = indexParam;
    this->result = NULL;
}
void TokenResult::getResult(char** resultCopy){
    StrHelper::copyString(resultCopy, this->result);
}
void TokenResult::setResult(const char* resultParam){
    if(this->result != NULL){
        delete[] this->result;
    }
    StrHelper::copyString(&this->result, resultParam);
}

TokenResult::~TokenResult(){
    if(this->result != NULL){
        delete[] this->result;
    }
}