#include "TextParser.h"

int main(){


  TP_HANDLE tp_hand;
  int status;
  tp_hand=tp_createInstance();

 status = tp_read(tp_hand,"./tpp_examples/correct_label_4.txt");
 
 status = tp_updateValue(tp_hand,"/foo/qux/baz","10");
 status = tp_deleteLeaf(tp_hand,"/foo/qux/baz1");
 status = tp_changeNode(tp_hand,"/foo");
 status = tp_createLeaf(tp_hand,"cdf","\"filename\"");

 status =  tp_write(tp_hand,"tmp_c.tpp");


 tp_deleteInstance(tp_hand);

}
