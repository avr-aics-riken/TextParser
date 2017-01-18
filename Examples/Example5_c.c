/*
 * TextParser - Text Parsing Library
 *
 * Copyright (C) 2012-2015 Institute of Industrial Science, The University of Tokyo.
 * All rights reserved.
 *
 * Copyright (c) 2014-2016 Advanced Institute for Computational Science, RIKEN.
 * All rights reserved.
 */

/* @file Example5_c.c
 * @retval 0-success / 1-fail
 */

#include "TextParser.h"

int main(){

  TP_HANDLE tp_hand;
  int st, status=0;

  tp_hand=tp_createInstance();

  st = tp_read(tp_hand, "./tpp_examples/correct_label_4.txt");
  status += st;

  st = tp_updateValue(tp_hand, "foo/qux/baz","10");
  status += st;

  st = tp_deleteLeaf(tp_hand, "foo/qux/baz1");
  status += st;

  st = tp_changeNode(tp_hand, "foo");
  status += st;

  st = tp_createLeaf(tp_hand, "cdf","\"filename\"");
  status += st;

  st =  tp_write(tp_hand, "tmp_c.tpp");
  status += st;

  tp_deleteInstance(tp_hand);

  return (status==0)?0:1;
}
