//
//  LineResult.cpp
//  TokenSearch
//
//  Created by b san on 3/14/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#include "LineResult.h"

LineResult::LineResult(int lineNumberParam){
    this->lineNumber = lineNumberParam;
}

LineResult::~LineResult(){
    for (std::list<TokenResult*>::iterator it = tokenResults.begin(); it != tokenResults.end(); it++){
        delete *it;
        tokenResults.pop_front();
    }
}