//
//  GToken.h
//  TokenSearch
//
//  Created by b san on 3/14/13.
//  Copyright (c) 2013 b san. All rights reserved.
//

#ifndef __TokenSearch__GToken__
#define __TokenSearch__GToken__

#include <iostream>
#include "Token.h"

// Used to force the correct type of segment initialization

class GToken : public Segment{
public:
    GToken();
    
    static const int GTOKEN_TYPE = 4;
};

#endif /* defined(__TokenSearch__GToken__) */
