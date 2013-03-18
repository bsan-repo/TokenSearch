//
//  Search.cpp
//  TokenSearch
//
//  Created by b san on 3/14/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#include "Search.h"
#include "SegmentFactory.h"
#include "StrHelper.h"

Search::Search(File* file, Pattern* pattern, PCREProcessor* processor){
    this->file = file;
    this->pattern = pattern;
    this->processor = processor;
    
    char* lineContents = NULL;
    
    const std::list<Line*> fileLines = this->file->getLines();
    
    for (std::list<Line*>::const_iterator cit = fileLines.begin(); cit != fileLines.end(); cit++) {
        lineContents = NULL;
        (*cit)->getContents(&lineContents);
        // Skip empty lines
        if(lineContents != NULL){
            if (this->isPatternInLine(lineContents)){
                LineResult* lineResult = new LineResult((*cit)->getNumber());
                this->getTokensForLine(lineContents, lineResult);
                this->lineResults.push_back(lineResult);
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
    char literalTextRegEx[200];
    bool gTokenBackwardsSearchCompleted = false;
    
    const std::list<Segment*> patternSegments = this->pattern->getSegments();
    pattern->getPattern(&patternStr);
    int patternSegmentsSize = (int)patternSegments.size();
    int patternCounter = 1;
    
    for (std::list<Segment*>::const_iterator cit = patternSegments.begin(); cit != patternSegments.end(); cit++) {
        segment = (*cit);
        
        switch (segment->getType()) {
            case SegmentFactory::LITERALTEXT:{
                // Skipt literal text
                int offset = segment->getOffset();
                int length = segment->getLength();
                results = NULL;
                errorMsg = NULL;
                sprintf(literalTextRegEx, "^%.*s", length, patternStr+offset);
                
                processor->match(literalTextRegEx, (lineContents+lineOffset), &results, &resultSize, &errorMsg);
                if(resultSize > 0){
                    lineOffset += results[0]+results[1];//lineOffset+=offset+lenght
                }
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
                        sprintf(currentRegEx, "^(\\b\\w+\\b)");
                    }else{
                        sprintf(currentRegEx, "^((\\b\\w+\\b ){1,%d}(\\b\\w+\\b))", spaces);
                    }
                }else{
                    if(patternCounter >= patternSegmentsSize){
                        sprintf(currentRegEx, "^.*");
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
                }
                if(results != NULL){delete [] results; results = NULL;}
                if(errorMsg != NULL){delete [] errorMsg; errorMsg = NULL;}
                break;
            }
            case SegmentFactory::GTOKEN:{
                gTokenBackwardsSearchCompleted = true;
                // Extract the only leaving content = lineContents+lineOffset
                this->extractPatternsBackwards(lineContents+lineOffset, segment, lineResult, patternSegments);
                break;
            }
            default:
                break;
        }
        
        
        if(results != NULL){delete[] results; results = NULL;}
        if (errorMsg != NULL){delete[] errorMsg; errorMsg = NULL;}
        patternCounter++;
        
        if(gTokenBackwardsSearchCompleted == true){
            break;
        }
    }
}

// Extract the patterns backwards leaving the space for greedy token extraction
void Search::extractPatternsBackwards(char* lineContents, Segment* currentSegment, LineResult* lineResult, const std::list<Segment*> &patternSegments){
    
    int* results = NULL;
    int resultSize = 0;
    char* errorMsg = NULL;
    Segment* segment = NULL;
    char* patternStr = NULL;
    char currentRegEx[100];
    char literalTextRegEx[200];
    char* lineAnalyzed = NULL;
    StrHelper::copyString(&lineAnalyzed, lineContents);
    int lineAnalyzedLength = (int)strlen(lineAnalyzed);
    
    pattern->getPattern(&patternStr);
    
    for(std::list<Segment*>::const_reverse_iterator rit = patternSegments.rbegin(); rit!=patternSegments.rend(); rit++){
        segment = (*rit);
        
        switch (segment->getType()) {
            case SegmentFactory::LITERALTEXT:{
                // Skipt literal text
                int offsetPattern = segment->getOffset();
                int lengthPattern = segment->getLength();
                results = NULL;
                errorMsg = NULL;
                sprintf(literalTextRegEx, "%.*s$", lengthPattern, patternStr+offsetPattern);
                
                processor->match(literalTextRegEx, lineAnalyzed, &results, &resultSize, &errorMsg);
                if(resultSize > 0){
                    lineAnalyzed[lineAnalyzedLength-lengthPattern] = NULL;
                    lineAnalyzedLength -= lengthPattern;
                }
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
                        sprintf(currentRegEx, "(\\b\\w+\\b)$");
                    }else{
                        sprintf(currentRegEx, "(\\b\\w+\\b ){1,%d}(\\b\\w+\\b)$", spaces);
                    }
                }else{
                    sprintf(currentRegEx, "(\\b\\w+\\b)$");
                }
                processor->match(currentRegEx, lineAnalyzed, &results, &resultSize, &errorMsg, true);
                if(resultSize > 0){
                    int offsetResult = results[0];
                    int lengthResult = results[1];
                    char* tokenResultStr = new char[lengthResult];
                    strncpy(tokenResultStr, (lineContents+offsetResult), lengthResult);
                    TokenResult* tokenResult = new TokenResult(((Token*)segment)->getIndex(), tokenResultStr);
                    lineResult->addTokenResult(tokenResult);
                    
                    lineAnalyzedLength -= results[1];
                }
                if(results != NULL){delete [] results; results = NULL;}
                if(errorMsg != NULL){delete [] errorMsg; errorMsg = NULL;}
                break;
            }
            case SegmentFactory::GTOKEN:{
                // Ignore
                break;
            }
            default:
                break;
        }
        
        
        if(results != NULL){delete[] results; results = NULL;}
        if (errorMsg != NULL){delete[] errorMsg; errorMsg = NULL;}
        
        if ((*rit) == currentSegment) {
            TokenResult* tokenResult = new TokenResult(((Token*)segment)->getIndex(), lineAnalyzed);
            lineResult->addTokenResult(tokenResult);
            break;
        }
    }
    
    if(lineAnalyzed != NULL){
        delete[] lineAnalyzed;
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
