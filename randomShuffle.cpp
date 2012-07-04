//
//  randomShuffle.cpp
//  Boggle
//
//  Created by Alok K Shukla on 04/07/12.
//  Copyright (c) 2012 MNNIT Allahabad. All rights reserved.
//

#include <iostream>
#include <string>
#include "randomShuffle.h"
#include "random.h"

using namespace std;

string randomShuffle(string input) {
    string result;
    if (input=="") {
        result += "";
    }
    else {
        string rest;
        int index=randomInteger(0, input.size()-1);
        char ch=input[index];
        if (index!=input.size()-1) {
            rest = input.substr(0, index) + input.substr(index + 1);    
        }
        else {
            rest=input.substr(0,index);
        }
        result+= ch+randomShuffle(rest);
    }
    return result;
    
    
}
