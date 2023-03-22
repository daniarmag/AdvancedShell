#include <stdio.h>#include <stdlib.h>#include <string.h>#include <fcntl.h>#include <errno.h>#include <sys/types.h>#include <unistd.h>#define SIZE 128void errorMsg(char* str);/*This command creates a file for each store, and adds the store to the camp_partic file.*/int main(int argc, char* argv[]){	int camp, rbytes, wbytes, file, len = 0;	char buffer[SIZE] = { 0 }, name[30] = { 0 }, nameFolder[50] = { 0 }, options[][25] = {"Enjoyed", "Shop Now and have fun", "Have Fun", "Other"}, text[SIZE], *lastString;	if (argc != 3)		errorMsg("Incorrect amount of args/parms");	//Creating the file name.	strcat(name, "Black_Friday/");	strcat(name, argv[1]);	strcat(name, ".txt");	//Creating the file.	if((file = open(name, O_WRONLY | O_CREAT, 0664)) == -1)		errorMsg("open");	//Printing the name and the discount into a variable which is immediately after writed to the file.	sprintf(text, "\t\t%s Sale\n\t\t%s%% off\n", argv[1], argv[2]);	if ((wbytes = write(file, text, strlen(text))) == -1)		errorMsg("write");	printf("Insert item and item cost:\n");	while (strcmp(buffer,"Stop\n"))	{		//Reseting buffer after every iteration.		memset(buffer, 0, sizeof(buffer));		//User input.		if ((rbytes = read(0, &buffer, sizeof(buffer))) == -1)			errorMsg("Read");		if (strcmp(buffer,"Stop\n"))		{				//Finding the last string(price) to seperate it and place it after the dots.			lastString = strrchr(buffer, ' ');			len = rbytes - strlen(lastString);			//Writing the name of the product to the file.			if ((wbytes = write(file, &buffer, len)) == -1)				errorMsg("write");			//Starting the amount of dots as a default of 30, but substracting the length of the price and product name strings.			if ((wbytes = write(file, ".............................................", 45 - len - strlen(lastString))) == -1)				errorMsg("write");			write(file, " ", 1);			//Writing the price, + 1 to move the pointer and skip the space that strrchr returns with the string.			if ((wbytes = write(file, lastString + 1, strlen(lastString + 1) - 1)) == -1)				errorMsg("write");			write(file, "NIS\n", 4);		}	}	//Using memset to reset the string.	memset(buffer, 0, sizeof(buffer));	printf("What is your choice?\n1.%s\n2.%s\n3.%s\n4.%s\n", options[0], options[1], options[2], options[3]);	if ((rbytes = read(0, &buffer, sizeof(buffer))) == -1)			errorMsg("Read");	write(file, "\t\t", strlen("\t\t"));	//A condition specifically for option 4.	if (strcmp (buffer, "4\n") == 0)		{		printf("Insert your word:\n");		memset(buffer, 0, sizeof(buffer));		if ((rbytes = read(0, &buffer, sizeof(buffer))) == -1)			errorMsg("Read");		if ((wbytes = write(file, &buffer, strlen(buffer))) == -1)				errorMsg("write");	}	else	{		//Using atoi to convert the input to an integer and then write the suitable option.		if ((wbytes = write(file, options[atoi(buffer) - 1], strlen(options[atoi(buffer) - 1]))) == -1)				errorMsg("write");	}	//Creating the folder name and the folder itself.	strcat(nameFolder, "Black_Friday/");	strcat(nameFolder, argv[1]);	strcat(nameFolder, "_Order");	mkdir(nameFolder, 0777);	printf("Successfully created // %s.txt created , %s_Order dir created\n", argv[1], argv[1]);	//Opening camp_partic file and updating it.	if ((camp = open("Black_Friday/camp_partic.txt", O_RDWR)) == -1)		errorMsg("Open");	//Moving the file pointer to the EOF.	lseek(camp, 0, SEEK_END);	//Adding the store to camp_partic file.	if ((wbytes = write(camp, argv[1], strlen(argv[1]))) == -1)		errorMsg("write");	write(camp, "\n", 1);		close(camp);	close(file);	return 0;}/*This function will be called incase there's an error and the program needs to be terminated.*/void errorMsg(char* str){	perror(str);	exit(1);}