void setUpContacts();

/* Menu functions */
List *addNewElement(List *, ListControl *);
List *loadContacts(List *, ListControl *);
void  printFullList(List *, ListControl *);
void  searchInList(List *, ListControl *);
void  removeAnElement(List *, ListControl *);
void  updateAnElement(List *, ListControl *);
/* ~~~~ ~~~~ ~~~~ */

/* Getting-data functions */
char *getName();
char *getEmailAddress();
char *getHomeAddress();
char *getDateOfBirth();
char *getCellphoneNumber();
char *getWorkphoneNumber();
/* ~~~~ ~~~~~ ~~~~~ ~~~~~ */

void setUpContacts(){
	FILE *contacts;
	contacts = fopen("contacts.db", "a+");
	if(contacts == NULL)
		exit(EXIT_FAILURE);
	fclose(contacts);
	
	contacts = fopen("contacts.db", "r");
	if(contacts == NULL)
		exit(EXIT_FAILURE);
		
	char analyzing = 'x';
	int j = 0;
	
	while(analyzing != '#'){
		analyzing = fgetc(contacts);
		if(j == 0 && analyzing != '$')
			break;
		if(analyzing == '$')
			auxiliary_2++;
		j++;
	}
	
	if(auxiliary_2 == 0)
		allowLoadContacts = false;
	
	fclose(contacts);
};

