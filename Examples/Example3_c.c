/*
 * TextParser - Text Parsing Library
 *
 * Copyright (C) 2012-2014 Institute of Industrial Science, The University of Tokyo.
 * All rights reserved.
 *
 */

/** @file Example3_c.c
 * サンプルプログラム
 */

#include <stdio.h>
#include <stdlib.h>
#include "TextParser.h"
#define TP_STRING_MAX_SIZE 512

int scan_all_parameters(char *filename,TP_HANDLE tp_handle)
{
  

  int i ;
  unsigned int j;
  int ierror = 0;
  unsigned int number = 0;
  unsigned int vector_number=0;
  //  char *label;
  //  char *value;
  char label[TP_STRING_MAX_SIZE];
  char value[TP_STRING_MAX_SIZE];
  char val[512];
    TextParserValueType type;
    int itype;
    char cval;
    short sval;
    int ival;
    long lval;
    long long llval;
    float fval;
    double dval;



    // ファイルの読み込み
    printf("filename: %s\n", filename);
    ierror=tp_read(tp_handle,filename);
    if (ierror != 0) {
        printf("ERROR in tp_read file: %s ERROR CODE %d\n", filename, ierror);
        return ierror;
    }

    // パラメータの総数の取得
    ierror=tp_getNumberOfLeaves(tp_handle,&number);
    if (ierror != 0) {
        printf("ERROR in tp_getNumberOfLeaves file: %s ERROR CODE %d\n", filename, ierror);
        return ierror;
    }
    printf("Total label number: %d\n", number);

    // 全てのパラメータのラベルを取得
    for (i = 0; i < number; i++) {
      ierror = tp_getLabel(tp_handle,i, label);
        printf("%d %s\n", i, label);
        if (ierror != 0) {
            printf("ERROR in tp_getLabels file: %s ERROR CODE %d\n", filename, ierror);
            return ierror;
        }


        ierror = tp_getValue(tp_handle,label,value);
        printf("%d %s\n", i, value);
        if (ierror != 0) {
            printf("ERROR in tp_getValue file: %s ERROR CODE %d\n", filename, ierror);
            return ierror;
        }

	
        ierror = tp_getType(tp_handle,label, &itype);
	type=(TextParserValueType)itype;
        printf("%d value type: %d\n", i, type);
        if (ierror != 0) {
            printf("ERROR in tp_getType file: %s ERROR CODE %d\n", filename, ierror);
            return ierror;
        }


        if (type == TP_NUMERIC_VALUE) {
	  cval = tp_convertChar(tp_handle,value, &ierror);
            if (ierror != 0) {
                printf("ERROR in tp_convertChar file: %s ERROR CODE %d\n", filename, ierror);
                return ierror;
            }
            printf("%d convert to char: %c\n", i, cval);
            sval = tp_convertShort(tp_handle,value, &ierror);
            if (ierror != 0) {
                printf("ERROR in tp_convertShort file: %s ERROR CODE %d\n", filename, ierror);
                return ierror;
            }
            printf("%d convert to short: %d\n", i, sval);
            ival = tp_convertInt(tp_handle,value, &ierror);
            if (ierror != 0) {
                printf("ERROR in tp_convertInt file: %s ERROR CODE %d\n", filename, ierror);
                return ierror;
            }
            printf("%d convert to int: %d\n", i, ival);
            lval = tp_convertLong(tp_handle,value, &ierror);
            if (ierror != 0) {
                printf("ERROR in tp_convertLong file: %s ERROR CODE %d\n", filename, ierror);
                return ierror;
            }
            printf("%d convert to long: %ld\n", i, lval);
            llval = tp_convertLongLong(tp_handle,value, &ierror);
            if (ierror != 0) {
                printf("ERROR in tp_convertLongLong file: %s ERROR CODE %d\n", filename, ierror);
                return ierror;
            }
            printf("%d convert to long long: %lld\n", i, llval);
            fval = tp_convertFloat(tp_handle,value, &ierror);
            if (ierror != 0) {
                printf("ERROR in tp_convertFloat file: %s ERROR CODE %d\n", filename, ierror);
                return ierror;
            }
            printf("%d convert to float: %f\n", i, fval);
            dval = tp_convertDouble(tp_handle,value, &ierror);
            if (ierror != 0) {
                printf("ERROR in tp_convertDouble file: %s ERROR CODE %d\n", filename, ierror);
                return ierror;
            }
            printf("%d convert to double: %lf\n", i, dval);
        } else if (type == TP_VECTOR_NUMERIC) {
	  ierror = tp_getNumberOfElements(tp_handle, value, &vector_number);
	  printf ("# of Elements %d\n",vector_number );
            if (ierror != 0) {
                printf("ERROR in tp_convertDouble file: %s ERROR CODE %d\n", filename, ierror);
                return ierror;
            }
            for (j = 0; j < vector_number; j++) {
                //val = MGPPSplitVector(value, j, &ierror); // 取れない
	      ierror=tp_getIthElement(tp_handle,value, j, val) ;
                if (ierror != 0) {
                    printf("ERROR in tp_getIthElement file: %s ERROR CODE %d\n", filename, ierror);
                    return ierror;
                }
                cval = tp_convertChar(tp_handle,val, &ierror);
                if (ierror != 0) {
                    printf("ERROR in tp_convertChar file: %s ERROR CODE %d\n", filename, ierror);
                    return ierror;
                }
                sval = tp_convertShort(tp_handle,val, &ierror);
                if (ierror != 0) {
                    printf("ERROR in tp_convertShort file: %s ERROR CODE %d\n", filename, ierror);
                    return ierror;
                }
                ival = tp_convertInt(tp_handle,val, &ierror);
                if (ierror != 0) {
                    printf("ERROR in tp_convertInt file: %s ERROR CODE %d\n", filename, ierror);
                    return ierror;
                }
                lval = tp_convertLong(tp_handle,val, &ierror);
                if (ierror != 0) {
                    printf("ERROR in tp_convertLong file: %s ERROR CODE %d\n", filename, ierror);
                    return ierror;
                }
                llval = tp_convertLongLong(tp_handle,val, &ierror);
                if (ierror != 0) {
                    printf("ERROR in tp_convertLongLong file: %s ERROR CODE %d\n", filename, ierror);
                    return ierror;
                }
                fval = tp_convertFloat(tp_handle,val, &ierror);
                if (ierror != 0) {
                    printf("ERROR in tp_convertFloat file: %s ERROR CODE %f\n", filename, ierror);
                    return ierror;
                }
                dval = tp_convertDouble(tp_handle,val, &ierror);
                if (ierror != 0) {
                    printf("ERROR in tp_convertDouble file: %s ERROR CODE %lf\n", filename, ierror);
                    return ierror;
                }
                printf("%d %s char %c short %d int %d long %ld long long %lld float %f double %lf\n",
                    j, val, cval, sval, ival, lval, llval, fval, dval);
            }

        } else if (type == TP_VECTOR_STRING) {
	  ierror = tp_getNumberOfElements(tp_handle, value,&vector_number);
            if (ierror != 0) {
                printf("ERROR in tp_getNumberOfElements file: %s ERROR CODE %d\n", filename, ierror);
                return ierror;
            }
            for (j = 0; j < vector_number; j++) {
	      ierror=tp_getIthElement(tp_handle, value, j, val);
                printf("%d %s\n", j, val);
	      if (ierror != 0) {
		printf("ERROR in tp_getIthElement file: %s ERROR CODE %d\n", filename, ierror);
		return ierror;
	      }
	      printf("%d %s\n", j, val);
            }
        }
    }

    // パラメータの削除
    ierror=tp_remove(tp_handle);
    if (ierror != 0) {
        printf("ERROR in tp_remove file: %s ERROR CODE %d\n", filename, ierror);
        return ierror;
    }

    printf("\n");

    //    ierror = tp_deleteInstance(tp_handle);
    //    if (ierror != 0) {
    //        printf("ERROR in tp_deleteInstance %s %d\n", filename, ierror);
    //        return ierror;
    //    }

    return 0;
}

int main(int argc, char* argv[])
{

    TP_HANDLE tp_handle;
    tp_handle = tp_createInstance();

    /* scan_all_parameters("Input0-1.txt"); */
    /* scan_all_parameters("Input1-1.txt"); */
    /* scan_all_parameters("Input4-1.txt"); */
    /* scan_all_parameters("Input4-2.txt"); */

    scan_all_parameters("./tpp_examples/correct_basic_1.txt",tp_handle);
    scan_all_parameters("./tpp_examples/correct_string_1.txt",tp_handle);
    scan_all_parameters("./tpp_examples/correct_label_2.txt",tp_handle);
    scan_all_parameters("./tpp_examples/correct_cond_10.txt",tp_handle);
    scan_all_parameters("./tpp_examples/correct_cond_9.txt",tp_handle);
    //    printf("end main\n");

    tp_deleteInstance(tp_handle);
    return 0;
}
