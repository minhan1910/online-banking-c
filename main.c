#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct user {
	char phone[50];
	char ac[50];
	char password[50];
	double balance;
};

FILE* open(const char* filename, const char* ext) {
	char fullFilename[strlen(filename) + strlen(ext)];
	strcpy(fullFilename, filename);
	strcat(fullFilename, ext);
	
	return fopen(fullFilename, "w");
}

int close(FILE** file) {
	return fclose(*file);
}

void testFile() {
	const char* fileName = "MinhAn";
	const char* ext = ".txt";
	
	FILE* f = open(fileName, ext);
	
	if (close(&f) == -1) {
		printf("File can not close!");
	} else {
		printf("File is closed");
	}
}

void allocater(int **ptrAllocater) {
	*ptrAllocater = (int *)malloc(sizeof(int));
	if (ptrAllocater == NULL) {
		perror("in allocater() memory allocation error");
		exit(EXIT_FAILURE);
	}
}

void testAllocater() {
	
	int* ptrInt = NULL;
	allocater(&ptrInt);
	
	if (ptrInt == NULL) {
		printf("memory not allocated\n");
        exit(EXIT_FAILURE);
	}
	
    printf("memory allocated and assigned to ptrMain");
    printf(" from trueAllocater\n");
	
	free(ptrInt);
	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
	struct user user, user1;
	FILE *fp;
	char filename[50], 
		 phone[50],
		 pword[50];
	int opt, choice;
	double amount;
	char cont = 'y';
	
	printf("\nWhat do you want to do?");
	printf("\n\n1. Register an account");
	printf("\n2. Login to an account");	
	
	printf("\n\nYour choice:\t");
	scanf("%d", &opt);
	
	if (opt == 1) {
		system("cls");
		printf("Enter your account no:\t");
		scanf("%s", user.ac);
		printf("Enter your phone no:\t");
		scanf("%s", user.phone);
		printf("Enter your new password:\t");
		scanf("%s", user.password);
		user.balance = 0;		
		
		strcpy(filename, user.phone);
		strcat(filename, ".dat");
		fp = fopen(filename, "w");
		fwrite(&user, sizeof(struct user), 1, fp);	
		if (fwrite != 0) {
			printf("\n\nAccount successfully registered");
		} else {
			printf("\\n\nSomething went wrong please try again!");
		}
		fclose(fp);
	}	
	
	if (opt == 2) {
		system("cls");
		printf("\nPhone number:\t");
		scanf("%s", &phone);
		printf("\nPassword:\t");
		scanf("%s", &pword);
		strcpy(filename, phone);
		fp = fopen(strcat(filename, ".dat"), "r");
		
		if (fp == NULL) {
			printf("\nAccount number not registered");
			return EXIT_FAILURE;
		} 
		
		fread(&user, sizeof(struct user), 1, fp);
		fclose(fp);
		
		if (!strcmp(pword, user.password)) {
			while (cont == 'y') {
				system("cls");
				printf("\n\tWelcome %s", user.phone);
				printf("\nPress 1 for balance inquiry");
				printf("\nPress 2 for depositing fund");
				printf("\nPress 3 for cash withdrawal");
				printf("\nPress 4 for online transfer");
				printf("\nPress 5 for changing password\n\n");
				scanf("%d",&choice);
				
				switch(choice) {
					case 1:
						printf("\nYour current balance is Rs.%.2f", user.balance);                        
						break;
					
					case 2:
						printf("\nEnter the amount:\t");
                        scanf("%lf",&amount);
                        user.balance += amount;
                        printf("%.2f", user.balance);
						printf("%s", filename);
                        
                        fp = fopen(filename, "w");
                        fwrite(&user, sizeof(struct user), 1, fp);
                        fclose(fp);
                        
						if (fwrite != NULL) {
                        	printf("\nSuccessfully deposited!");
						}
						
						break;
					
					case 3:
						printf("\nEnter the amount:\t");
						scanf("%lf", &amount);
						if (amount > user.balance) {
							printf("You can not withdraw since the current balance is less than the number of amounts you required!");
						} else {
							user.balance -= amount;
							fp = fopen(filename, "w");
							fwrite(&user, sizeof(struct user), 1, fp);
							fclose(fp);
							printf("You have withdrawn successfully!");	
						} 
						break;
						
					case 4:
						printf("\nPlease enter the phone number to transfer the balance:\t");
                        scanf("%s",phone);
                	                  
						strcpy(filename, phone);
                        strcat(filename, ".dat");
                        fp = fopen(filename, "r");
                        
                        if (fp == NULL) {
                        	printf("\nAccount number not registered");
                        	break;
						} else {
							fread(&user1, sizeof(struct user), 1, fp);
							fclose(fp);
						} 
				
				        printf("\nPlease enter the amount to transfer:\t");
                        scanf("%lf",&amount);      
						
						if (amount > user.balance) {
							printf("You can not tranfer since the current balance is less than the number of amounts you required!");
							break;
						}
						
						fp = fopen(filename, "w");
						user1.balance += amount;
						fwrite(&user1, sizeof(struct user), 1, fp);
						fclose(fp);
						
						if (fwrite != NULL) {
							printf("\nYou have succesfully transfered Rs.%.2f to %s",amount,phone);
							strcpy(filename, user.phone);
							fp = fopen(strcat(filename, ".dat"), "w");
							user.balance -= amount;
							fwrite(&user, sizeof(struct user), 1, fp);
							fclose(fp);	   
						}
                        
						break;
						
					case 5:
						printf("\nPlease enter your new password:\t");
                        scanf("%s",pword);
                        fp = fopen(filename, "w");
                        strcpy(user.password, pword);
                        fwrite(&user, sizeof(struct user), 1, fp);
						fclose(fp);
						if(fwrite != NULL) {						
                        	printf("\nPassword succesfully changed");
                        }
						break;
											
					default:
						printf("\nInvalid option");
						break;
				}
				
				printf("\n\nDo you want to continue?[y/n]:\t");
				scanf("%s",&cont);
			}
		
		} else {
			printf("\nInvalid password");
		}
	}
	
	return EXIT_SUCCESS;
}




