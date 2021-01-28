#pragma once

#define COUNTRIES_DIR "Countries_Dir/"

typedef struct
{
    char confirmed[20];
    char deaths[20];
    char recovered[20];
    char active[20];
    char date[30];
} oneDay;

typedef struct
{
    char name[50];
    oneDay* data;
    int numOfDays;
} countryData;

typedef struct
{
    countryData* countries;
    int numOfCountries;
} allCountriesData;

typedef enum
{
    NO_ERR = 0,
    MEMORY_ALLOCATION_FAILED_ERR,
    FILE_OPENING_FAILED_ERR,
    NO_DATE_FOUND
} eError;

typedef enum 
{
	Confirmed,
	Deaths,
	Recovered,
	Active,
    Date
} Key;

void load_file_by_country(char* fileName, countryData* country, eError* err);
void load_all_countries(allCountriesData* allCountries, eError* err);
void free_country_data(countryData* country);
void free_all_countries_data(allCountriesData* allCountries);

Key valid_key(char* key);
int validate_input(int size, char* input[], char* parameter, char* toCompare);

char* get_key(oneDay* oneDay, Key key);
char* error_message(eError err);

//#endif