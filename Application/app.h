
#ifndef APP_h
#define APP_h
//including the header files
#include "../Server/server.h"

void init_accountDB();
void transaction_DB(ST_cardData_t cardData, ST_terminalData_t termData, uint32_t sequence);

void appStart(void);
#endif 
