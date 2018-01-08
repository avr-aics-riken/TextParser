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

 /* @file Example8_cpp.cpp
  * @retval 0-success / 1-fail
  */

#include <iostream>
#include <string>
#include <vector>
#include "TextParser.h"

int main(int argc, char** argv){


    std::string filename;
    int status =0;

    TextParser* tp=TextParser::get_instance_singleton();
    //すべてパースエラー
    filename = "tpp_examples/incorrect_range_1.tpp";
    TextParserError error = tp->read(filename);
    if(error!=TP_NO_ERROR) {
      std::cout<< "tpp file parse error file="<<filename<<std::endl;
      status++;
    }

    filename = "tpp_examples/incorrect_range_2.tpp";
    error=tp->read(filename);
    if(error!=TP_NO_ERROR) {
      std::cout<< "tpp file parse error file="<<filename<<std::endl;
      status++;
    }

    filename = "tpp_examples/incorrect_range_3.tpp";
    error=  tp->read(filename);
    if(error!=TP_NO_ERROR) {
      std::cout<< "tpp file parse error file="<<filename<<std::endl;
      status++;
    }

    filename = "tpp_examples/incorrect_list_1.tpp";
    error=tp->read(filename);
    if(error!=TP_NO_ERROR) {
      std::cout<< "tpp file parse error file="<<filename<<std::endl;
      status++;
    }


    return (status==0)?0:1;
}