void saveContacts(List *li, ListControl *liC){
	FILE *contacts;
	List *element;
	contacts = fopen("contacts.db", "w");
	if(contacts == NULL)
		exit(EXIT_FAILURE);
	
	if(liC->lenght > 0){
		for(element = liC->first; element != NULL; element = element->after){
			fprintf(contacts, "$\n");
			fprintf(contacts, "%s\n",  element->completeName);
			fprintf(contacts, "%s\n",  element->emailAddress);
			fprintf(contacts, "%s\n",  element->homeAddress);
			fprintf(contacts, "%s\n",  element->dateOfBirth);
			fprintf(contacts, "%s\n",  element->cellphoneNumber);
			fprintf(contacts, "%s\n",  element->workphoneNumber);
		}
		fprintf(contacts, "#\n");
	}
};
List *loadContacts(List *li, ListControl *liC){
	List 	*element;
	element = (List *) malloc(sizeof(List));
	if(element == NULL)
		exit(EXIT_FAILURE);
		
	FILE *contacts;
	contacts = fopen("contacts.db", "r");
	
	char analyzing;
	char completeName[100];
	char emailAddress[100];
	char homeAddress[100];
	char dateOfBirth[10];
	char cellphoneNumber[15];
	char workphoneNumber[15];
	int  i = 1;
	
	strcpy(completeName,    " ");
	strcpy(emailAddress,    " ");
	strcpy(homeAddress,     " ");
	strcpy(dateOfBirth,     " ");
	strcpy(cellphoneNumber, " ");
	strcpy(workphoneNumber, " ");
	
	while(i <= auxiliary_1){
		fscanf(contacts, " %c",      &analyzing);
		fscanf(contacts, " %[^\n]s", completeName);
		fscanf(contacts, " %[^\n]s", emailAddress);
		fscanf(contacts, " %[^\n]s", homeAddress);
		fscanf(contacts, " %[^\n]s", dateOfBirth);
		fscanf(contacts, " %[^\n]s", cellphoneNumber);
		fscanf(contacts, " %[^\n]s", workphoneNumber);
		i++;
	}
		if(liC->first == NULL){
			liC->first = element;
			liC->last  = element;
			element->after  = NULL;
			element->before = NULL;	
		} else if(liC->first == liC->last){
			liC->last = element;
			liC->first->after = element;
			element->after   = NULL;
			element->before = liC->first;
		} else {
			element->before = liC->last;
			liC->last->after = element;
			liC->last = element;
			element->after   = NULL;
		}
		strcpy(element->completeName,    completeName);
		strcpy(element->emailAddress,    emailAddress);
		strcpy(element->homeAddress,     homeAddress);
		strcpy(element->dateOfBirth,     dateOfBirth);
		strcpy(element->cellphoneNumber, cellphoneNumber);
		strcpy(element->workphoneNumber, workphoneNumber);
		liC->lenght++;
	
	fclose(contacts);
	
	return element;
};
List *addNewElement(List *li, ListControl *liC){
	List 	*element;
	element = (List *) malloc(sizeof(List));
	if(element == NULL)
		exit(EXIT_FAILURE);
	
	if(liC->first == NULL){
		liC->first = element;
		liC->last  = element;
		element->after   = NULL;
		element->before = NULL;	
	} else if(liC->first == liC->last){
		liC->last = element;
		liC->first->after = element;
		element->after   = NULL;
		element->before = liC->first;
	} else {
		element->before = liC->last;
		liC->last->after = element;
		liC->last = element;
		element->after   = NULL;
	}
	clearScreen();
	strcpy(element->completeName,    getName());
	strcpy(element->emailAddress,    getEmailAddress());
	strcpy(element->homeAddress,     getHomeAddress());
	strcpy(element->dateOfBirth,     getDateOfBirth());
	strcpy(element->cellphoneNumber, getCellphoneNumber());
	strcpy(element->workphoneNumber, getWorkphoneNumber());
	liC->lenght++;
	
	return element;	
};
void printFullList(List *li, ListControl *liC){
	List *element;
	
	clearScreen();
	if(liC->lenght == 0){
		printf("\n");
		printf("\t Oops, you are trying to print your list but it is empty.\n");
		printf("\n");
		printf("\n");
	    printf("\t-> Press any key to go back to menu... ");
	    getch();
		return;	
	};
	
	printf("\n");
	printf("\t Printing all your contact list:\n");
	printf("\n");
	for(element = liC->first; element != NULL; element = element->after){
		printf("\t##########################################################################################################\n");
		printf("\n");
		printf("\t COMPLETE NAME:      %s\n",  element->completeName);
		printf("\t HOME ADDRESS:       %s\n",  element->homeAddress);
		printf("\t DATE OF BIRTHDAY:   %s\n",  element->dateOfBirth);
		printf("\n");
		printf("\t E-MAIL ADDRESS:     %s\n",  element->emailAddress);
		printf("\t CELLPHONE NUMBER:   %s\n",  element->cellphoneNumber);
		printf("\t WORKPHONE NUMBER:   %s\n",  element->workphoneNumber);
		printf("\n");
	}
	    printf("\t##########################################################################################################\n");
	    printf("\n");
	    printf("\t-> Press any key to go back to menu... ");
	    getch();
};
void searchInList(List *li, ListControl *liC){;
	List *element;
	
	char searching[100];
	char *result;
	int results = 0;
	
	clearScreen();
	if(liC->lenght == 0){
		printf("\n");
		printf("\t Oops, you are trying to print your list but it is empty.\n");
		printf("\n");
		printf("\n");
	    printf("\t-> Press any key to go back to menu... ");
	    getch();
		return;	
	};
	
	printf("\n");
	printf("\t Search by name: ");
	scanf(" %[^\n]s", searching);
	printf("\n");
	printf("\t Printing results for \"%s\":\n", searching);
	printf("\n");
	for(element = liC->first; element != NULL; element = element->after){
		result = strstr(element->completeName, searching);
		if (result != NULL){
			results++;
			printf("\t##########################################################################################################\n");
			printf("\n");
			printf("\t COMPLETE NAME:      %s\n",  element->completeName);
			printf("\t HOME ADDRESS:       %s\n",  element->homeAddress);
			printf("\t DATE OF BIRTHDAY:   %s\n",  element->dateOfBirth);
			printf("\n");
			printf("\t E-MAIL ADDRESS:     %s\n",  element->emailAddress);
			printf("\t CELLPHONE NUMBER:   %s\n",  element->cellphoneNumber);
			printf("\t WORKPHONE NUMBER:   %s\n",  element->workphoneNumber);
			printf("\n");
		}
	}
		if(results == 0){
			printf("\t##########################################################################################################\n");
			printf("\n");
			printf("\n");
			printf("\t Oops, the program couldn't find any results for \"%s\".\n", searching);
			printf("\n");
			printf("\n");
		}
	    printf("\t##########################################################################################################\n");
	    printf("\n");
	    printf("\t-> Press any key to go back to menu... ");
	    getch();
};
void removeAnElement(List *li, ListControl *liC){
	List *element;
	List *remove;
	
	char searching[100];
	char *result;
	char decision;
	int  i = 0;
	int results = 0;
	clearScreen();
	
	if(liC->lenght == 0){
		printf("\n");
		printf("\t Oops, you are trying to delete a contact but your list is empty.\n");
		printf("\n");
		printf("\n");
	    printf("\t-> Press any key to go back to menu... ");
	    getch();
		return;	
	};
	
	printf("\n");
	printf("\t Search by name: ");
	scanf(" %[^\n]s", searching);
	printf("\n");
	printf("\t##########################################################################################################\n");
	printf("\n");
	printf("\n");

	for(element = liC->first; element != NULL; element = element->after){
		i++;
		result = strstr(element->completeName, searching);
		if(result != NULL){
			results++;
			printf("\t Are you sure you want to delete \"%s\"'s contact? [Y/N] ", element->completeName);
			decision = getch();
			printf("\n");
			printf("\n");
			if(decision == 'Y' || decision == 'y'){;
				if(i == 1){ // Removing first list element.
					remove = liC->first;
					liC->first = liC->first->after;
				
					if(liC->first == NULL)
						liC->last == NULL;
					else 
						liC->first->before == NULL;
				} else if (element == liC->last){ // Removing last list element.
					remove = liC->last;
					liC->last->before->after = NULL;
					liC->last = liC->last->before;
				} else { // Removing from somewhere else.
					remove = element;
					element->before->after = element->after;
					element->after->before = element->before;
				}
				free(remove);
				liC->lenght--;
				printf("\t Alright, that contact was succesfully deleted.\n");
				printf("\n");
			} else {
				printf("\t Alright, that contact was not deleted.\n");
				printf("\n");
			}
		}
	}
		if(results == 0){
			printf("\t Oops, the program couldn't find any results for \"%s\".\n", searching);
			printf("\n");
			printf("\n");
		}
		printf("\t##########################################################################################################\n");
	    printf("\n");
	    printf("\t-> Press any key to go back to menu... ");
	    getch();
};
void updateAnElement(List *li, ListControl *liC){
	List *element;
	
	char searching[100];
	char *result;
	char decision;
	int  i = 0;
	int results = 0;
	clearScreen();
	
	if(liC->lenght == 0){
		printf("\n");
		printf("\t Oops, you are trying to update a contact but your list is empty.\n");
		printf("\n");
		printf("\n");
	    printf("\t-> Press any key to go back to menu... ");
	    getch();
		return;	
	};
	
	printf("\n");
	printf("\t Search by name: ");
	scanf(" %[^\n]s", searching);
	printf("\n");
	printf("\t##########################################################################################################\n");
	printf("\n");
	printf("\n");

	for(element = liC->first; element != NULL; element = element->after){
		i++;
		result = strstr(element->completeName, searching);
		if(result != NULL){
			results++;
			printf("\t Are you sure you want to update \"%s\"'s contact? [Y/N] ", element->completeName);
			decision = getch();
			printf("\n");
			printf("\n");
			if(decision == 'Y' || decision == 'y'){
				strcpy(element->completeName,    getName());
				strcpy(element->emailAddress,    getEmailAddress());
				strcpy(element->homeAddress,     getHomeAddress());
				strcpy(element->dateOfBirth,     getDateOfBirth());
				strcpy(element->cellphoneNumber, getCellphoneNumber());
				strcpy(element->workphoneNumber, getWorkphoneNumber());
				printf("\n");
				printf("\t Alright, that contact was succesfully update.\n");
				printf("\n");
			} else {
				printf("\t Alright, that contact was not updated.\n");
				printf("\n");
			}
		}
	}
		if(results == 0){
			printf("\t Oops, the program couldn't find any results for \"%s\".\n", searching);
			printf("\n");
			printf("\n");
		}
		printf("\t##########################################################################################################\n");
	    printf("\n");
	    printf("\t-> Press any key to go back to menu... ");
	    getch();
};

