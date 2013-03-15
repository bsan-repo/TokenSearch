//
//  Line.cpp
//  TokenSearch
//
//  Created by b san on 3/13/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#include "Line.h"
#include "StrHelper.h"

Line::Line(){
    contents = NULL;
    patternFoundInLine = false;
}

void Line::set(char* contentsParam){
    int size = (int)strlen(contentsParam);
    this->contents = new char[size];
    strcpy(this->contents, contentsParam);
}

void Line::getContents(char** contentsCopyPtr){
    StrHelper::copyString(contentsCopyPtr, this->contents);
}

void Line::clean(){
    if(contents != NULL){
        delete[] contents;
        contents = NULL;
    }
    patternFoundInLine = false;
}

Line::~Line(){
    clean();
}