#include <stdio.h>
#include <windows.h>
#include <mysql.h>
#include <sstream>

using namespace std;

const char* SERVEUR = "your-server-name";
const char* LOGIN = "your-login";
const char* PASSWORD = "your-password";
const char* DTB = "your-database-name";
const char* QUERY = "SELECT * FROM mutualcomprehension";
const char* QUERY2 = "UPDATE mutualcomprehension SET score = ";
int COMPREHENSION = 0;

void connection();
MYSQL sql;
void getComprehension();
void decreaseComprehension();
void increaseComprehension();
void start();
void selection();
void end();
int  clean_stdin();
void concatIntToChar(char* str, int number, char* result);

int main() {
    start();
    connection();
    end();
}
void connection(){
    mysql_init(&sql);
    if((mysql_real_connect(&sql, SERVEUR, LOGIN, PASSWORD, DTB, 0, NULL, 0))){
          getComprehension();
          selection();
    }
    else
        printf("An error occurred while connecting to the online database");
}
int clean_stdin(){
    while (getchar()!='\n');
    return 0;
}
void increaseComprehension(){
	COMPREHENSION++;
	char result[100];
	concatIntToChar(QUERY2, COMPREHENSION, result);
	mysql_query(&sql, result);
	printf("\n The comprehension has been increased!");
}
void decreaseComprehension(){
    COMPREHENSION--;
	char result[100];
	concatIntToChar(QUERY2, COMPREHENSION, result);
	mysql_query(&sql, result);
	printf("\n The comprehension has been decreased!");
}
void start(){
	system("cls");
	printf ("\n          \\\\\\||||||//// ");
    printf ("\n           \\\\  ~ ~  // ");
    printf ("\n            (  @ @  ) ");
	printf ("\n ==========oOOo(_)oOOo=========   ");
	printf ("\n ==                          ==   ");
	printf ("\n ==   MUTUAL COMPREHENSION   ==   ");
	printf ("\n ==                          ==   ");
	printf ("\n ============================== \n");
    printf ("\n 1. Jeez Rick! It's gibberish!      ");
	printf ("\n 2. C'mon Morty! It's crystal-clear! ");
}
void selection(){
    int  choice;
    char c;
    do{
    	printf ("\n Your choice : ");
    }while (((scanf("%d%c", &choice, &c)!=2 || c!='\n') && clean_stdin()) || choice<1 || choice>2);

    if(choice == 1)
    	decreaseComprehension();
    else
    	increaseComprehension();
}
void end(){
    printf("\n The final comprehension score is %d. \n", COMPREHENSION);
    mysql_close(&sql);
    getchar();
}
void getComprehension(){
    mysql_query(&sql, QUERY);
    MYSQL_RES *result = NULL;
    MYSQL_ROW row;
    result = mysql_use_result(&sql);
    row = mysql_fetch_row(result);
    COMPREHENSION = atoi(row[0]);
    mysql_free_result(result);
}
void concatIntToChar(char* a, int number, char* result){
	stringstream strs;
    strs << number;
	string temp_str = strs.str();
    char const* pchar = temp_str.c_str();
	strcpy(result,a);
	strcat(result,pchar);
}
