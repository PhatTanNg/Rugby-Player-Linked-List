#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <stdbool.h>

//struct for login detail
struct Login {
	char username[20];
	char password[20];
};


//struct for the list of players
typedef struct node
{
	int irfuNum;
	int age;
	char firstName[30];
	char secondName[30];
	int height;
	int weight;
	char club[30];
	char email[30];
	char position[30];
	char missTackles[50];
	char meterInGame[50];
	struct node* NEXT;
}nodeT;


//function of the program
void read_login_file(char* file_path, struct Login logins[], int* num_logins); 
int authenticate(char* username, char* password, struct Login logins[], int num_logins);
void initializeFromFile(nodeT** top);
void addPlayer(nodeT** top);
void displayAll(nodeT* top);
void playerDisplay(nodeT* top);
void updatePlayer(nodeT* top);
void deletePlayer(nodeT** top);
void generateStat(nodeT* top);
void printFile(nodeT* top);
void orderOfHeight(nodeT** top);

void main()
{
	//login session
	//login details: 121212 aaaaaa
	//				 232323 bbbbbb
	//				 343434 cccccc

	struct Login logins[3];
	int num_logins;
	char username[20];
	char password[20];

	// Read login records from file
	read_login_file("loginDetail.txt", logins, &num_logins);

	// Get user input for username
	printf("Enter username (121212):");
	scanf("%s", username);

	// Get password without displaying it on the screen
	printf("Enter password (aaaaaa): ");
	int i = 0;
	while (i < sizeof(password) - 1) {
		char ch = getch();
		if (ch == '\r') {
			break;
		}
		else if (ch == '\b') {
			if (i > 0) {
				printf("\b \b");
				i--;
			}
		}
		else {
			password[i++] = ch;
			printf("*");
		}
	}
	password[i] = '\0';  // Null-terminate the password

	// Authenticate user
	if (authenticate(username, password, logins, num_logins)) {
		printf("\nLogin successful!\n");
		nodeT* headPtr = NULL;
		nodeT* temp;
		nodeT* prev_temp;
		nodeT* newNode;
		int choice;

		initializeFromFile(&headPtr);

		printf("Please enter 1 to add a player:\n");
		printf("Please enter 2 to display all player:\n");
		printf("Please enter 3 to display a player's details:\n");
		printf("Please enter 4 to update player's statistic:\n");
		printf("Please enter 5 to delete a player:\n");
		printf("Please enter 6 to generate statistic (a-h) based on a range of player weights:\n");
		printf("Please enter 7 to print all player details into a report file:\n");
		printf("Please enter 8 to list all the players in order of height:\n");
		printf("Please enter -1 to exit:\n");
		scanf("%d", &choice);

		while (choice != -1)
		{
			if (choice == 1)
			{
				addPlayer(&headPtr);
			}
			else if (choice == 2)
			{
				displayAll(headPtr);
			}

			else if (choice == 3)
			{
				playerDisplay(headPtr);
			}
			else if (choice == 4)
			{
				updatePlayer(headPtr);
			}
			else if (choice == 5)
			{
				deletePlayer(&headPtr);
			}
			else if (choice == 6)
			{
				generateStat(headPtr);
			}
			else if (choice == 7)
			{
				printFile(headPtr);
			}
			else if (choice == 8)
			{
				orderOfHeight(&headPtr);
			}
			printf("Please enter 1 to add a player:\n");
			printf("Please enter 2 to display all player:\n");
			printf("Please enter 3 to display a player's details:\n");
			printf("Please enter 4 to update player's statistic:\n");
			printf("Please enter 5 to delete a player:\n");
			printf("Please enter 6 to generate statistic (a-h) based on a range of player weights:\n");
			printf("Please enter 7 to print all player details into a report file:\n");
			printf("Please enter 8 to list all the players in order of height:\n");
			printf("Please enter -1 to exit:\n");
			scanf("%d", &choice);
		}
	}
	//wrong login detail
	else {
		printf("\nInvalid username or password.\n");
	}

	
}

