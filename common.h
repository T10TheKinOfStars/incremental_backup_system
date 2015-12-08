#ifndef COMMON_H
#define COMMON_H

#include "smartSync_types.h"
#include <vector>

using namespace std;

#ifdef DEBUG
#define dprintf printf
#else
#define dprintf(...)
#endif

size_t getSizeOfObject(RFileMetadata data);
size_t getSizeOfObject(Filedes data);
size_t getSizeOfObject(Filechk data);
size_t getSizeOfObject(RFile data);
size_t getSizeOfObject(vector<Filechk> vdata);
size_t getSizeOfObject(vector<Filedes> vdata);

/*
size_t getMetaSize(RFileMetadata data);
size_t getFiledesSize(Filedes data);
size_t getFilechkSize(Filechk data);
size_t getRFileSize(RFile data);
size_t getFilechksSize(vector<Filechk> vdata);
size_t getFiledessSize(vector<Filedes> vdata);
*/
#endif
