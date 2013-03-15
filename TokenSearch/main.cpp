
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


int main(int argc, const char * argv[])
{
    // insert code here...
    std::cout << "Token search utility - v1\n\n";
    
    
    char *line = new char[1000];
    char* patternStr = {(char*)"bar %{0G} foo %{1}"};//"foo %{0} is a %{1S0}"};
    
    File* file = new File();
    Pattern* pattern = new PCREPattern(patternStr);
    PCREProcessor processor;
    Search search(file, pattern, &processor);
    
    std::cout << "Pattern: "<<patternStr;
    char* regEx = NULL;
    pattern->getRegEx(&regEx);
    std::cout << "Pattern: "<<regEx;
    
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
                printf("> %s  : %d\n", line, search.isPatternInLine(line));
            }else{
                line[dataCounter] = c;
                dataCounter++;
            }
        }
        line[dataCounter-1] = NULL;
        dataCounter = 0;
        file->addLine(line);
        printf("_____> %s  : %d \n\n", line, search.isPatternInLine(line));
    }
    
    /*
    printf("---------------------\n");
    int dataCounter = 0;
    while(!feof(stdin)){
        char c = fgetc(stdin);
        printf("%c", c);
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
    printf("---------------------\n");
    */
    
    delete file;
    
    return 0;
}
