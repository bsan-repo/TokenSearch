//
//  StdPrintResultsSearch.h
//  TokenSearch
//
//  Created by b san on 3/15/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#ifndef __TokenSearch__StdPrintResultsSearch__
#define __TokenSearch__StdPrintResultsSearch__

#include <iostream>
#include "Search.h"

class StdPrintResultsSearch{
private:
    static void printTokens(const std::list<TokenResult*> &tokenResults);
public:
    static void print(Search* search, File* file);
};

#endif /* defined(__TokenSearch__StdPrintResultsSearch__) */
