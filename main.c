#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "utility.h"
#include "time.h"


void ArgsParser(int argc , char** argv, IniFile* ini)
{
	for(int i=1; i<argc; i++)
	{
		const char* ARGS = argv[i];
		if (compare(ARGS , "--current") || compare(ARGS , "-c"))
		{
			const char* module = getCurrentModule(ini);
			printf("Current Mod: %s\n" , module);
		}
		if(compare(ARGS , "--random") || compare(ARGS , "-r"))
		{
			char buffer[254];
			const char* module = getCurrentModule(ini);
			ConfigEntry currentModData = getElementComponents(module, ini);
			for(int i=0; i<currentModData.size; i++)
			{
				if(compare( "Path" ,currentModData.parms[i].key))
				{
					strcpy(buffer, currentModData.parms[i].value);
					buffer[254] = 0;
				}
			}
			const char* path = getRandomWallpaper(buffer);
			changeWallpaper(path);
		}

		if(compare(ARGS , "--edit") || compare(ARGS , "-e"))
		{
			char buffer[255];
			char* path = getConfigPath();

			sprintf(buffer, "start \"\" notepad \"%s\"", path);
			system(buffer);
		}

		if(compare(ARGS , "--path") || compare(ARGS , "-p"))
		{
			char* path = argv[i+1];
			changeWallpaper(path);
		}

		if(compare(ARGS , "--web") || compare(ARGS , "-w"))
		{
			char* path = argv[i+1];
			getWallpaperFromWeb(path);
		}

		if (compare(ARGS , "--help") || compare(ARGS , "-h"))
		{
			printf("Usage of Wall:\n");
			printf("--current: Shows the current in use module\n");
			printf("--path: Pass a wallpaper path to change it\n");
			printf("--random: Apply a random wallpaper from the current module\n");
			printf("--edit: Edit the config file\n\n");

			printf("Note: Either use full arg flag or one dash and first letter\n");
			printf("Example: --current -> -c\n");
		}
		
	}
}

int main(int argc , char** argv)
{
	srand(time(NULL));  
	IniFile ini = {0};
	if(checkExistance()){
		init_ini(getConfigPath() , &ini);
		ArgsParser(argc , argv, &ini);
	}
}
