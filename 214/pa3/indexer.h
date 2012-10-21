#ifndef INDEXER_H
#define INDEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>


int fileCallback(const char* pathname, const struct stat* ptr, int flag);


#endif
