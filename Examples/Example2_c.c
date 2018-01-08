/*
 * TextParser - Text Parsing Library
 *
 * Copyright (C) 2012-2015 Institute of Industrial Science, The University of Tokyo.
 * All rights reserved.
 *
 * Copyright (c) 2014-2016 Advanced Institute for Computational Science, RIKEN.
 * All rights reserved.
 *
 * Copyright (c) 2016-2018 Research Institute for Information Technology, Kyushu University.
 * All rights reserved.
 *
 */

/** @file Example2_c.c
 *  @retval 0-success / 1-fail
 */

#include <stdio.h>
#include <stdlib.h>
#include "TextParser.h"

int read_parameters(TP_HANDLE tp_handle,char *ifilename, char *ofilename)
{
    int stat = 0;

    // ファイルの読み込み
    printf(">>> Reading file(%s)\n", ifilename);
    stat=tp_read(tp_handle,ifilename);
    if (stat == 0) {
        printf("# Successful completion of reading a file : %s\n", ifilename);
    } else {
        printf("# Error occurs during reading a file : C%d\n", stat);
        return 1;
    }


    //
    stat=tp_remove(tp_handle);
    if (stat == 0) {
        printf("# Successful completion of deleting a Data base.\n");
    } else {
        printf("# Error occurs during deleting a Data base : C%d\n", stat);
        return 1;
    }
    printf("\n");
    return 0;
}

int main(int argc, char* argv[])
{
  TP_HANDLE tp_handle=tp_getInstanceSingleton();

  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_basic_1.txt",
		    "./tpp_examples/incorrect_basic_1_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_basic_2.txt",
		    "./tpp_examples/incorrect_basic_2_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_basic_3.txt",
		    "./tpp_examples/incorrect_basic_3_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_basic_4.txt",
		    "./tpp_examples/incorrect_basic_4_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_basic_5.txt",
		    "./tpp_examples/incorrect_basic_5_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_basic_6.txt",
		    "./tpp_examples/incorrect_basic_6_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_basic_7.txt",
		    "./tpp_examples/incorrect_basic_7_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_basic_8.txt",
		    "./tpp_examples/incorrect_basic_8_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_basic_9.txt",
		    "./tpp_examples/incorrect_basic_9_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_basic_10.txt",
		    "./tpp_examples/incorrect_basic_10_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_basic_11.txt",
		    "./tpp_examples/incorrect_basic_11_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_basic_12.txt",
		    "./tpp_examples/incorrect_basic_12_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_basic_13.txt",
		    "./tpp_examples/incorrect_basic_13_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_basic_14.txt",
		    "./tpp_examples/incorrect_basic_14_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_basic_15.txt",
		    "./tpp_examples/incorrect_basic_15_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_basic_16.txt",
		    "./tpp_examples/incorrect_basic_16_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_basic_17.txt",
		    "./tpp_examples/incorrect_basic_17_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_basic_18.txt",
		    "./tpp_examples/incorrect_basic_18_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_basic_19.txt",
		    "./tpp_examples/incorrect_basic_19_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_cond_1.txt",
		    "./tpp_examples/incorrect_cond_1_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_cond_2.txt",
		    "./tpp_examples/incorrect_cond_2_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_cond_3.txt",
		    "./tpp_examples/incorrect_cond_3_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_cond_4.txt",
		    "./tpp_examples/incorrect_cond_4_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_cond_5.txt",
		    "./tpp_examples/incorrect_cond_5_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_label_1.txt",
		    "./tpp_examples/incorrect_label_1_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_label_2.txt",
		    "./tpp_examples/incorrect_label_2_out.txt") ) return 1;
    //    read_parameters(tp_handle,"./tpp_examples/incorrect_label_3.txt",
    //    "./tpp_examples/incorrect_label_3_out.txt");
    //    read_parameters(tp_handle,"./tpp_examples/incorrect_label_4.txt",
    //    "./tpp_examples/incorrect_label_4_out.txt");
    //    read_parameters(tp_handle,"./tpp_examples/incorrect_label_5.txt",
    //    "./tpp_examples/incorrect_label_5_out.txt");
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_label_6.txt",
		    "./tpp_examples/incorrect_label_6_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_label_7.txt",
		    "./tpp_examples/incorrect_label_7_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_label_8.txt",
		    "./tpp_examples/incorrect_label_8_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_label_9.txt",
		    "./tpp_examples/incorrect_label_9_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_label_10.txt",
		    "./tpp_examples/incorrect_label_10_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_label_11.txt",
		    "./tpp_examples/incorrect_label_11_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_label_12.txt",
		    "./tpp_examples/incorrect_label_12_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_label_13.txt",
		    "./tpp_examples/incorrect_label_13_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_label_14.txt",
		    "./tpp_examples/incorrect_label_14_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_label_15.txt",
		    "./tpp_examples/incorrect_label_15_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_label_16.txt",
		    "./tpp_examples/incorrect_label_16_out.txt") ) return 1;
    //    read_parameters(tp_handle,"./tpp_examples/incorrect_label_17.txt",
    //    "./tpp_examples/incorrect_label_17_out.txt");
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_labelarray_1.txt",
		    "./tpp_examples/incorrect_labelarray_1_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_labelarray_2.txt",
		    "./tpp_examples/incorrect_labelarray_2_out.txt") ) return 1;
  if ( read_parameters(tp_handle,"./tpp_examples/incorrect_labelarray_3.txt",
		    "./tpp_examples/incorrect_labelarray_3_out.txt") ) return 1;

    return 0;
}
