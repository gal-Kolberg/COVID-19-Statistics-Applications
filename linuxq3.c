#include "corona_api_utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void writeFileLine(FILE* fp, oneDay* oneDay);
void createCsvFile(char *filename, FILE* destFile);

int main(int  argc, char*  argv[])
{
    char filename[50];
	char* key;

	if(validate_input(argc, argv, filename, "--country") == 0)
	{
		printf("Invalid input, please try again\n");
		exit(1);
	}

    int index;
    countryData country;
    eError err;
    FILE* destFile;
    
    //Load data fron country file
    load_file_by_country(filename, &country, &err);

    if(err != NO_ERR)
    {
        printf("%s", error_message(err));
        exit(1);
    }

    //Open csv file
    char* tok = (char*) malloc(40);
    strcpy(tok, filename);
    tok = strcat(tok,"_csv");
    destFile = fopen(tok,"w+");

    if(destFile == NULL)
    {
        printf("ERROR: File %s doesn't exists!\n", filename);
        exit(1);
    }

    fprintf(destFile,"date;confirmed;deaths;recovered;active\n"); //write the categories 

    //process data
    for(index = 0; index < country.numOfDays-1; index++)
    {
        writeFileLine(destFile, &(country.data[index]));
    }

    fclose(destFile);
    
    free_country_data(&country);  
}

void writeFileLine(FILE* fp, oneDay* oneDay)
{
    fprintf(fp, "%s;%s;%s;%s;%s\n", oneDay->date, oneDay->confirmed, oneDay->deaths, oneDay->recovered, oneDay->active);
}