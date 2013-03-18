//
//  RegExProcessor.h
//  TokenSearch
//
//  Created by b san on 3/14/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#ifndef __TokenSearch__RegExProcessor__
#define __TokenSearch__RegExProcessor__

#include <iostream>

// Executes a search in a text of a regular expression

class RegExProcessor{
public:
    // Match the pattern over the subject and save the results to 'results' in pairs,
    // offset-length.
    // Return false if it encounters an error while executing the search,
    // the msg is saved to 'errorMsg'.
    bool match(char* pattern, char* subject, int** results, int* resultsSize, char** errorMsg, bool firstOnly=false){return false;};
};

#endif /* defined(__TokenSearch__RegExProcessor__) */
