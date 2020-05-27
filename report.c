#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "VAR.h"
#include "manpage.h"


void Validate(char * flag[])
{
	if(strcmp(flag[1], "-h")==0 || strcmp(flag[1], "--help")==0)
	{
		help();
	}
	else if(strcmp(flag[1], "-u")==0 || strcmp(flag[1], "--user")==0)
		UserValidate();
	else if(strcmp(flag[1], "-a")==0 || strcmp(flag[1], "--admin")==0)
		AdminValidate();
	else
		printf("\'-h\' or \'--help\' flag for help section\n");
}

void AdminValidate()
{
	char pass[128] = "";
	printf("Please enter password for admin:\n");
	scanf("%s", pass);
	if(strcmp(pass, "admin123")==0)
		Admin();
	else
	{
		printf("Incorrect password for admin.\n");
		exit(0);
	}
}

void Admin()
{
	int ad_choice;
	printf("[1] Resolve a bug\n");
	printf("[2] View all Bug reports\n");
	printf("[3] Exit\n");
	printf("Enter your choice [1/2/3]: "); 
	scanf("%d", &ad_choice);
	switch(ad_choice)
	{
		case 1: Resolve(); break;
		case 2: View(); break;
		case 3: exit(0); break;
	}
}

void UserValidate()
{
	int choice;
	printf("\n\n\n[1] Login\n");
	printf("[2] SignUp\n");
	printf("[3] Exit\n");
	printf("Enter choice (1/2): ");
	scanf("%d", &choice);
	switch(choice)
	{
		case 1: Login(); break;
		case 2: SignUp(); break;
		case 3: exit(0); break;
		default: printf("Enter a valid choice.\n\n"); UserValidate(); break;
	}
}

void Login()
{
	int found = 0;
	int fielc_count = 0;
	char us[128];
	char *pass;
	char ch[3096];
	FILE *fp = fopen("Users.csv", "r");

	printf("Enter Username:\n");
	scanf("%s", us);
	if(!fp)
	{
		printf("Users.csv file is inaccesible\n");
		UserValidate();
	}
	else
	{
		while(fgets(ch, 3096, fp))
		{
			found = 0;
			char * buf = strtok(ch, ",");
			for(buf; buf && *buf; buf = strtok(NULL, ","))
			{
				if(found==1)
					pass = buf;
				if(strcmp(buf, us)==0)
					found = 1;
			}
			if(found == 1)
				break;
		}
		if(found == 1)
		{
			found = 0;
			char pa[128];
			printf("Enter password:\n");
			scanf("%s", pa);
			if(strcmp(pa, strtok(pass, "\n"))==0)
			{
				printf("Login Succesful!\n");
				User(us);
			}
			else
			{
				printf("Incorrect Password!\n");
				Login();
			}
		}
		else
		{
			printf("Username not found~\n");
			Login();
		}
	}
	fclose(fp);
}

void SignUp()
{
	printf("Register\n");
	char us[128];
	char pa[128];
        FILE * fp = fopen("Users.csv", "a");

	printf("Enter Username:\n");
	scanf("%s", us);
	printf("Enter password:\n");
	scanf("%s", pa);

        fputs(us, fp);
        fputs(",",fp);
        fputs(pa,fp);
        fclose(fp);
	printf("Registration Complete!\n");
	Login();
}

void User(char us[])
{
	int user_choice;
	printf("Would you like to:\n");
	printf("[1] Report a bug\n");
	printf("[2] View status of your bugs\n");
	printf("[3] Exit\n");
	scanf("%d", &user_choice);
	switch(user_choice)
	{
		case 1: report(us); break;
		case 2: UserExtract(us); break;
		case 3: exit(0); break;
	}
}

int rand_gen()
{
	time_t t;
	int rand_num = 0;
	srand((unsigned) time(&t));
	for(int i =0; i<6; i++)
	{
		rand_num = (rand_num*10) + rand()%10;
	}

	return rand_num;
}

void report(char us[])
{
	char bugid[10];
	char user[128];
	char stat[128] = "Pending";
	char desc[1024];
	FILE * fp = fopen("BugReport.csv", "a");

	*user = *us;
	sprintf(bugid, "%d", rand_gen());
	printf("Enter bug description:\n");
	scanf("%s", desc);

	fputs(bugid, fp);
        fputs(",",fp);
        fputs(us,fp);
	fputs(",", fp);
	fputs(desc, fp);
        fputs(",",fp);
        fputs(stat,fp);
        fputs("\n",fp);
        fclose(fp);

	printf("Bug successfully reported with id:%s\n", bugid);
}

