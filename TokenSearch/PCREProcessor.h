//
//  PCREProcessor.h
//  TokenSearch
//
//  Created by b san on 3/14/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#ifndef __TokenSearch__PCREProcessor__
#define __TokenSearch__PCREProcessor__

#include <iostream>
#include "RegExProcessor.h"

class PCREProcessor : public RegExProcessor{
public:
    bool match(char* pattern, char* subject, int** results, int* resultsSize, char** errorMsg, bool firstOnly=false);
};

#endif /* defined(__TokenSearch__PCREProcessor__) */