char *getName(){
	char *completeName = (char *) malloc(sizeof(char) * 100);
	if(completeName == NULL)
		exit(EXIT_FAILURE);
	printf("\n");
	printf("\t!! FOR A BETTER USE OF THIS PROGRAM: IF YOU DON'T HAVE ANY INFORMATION REQUESTED BELOW, THEN JUST TYPE '--' !!\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\tPlease insert the complete name of your new contact: ");
	scanf(" %[^\n]s", completeName);
	printf("\n");
	return completeName;
};
char *getEmailAddress(){
	char *emailAddress = (char *) malloc(sizeof(char) * 100);
	if(emailAddress == NULL)
		exit(EXIT_FAILURE);
	printf("\n");
	printf("\tPlease insert the e-mail address of your new contact: ");
	scanf(" %[^\n]s", emailAddress);
	printf("\n");
	return emailAddress;
};
char *getHomeAddress(){
	char *homeAddress = (char *) malloc(sizeof(char) * 100);
	if(homeAddress == NULL)
		exit(EXIT_FAILURE);
	printf("\n");
	printf("\tPlease insert the home address of your new contact: ");
	scanf(" %[^\n]s", homeAddress);
	printf("\n");
	return homeAddress;
};
char *getDateOfBirth(){
	char *dateOfBirth = (char *) malloc(sizeof(char) * 15);
	if(dateOfBirth == NULL)
		exit(EXIT_FAILURE);
	printf("\n");
	printf("\tPlease insert the date of birth of your new contact [MM/DD/YYYY]: ");
	scanf(" %[^\n]s", dateOfBirth);
	printf("\n");
	return dateOfBirth;
};
char *getCellphoneNumber(){
	char *cellphoneNumber = (char *) malloc(sizeof(char) * 15);
	if(cellphoneNumber == NULL)
		exit(EXIT_FAILURE);
	printf("\n");
	printf("\tPlease insert the cellphone number of your new contact: ");
	scanf(" %[^\n]s", cellphoneNumber);
	printf("\n");
	return cellphoneNumber;
};
char *getWorkphoneNumber(){
	char *workphoneNumber = (char *) malloc(sizeof(char) * 15);
	if(workphoneNumber == NULL)
		exit(EXIT_FAILURE);
	printf("\n");
	printf("\tPlease insert the workphone number of your new contact: ");
	scanf(" %[^\n]s", workphoneNumber);
	printf("\n");
	return workphoneNumber;
};
