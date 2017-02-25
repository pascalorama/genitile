///////////////////////////////////////////////////////////////////////////////
// Output binary plugins for mdtt
// 
//
//
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Includes

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

#include "../../../mdttSDK.h"

///////////////////////////////////////////////////////////////////////////////
// Local variables


///////////////////////////////////////////////////////////////////////////////
// Get the description of the plugins

DLLEXPORT char* GetDescription(void)
{
	return "Binary Output";
}

///////////////////////////////////////////////////////////////////////////////
// Get the author name

DLLEXPORT char* GetAuthor(void)
{
	return "Spoutnick Team";
}

///////////////////////////////////////////////////////////////////////////////
// Get author contact info

DLLEXPORT char* GetContactInfo(void)
{
	return "www.spoutnickteam.com";
}

///////////////////////////////////////////////////////////////////////////////
// Get build version

DLLEXPORT char* GetBuildVersion(void)
{
	return "1.0";
}

///////////////////////////////////////////////////////////////////////////////
// Get id of the plugins (should be unique!)

DLLEXPORT char* GetID(void)
{
	return"bin";
}

///////////////////////////////////////////////////////////////////////////////
// file extension

DLLEXPORT char* GetExt(void)
{
	return"bin";
}

///////////////////////////////////////////////////////////////////////////////
// define the type of ouput

DLLEXPORT int GetOutputType(void)
{
	return tgOutputType_Raw;
}

///////////////////////////////////////////////////////////////////////////////
// Output the data

DLLEXPORT int OutputData(const char *filename,const char *name,int type,uint8* data,int size)
{
	FILE *out_file=NULL;
	out_file=fopen(filename,"wb");
	if(!out_file)
	{	return tgERR_SAVINGFILE;}
	
	//case OUTPUT_TILES:

	if( (size & 1)==0)
	{
		unsigned char *mem=(unsigned char*)malloc(size);
		int i;
		for(i = 0; i < size; i += 2)
		{	mem[i+0] = data[i+1];
			mem[i+1] = data[i+0];
		}
		if(type==OUTPUT_TILES)
		{	
			if( (size&3)==0)
			{	unsigned short *memw=(unsigned short*) mem;
				unsigned short *dataw=(unsigned short*) data;
				for(i = 0; i < size/2; i += 2)
				{	unsigned short t=memw[i+0];
					memw[i+0] = memw[i+1];
					memw[i+1] = t;
				}				
				fwrite(mem,size,1,out_file);
			}
			else
				fwrite(mem,size,1,out_file);
		}
		else
			fwrite(mem,size,1,out_file);
		free(mem);
	}
	else
		fwrite(data,size,1,out_file);	

	fclose(out_file);
	
	return tgOK;
}

