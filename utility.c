#include "utility.h"
#include "stdlib.h"
#include "stdio.h"
#include "Ini.h"
#include "string.h"
#include "time.h"

#define WIN32_LEAN_AND_MEAN
#include "Windows.h"

bool checkExistance()
{
	char* checkPath = getConfigPath();
	if(fopen(checkPath , "r")){
		return true;
	}
	else{
		FILE* fp = fopen(getConfigPath(), "w"); 
		fprintf(fp , "(use)\n");
		fprintf(fp , "Module: NULL\n\n");

		fprintf(fp , "(Krooz)\n");
		fprintf(fp , "Path: Add Wallpaper Folder Path\n");
		fclose(fp);

		printf("File: %s is Created...\n" , getConfigPath());
		return true;
	}

	return false;
}


char* getConfigPath() {
    char* UserDir = getenv("USERPROFILE");  
    const char* filename = "\\.Swap.ini"; 
    int pathLen = strlen(UserDir) + strlen(filename) + 1;
    char* newPath = malloc(pathLen);

    strcpy(newPath, UserDir);
    strcat(newPath, filename);

    return newPath; 
}

bool compare(const char* src,const char* tar){
	return strcmp(src ,tar) == 0;
}


const char* getCurrentModule(IniFile* ini){
	static char buffer[255];
	ConfigEntry data = getElementComponents("use" , ini);
	for(int i=0; i<data.size; i++){
		if (compare("Module", data.parms[i].key)) {
			if(compare("NULL", data.parms[i].value)){
				printf("Error: Module Is Null Create One\n");
				exit(0);
			}
			strncpy(buffer, data.parms[i].value, 255);
            buffer[255] = 0;
			return buffer;
		}
	}

	return "";
}

const char* getRandomWallpaper(const char* folder)
{
    static char randFile[512];
    char searchPath[512];

    snprintf(searchPath, sizeof(searchPath), "%s\\*", folder);
    WIN32_FIND_DATA findData;
    HANDLE hFind = FindFirstFile(searchPath, &findData);

    char* files[1024];
    int count = 0;

    do {
		DWORD attr = findData.dwFileAttributes;
        if ((attr & FILE_ATTRIBUTE_DIRECTORY) == 0 &&
        (attr & FILE_ATTRIBUTE_HIDDEN) == 0 &&
        (attr & FILE_ATTRIBUTE_SYSTEM) == 0)  {
            files[count++] = _strdup(findData.cFileName);
        }
    } while (FindNextFile(hFind, &findData) && count < 1024);

    FindClose(hFind);

    int randIndex = rand() % count;

	printf("Applying: %s\n" , files[randIndex]);

    // build full path
    snprintf(randFile, sizeof(randFile), "%s\\%s", folder, files[randIndex]);
    for (int i = 0; i < count; i++) free(files[i]);
    return randFile; 
}

void changeWallpaper(const char* path)
{
	SystemParametersInfo(
		SPI_SETDESKWALLPAPER,         
        0,                             
        (PVOID)path,         
        SPIF_UPDATEINIFILE | SPIF_SENDCHANGE 
	);	
}

const char* getWallpaperFromWeb(const char* path){
	char tempPath[MAX_PATH];
    DWORD len = GetTempPathA(MAX_PATH, tempPath);
	char* tempWall = "wallpaper.png";

	char FullPath[MAX_PATH];
	sprintf(FullPath , "%s\%s", tempPath , tempWall);


	char command[MAX_PATH];
	sprintf(command , "curl -s -o %s %s", FullPath , path);
	system(command);
	
	if(fopen(FullPath,"r")){
		changeWallpaper(FullPath);
	}
}
