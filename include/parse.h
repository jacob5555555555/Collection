#ifndef PARSE_H_INCLUDED
#define PARSE_H_INCLUDED

#include <string>
#include <vector>

#include "Objects/Object.h"

ObjRef parse(std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end);

#endif // PARSE_H_INCLUDED
