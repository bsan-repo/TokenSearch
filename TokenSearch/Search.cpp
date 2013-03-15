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
    
    const std::list<Line*> fileLines = this->file->getLines();
    
    for (std::list<Line*>::const_iterator cit = fileLines.begin(); cit != fileLines.end(); cit++) {
        char* lineContents = NULL;
        (*cit)->getContents(&lineContents);
        if (this->isPatternInLine(lineContents)){
            LineResult* lineResult = new LineResult((*cit)->getNumber());
            this->getTokensForLine(lineContents, lineResult);
            this->lineResults.push_back(lineResult);
        }
        delete[] lineContents;
    }
}

Search::~Search(){
    for (std::list<LineResult*>::iterator it = lineResults.begin(); it != lineResults.end(); it++){
        delete *it;
        lineResults.pop_front();
    }
}

void Search::getTokensForLine(char* lineContents, LineResult* lineResult){
    const std::list<Segment*> patternSegments = this->pattern->getSegments();
    int  lineOffset = 0;
   
    for (std::list<Segment*>::const_iterator cit = patternSegments.begin(); cit != patternSegments.end(); cit++) {
        int* results = NULL;
        int resultSize = 0;
        char* errorMsg = NULL;
        Segment* segment = (*cit);
        char* patternStr = NULL;
        char* currentRegEx = NULL;
        
        pattern->getPattern(&patternStr);
        
        switch (segment->getType()) {
            case SegmentFactory::LITERALTEXT:{
                // Skipt literal text
                results = NULL;
                errorMsg = NULL;
                int offset = segment->getOffset();
                int length = segment->getLength();
                char literalTextRegEx[200];
                sprintf(literalTextRegEx, "\'%.*s", length, patternStr+offset);
                
                literalTextRegEx[0]='^';
                processor->match(literalTextRegEx, (lineContents+lineOffset), &results, &resultSize, &errorMsg);
                if(resultSize > 0){
                    lineOffset += results[0]+results[1];//lineOffset+=offset+lenght
                }
                if(results != NULL){delete [] results;} //TODO solve bug with memory release error
                if(errorMsg != NULL){delete [] errorMsg;}
                break;
            }
            case SegmentFactory::TOKEN:
            case SegmentFactory::STOKEN:{
                results = NULL;
                errorMsg = NULL;
                currentRegEx = NULL;
                Token* token = ((Token*)segment);
                token->getRegEx(&currentRegEx);
                char* tokenRegEx = new char[strlen(currentRegEx)+2];
                sprintf(tokenRegEx, "^%s", currentRegEx);
                processor->match(tokenRegEx, (lineContents+lineOffset), &results, &resultSize, &errorMsg, true);
                if(resultSize > 0){
                    int offset = results[0];
                    int length = results[1];
                    char* tokenResultStr = new char[length];
                    strncpy(tokenResultStr, (lineContents+lineOffset+offset), length);
                    TokenResult* tokenResult = new TokenResult(token->getIndex(), tokenResultStr);
                    lineResult->addTokenResult(tokenResult);
                    
                    lineOffset += results[0]+results[1];//lineOffset+=offset+lenght
                    
                    if(tokenRegEx != NULL){delete [] tokenRegEx;}
                }
                if(currentRegEx != NULL){delete [] currentRegEx;}
                if(results != NULL){delete [] results;}
                if(errorMsg != NULL){delete [] errorMsg;}
                break;
            }
            case SegmentFactory::GTOKEN:{
                // TODO Implement functionality to extract GTokens
                break;
            }
            default:
                break;
        }
        
        
        if(results != NULL){delete[] results;}
        if (errorMsg != NULL){delete[] errorMsg;}
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
