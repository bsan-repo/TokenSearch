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
    int patternLength = (int)strlen(patternStr);

    // Extract the items usind RegExs
    bool execOK = regExProcessor.match((char*)"\\%\\{[a-zA-Z]?\\d*([sS]\\d*|G)?}", patternStr, &results, &resultsSize, &errorMsg);
    
    if(execOK == true){
        // Create the list of segments for the pattern
        int literalTextBegin = 0;
        
        if(resultsSize>0){
            for(int i = 0; i<resultsSize; i+=2){
                int matchOffset = results[i];
                int matchLength = results[i+1];
                // If before the current token and the previous or the
                // begining of the file there are characters add then as
                // a literal text segment
                if(literalTextBegin < matchOffset){
                    Segment* segment = this->newLiteralTextSegment(literalTextBegin, matchOffset-literalTextBegin);
                    this->segments.push_back(segment);
                }
                // Extract the token
                this->segments.push_back(this->extractToken(matchOffset, matchLength));
                literalTextBegin = matchOffset + matchLength;
                // If it's the last pattern check if there's literal text after it
                // added to the segments
                if(i>=(resultsSize-2)){
                    if (literalTextBegin<patternLength) {
                        Segment* segment = this->newLiteralTextSegment(literalTextBegin, patternLength-literalTextBegin);
                        this->segments.push_back(segment);
                    }
                }
            }
        }else{
            // No tokens were found, copy the whole literal text as Reg Ex
            Segment* segment = this->newLiteralTextSegment(0, patternLength);
            this->segments.push_back(segment);

        }
        // Create the regular expression from the initial pattern
        // once all the segments were extracted
        this->constructRegEx();
    }else{
        printf("ERROR: %s\n", errorMsg); // DEV
    }
    
    if(results != NULL){delete[] results;}
    if (errorMsg != NULL){delete[] errorMsg;}
}

void PCREPattern::constructRegEx(){
    
    this->regEx = new char[500];
    int regExCurrentOffset = 0;
    int numberOfSegments = (int)segments.size();
    int currentSegment = 1;
    bool hasGToken = false;
    
    // Iterate for all segments
    for (std::list<Segment*>::iterator it = this->segments.begin(); it != this->segments.end(); it++) {
        int type = (*it)->getType();
        int offset = (*it)->getOffset();
        int length = (*it)->getLength();
        // TODO Reallocate more memory and copy contents if file bigger than
        // current size of regEx  StrHelper::resizeString(char** , int increment)
        
        switch (type) {
            case SegmentFactory::LITERALTEXT:{
                // Add all the literal text to the regular expression
                strncpy(this->regEx+regExCurrentOffset, this->pattern+offset, length);
                // Move the end of the regular expression to account for the added segment
                regExCurrentOffset += length;
                break;
            }
            case SegmentFactory::TOKEN:{
                char* tokenRegEx = (char*)"\\b\\w+\\b";
                int tokenRegExSize = (int)strlen(tokenRegEx);
                strcpy(this->regEx+regExCurrentOffset, tokenRegEx);
                // Move the end of the regular expression to account for the added segment
                regExCurrentOffset += tokenRegExSize;
                break;
            }
            case SegmentFactory::STOKEN:{
                int spaces = ((SToken*)*it)->getSpaces();
                // TODO Make stoken reg ex string secure allowing to have n digits
                char sTokenRegEx[25] = {0};
                // Account for special case when there is are zero spaces
                if(spaces < 1){
                    sprintf(sTokenRegEx, "(\\b\\w+\\b)");
                }else{
                    sprintf(sTokenRegEx, "(\\b\\w+\\b ){1,%d}(\\b\\w+\\b)", spaces);
                }
                if(currentSegment >= numberOfSegments){
                    int sTokenRegExSize = (int)strlen(sTokenRegEx);
                    sTokenRegEx[sTokenRegExSize] = '$';
                    sTokenRegEx[sTokenRegExSize+1] = NULL;
                }
                int sTokenRegExSize = (int)strlen(sTokenRegEx);
                strcpy(this->regEx+regExCurrentOffset, sTokenRegEx);
                // Move the end of the regular expression to account for the added segment
                regExCurrentOffset += sTokenRegExSize;
                break;
            }
            case SegmentFactory::GTOKEN:{
                char* gTokenRegEx = (char*)".+(";
                int gTokenRegExSize = (int)strlen(gTokenRegEx);
                strcpy(this->regEx+regExCurrentOffset, gTokenRegEx);
                // Move the end of the regular expression to account for the added segment
                regExCurrentOffset += gTokenRegExSize;
                hasGToken = true;
                break;
            }
            default:
                break;
        }
        currentSegment += 1;
    }
    if(hasGToken == true){
        int regExSize = (int)strlen(this->regEx);
        this->regEx[regExSize] = ')';
        this->regEx[regExSize+1] = NULL;
    }
    //printf("REG EX --- -- %s\n", this->regEx);
}

Segment* PCREPattern::newLiteralTextSegment(int offset, int length){
    Segment* segment = SegmentFactory::getSegment(SegmentFactory::LITERALTEXT);
    segment->setOffset(offset);
    segment->setLength(length);
    
    return segment;
}

void PCREPattern::getRegEx(char** regExParam){
    StrHelper::copyString(regExParam, this->regEx);
}