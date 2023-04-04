#ifndef LOGIN_SYSTEM_LOGIN_SYSTEM_H_
#define LOGIN_SYSTEM_LOGIN_SYSTEM_H_


#include "DIO_Interface.h"

#define Relay DIO_PD7


void Login_System_init (void);

typedef enum {
	RESPONSE,
	NORESPONSE
}Person_state_t;

void Login_System_init (void);
void Login_System_Runnable (void);
static void System_stand_by (void);
static Person_state_t System_Ready (void);
static Person_state_t System_Enter_Password (void);
static void System_Successful_Login (void);



#endif /* LOGIN_SYSTEM_LOGIN_SYSTEM_H_ */
