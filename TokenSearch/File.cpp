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
    numberOfLines = 0;
}

void File::addLine(char* lineContentsParam){
    numberOfLines += 1;
    Line* line = new Line(numberOfLines, lineContentsParam);
    lines.push_back(line);
    
    char* contentsCopy = NULL;
    line->getContents(&contentsCopy);
}

File::~File(){
    for (std::list<Line*>::iterator it = lines.begin(); it != lines.end(); it++){
        delete *it;
        lines.pop_front();
    }
}
