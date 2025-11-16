#pragma once
#define MAX_COUNT 16
#define MAX_CHAR 32

typedef struct {
    char key[MAX_CHAR];
    char value[MAX_CHAR];
} Entry;

typedef struct {
    char name[MAX_CHAR];           
    Entry parms[MAX_COUNT];   
    int size;                
} ConfigEntry;

typedef struct {
    ConfigEntry sections[MAX_COUNT];
    int count;
} IniFile;

void init_ini(const char* file , IniFile* ini);
ConfigEntry getElementComponents(const char* comp,IniFile* ini);

