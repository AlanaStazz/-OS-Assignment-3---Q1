//Threaded Stats Calculator
//Alana Staszczyszyn & Elijah Tavenor
//OS Design - Assignment 3 Pt 1

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>


//Function Declarations
void inputCheck(int n, char **input);
int calc_min(void *input_ints);
int calc_max(void *input_ints);
int calc_avg(void *input_ints);


int main(int argc, char *argv[]){

	//Variables
	int x, y;
	int numOfInts = (argc - 1);
	int argArr[numOfInts];
	void *min;
	void *max;
	void *avg;

	//Input sanitization
	inputCheck(argc, argv);

	//Populate array with cmd line args
	for(x = 1; x <=numOfInts; x++){
		argArr[x - 1] = atoi(argv[x]);
	}
	

	//Make threads & check for errors
	//Quits because calculating on wrong block of memory could return wrong info dangerously
	pthread_t thr[3];


	y = pthread_create(&thr[0], NULL, (void *)calc_min, (void *) argArr);

	if (y != 0){

		perror("\n\nFATAL THREAD CREATION ERROR: ");
		exit(1);	
	}


	y = pthread_create(&thr[1], NULL, (void *)calc_max, (void *) argArr);

	if (y != 0){

		perror("\n\nFATAL THREAD CREATION ERROR: ");
		exit(1);	
	}



	y = pthread_create(&thr[2], NULL, (void *)calc_avg, (void *) argArr);

	if (y != 0){

		perror("\n\nFATAL THREAD CREATION ERROR: ");
		exit(1);	
	}



	//Joins & collect function output from threads
	//Quits because main thread outputting values prematurely could lead to dangerous unauthorized memory access
	y = pthread_join(thr[0], &min);

	if (y != 0){

		perror("\n\nFATAL THREAD JOIN ERROR: ");
		exit(1);	
	}

	
	y = pthread_join(thr[1], &max);

	if (y != 0){

		perror("\n\nFATAL THREAD JOIN ERROR: ");
		exit(1);	
	}

	y = pthread_join(thr[2], &avg);

	if (y != 0){

		perror("\n\nFATAL THREAD JOIN ERROR: ");
		exit(1);	
	}


	//Final output	
	printf("\n\n* * * The calculation results are: * * * \n\nMinimum value: %d \nMaximum Value: %d \nAverage Value: %d\n\n", (uintptr_t)min, (uintptr_t)max, (uintptr_t)avg);

	return(0);

}

//Input Validation & Sanitization
void inputCheck(int n, char **input){

	//If too few arguments, exit
	if (n <= 1){
	fprintf(stderr,"Format error; usage: statCalc <int1> <int2> . . . <intn>");

	exit(1);

	}

	//Make sure every argument is actually an int
	int i, j;

	for (i=1; i < n; i++){

		j=0;

		while(input[i][j] != '\0'){

			if(!isdigit(input[i][j])){

				fprintf(stderr, "Format error: all input must be integers. Exiting...\n\n");
				exit(1);
			}

			j++;

			//Also make sure no overflow
			if(j > 9){

				fprintf(stderr, "Overflow error: Please only input ints less less than 10 digits. Exiting...\n\n");
				exit(1);
			}
		}

	}

}

//Calculate the min
int calc_min(void *input_ints){

	int i;
	int min = INT_MAX;
	int *ptr = (int *)input_ints;

	//Iterate through input array for min. value
	while(*ptr != '\0'){
		
		if(*ptr < min){
		min = *ptr;
	}

		ptr++;
	}

	return min;

}

//Calculate the max
int calc_max(void *input_ints){

	int i;
	int max = INT_MIN;
	int *ptr = (int *)input_ints;

	//Iterate through input array for max. value
	while(*ptr != '\0'){
		
		if(*ptr > max){
		max = *ptr;
	}

		ptr++;
	}

	return max;

}

//Calculate the avg
int calc_avg(void *input_ints){

	int i;
	int sum = 0;
	int n = 0;
	int *ptr = (int *)input_ints;

	//Iterate through input array for sum, then find avg
	while(*ptr != '\0'){
		
		sum += *ptr;
		n++;

		ptr++;
	}

	return (sum/n);
}
