/*
 * TextParser - Text Parsing Library
 *
 * Copyright (C) 2012-2015 Institute of Industrial Science, The University of Tokyo.
 * All rights reserved.
 *
 * Copyright (c) 2014-2016 Advanced Institute for Computational Science, RIKEN.
 * All rights reserved.
 *
 * Copyright (c) 2016-2017 Research Institute for Information Technology, Kyushu University.
 * All rights reserved.
 */

/* @file Example1_c.c
 * @retval 0-success / 1-fail
 */

#include <stdio.h>
#include <stdlib.h>
#include "TextParser.h"

int read_write_parameters(char *ifilename, char *ofilename)
{
    int stat = 0;

    TP_HANDLE tp_ptr=tp_createInstance();

    // ファイルの読み込み
    printf(">>> Reading file(%s)\n", ifilename);
    stat=tp_read(tp_ptr,ifilename);
    if (stat == 0) {
        printf("# Successful completion of reading a file : %s\n", ifilename);
        // パラメータ書き出し
        stat=tp_write(tp_ptr,ofilename);
        if (stat == 0) {
            printf("# Successful completion of writing a file : %s\n", ofilename);
        } else {
            printf("# Error occurs during writing a file : C%d\n", stat);
            tp_deleteInstance(tp_ptr);
            return 1;
        }
    } else {
        printf("# Error occurs during reading a file : C%d\n", stat);
        tp_deleteInstance(tp_ptr);
        return 1;
    }


    //
    //tp_remove(&stat);
    tp_remove(tp_ptr);
    if (stat == 0) {
        printf("# Successful completion of deleting a Data base.\n");
    } else {
        printf("# Error occurs during deleting a Data base : C%d\n", stat);
        tp_deleteInstance(tp_ptr);
        return 1;
    }
    printf("\n");
    tp_deleteInstance(tp_ptr);

  return 0;
}

int main(int argc, char* argv[])
{
  //  TP_HANDLE tp_ptr=tp_getInstanceSingleton();
  //    TP_HANDLE tp_ptr=tp_createInstance();

    if ( read_write_parameters("./tpp_examples/correct_basic_1.txt",
			  "./tpp_examples/correct_basic_1_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_basic_2.txt",
			  "./tpp_examples/correct_basic_2_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_basic_3.txt",
			  "./tpp_examples/correct_basic_3_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_basic_4.txt",
			  "./tpp_examples/correct_basic_4_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_basic_5.txt",
			  "./tpp_examples/correct_basic_5_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_basic_6.txt",
			  "./tpp_examples/correct_basic_6_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_basic_7.txt",
			  "./tpp_examples/correct_basic_7_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_basic_8.txt",
			  "./tpp_examples/correct_basic_8_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_basic_9.txt",
			  "./tpp_examples/correct_basic_9_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_basic_10.txt",
			  "./tpp_examples/correct_basic_10_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_basic_11.txt",
			  "./tpp_examples/correct_basic_11_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_basic_12.txt",
			  "./tpp_examples/correct_basic_12_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_basic_13.txt",
			  "./tpp_examples/correct_basic_13_out.txt") ) return 1;

    if ( read_write_parameters("./tpp_examples/correct_string_1.txt",
			  "./tpp_examples/correct_string_1_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_string_2.txt",
			  "./tpp_examples/correct_string_2_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_string_3.txt",
			  "./tpp_examples/correct_string_3_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_string_4.txt",
			  "./tpp_examples/correct_string_4_out.txt") ) return 1;

    if ( read_write_parameters("./tpp_examples/correct_label_1.txt",
			  "./tpp_examples/correct_label_1_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_label_2.txt",
			  "./tpp_examples/correct_label_2_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_label_3.txt",
			  "./tpp_examples/correct_label_3_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_label_4.txt",
			  "./tpp_examples/correct_label_4_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_label_5.txt",
			  "./tpp_examples/correct_label_5_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_label_6.txt",
			  "./tpp_examples/correct_label_6_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_label_7.txt",
			  "./tpp_examples/correct_label_7_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_label_8.txt",
			  "./tpp_examples/correct_label_8_out.txt") ) return 1;

    if ( read_write_parameters("./tpp_examples/correct_cond_1.txt",
			  "./tpp_examples/correct_cond_1_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_cond_2.txt",
			  "./tpp_examples/correct_cond_2_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_cond_3.txt",
			  "./tpp_examples/correct_cond_3_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_cond_4.txt",
			  "./tpp_examples/correct_cond_4_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_cond_5.txt",
			  "./tpp_examples/correct_cond_5_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_cond_6.txt",
			  "./tpp_examples/correct_cond_6_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_cond_7.txt",
			  "./tpp_examples/correct_cond_7_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_cond_8.txt",
			  "./tpp_examples/correct_cond_8_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_cond_9.txt",
			  "./tpp_examples/correct_cond_9_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_cond_10.txt",
			  "./tpp_examples/correct_cond_10_out.txt") ) return 1;

    if ( read_write_parameters("./tpp_examples/correct_cond_11.txt",
			  "./tpp_examples/correct_cond_11_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_cond_12.txt",
			  "./tpp_examples/correct_cond_12_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_cond_13.txt",
			  "./tpp_examples/correct_cond_13_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_cond_14.txt",
			  "./tpp_examples/correct_cond_14_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_cond_15.txt",
			  "./tpp_examples/correct_cond_15_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_cond_16.txt",
			  "./tpp_examples/correct_cond_16_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_cond_17.txt",
			  "./tpp_examples/correct_cond_17_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_cond_18.txt",
			  "./tpp_examples/correct_cond_18_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_cond_19.txt",
			  "./tpp_examples/correct_cond_19_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_cond_20.txt",
			  "./tpp_examples/correct_cond_20_out.txt") ) return 1;

    if ( read_write_parameters("./tpp_examples/correct_labelarray_1.txt",
			  "./tpp_examples/correct_labelarray_1_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_labelarray_2.txt",
			  "./tpp_examples/correct_labelarray_2_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_labelarray_3.txt",
			  "./tpp_examples/correct_labelarray_3_out.txt") ) return 1;
    if ( read_write_parameters("./tpp_examples/correct_labelarray_4.txt",
			  "./tpp_examples/correct_labelarray_4_out.txt") ) return 1;

    return 0; // success
}
