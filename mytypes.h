#ifndef MYTYPES_H
#define MYTYPES_H
#include <unordered_map>
#include <iostream>
#include "smartSync_types.h"

typedef unsigned long checksum;
typedef std::unordered_multimap<checksum,Filechk> FileDstTb;
typedef std::map<std::string, RFileMetadata> NameDataMap;

using namespace std;
#endif
