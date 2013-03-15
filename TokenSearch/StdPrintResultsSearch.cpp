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

void StdPrintResultsSearch::print(Search* search){
    const std::list<LineResult*> lineResults = search->getLineResults();;
    for(std::list<LineResult*>::const_iterator citl = lineResults.begin(); citl != lineResults.end(); citl++){
        const std::list<TokenResult*> tokenResults = (*citl)->getTokenResults();
        std::cout<<"> LINE NUMBER: "<<(*citl)->getLineNumber()<<std::endl;
        for (std::list<TokenResult*>::const_iterator citt = tokenResults.begin(); citt != tokenResults.end(); citt++) {
            char* result = NULL;
            (*citt)->getResult(&result);
            std::cout<<"--- TOKEN index{"<<(*citt)->getIndex()<<"} = "<<result<<std::endl;
            if(result!=NULL){
                delete[] result;
            }
        }
    }
}