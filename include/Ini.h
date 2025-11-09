#pragma once
#define MAX_SECTIONS 16
#define MAX_KEYS 16

typedef struct {
    char key[64];
    char value[255];
} Entry;

typedef struct {
    char name[64];           
    Entry parms[MAX_KEYS];   
    int size;                
} ConfigEntry;

typedef struct {
    ConfigEntry sections[MAX_SECTIONS];
    int count;
} IniFile;

void init_ini(const char* file , IniFile* ini);
ConfigEntry getElementComponents(const char* comp,IniFile* ini);

