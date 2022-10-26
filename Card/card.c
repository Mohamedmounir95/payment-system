#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//including the card library
#include "card.h"
//function to ask the user to enter card holder name
EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
    printf("welcome to the payment system\n");
    printf("made by mohamed mounir\n");
    printf("Enter the Card holder name\n");
    //gets the name from the user
    gets((char*)cardData->cardHolderName);
    fflush(stdin);
    //checking if the name is valid or not
    if (cardData->cardHolderName == NULL || strlen((char*)cardData->cardHolderName) < 20 || strlen((char*)cardData->cardHolderName) > 24)
        return WRONG_NAME;
    else {
        return OK;
    }
}
//function to ask the user to enter card expiration date
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
    printf("Enter the Card Expiration date in this format 'MM/YY'\n");
    //gets the expiration date from the user
    gets((char*)cardData->cardExpirationDate);
    fflush(stdin);
    int month = (cardData->cardExpirationDate[0] - '0') * 10 + cardData->cardExpirationDate[1] - '0';
    //checking if the expiration date is valid or not
    if (strlen((char*)cardData->cardExpirationDate) != 5 || cardData->cardExpirationDate[2] != '/' || month > 12)
        return WRONG_EXP_DATE;
    else {
        return OK;
    }
}
//function to ask the user to enter card pan
EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
    int i ;
    printf("Enter the Card primary acount numper (PAN) \n");
    //gets tha pan from the user
    gets((char*)cardData->primaryAccountNumber);
    //checking if the pan is valid or not
    if (cardData->primaryAccountNumber==NULL || strlen((char*)cardData->primaryAccountNumber) > 19 || strlen((char*)cardData->primaryAccountNumber) < 16) {
        return WRONG_PAN;
    }
    for (i = 0; i < strlen((char*)cardData->primaryAccountNumber) - 1; i++) {
        if (isalnum(cardData->primaryAccountNumber[i]) == 0) {
            return WRONG_PAN;
        }
    }
        return OK;
}