//read login file and put in a list
void read_login_file(char* file_path, struct Login logins[], int* num_logins) {
	FILE* file = fopen(file_path, "r");
	if (file == NULL) {
		printf("Error: Unable to open file.\n");
		exit(EXIT_FAILURE);
	}

	*num_logins = 0;
	while (fscanf(file, "%s %s\n", logins[*num_logins].username, logins[*num_logins].password) != EOF) {
		(*num_logins)++;
	}

	fclose(file);
}
//check if login details are correct or not
int authenticate(char* username, char* password, struct Login logins[], int num_logins) {
	for (int i = 0; i < num_logins; i++) {
		if (strcmp(logins[i].username, username) == 0 && strcmp(logins[i].password, password) == 0) {
			return true;
		}
	}
	return false;
}
//read the initalize file
void initializeFromFile(nodeT** top) {
	FILE* file = fopen("Rugby.txt", "r");
	if (file == NULL) {
		printf("There is nothing in the file\n");
		return;
	}

	
	while (!feof(file)) {
		nodeT* temp = (nodeT*)malloc(sizeof(nodeT));
		fscanf(file, "The player's IRFU Number  is %d\n", &temp->irfuNum);
		fscanf(file, "The player's first name is %s\n", temp->firstName);
		fscanf(file, "The player's second name is %s\n", temp->secondName);
		fscanf(file, "The player's age is %d\n", &temp->age);
		fscanf(file, "The player's height is %d\n", &temp->height);
		fscanf(file, "The player's weight is %d\n", &temp->weight);
		fscanf(file, "The player's club is %s\n", temp->club);
		fscanf(file, "The player's email is %s\n", temp->email);
		fscanf(file, "The player's position is %s\n", temp->position);
		fscanf(file, "The player's missed tackled is %49[^\n]\n", temp->missTackles);
		fscanf(file, "The player's metres made is %49[^\n]\n", temp->meterInGame);

		temp->NEXT = *top;
		*top = temp;
	}

	fclose(file);
	printf("Passed the old player list into the linked list\n");
}


//add player to the start of the list
void addPlayer(nodeT** top) {
	nodeT* temp;
	temp = (nodeT*)malloc(sizeof(nodeT));

	int option;
	printf("Please enter the player IRFU number:\n");
	scanf("%d", &temp->irfuNum);

	//check if IRFU is different or not
	nodeT* current = *top;
	while (current != NULL) {
		if (current->irfuNum == temp->irfuNum) {
			printf("IRFU number already exists. Please enter a different IRFU number.\n");
			scanf("%d", &temp->irfuNum);
		
			current = *top;
		}
		else {
			current = current->NEXT;
		}
	}
	printf("Please enter player's first name:\n");
	scanf("%s", temp->firstName);
	printf("Please enter player's second name:\n");
	scanf("%s", temp->secondName);
	printf("Please enter player's age:\n");
	scanf("%d", &temp->age);
	printf("Please enter player's height (in cm):\n");
	scanf("%d", &temp->height);
	printf("Please enter player's weight (in kg):\n");
	scanf("%d", &temp->weight);
	printf("Please enter player's club:\n");
	scanf("%s", temp->club);
	printf("Please enter player's email:\n");
	scanf("%s", temp->email);
	//email has to contain '@' and '.com'
	while (strstr(temp->email, "@") == NULL || strstr(temp->email, ".") == NULL || strstr(temp->email, ".com") == NULL)
	{
		printf("Valid email should contain '@' ,'.com'\n");
		printf("Please enter player's email again:\n");
		scanf("%s", temp->email);
	}
	do
	{
		printf("Please enter player's position:\n");
		printf("\t\t 1 for Prop\n");
		printf("\t\t 2 for Hooker\n");
		printf("\t\t 3 for Second Row\n");
		printf("\t\t 4 for Back Row\n");
		printf("\t\t 5 for Half Back\n");
		printf("\t\t 6 for Centres\n");
		printf("\t\t 7 for Winders/Full Back\n");
		scanf("%d", &option);
		if(option==1)
			strcpy(temp->position, "Prop");
		else if(option ==2)
			strcpy(temp->position, "Hooker");
		else if (option==3)
			strcpy(temp->position, "Second Row");
		else if(option ==4)
			strcpy(temp->position, "Back Row");
		else if (option==5)
			strcpy(temp->position, "Half Back");
		else if(option==6)
			strcpy(temp->position, "Centres");
		else if(option==7)
			strcpy(temp->position, "Wingers/Full Back");
		else
			printf("Wrong input\n");
	} while (option >= 8||option<=0);
	do
	{
		printf("Please enter tackles player missed per match:\n");
		printf("\t\t1 for Never\n");
		printf("\t\t2 for Less than three times per match\n");
		printf("\t\t3 for Less than five times per match\n");
		printf("\t\t4 for More than five times per match\n");
		scanf("%d", &option);
		if (option == 1)
			strcpy(temp->missTackles, "Never");
		else if (option == 2)
			strcpy(temp->missTackles, "Less than three times per match");
		else if (option == 3)
			strcpy(temp->missTackles, "Less than five times per match");
		else if (option == 4)
			strcpy(temp->missTackles, "More than five time per match");
		else
			printf("Wrong input\n");
	} while (option >=5 || option <= 0);
	do {
		printf("Please enter metres player made per match:\n");
		printf("\t\t1 for None\n");
		printf("\t\t2 for Less than 10 metres\n");
		printf("\t\t3 for Less than 20 metres\n");
		printf("\t\t4 for More than 20 metres\n");
		scanf("%d", &option);
		if (option == 1)
			strcpy(temp->meterInGame, "None");
		else if (option == 2)
			strcpy(temp->meterInGame, "Less than 10 metres");
		else if (option == 3)
			strcpy(temp->meterInGame, "Less than 20 metres");
		else if (option == 4)
			strcpy(temp->meterInGame, "More than 20 metres");
		else
			printf("Wrong input\n");
	} while (option >= 5 || option <= 0);
	temp->NEXT = *top;
	*top = temp;
}

