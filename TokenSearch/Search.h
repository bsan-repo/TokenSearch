//
//  Search.h
//  TokenSearch
//
//  Created by b san on 3/14/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#ifndef __TokenSearch__Search__
#define __TokenSearch__Search__

#include <iostream>
#include <list>
#include "File.h"
#include "Pattern.h"
#include "LineResult.h"
#include "RegExProcessor.h"
#include "PCREProcessor.h"


// Performs a search using a pattern in a file both given as arguments
// when creating an instance.
class Search{
protected:
    File* file;
    Pattern* pattern;
    PCREProcessor* processor;
    // The results of the search
    std::list<LineResult*> lineResults;
    
    // Extracts the tokens contents of a line and add them
    // to the attribute lineResults
    void getTokensForLine(char* lineContents, LineResult* lineResult);
    // Determine is the given pattern exist for the contents of a line
    bool isPatternInLine(char* line);
    // Extract the tokens of a line contents in backwards direction (From the
    // last segment in the pattern to the current segment passed as parameter)
    void extractPatternsBackwards(char* lineContents, Segment* currentSegment, LineResult* lineResult, const std::list<Segment*> &patternSegments);
public:
    // Performs the search for the given parameters and store it in the
    // lineResults attribute, accessible through the getLineResults method.
    Search(File* file, Pattern* pattern, PCREProcessor* processor);
    // Returns the results for all the given file
    // - Only lines where the pattern was found are included.
    // - Contains also the contents of all the pattern tokens
    //   found in the line
    const std::list<LineResult*> getLineResults(){return lineResults;}
    
    inline File* getFile(){return file;}
    inline Pattern* getPattern(){return pattern;}
    ~Search();
};

#endif /* defined(__TokenSearch__Search__) */
