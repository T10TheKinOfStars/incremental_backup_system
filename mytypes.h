#ifndef MYTYPES_H
#define MYTYPES_H
#include <unordered_map>
#include <iostream>
#include "smartSync_types.h"

using namespace std;

typedef unsigned long checksum;
typedef unordered_multimap<checksum,Filechk> FileDstTb;
//map<filename, metadata>
typedef map<string, RFileMetadata> NameDataMap;

#endif
