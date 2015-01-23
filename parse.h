#ifndef PARSE_H_INCLUDED
#define PARSE_H_INCLUDED

#include <Object.h>
#include <Expression.h>
#include <NumberObject.h>
#include <UserDefinedObject.h>
#include <string>
#include <vector>

ObjRef parse(const std::vector<std::string>& line);

#endif // PARSE_H_INCLUDED
