
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


int main(int argc, const char * argv[])
{
    // insert code here...
    std::cout << "\n\n\n\nToken search utility - v1\n\n";
    
    char *line = new char[1000];
    char patternStr[200];
    
    // TODO argument verification
    if(argc > 1){
        strcpy(patternStr, argv[1]);
    
        File* file = new File();
        Pattern* pattern = new PCREPattern(patternStr);
        PCREProcessor processor;
        Search searchInLines(file, pattern, &processor);
        
        // Print info
        std::cout << "=========================================="<<std::endl;
        std::cout << "      Pattern: "<<patternStr<<std::endl;
        char* regEx = NULL;
        pattern->getRegEx(&regEx);
        std::cout << "      RegEx: "<<regEx<<std::endl;
        std::cout << "==========================================="<<std::endl;
        
        /////////////////////////////////////////////////////////
        FILE *testFile;
        if((testFile = fopen("/Users/6opC4h4e3/Desktop/testFile.txt", "r"))== NULL){
            printf("file not found\n");
        }else{
            int dataCounter = 0;
            while(!feof(testFile)){
                char c = fgetc(testFile);
                //printf("%c", c);
                if(c == '\n'){
                    line[dataCounter] = NULL;
                    dataCounter = 0;
                    file->addLine(line);
                }else{
                    line[dataCounter] = c;
                    dataCounter++;
                }
            }
            line[dataCounter-1] = NULL;
            dataCounter = 0;
            file->addLine(line);
        }
        
        Search search(file, pattern, &processor);
        StdPrintResultsSearch::print(&search, file);
        
        delete file;
        /*
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
        line[dataCounter-1] = NULL;
        dataCounter = 0;
        file->addLine(line);
    
        Search search(file, pattern, &processor);
        StdPrintResultsSearch::print(&search);
        */
    }else{
        std::cout<<"No pattern was given.\n";
    }
    
    return 0;
}
