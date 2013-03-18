
//
//  main.cpp
//  TokenSearch
//
//  Created by b san on 3/13/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#include <iostream>
#include "File.h"
#include "PCREPattern.h"
#include "PCREProcessor.h"
#include "Search.h"
#include "StdPrintResultsSearch.h"


// Receives the contents of a file from stdin and using the pattern passed as the
// first argument attemps to find it in each line of the file. 
// - A segment of text can be extracted from the pattern using tokens.
//   A token is a segment of text enclosed between separation characters like spaces
//   or includes the whole text if at the end of the pattern.
//   The token can be determined by %{} character sequence, and need to have a
//   positive number index. e.g. "foo %{0} is a %{1}". 
// - A character can be included at before the number index. e.g. "%{x12}"
// - After the number two options can be included:
//      + An 'S' character to indicate the number of separation characters
//        that need to be included to determine the token contents. It
//        must be followed by a number indicating the numbers of spaces.
//        e.g. Include 0 spaces: "%{3s0}", include 3 spaces: "%{3s3}"
//      + A 'G' character to indicate that is a greedy search an that all
//        the characters before the following pattern should be included.
//        e.g. "%{3G}".

int main(int argc, const char * argv[])
{
    // insert code here...
    std::cout << "\n\n\n\nToken search utility - v1\n\n";
    
    char *line = new char[1000];
    char patternStr[200];
    
    if(argc > 1){
        strcpy(patternStr, argv[1]);
    
        // Extract the regular expression from the pattern
        File* file = new File();
        Pattern* pattern = new PCREPattern(patternStr);
        
        // Print info
        std::cout << "=========================================="<<std::endl;
        std::cout << "      Pattern: "<<patternStr<<std::endl;
        char* regEx = NULL;
        pattern->getRegEx(&regEx);
        std::cout << "      RegEx: "<<regEx<<std::endl;
        std::cout << "==========================================="<<std::endl;
        
        // Store the contents of the file
        int dataCounter = 0;
        while(!feof(stdin)){
            char c = fgetc(stdin);
            if(c == '\n'){
                line[dataCounter] = NULL;
                dataCounter = 0;
                file->addLine(line);
            }else{
                line[dataCounter] = c;
                dataCounter++;
            }
        }
        // The last line doesn't have a new line char that triggers
        // the bucle condition to add the line
        line[dataCounter-1] = NULL;
        dataCounter = 0;
        file->addLine(line);
        
        // Create the implementation processor and pass it to the search
        PCREProcessor processor;
        Search search(file, pattern, &processor);
        // Print the results
        StdPrintResultsSearch::print(&search, file);
        
    }else{
        std::cout<<"\nNo pattern was given.\n\n";
    }
    
    return 0;
}
