#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *file;

int main(int argc, char **argv) {
	if(argc < 2){
		printf("Please input file as an argument as a part of the opening of this program\n");
		exit(0);
	}
	//intialize file pointer
	printf("You are opening %s\n", argv[1]);
	file = fopen(argv[1], "a");//check file
	if (file == NULL){
		printf("Failed to File\n");//fail to file
		exit(0);
	}
	
	//user input
	char input[1000];
	printf("input text\n");
	fgets(input, 1000, stdin);
	fprintf(file, input);
	fclose(file);
	
	
	//getting array size
	int size;
	file = fopen(argv[1], "r");
	if (file == NULL){
		printf("Failed to File\n");//fail to file
		exit(0);
	}
	char *store = malloc(1000);
	int columCount = 10;
	int rowCount = 0;
	int hold = 0;
	while(getline(&store, &size, file) != -1){
		//printf(store);
		if(strlen(store) > columCount)
			columCount = strlen(store);
		rowCount++;
		}
		//printf("row:%i colum:%i\n", rowCount, columCount);
		rowCount++;
		
		//create array
	char **fileArray = (char**)calloc(rowCount, sizeof(char*));
	for (int i=0;i<rowCount;i++)
    fileArray[i] = (char*)calloc(columCount, sizeof(char));
	
	//store file in array
	rewind(file);
	for(int i=0;i<rowCount;i++)
		fgets(fileArray[i], columCount, file);
	
	
	//print array
	printf("Printing %s\n", argv[1]);
	for(int i=0;i<rowCount;i++){
		printf("%s", fileArray[i]);
	}
	
	
	fclose(file);//close file
	
	return 0;
}