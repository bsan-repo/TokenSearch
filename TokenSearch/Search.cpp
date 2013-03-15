//
//  Search.cpp
//  TokenSearch
//
//  Created by b san on 3/14/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#include "Search.h"

Search::Search(File* file, Pattern* pattern, PCREProcessor* processor){
    this->file = file;
    this->pattern = pattern;
    this->processor = processor;
    
    
}

Search::~Search(){
    for (std::list<LineResult*>::iterator it = lineResults.begin(); it != lineResults.end(); it++){
        delete *it;
        lineResults.pop_front();
    }
}

bool Search::isPatternInLine(char* line){
    int* results = NULL;
    int resultsSize = 0;
    char* errorMsg = NULL;
    char* regExPattern = NULL;
    
    pattern->getRegEx(&regExPattern);
    
    // Extract the items using RegExs
    bool execOK = processor->match(regExPattern, line, &results, &resultsSize, &errorMsg, true);
    
    if(execOK == true && resultsSize>0){
        return true;
    }
    return false;
}
