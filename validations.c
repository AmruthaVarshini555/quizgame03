
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <ctype.h>
//
int integer_validation(char *str)
{
	long int num ;
	int len =0 , count = 0;
	num = atoi(str);
	len = strlen(str);
	//printf("num : %d and len : %d\n",num,len);
	if(num <= 0)
	{
		return 1;
	}
	else
	{	
		do {
			num /= 10;
			++count;
		  }while(num != 0);
		  if(len == count)
		  	return 0;
		  else 
		  	return 1;	
        }
}
//name validation
int alpha_validator(char *s)
{

        //validation for alphabets
        for(char *p=s;*p!='\0';p++)
        {
                if((!isalpha(*p)) && (*p!=' '))
                        return 0;
        }
        //validation for length
        if(strlen(s)>15 || strlen(s) < 3)
        {
                printf("Enter name within the length of 3 to 15\n");
                return 0;
        }
        return 1;
}
//Phone number validation
int phone_validation(char *str)
{
	
	long int num;
	int len =0 , count = 0;
	len = strlen(str);
	if(num <= 0 || len < 10 || len > 10)
	{
		return 0;
	}
	else
	{
		num = atoi(str);	
		do {
			num /= 10;
			++count;
		  }while(num != 0);
		  if(len == count)
		  	return 1;
		  else 
		  	return 0;	
        }	
}
//Password Validation
int password_validation(char *str)
{
	char *ptr = str;	
	int c_count = 0 , s_count = 0 , i_count = 0;
	while(*ptr !='\0')
	{
		if(*ptr >= 'A' && *ptr <= 'Z')	
		{
			c_count = 1;	
			//printf("Capital\n");
		}
		else if(*ptr >= 'a' && *ptr <= 'z')
		{
			s_count = 1;
			//printf("small\n");
		}
		else if(*ptr >= 48 && *ptr <= 58 )
		{
			i_count = 1;
			//printf("num\n");
		}
		ptr++;
	}
	if(c_count &&s_count &&i_count )
	return 1;
	else 
	return 0;
}
//E-mail validation
int email_validation(char *ptr)
{
	int c_count = 0 , s_count = 0 , i_count = 0 , n_count = 0;
	while(*ptr !='\0')
	{
		if(*ptr >= 'A' && *ptr <= 'Z')	
		{
			c_count = 1;	
			//printf("Capital\n");
		}
		else if(*ptr >= 'a' && *ptr <= 'z')
		{
			s_count = 1;
			//printf("small\n");
		}
		else if(*ptr == '.' )
		{
			i_count = 1;
			//printf("num\n");
		}
		else if(*ptr == '@')
		{
			n_count = 1;		
		}
		
		ptr++;
	}
	if(n_count &&i_count )
	return 1;
	else 
	return 0;
}



