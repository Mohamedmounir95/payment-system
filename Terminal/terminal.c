#pragma warning(disable : 4996)
#include "terminal.h"
#include <stdio.h>
#include "../Card/card.h"
// including a function for time
#include<time.h>

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
    time_t tim = time(NULL);
    struct tm tm = *localtime(&tim);

    termData->transactionDate[0] = (tm.tm_mday / 10 + '0');
    termData->transactionDate[1] = (tm.tm_mday % 10 + '0');
    termData->transactionDate[2] = '/';
    termData->transactionDate[3] = (tm.tm_mon / 10 + '0');
    termData->transactionDate[4] = (tm.tm_mon % 10 + 1 + '0');
    termData->transactionDate[5] = '/';
    termData->transactionDate[6] = ((tm.tm_year + 1900) / 1000 + '0');
    termData->transactionDate[7] = (((tm.tm_year + 1900) % (((tm.tm_year + 1900) / 1000) * 1000)) / 100 + '0');
    termData->transactionDate[8] = ((((tm.tm_year + 1900) % (((tm.tm_year + 1900) / 1000) * 1000)) % (termData->transactionDate[7] - '0' * 100)) / 10 + '0');
    termData->transactionDate[9] = ((((tm.tm_year + 1900) % (((tm.tm_year + 1900) / 1000) * 1000)) % (termData->transactionDate[8] - '0' * 10)) / 10 + '0');
    termData->transactionDate[10] = '\0';
    return ok;
}
//function for checking the expiration date 
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData) {
    if (
        ((cardData.cardExpirationDate[3] - '0') * 10) + cardData.cardExpirationDate[4] - '0' > (termData.transactionDate[8] - '0') * 10 + termData.transactionDate[9] - '0') {
        return ok;
    }
    else if (((cardData.cardExpirationDate[3] - '0') * 10) + cardData.cardExpirationDate[4] - '0' == (termData.transactionDate[8] - '0') * 10 + termData.transactionDate[9] - '0' && ((cardData.cardExpirationDate[0] - '0') * 10) + cardData.cardExpirationDate[1] - '0' > (termData.transactionDate[3] - '0') * 10 + termData.transactionDate[4] - '0') {
        return ok;
    }
    else {
        return EXPIRED_CARD; //the card is expired
    }
}
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData) {
    int j, sum = 0, number1, number2;
    for (j = 0; j < strlen((char *)cardData->primaryAccountNumber); j += 2) {
        if ((cardData->primaryAccountNumber[j] - '0') * 2 >= 10) {
            number1 = ((cardData->primaryAccountNumber[j] - '0') * 2) / 10;
            number2 = ((cardData->primaryAccountNumber[j] - '0') * 2) % 10;
            sum += number1 + number2;
        }
        else {
            sum += (cardData->primaryAccountNumber[j] - '0') * 2;
        }
    }
    for (j = 1; j < 16; j += 2) {
        sum += cardData->primaryAccountNumber[j] - '0';
    }
    if (sum % 10 == 0)
        return ok;

    else {
        return INVALID_CARD;
    }
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {

    printf("please Enter the transaction amount \n");
    scanf("%f", &termData->transAmount);
    if (termData->transAmount <= 0)
        return INVALID_AMOUNT;
    else {
        return ok;
    }
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
    setMaxAmount(termData);
    if (termData->transAmount > termData->maxTransAmount)
        return EXCEED_MAX_AMOUNT;//the amount is more than the maximum amount
    else
        return ok;
}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {
    termData->maxTransAmount = maximum_amount;
    if (termData->maxTransAmount >= 0)
        return INVALID_MAX_AMOUNT;
    else
        return ok;
}

