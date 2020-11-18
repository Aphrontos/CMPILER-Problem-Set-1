#include<stdio.h>
#include <string.h>

void start(int *state, char c)
{
	if(c == 'D')
		*state = 1;
	else if(c == '$')
		*state = 11;
	else if(c == 'R')
		*state = 14;
	else if(c == 'F')
		*state = 16;
}

void state1(int *state, char c)
{
	if(c == 'A')
		*state = 2;
	else if(c == 'M')
		*state = 7;
}

void state2(int *state, char c)
{
	if(c == 'D')
		*state = 3;
}

void state3(int *state, char c)
{
	if(c == 'D')
		*state = 4;
}

void state4(int *state, char c)
{
	if(c == 'I')
		*state = 5;
	else if(c == 'U')
		*state = 6;
	else
		*state = 20;
}

void state5(int *state, char c)
{
	if(c == 'U')
		*state = 6;
}

// State 6 is the first of the deadends
void state6(int *state, char c)
{
	if(c != '\0')
		*state = 20;
}

void state7(int *state, char c)
{
	if(c == 'U')
		*state = 8;
}

void state8(int *state, char c)
{
	if(c == 'L')
		*state = 9;
}

void state9(int *state, char c)
{
	if(c == 'T')
		*state = 10;
}

void state10(int *state, char c)
{
	if(c == 'U')
		*state = 6;
	else
		*state = 20;
}

/*--------------------------------------------------------*/

void state11(int *state, char c)
{
	if(c == '3')
		*state = 12;
	else if(c == '0' || (c >= '4' && c <= '9'))
		*state = 13;
	else if(c == '1' || c == '2')
		*state = 15;
	else if(c == 'F')
		*state = 16;
}

void state12(int *state, char c)
{
	if(c == '0' || c == '1')
		*state = 13;
	else
		*state = 20;
}

// State 13 is the second of the deadends
void state13(int *state, char c)
{
	if(c != '\0')
		*state = 20;
}

void state14(int *state, char c)
{
	if(c == '3')
		*state = 12;
	else if(c == '0' || (c >= '4' && c <= '9'))
		*state = 13;	
	else if(c == '1' || c == '2')
		*state = 15;
}

void state15(int *state, char c)
{
	if(c >= '0' && c <= '9')
		*state = 13;
	else
		*state = 20;
}

/*--------------------------------------------------------*/

void state16(int *state, char c)
{
	if(c == '3')
		*state = 17;
	else if(c == '1' || c == '2')
		*state = 18;
	else if(c == '0' || (c >= '4' && c <= '9'))
		*state = 19;
}

void state17(int *state, char c)
{
	if(c == '0' || c == '1')
		*state = 19;
	else
		*state = 20;
}

void state18(int *state, char c)
{
	if(c >= '0' && c <= '9')
		*state = 19;
	else
		*state = 20;
}

// State 19 is the last of the deadends
void state19(int *state, char c)
{
	if(c != '\0')
		*state = 20;
}

int DFA(int *state, char string[])
{	
	*state = 0;
	
	int len = strlen(string), result;
	for(int i = 0; i < len; i++)
	{
			 if(*state == 0)
			start(state, string[i]);
		else if(*state == 1)
			state1(state, string[i]);
		else if(*state == 2)
			state2(state, string[i]);
		else if(*state == 3)
			state3(state, string[i]);
		else if(*state == 4)
			state4(state, string[i]);
		else if(*state == 5)
			state5(state, string[i]);
		else if(*state == 7)
			state7(state, string[i]);
		else if(*state == 8)
			state8(state, string[i]);
		else if(*state == 9)
			state9(state, string[i]);
		else if(*state == 10)
			state10(state, string[i]);
		else if(*state == 11)
			state11(state, string[i]);
		else if(*state == 12)
			state12(state, string[i]);
		else if(*state == 13)
			state13(state, string[i]);
		else if(*state == 14)
			state14(state, string[i]);
		else if(*state == 15)
			state15(state, string[i]);
		else if(*state == 16)
			state16(state, string[i]);
		else if(*state == 17)
			state17(state, string[i]);
		else if(*state == 18)
			state18(state, string[i]);
		else if(*state == 19)
			state19(state, string[i]);
	}
			
	/*\                                       /*\ 
	|*|---------------------------------------|*| 
	|*| Code: 0                               |*|
	|*| Description: Reject State             |*|
	|*| Member(s): 19                         |*|
	|*|---------------------------------------|*|
	|*| Code: 1                               |*|
	|*| Description: Accepted State (KEYWORD) |*|
	|*| Member(s): 4, 6, 10                   |*|
	|*|---------------------------------------|*|
	|*| Code: 2                               |*|
	|*| Description: Accepted State (GPR)     |*|
	|*| Member(s): 12, 13, 15                 |*|
	|*|---------------------------------------|*|
	|*| Code: 3                               |*|
	|*| Description: Accepted State (FPR)     |*|
	|*| Member(s): 17, 18, 19                 |*|
	|*|---------------------------------------|*|
	\*/                                     /*\*/
		 if(*state == 4 ||
	   		*state == 6 ||
	   		*state == 10)
		return 1;
	else if(*state == 12 ||
			*state == 13 ||
			*state == 15)
		return 2;
	else if(*state == 17 ||
			*state == 18 ||
			*state == 19)
		return 3;
	else
		return 0;
}

void maximalMunch(int* state, char string[], char token[], FILE *out)
{
	int		i = 0, 
			j = 0, 
			len = strlen(string);
	while(i < len)
		if(string[i] == ' ' || string[i] == ',' || string[i] == '\n')
		{
			i++;
			j = 0;
			
			if(strcmp(token, "") != 0)
			{
				printf("%s ", token);
			
				if(DFA(state, token) == 0)
					fprintf(out, "ERROR ");
				else if(DFA(state, token) == 1)
					fprintf(out, "KEYWORD ");
				else if(DFA(state, token) == 2)
					fprintf(out, "GPR ");
				else if(DFA(state, token) == 3)
					fprintf(out, "FPR ");
				
				memset(token, 0, 1000);
			}
		}
		else
		{
			token[j] = string[i];
			i++;
			j++;
		}
	
	printf("\n");
	fprintf(out, "\n");
}

int main(void)
{
	int		state = 0, 
			i = 0, 
			j = 0;
	FILE   *in  = fopen("INPUT.txt" , "r"),
		   *out = fopen("OUTPUT.txt", "w");
	char 	string[1000],
		 	token[1000];
	
	if(in == NULL)
	{
		printf("Error 404: INPUT.txt is not found in the same directory as Parser.exe");
		return -1;
	}
	else
		printf("INPUT.txt is found in the same directory as Parser.exe\n\n");
	
	while(fgets(string, 1000, (FILE *)in) != NULL)
	{
		maximalMunch(&state, string, token, out);
		memset(token, 0, 1000);
	}
	
	fclose(in);	
	fclose(out);
}
