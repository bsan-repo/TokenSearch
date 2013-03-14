//
//  File.cpp
//  TokenSearch
//
//  Created by b san on 3/13/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#include "File.h"

#include <vector>

File::File(){
    
}

void File::addLine(char* lineContentsParam){
    Line* line = new Line();
    line->set(lineContentsParam);
    lines.push_back(line);
    
    char* contentsCopy = NULL;
    line->getContents(&contentsCopy);
}

void File::cleanFile(){
    
}

File::~File(){
    for (auto it = lines.begin(); it != lines.end(); it++){
        delete *it;
        lines.pop_front();
    }
}
