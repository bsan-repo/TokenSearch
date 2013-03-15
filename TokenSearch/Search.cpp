//
//  Search.cpp
//  TokenSearch
//
//  Created by b san on 3/14/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#include "Search.h"

Search::Search(File* file, Pattern* pattern){
    this->file = file;
    this->pattern = pattern;
}

Search::~Search(){
    for (std::list<LineResult*>::iterator it = lineResults.begin(); it != lineResults.end(); it++){
        delete *it;
        lineResults.pop_front();
    }
}
