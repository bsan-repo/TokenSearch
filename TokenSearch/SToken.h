//
//  SToken.h
//  TokenSearch
//
//  Created by b san on 3/13/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#ifndef __TokenSearch__SToken__
#define __TokenSearch__SToken__

#include <iostream>
#include "Token.h"

class SToken : public Token{
protected:
    int spaces;
public:
    SToken();
    inline int getSpaces(){return spaces;}
    inline void setSpaces(int spacesParam){this->spaces = spacesParam;}
    
    static const int STOKEN_TYPE = 3;
};

#endif /* defined(__TokenSearch__SToken__) */
