#include "corona_api_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int NUMBER_OF_SPACES = 100;

void print_graph(char* fileName_country, Key key);
void print_spaces(int numOfSpaces);

int main(int argc, char* argv[])
{
	char country[50], key[10];

	if(validate_input(argc, argv, country, "--country") == 0 || validate_input(argc, argv, key, "--key") == 0)
	{
		printf("Invalid input, please try again\n");
		exit(1);
	}

	print_graph(country, valid_key(key));
	return 0;
}

void print_graph(char* fileName_country, Key key)
{
	eError error;
	countryData country;
	
	load_file_by_country(fileName_country, &country, &error);

	if (error != 0)
	{
		char* errorMsg = error_message(error);
		printf("%s", errorMsg);
		exit(1);
	}

	int i, keyValue, numOfSpaces = 0, maxValue = 0, numOfDays = country.numOfDays;

	for ( i = 0; i < numOfDays; i++)
	{ // Get the maximun value of the given key
		keyValue = atoi(get_key(&(country.data[i]) ,key));

		if (maxValue < keyValue)
		{
			maxValue = keyValue;
		}
	}

	for ( i = 0; i < numOfDays; i++)
	{
		keyValue = atoi(get_key(&(country.data[i]) ,key));
		numOfSpaces = (keyValue * NUMBER_OF_SPACES) / maxValue;

		print_spaces(numOfSpaces);
		printf("%d\n", keyValue);
	}

	free_country_data(&country);
}

void print_spaces(int numOfSpaces)
{
	int i;

	for (i = 0; i < numOfSpaces; i++)
	{
		printf(" ");
	}
}