void UserExtract(char us[])
{
	int found = 1;
	char *bugid;
	char *user;
	char *stat;
	char *desc;
	char temp[1024];
	int row_count =0,  field_count=0;
	char ch[3096];
	FILE *fp = fopen("BugReport.csv", "r");


	if(!fp)
	{
		printf("Unable to read BugRetport.csv\n");
		return;
	}	


	while(fgets(ch, 3096, fp))
	{
		found = 1;
		field_count = 0;
		*temp = *ch;
		char *buf = strtok(ch, ",");
		while(buf)
		{
			if(field_count == 0)
				bugid = buf;

			else if(field_count == 1) 
			{
				user = buf;
				if(( strcmp(us, buf)==0))
					found = 0;
				
			}			
			else if(field_count == 2)
				desc = buf;

			else if(field_count == 3)
				stat = buf;
			else
				printf("Unknown error\n");
			field_count++;	
				
				
				
			buf = strtok(NULL, ",");
		}
		if(found == 0)
			printf("\nbugid:\t\t%s\nUsername:\t%s\nRepors:\t\t%s\nStatus:\t\t%s\n", bugid, user, desc, stat);
	}
	fclose(fp);
}


void Resolve()
{
	FILE *fp, *fp1, *fp2;
	char *bugid, *user, *desc, *stat;
	int field_count = 0, found = 1;
	char res_bugid[10], ch[3096], chre[3096];
        fp1 = fopen("BugReport.csv", "r");
        fp2 = fopen("temp.csv", "a");
        if(!fp1 || !fp2)
        {
                printf("Unable to access Report.csv\n");
                return;
        }
	
	printf("Enter bugid of resolved bug: ");
	scanf("%s", res_bugid);

	while(fgets(ch, 3096, fp1))
	{
		field_count = 0;
		char *buf = strtok(ch, ",");
		while(buf)
		{
			switch(field_count)
			{
				case 0: bugid = buf; break;
				case 1: user = buf; break;
				case 2: desc = buf; break;
				case 3: stat = buf; break;
			}
			field_count++;
			buf = strtok(NULL, ",");
		}
		if(strcmp(res_bugid, bugid)==0)
		{
			stat = "Resolved\n";
			fputs(bugid, fp2);
        		fputs(",",fp2);
        		fputs(user,fp2);
			fputs(",", fp2);
			fputs(desc, fp2);
        		fputs(",",fp2);
        		fputs(stat,fp2);
		}
		else
		{
			fputs(bugid, fp2);
        		fputs(",",fp2);
        		fputs(user,fp2);
			fputs(",", fp2);
			fputs(desc, fp2);
        		fputs(",",fp2);
        		fputs(stat,fp2);
		}
	}
	fclose(fp1);
	fclose(fp2);
	
	//erasing redundant data in BugReport.csv
	fp = fopen("BugReport.csv", "w");
	fputs("", fp);
	fclose(fp);
	
	//rewriting BugReport.csv
	fp1 = fopen("BugReport.csv", "a");
        fp2 = fopen("temp.csv", "r");
        if(!fp1 || !fp2)
        {
                printf("Unable to access Report.csv\n");
                return;
        }
        
        while(fgets(chre, 3096, fp2))
	       	fputs(chre, fp1);

        fclose(fp1);
        fclose(fp2);
	
	//erasing data from temp.csv
	fp = fopen("temp.csv", "w");
	fputs("", fp);
	fclose(fp);
	
	View();
}

void View()
{
	printf("\n\nAll Bug Reports:\n");
	int field_count=0;
	char ch[3096];
	FILE *fp = fopen("BugReport.csv", "r");

	if(!fp)
	{
		printf("Unable to read BugRetport.csv\n");
		return;
	}	


	while(fgets(ch, 3096, fp))
	{
		field_count = 0;
		char *buf = strtok(ch, ",");
		while(buf)
		{
			if(field_count == 0)
				printf("Bugid:\t\t%s\n", buf);
			else if(field_count == 1)
				printf("Username:\t%s\n", buf);			
			else if(field_count == 2)
				printf("Report:\t\t%s\n", buf);
			else if(field_count == 3)
				printf("Status:\t\t%s\n\n", buf);
			else
				printf("Unknown error\n");
			field_count++;		
			buf = strtok(NULL, ",");
		}
//		printf("\nbugid:\t\t%s\nUsername:\t%s\nRepors:\t\t%s\nStatus:\t\t%s\n", bugid, user, desc, stat);
	}
	fclose(fp);

}
