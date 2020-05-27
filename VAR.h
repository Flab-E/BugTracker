#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>

//Functions declared:
void help();				//for help section output
void AdminValidate(void);		//To Valiate admin login with admin password
void UserValidate(void);		//to validate if the user is logging in or registering
void Validate(char * flag[10]);		//commom validate to identify user or admin
void Login(void);			//user login with password
void SignUp(void);			//user regiteration
void Admin(void);			//Admin home section
void User(char us[]);			//user home section
int rand_gen();				//random 6 digit generator for bugid
void UserExtract(char us[]);		//to outpu user's bug reports
void report(char us[]);			//user's bug report section
void Resolve(void);			//admin's bug resolved section
void View(void);			//view all bug reports
void SearchBug(void);			//Search for Bugs based on query
