//
//  StdPrintResultsSearch.cpp
//  TokenSearch
//
//  Created by b san on 3/15/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#include "StdPrintResultsSearch.h"
#include <list>
#include "LineResult.h"
#include "TokenResult.h"
#include "Line.h"

void StdPrintResultsSearch::print(Search* search, File* file){
    const std::list<Line*> lines = file->getLines();
    const std::list<LineResult*> lineResults = search->getLineResults();
    std::list<LineResult*>::const_iterator citlr = lineResults.begin();
    char* line = NULL;
    int lineNumber = 0;
    
    for(std::list<Line*>::const_iterator citline = lines.begin(); citline != lines.end(); citline++){
        lineNumber = (*citline)->getNumber();
        line = NULL;
        (*citline)->getContents(&line);
        printf("(%2d) > %s\n", lineNumber, line);        
        
        if(lineNumber == (*citlr)->getLineNumber()){
            std::cout<<"     > FOUND"<<std::endl;
            StdPrintResultsSearch::printTokens((*citlr)->getTokenResults());
            if(citlr != lineResults.end()){
                citlr++;
            }
        }
    }
}

void StdPrintResultsSearch::printTokens(const std::list<TokenResult *> &tokenResults){
    for (std::list<TokenResult*>::const_iterator citt = tokenResults.begin(); citt != tokenResults.end(); citt++) {
        char* result = NULL;
        (*citt)->getResult(&result);
        std::cout<<"     > TOKEN %{"<<(*citt)->getIndex()<<"}: ["<<result<<"]"<<std::endl;
        if(result!=NULL){
            delete[] result;
        }
    }
}

