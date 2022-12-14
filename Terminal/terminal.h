#pragma once
#ifndef TERMINAL_H
#define TERMINAL_H

#include"../Card/card.h"
//typedef for unsigned char
typedef unsigned char uint8_t;
//macro for maximum amount
#define maximum_amount 10000.0
typedef struct ST_terminalData_t
{
	//declaring some data
	float transAmount;
	float maxTransAmount;
	uint8_t transactionDate[11];
}ST_terminalData_t;
//typedef for enum
typedef enum EN_terminalError_t
{
	ok, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData);
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData);

#endif