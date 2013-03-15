//
//  Token.cpp
//  TokenSearch
//
//  Created by b san on 3/13/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#include "Token.h"
#include "StrHelper.h"

Token::Token(){
    this->type = Token::TOKEN_TYPE;
    this->index = 0;
    this->regEx = NULL;
}
void Token::getRegEx(char** regExCopy){
    StrHelper::copyString(regExCopy, this->regEx);
}
void Token::setRegEx(const char* regExParam){
    if(this->regEx != NULL){
        delete [] this->regEx;
    }
    StrHelper::copyString(&this->regEx, regExParam);
}