//display all players
void displayAll(nodeT* top) {

	nodeT* temp = top;
	int count = 0;
	int found = 0;
	while (temp != NULL)
	{
		found = 1;
		count++;
		printf("The player's IRFU Number at position %d is %d\n", count,temp->irfuNum);
		printf("The player's first name at position %d is %s\n", count, temp->firstName);
		printf("The player's second name at position %d is %s\n", count, temp->secondName);
		printf("The player's age at position %d is %d\n", count, temp->age);
		printf("The player's height at position %d is %d\n", count, temp->height);
		printf("The player's weight at position %d is %d\n", count, temp->weight);
		printf("The player's club at position %d is %s\n", count, temp->club);
		printf("The player's email at position %d is %s\n", count, temp->email);
		printf("The player's position at position %d is %s\n", count, temp->position);
		printf("The player's missed tackled at position %d is %s\n", count, temp->missTackles);
		printf("The player's metres made at position %d is %s\n\n", count, temp->meterInGame);
		temp = temp->NEXT;
	}
	if (found == 0)
	{
		printf("There is no player in this list\n");
	}

}
//search for player
void playerDisplay(nodeT* top) {
	nodeT* temp = top;
	char input[30];
	fflush(stdin);
	char IRFU[30];
	char fullName[30];
	int found = 0;
	//getchar and fget to get a long string like player's full name
	printf("Please input player's IRFU or player's full name:\n");
	getchar();
	fgets(input, sizeof(input), stdin);
	while (temp != NULL)
	{
		//passing IRFU to a string for comparing
		sprintf(IRFU, "%d", temp->irfuNum);
		//condition if user input is contained first name and last name OR user input same as IRFU number
		if (strstr(input,temp->firstName) !=NULL && strstr(input,temp->secondName)!=NULL || strstr(input,IRFU)!=NULL)
		{
			found = 1;
			printf("The player's IRFU Number  is %d\n",temp->irfuNum);
			printf("The player's first name  is %s\n", temp->firstName);
			printf("The player's second name  is %s\n",temp->secondName);
			printf("The player's age is %d\n", temp->age);
			printf("The player's height is %d\n", temp->height);
			printf("The player's weight is %d\n",  temp->weight);
			printf("The player's club is %s\n", temp->club);
			printf("The player's email is %s\n", temp->email);
			printf("The player's position is %s\n",temp->position);
			printf("The player's missed tackled is %s\n", temp->missTackles);
			printf("The player's metres made is %s\n\n", temp->meterInGame);
		}
		temp = temp->NEXT;
	}
	if (found == 0)
	{
		printf("Can not find the player in this list\n");
	}

}
//update user info
void updatePlayer(nodeT* top)
{
	nodeT* temp = top;
	int option;
	char input[30];
	fflush(stdin);
	char IRFU[30];
	char fullName[30];
	int found = 0;
	//getchar and fget to get a long string like player's full name
	printf("Please input player's IRFU or player's full name:\n");
	getchar();
	fgets(input, sizeof(input), stdin);
	while (temp != NULL)
	{
		//passing IRFU to a string for comparing
		sprintf(IRFU, "%d", temp->irfuNum);
		//condition if user input is contained first name and last name OR user input same as IRFU number
		if (strstr(input, temp->firstName) != NULL && strstr(input, temp->secondName) != NULL || strstr(input, IRFU) != NULL)
		{
			found = 1;
			do
			{
				printf("Please enter player's position:\n");
				printf("\t\t 1 for Prop\n");
				printf("\t\t 2 for Hooker\n");
				printf("\t\t 3 for Second Row\n");
				printf("\t\t 4 for Back Row\n");
				printf("\t\t 5 for Half Back\n");
				printf("\t\t 6 for Centres\n");
				printf("\t\t 7 for Winders/Full Back\n");
				scanf("%d", &option);
				if (option == 1)
					strcpy(temp->position, "Prop");
				else if (option == 2)
					strcpy(temp->position, "Hooker");
				else if (option == 3)
					strcpy(temp->position, "Second Row");
				else if (option == 4)
					strcpy(temp->position, "Back Row");
				else if (option == 5)
					strcpy(temp->position, "Half Back");
				else if (option == 6)
					strcpy(temp->position, "Centres");
				else if (option == 7)
					strcpy(temp->position, "Wingers/Full Back");
			} while (option >= 8 || option <= 0);
			do
			{
				printf("Please enter tackles player missed per match:\n");
				printf("\t\t1 for Never\n");
				printf("\t\t2 for Less than three times per match\n");
				printf("\t\t3 for Less than five times per match\n");
				printf("\t\t4 for More than five times per match\n");
				scanf("%d", &option);
				if (option == 1)
					strcpy(temp->missTackles, "Never");
				else if (option == 2)
					strcpy(temp->missTackles, "Less than three times per match");
				else if (option == 3)
					strcpy(temp->missTackles, "Less than five times per match");
				else if (option == 4)
					strcpy(temp->missTackles, "More than five time per match");

			} while (option >= 5 || option <= 0);
			do {
				printf("Please enter metres player made per match:\n");
				printf("\t\t1 for None\n");
				printf("\t\t2 for Less than 10 metres\n");
				printf("\t\t3 for Less than 20 metres\n");
				printf("\t\t4 for More than 20 metres\n");
				scanf("%d", &option);
				if (option == 1)
					strcpy(temp->meterInGame, "None");
				else if (option == 2)
					strcpy(temp->meterInGame, "Less than 10 metres");
				else if (option == 3)
					strcpy(temp->meterInGame, "Less than 20 metres");
				else if (option == 4)
					strcpy(temp->meterInGame, "More than 20 metres");
			} while (option >= 5 || option <= 0);
			return 0;
		}
	}
	if (found == 0)
	{
		printf("Can not find the player in this list\n");
	}
}
void deletePlayer(nodeT** top)
{
	char input[30];
	//get user input IRFU number OR player's full name
	printf("Please input player's IRFU or player's full name:\n");
	fflush(stdin);
	getchar();
	fgets(input, sizeof(input), stdin);

	nodeT* current = *top;
	nodeT* prev = NULL;

	while (current != NULL)
	{
		char IRFU[30];
		sprintf(IRFU, "%d", current->irfuNum);

		if (strstr(input, current->firstName) != NULL && strstr(input, current->secondName) != NULL || strstr(input, IRFU) != NULL)
		{
			if (prev == NULL) // If the node to be deleted is the first node
				*top = current->NEXT;
			else
				prev->NEXT = current->NEXT;

			free(current);
			printf("Player deleted successfully.\n");
			return; 
		}

		prev = current;
		current = current->NEXT;
	}

	printf("Can not find the player in this list.\n");
}
//generate Statictis
void generateStat(nodeT* top)
{
	nodeT* temp = top;
	char option;
	int count = 0;
	int found = 0;
	int sum = 0;
	float result;
	printf("Enter A-H to chooose statistics to generate:\n");
	printf("\t\t A for percentage of player who miss no tackles\n");
	printf("\t\t B for percentage of player who miss less than 3 tackles per match\n");
	printf("\t\t C for percentage of player who miss less than 5 tackles per match\n");
	printf("\t\t D for percentage of player who miss more than 5 tackles per match\n");
	printf("\t\t E for percentage of player who make no metres in a game\n");
	printf("\t\t F for percentage of player who make less than 10 metres in a game\n");
	printf("\t\t G for percentage of player who make less than 20 metres in a game\n");
	printf("\t\t H for  of player who make more than 20 metres in a game\n");
	scanf(" %c",&option);
	option = toupper(option);//put Upper case for input
	//get the sum of all player from the list
	while (temp != NULL)
	{
		sum++;
		temp = temp->NEXT;
	}
	if (sum == 0) {
		printf("The list is empty.\n");
		return;
	}

	temp = top;  // Reset temp to the beginning of the list

	//in the while loop, we count for number of player that match the chosen option
	while (temp != NULL) {
		switch (option) {
		case 'A':
			if (strcmp(temp->missTackles, "Never") == 0)
				found++;
			break;
		case 'B':
			if (strcmp(temp->missTackles, "Less than three times per match") == 0)
				found++;
			break;
		case 'C':
			if (strcmp(temp->missTackles, "Less than five times per match") == 0)
				found++;
			break;
		case 'D':
			if (strcmp(temp->missTackles, "More than five times per match") == 0)
				found++;
			break;
		case 'E':
			if (strcmp(temp->meterInGame, "None") == 0)
				found++;
			break;
		case 'F':
			if (strcmp(temp->meterInGame, "Less than 10 metres") == 0)
				found++;
			break;
		case 'G':
			if (strcmp(temp->meterInGame, "Less than 20 metres") == 0)
				found++;
			break;
		case 'H':
			if (strcmp(temp->meterInGame, "More than 20 metres") == 0)
				found++;
			break;
		default:
			printf("Wrong inupt\n");
			break;

		}
		temp = temp->NEXT;
	}
	
	// Calculate percentage and print result
	result = (found / (float)sum) * 100;
	printf("The percentage of players matching the criteria is: %.2f%%\n", result);

}
void printFile(nodeT* top) {
	nodeT* temp = top;
	FILE* op;

	op = fopen("Rugby.txt", "w");
	if (op == NULL)
		printf("Sorry the list could not be backed up\n");
	else
	{
		while (temp != NULL)
		{
			fprintf(op, "The player's IRFU Number is %d\n", temp->irfuNum);
			fprintf(op, "The player's first name is %s\n", temp->firstName);
			fprintf(op, "The player's second name is %s\n", temp->secondName);
			fprintf(op, "The player's age is %d\n", temp->age);
			fprintf(op, "The player's height is %d\n", temp->height);
			fprintf(op, "The player's weight is %d\n", temp->weight);
			fprintf(op, "The player's club is %s\n", temp->club);
			fprintf(op, "The player's email is %s\n", temp->email);
			fprintf(op, "The player's position is %s\n", temp->position);
			fprintf(op, "The player's missed tackled is %s\n", temp->missTackles);
			fprintf(op, "The player's metres made is %s\n", temp->meterInGame);
			temp = temp->NEXT;
		}
		fclose(op);
	}


}
void orderOfHeight(nodeT** top) {
	if (*top == NULL || (*top)->NEXT == NULL) {
		printf("There are no players or only one player in the list.\n");
		return;
	}

	nodeT* current;
	int swapped;
	nodeT* temp = NULL;

	do {
		swapped = 0;
		current = *top;

		while (current->NEXT != temp) {
			if (current->height > current->NEXT->height) {
				// Swap entire node structures
				nodeT* tempNode = current->NEXT;
				current->NEXT = tempNode->NEXT;
				tempNode->NEXT = current;
				if (current == *top) {
					*top = tempNode;
				}
				else {
					nodeT* prev = *top;
					while (prev->NEXT != current) {
						prev = prev->NEXT;
					}
					prev->NEXT = tempNode;
				}
				swapped = 1;
			}
			else {
				current = current->NEXT;
			}
		}
		temp = current;
	} while (swapped);

	displayAll(*top);
}

