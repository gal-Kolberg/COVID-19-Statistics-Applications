# COVID-19-Statistics-Applications

REST API: https://documenter.getpostman.com/view/10808728/SzS8rjbc?version=latest

3 C programs that read the data and perform the following:
1) Print all countries specific data according to: 
  i. Date 
  ii. Key (Confirmed, Death, Recovered, active)
  
2) Print a “graph” according to: 
  i. country name 
  ii. Key (Confirmed, Death, Recovered, active)

3) Export data by country to CSV

A shared library that provides functionalities like load_db, load_country, iterate_by_key, get_next_element, etc... 
this library is compiled as a separate .so and used by all first 3 C programs

# Notes
1) Exercise 3 creates file in the following format: <country>_csv

2) All 3 of the programs takes parameters in the following format: 
    1. --date YYYY-MM-DD --key <key> (or switch between these)
    2. --country <country> --key <key> (or switch between these)
    * There is a global variable 'NUMBER_OF_SPACES', you can change it to what ever fit best to your screen
    3. --country <country>

Do the following actions:
a. unzip "Exersice1" to an empty directory
b. run through the bash terminal: chmod +x script
c. go to the directory from above and run through the bash terminal (it will take a few minutes): ./script
d. when all the file will be ready (you will get a message about it) run through the bash terminal: export LD_LIBRARY_PATH=`pwd`
e. run through the bash terminal: make
f. run through the bash terminal the executable programs with the formated parameters, for example: 
	./linuxq1.out --date 2020-04-25 --key Active
	./linuxq2.out --country india --key Deaths
	./linuxq3.out --country india
g. run through the bash terminal: make clean
