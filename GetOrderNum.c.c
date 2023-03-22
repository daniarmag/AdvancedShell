#include <stdio.h>#include <stdlib.h>#include <string.h>#include <fcntl.h>#include <errno.h>#include <sys/types.h>#include <unistd.h>#include <dirent.h> #define SIZE 256void errorMsg(char* str);/*This command writes the amount of orders in the specified store.*/int main(int argc, char* argv[]){	int file, len = 0, cnt = 0;	char name[30] = { 0 };	//Using dirent.h inroder to use its commands and count the amount of files.	DIR *d;    struct dirent *dir;	if (argc != 2)		errorMsg("Incorrect amount of args/parms");	//Creating the file name.	strcat(name, "Black_Friday/");	strcat(name, argv[1]);	strcat(name,"_Order");	//Opening the targeted file in order to check that the store exists in the campaign.	if((file = open(name, O_RDONLY)) == -1)	{			len = strlen("Company Not Found!\n");		write(0, "Company Not Found!\n", len);		exit(1);	}	d = opendir(name); 	//Iterating over the files in the folder and counting them. 	while (dir = readdir(d))	{		//ignoring '.' (link for the current folder) and '..' (link for the parent folder).		if (dir->d_name[0] != '.') 			cnt++;	}	printf("%s ---- %d Orders\n", argv[1], cnt);	close(file);    closedir(d);	return 0;}/*This function will be called in case there's an error and the program needs to be terminated.*/void errorMsg(char* str){	perror(str);	exit(1);}