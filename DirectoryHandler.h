#ifndef DIRECTORYHANDLER_H
#define DIRECTORYHANDLER_H_

void* create_shared_memory(size_t size);
void CreateDirectoryIfNotExist();
void obtenerNombre(int k,char* b,char* dirname);
void borrarAnt();
int ChooseFile(char* dirname);
void MoveFile(char* dirOrg, char* dirDest, char* card);
int ContarMazo(char*dirname);
#endif
