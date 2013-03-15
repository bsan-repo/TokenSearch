//
//  PCREPattern.cpp
//  TokenSearch
//
//  Created by b san on 3/13/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#include "PCREPattern.h"
#include "StrHelper.h"
#include "PCREProcessor.h"
#include "SegmentFactory.h"

PCREPattern::PCREPattern(char* patternStr):Pattern(patternStr){
    PCREProcessor regExProcessor;
    int* results = NULL;
    int resultsSize = 0;
    char* errorMsg = NULL;

    // Extract the items usind RegExs
    bool execOK = regExProcessor.match((char*)"\\%\\{[a-zA-Z]?\\d*([sS]\\d*|G)?}", patternStr, &results, &resultsSize, &errorMsg);
    
    if(execOK == true){
        // Create the list of segments for the pattern
        int literalTextBegin = 0;
        for(int i = 0; i<resultsSize; i+=2){
            int matchOffset = results[i];
            int matchLength = results[i+1];
            if(literalTextBegin < matchOffset){
                Segment* segment = SegmentFactory::getSegment(SegmentFactory::LITERALTEXT);
                segment->setOffset(literalTextBegin);
                segment->setLengt(matchLength);
                this->segments.push_back(segment);
                //printf("LITERAL__  %.*s\n", matchLength-1, this->pattern+literalTextBegin);
            }
            //printf("TOKEN__  %.*s  - offset: %d    length: %d, \n", matchLength, this->pattern+matchOffset, matchOffset, matchLength);
            this->segments.push_back(this->extractToken(matchOffset, matchLength));
            literalTextBegin = matchOffset + matchLength;
        }
        
        // Create the regular expression from the initial pattern
        this->constructRegEx();
    }else{
        //printf("ERROR: %s\n", errorMsg); // DEV
    }
}

void PCREPattern::constructRegEx(){
    
    this->regEx = new char[500];
    int regExCurrentOffset = 0;
    int numberOfSegments = (int)segments.size();
    int currentSegment = 1;
    bool hasGToken = false;
    for (std::list<Segment*>::iterator it = this->segments.begin(); it != this->segments.end(); it++) {
        int type = (*it)->getType();
        int offset = (*it)->getOffset();
        int length = (*it)->getLength();
        // TODO Reallocate more memory and copy contents if file bigger than
        // current size of regEx  StrHelper::resizeString(char** , int increment)
        
        switch (type) {
            case SegmentFactory::LITERALTEXT:{
                strncpy(this->regEx+regExCurrentOffset, this->pattern+offset, length);
                regExCurrentOffset += length;
                printf("LITERALTEXT: %.*s    RE: %s\n", length, this->pattern+offset, this->regEx);
                break;
            }
            case SegmentFactory::TOKEN:{
                char* tokenRegEx = (char*)"\\b\\w+\\b";
                int tokenRegExSize = (int)strlen(tokenRegEx);
                strcpy(this->regEx+regExCurrentOffset, tokenRegEx);
                regExCurrentOffset += tokenRegExSize;
                printf("TOKEN: %.*s    RE: %s\n", length, this->pattern+offset, this->regEx);
                break;
            }
            case SegmentFactory::STOKEN:{
                int spaces = ((SToken*)*it)->getSpaces();
                // TODO Make stoken reg ex string secure allowing to have n digits
                char sTokenRegEx[25] = {0};
                if(spaces > 0){
                    sprintf(sTokenRegEx, "(\\b\\w+\\b){1,%d}", spaces);
                }else{
                    strcpy(sTokenRegEx, (char*)"(\\b\\w+\\b)");
                }
                if(currentSegment >= numberOfSegments){
                    int sTokenRegExSize = (int)strlen(sTokenRegEx);
                    sTokenRegEx[sTokenRegExSize] = '$';
                    sTokenRegEx[sTokenRegExSize+1] = NULL;
                }
                int sTokenRegExSize = (int)strlen(sTokenRegEx);
                strcpy(this->regEx+regExCurrentOffset, sTokenRegEx);
                regExCurrentOffset += sTokenRegExSize;
                printf("STOKEN: %.*s    RE: %s\n", length, this->pattern+offset, this->regEx);
                break;
            }
            case SegmentFactory::GTOKEN:{
                char* gTokenRegEx = (char*)".+(";
                int gTokenRegExSize = (int)strlen(gTokenRegEx);
                strcpy(this->regEx+regExCurrentOffset, gTokenRegEx);
                regExCurrentOffset += gTokenRegExSize;
                hasGToken = true;
                printf("GTOKEN: %.*s    RE: %s\n", length, this->pattern+offset, this->regEx);
                break;
            }
            default:
                printf("DEFAULT: %.*s    RE: %s\n", length, this->pattern+offset, this->regEx);
                break;
        }
        currentSegment += 1;
    }
    if(hasGToken == true){
        int regExSize = (int)strlen(this->regEx);
        this->regEx[regExSize] = ')';
        this->regEx[regExSize+1] = '$';
        this->regEx[regExSize+2] = NULL;
    }
    printf("REG EX --- -- %s\n", this->regEx);
}

void PCREPattern::getRegEx(char** regExParam){
    StrHelper::copyString(regExParam, this->regEx);
}