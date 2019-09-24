#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>


void CreateDirectoryIfNotExist(char s[])
{
  int checkCardsFolder;

  checkCardsFolder = mkdir(s, ACCESSPERMS);
}
