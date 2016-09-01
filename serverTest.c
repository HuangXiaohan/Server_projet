#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "CUnit/CUnit.h"
#include "CUnit/Console.h"  
#include "myServer.h"

int InitSuite(){  
    return 0;  
}   
      
int EndSuite(){  
    return 0;  
}


void testSplit1(){
	char s1[10][80];
	char *res = malloc(sizeof(char *));
	strcpy(res,"hello?world");
	int p1 = split(s1,res,"?");
	CU_ASSERT_EQUAL("hello",s1[0]);
	CU_ASSERT_EQUAL(2,p1);
	
}

void testSplit2(){
	char s2[10][80];
	char *res = malloc(sizeof(char *));
	strcpy(res,"nihao");
	int p2 = split(s2,res,"/");
	CU_ASSERT_EQUAL("nihao",s2[0]);
	CU_ASSERT_EQUAL(1,p2);
}

void testSplit3(){
	char s3[10][80];
	char *res = malloc(sizeof(char *));
	strcpy(res,"what's up!");
	int p3 = split(s3,res,"!");
	CU_ASSERT_EQUAL("",s3[1]);
	CU_ASSERT_EQUAL(1,p3);
}

int main()
{
	 CU_pSuite pSuite = NULL;

	 if(CUE_SUCCESS != CU_initialize_registry())
	 	return CU_get_error();

	 pSuite =  CU_add_suite("Suite",InitSuite,EndSuite);
	 if(NULL == pSuite){
	 	CU_cleanup_registry();
	 	return CU_get_error();
	 }

	 if((NULL == CU_add_test(pSuite,"testSplit1",testSplit1)) ||
	 	(NULL == CU_add_test(pSuite,"testSplit2",testSplit2)) ||
	 	(NULL == CU_add_test(pSuite,"testSplit3",testSplit3))){
	 	CU_cleanup_registry();
	 	return CU_get_error();
	 }

	 CU_console_run_tests();
	 CU_cleanup_registry();
	 return CU_get_error();
}
