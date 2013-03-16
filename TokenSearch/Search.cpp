//
//  Search.cpp
//  TokenSearch
//
//  Created by b san on 3/14/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#include "Search.h"
#include "SegmentFactory.h"

Search::Search(File* file, Pattern* pattern, PCREProcessor* processor){
    this->file = file;
    this->pattern = pattern;
    this->processor = processor;
    
    char* lineContents = NULL;
    
    const std::list<Line*> fileLines = this->file->getLines();
    
    for (std::list<Line*>::const_iterator cit = fileLines.begin(); cit != fileLines.end(); cit++) {
        lineContents = NULL;
        (*cit)->getContents(&lineContents);
        printf("LINE CONTENTS _> %s\n", lineContents);
        // Skip empty lines
        if(lineContents != NULL){
            if (this->isPatternInLine(lineContents)){
                LineResult* lineResult = new LineResult((*cit)->getNumber());
                this->getTokensForLine(lineContents, lineResult);
                this->lineResults.push_back(lineResult);
                printf("RESULTS (%d) -> %s\n", lineResult->getLineNumber(), lineContents);
            }
            if(lineContents!= NULL){
                delete[] lineContents;
                lineContents = NULL;
            }
        }
    }
}

Search::~Search(){
    for (std::list<LineResult*>::iterator it = lineResults.begin(); it != lineResults.end(); it++){
        delete *it;
        *it = NULL;
        lineResults.pop_front();
    }
}

void Search::getTokensForLine(char* lineContents, LineResult* lineResult){
    int  lineOffset = 0;
    int* results = NULL;
    int resultSize = 0;
    char* errorMsg = NULL;
    Segment* segment = NULL;
    char* patternStr = NULL;
    char currentRegEx[100];
    int offset = 0;
    int length = 0;
    char literalTextRegEx[200];
    
    const std::list<Segment*> patternSegments = this->pattern->getSegments();
    pattern->getPattern(&patternStr);
    int patternSegmentsSize = (int)patternSegments.size();
    int patternCounter = 1;
    
    for (std::list<Segment*>::const_iterator cit = patternSegments.begin(); cit != patternSegments.end(); cit++) {
        segment = (*cit);
        
        
        ////////////////////////////
        char segmentText[100];
        sprintf(segmentText, "%.*s", segment->getLength(), patternStr+segment->getOffset());
        printf("SEGMENT: t(%d) -> %s off(%d) l(%d)\n", segment->getType(), segmentText, segment->getOffset(), segment->getLength());
        ////////////////////////////
        
        switch (segment->getType()) {
            case SegmentFactory::LITERALTEXT:{
                // Skipt literal text
                offset = segment->getOffset();
                length = segment->getLength();
                results = NULL;
                errorMsg = NULL;
                sprintf(literalTextRegEx, "^%.*s", length, patternStr+offset);
                
                processor->match(literalTextRegEx, (lineContents+lineOffset), &results, &resultSize, &errorMsg);
                if(resultSize > 0){
                    lineOffset += results[0]+results[1];//lineOffset+=offset+lenght
                }
                printf("LITERALTEXT M(%s) L_OFF(%d)\n", literalTextRegEx, lineOffset);
                if(results != NULL){delete [] results; results = NULL;}
                if(errorMsg != NULL){delete [] errorMsg; errorMsg = NULL;}
                break;
            }
            case SegmentFactory::TOKEN:
            case SegmentFactory::STOKEN:{
                results = NULL;
                errorMsg = NULL;
                if(segment->getType() == SegmentFactory::STOKEN){
                    int spaces = ((SToken*)segment)->getSpaces();
                    if(spaces < 1){
                        sprintf(currentRegEx, "(\\b\\w+\\b)");
                    }else{
                        sprintf(currentRegEx, "(\\b\\w+\\b ){1,%d}(\\b\\w+\\b)", spaces);
                    }
                }else{
                    if(patternCounter >= patternSegmentsSize){
                        sprintf(currentRegEx, ".*");
                    }else{
                        sprintf(currentRegEx, "^\\b\\w+\\b");
                    }
                }
                processor->match(currentRegEx, (lineContents+lineOffset), &results, &resultSize, &errorMsg, true);
                if(resultSize > 0){
                    int offset = results[0];
                    int length = results[1];
                    char* tokenResultStr = new char[length];
                    strncpy(tokenResultStr, (lineContents+lineOffset+offset), length);
                    TokenResult* tokenResult = new TokenResult(((Token*)segment)->getIndex(), tokenResultStr);
                    lineResult->addTokenResult(tokenResult);
                    
                    lineOffset += results[0]+results[1];//lineOffset+=offset+lenght
                    printf("TOKEN RESULT(%d): %s\n", ((Token*)segment)->getIndex(), tokenResultStr);
                }
                printf("TOKEN M(%s) L_OFF(%d)\n", currentRegEx, lineOffset);
                if(results != NULL){delete [] results; results = NULL;}
                if(errorMsg != NULL){delete [] errorMsg; errorMsg = NULL;}
                break;
            }
            case SegmentFactory::GTOKEN:{
                // TODO Implement functionality to extract GTokens
                break;
            }
            default:
                break;
        }
        
        
        if(results != NULL){delete[] results; results = NULL;}
        if (errorMsg != NULL){delete[] errorMsg; errorMsg = NULL;}
        patternCounter++;
    }
}

bool Search::isPatternInLine(char* line){
    int* results = NULL;
    int resultsSize = 0;
    char* errorMsg = NULL;
    char* regExPattern = NULL;
    
    pattern->getRegEx(&regExPattern);
    
    // Extract the items using RegExs
    bool execOK = processor->match(regExPattern, line, &results, &resultsSize, &errorMsg, true);
    
    if(execOK == true && resultsSize>0){
        return true;
    }
    return false;
}
