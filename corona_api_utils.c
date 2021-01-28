#include "corona_api_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int read_next_day(FILE* fp, oneDay* oneDay);
static int read_next_field(FILE* fp, char* line, char* field);
static int open_file_check(FILE* fp, eError* err);
static int allocation_check(void* pointer, eError* err);

int validate_input(int size, char* input[], char* parameter, char* toCompare)
{
	int i, res = 0;

	for (i = 0; i < size; i++)
	{
		if (strcmp(input[i], toCompare) == 0)
		{
			strcpy(parameter, input[++i]);
            res = 1;
            break;
		}
	}

    return res;
}

Key valid_key(char* key)
{
	if (strcmp(key, "Confirmed") == 0)
		return Confirmed;
	else if (strcmp(key, "Deaths") == 0)
		return Deaths;
	else if (strcmp(key, "Recovered") == 0)
		return Recovered;
	else if (strcmp(key, "Active") == 0)
		return Active;
	else
	{
		printf("Invalid key entered! try again\n");
		exit(1);
	}
}

void load_file_by_country(char* fileName, countryData* country, eError* err)
{
    FILE* fp;
    int size = 40;
    int index = 0;
	char filePath[255] = COUNTRIES_DIR;
	strcat(filePath, fileName);

    fp = fopen(filePath, "r+");

    if (!open_file_check(fp, err))
    {
        return;
    }

    country->data = (oneDay*) malloc(sizeof(oneDay)*size);
    strcpy(country->name, fileName);

    if(!allocation_check(country->data, err))
    {
        return;
    }

    while(read_next_day(fp, &(country->data[index] )) != 0)
    {
        if(index == size-1)
        {
            size *= 2;
            country->data = (oneDay*) realloc(country->data, sizeof(oneDay)*size);

            if (!allocation_check(country->data, err))
            {
                return;
            }
        }

        index++;
    }

    country->numOfDays = index - 1;
    fclose(fp);
    *err = NO_ERR;
}

void load_all_countries(allCountriesData* allCountries, eError* err)
{
    FILE* countriesFile;
    char fileName[50];
    int index = 0;
    int size = 124;

    countriesFile = fopen("countries", "r+");

    if (!open_file_check(countriesFile, err))
    {
        return;
    }

    allCountries->countries = (countryData*) malloc(sizeof(countryData) * size);

    if(!allocation_check(allCountries->countries, err))
    {
        return;
    }

    do
    {
        fscanf(countriesFile, "%s", fileName);
        load_file_by_country(fileName, &(allCountries->countries[index++]), err);

        if(*err != NO_ERR)
        {
            return;
        }

        if(index == size-1)
        {
            size *= 2;
            allCountries->countries = (countryData*) realloc(allCountries->countries, sizeof(countryData)*size);

            if(!allocation_check(allCountries->countries, err))
            {
                return;
            }
        }
    } while (!feof(countriesFile));

    allCountries->numOfCountries = index - 1;
    fclose(countriesFile);
}

static int read_next_day(FILE* fp, oneDay* oneDay)
{
    char line[100];

    if (feof(fp) == 1)
    {
        return 0;
    }

    read_next_field(fp, line, oneDay->confirmed);
    read_next_field(fp, line, oneDay->deaths);
    read_next_field(fp, line, oneDay->recovered);
    read_next_field(fp, line, oneDay->active);
    read_next_field(fp, line, oneDay->date);  

    return 1;  
}

static int read_next_field(FILE* fp, char* line, char* field)
{
    if (fgets(line, 100, fp) != NULL)
    {
        char* token;
        token = strtok(line, ":");
        token = strtok(NULL, "\r\n");
        strcpy(field, token);

        return 1;
    }

    return 0;
}

void free_country_data(countryData* country)
{
    free(country->data);  
}

void free_all_countries_data(allCountriesData* allCountries)
{
    int i, size = allCountries->numOfCountries;

    for(i = 0; i < size; i++)
    {
        free_country_data(&(allCountries->countries[i]));
    }
    
    free(allCountries->countries);
}

static int open_file_check(FILE* fp, eError* err)
{
    if(fp == NULL)
    {
        *err = FILE_OPENING_FAILED_ERR;
        return 0;
    }

    return 1;
}

static int allocation_check(void* pointer, eError* err)
{
    if(pointer == NULL)
    {
        *err = MEMORY_ALLOCATION_FAILED_ERR;
        return 0;
    }

    return 1;
}

char* error_message(eError err)
{
    switch (err)
    {
    case MEMORY_ALLOCATION_FAILED_ERR:
        return "Memory allocation failed\n";
    case FILE_OPENING_FAILED_ERR:
        return "File opening failed\n";
    case NO_DATE_FOUND:
        return "The requested date was not found\n";
    default:
    {
        return "Other error\n";
    }
    }
}

char* get_key(oneDay* oneDay, Key key)
{
    switch (key)
    {
    case Confirmed:
        return oneDay->confirmed;
    case Deaths:
        return oneDay->deaths;
    case Recovered:
        return oneDay->recovered;
    case Active:
        return oneDay->active;
    case Date:
        return oneDay->date;
    default:
        return "Invalid Key";
    }
}