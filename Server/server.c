#include<string.h>
#include<stdio.h>
#include"server.h"

EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
    //checking whether the card is stolen or not
    if (isValidAccount(&transData->cardHolderData) || isValidCardPAN(&transData->cardHolderData)) {
        transData->transState = DECLINED_STOLEN_CARD;
        return DECLINED_STOLEN_CARD;

    }
    //checking for the available amount in the card
    else if (isAmountAvailable(&transData->terminalData)) {
        transData->transState = DECLINED_INSUFFECIENT_FUND;
        return DECLINED_INSUFFECIENT_FUND;
    }
    else if (saveTransaction(transData)) {
        transData->transState = INTERNAL_SERVER_ERROR;
        return INTERNAL_SERVER_ERROR;
    }
    accounts[i].balance -= transData->terminalData.transAmount;
    return APPROVED;

}

EN_transState_t isValidAccount(ST_cardData_t* cardData) {
    for (i = 0; i < 2; i++) {
        if (!strcmp((char*)cardData->primaryAccountNumber, (char*)accounts[i].primaryAccountNumber)) {
            return APPROVED;
        }
    }
    printf("this is a Stolen Card\n");
    return DECLINED_STOLEN_CARD;
}
//checking whether the balance id available or not
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData) {

    if (termData->transAmount > accounts[i].balance) {
        return LOW_BALANCE;
    }


    return oK;
}
EN_serverError_t saveTransaction(ST_transaction_t* transData) {
    transData->transactionSequenceNumber = seq;
    seq++;
    if (transData->transState == DECLINED_STOLEN_CARD || transData->transState == DECLINED_INSUFFECIENT_FUND) {

        return SAVING_FAILED;
    }
    return oK;
}

