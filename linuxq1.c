#include "corona_api_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 30
#define NUM_OF_KEYS 5
#define SIZE_OF_STRING 80

oneDay* FindCountryInfoByDate(countryData allDatesInfo, char* dateToFind);
void PrintAllCountriesByKey(allCountriesData allCountries, char* dateToFind, char* strKey);

int main(int argc, char* argv[])
{
	char dateToFind[12], strKey[10];

	if(validate_input(argc, argv, dateToFind, "--date") == 0 || validate_input(argc, argv, strKey, "--key") == 0)
	{
		printf("Invalid input, please try again\n");
		exit(1);
	}

	allCountriesData allCountries;
	eError err;

	load_all_countries(&allCountries, &err);

	if (err != NO_ERR)
	{
		printf("%s", error_message(err));
		exit(1);
	}

	PrintAllCountriesByKey(allCountries, dateToFind, strKey);

	free_all_countries_data(&allCountries);
    return 0;
}

void PrintAllCountriesByKey(allCountriesData allCountries, char* dateToFind, char* strKey)
{
	oneDay* wantedDateInfo;
	int i, size = allCountries.numOfCountries;

	for (i = 0; i < size; i++)
	{
		wantedDateInfo = FindCountryInfoByDate(allCountries.countries[i], dateToFind);

		if(wantedDateInfo != NULL)
		{
			Key key = valid_key(strKey);
			printf("%s: %s\n", allCountries.countries[i].name, get_key(wantedDateInfo, key));
		}
	}
}

oneDay* FindCountryInfoByDate(countryData allDatesInfo, char * dateToFind)
{
	char* currentDate;

	for (int i = 0; i < allDatesInfo.numOfDays; i++)
	{
		currentDate = strtok(allDatesInfo.data[i].date, "T");
		
		if (strcmp(currentDate, dateToFind) == 0)
		{
			return &allDatesInfo.data[i];
		}
	}

	printf("%s: %s - %s\n",allDatesInfo.name, error_message(NO_DATE_FOUND), dateToFind);
	return NULL;
}