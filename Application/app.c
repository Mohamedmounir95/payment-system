#pragma warning(disable : 4996)
#include<stdio.h>
#include<string.h>
#include"app.h"

// the function that starts the project
void appstart(void) {
	int number = 0, status;
	EN_cardError_t length;
	init_accountDB();
	ST_cardData_t holder_name;
	ST_terminalData_t x;
	char ch = 'y';
	do {
		length = getCardHolderName(&holder_name);
		getCardPAN(&holder_name);
		getCardExpiryDate(&holder_name);
		getTransactionDate(&x);
		if (isCardExpired(holder_name, x)) {
			printf("Decline Expired card\n");
			return;
		}
		getTransactionAmount(&x);
		if (isBelowMaxAmount(&x)) {
			printf("Decline amount excedding limit\n");
			return;
		}

		transaction_DB(holder_name, x, number);
		status = recieveTransactionData(&tran[number]);
		if (status == 2 || length == WRONG_NAME) {
			printf("Declined Invalid account\n");
			return;
		}
		else if (status == 1) {
			printf("Declined insuffecient funds\n");
			return;
		}
		system("cls");
		printf("thanks for using our service\n");
		printf("%s\n", tran[number].cardHolderData.cardHolderName);
		printf("%s\n", tran[number].cardHolderData.primaryAccountNumber);
		printf("your new balance is %2f\n\n", accounts[i].balance);
		printf("--------------------------------------------\n");
		printf("for another transaction press y for yes and n for no (y,n): ");
		scanf(" %c%*c", &ch);
		system("cls");
		number++;
	} while (ch == 'y');
}

// global array having two accounts
void init_accountDB() {
	accounts[0].balance = 4000;
	strcpy((char*)accounts[0].primaryAccountNumber, "4117394577826109");
	accounts[1].balance = 9500;
	strcpy((char*)accounts[1].primaryAccountNumber, "4117394577826901");

}


void transaction_DB(ST_cardData_t cardData, ST_terminalData_t termData, uint32_t sequence) {
	tran[sequence].cardHolderData = cardData;
	tran[sequence].terminalData = termData;
}