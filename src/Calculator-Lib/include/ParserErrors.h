#pragma once

#include <string>
#include <sstream>
#include "include/Parse.h"

using namespace std;

string ParseErrorToString(ParserState error, string& input, int positon);