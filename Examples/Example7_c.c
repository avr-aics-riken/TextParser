/*
 * TextParser - Text Parsing Library
 *
 * Copyright (C) 2012-2014 Institute of Industrial Science, The University of Tokyo.
 * All rights reserved.
 *
 */

#include "TextParser.h"
#include <stdio.h>
#include <string.h>

int main(){


  TP_HANDLE tp_hand;
  int status;

  double from, to, step;
  char node[10];
  char label[10];
  char value[64];
  double expanded[100];
  int i;
  double check[6]={ 50.000000,57.000000,64.000000,
		    71.000000,78.000000,85.000000,};
  double check2[5]={ 19,0.4,-3,10.3,-3.0,};
  double check3[5]={-3,-3,0.4,10.3,19,};
  double check4[5]={19,10.3,0.4,-3,-3,};
  int check_count;

  tp_hand=tp_createInstance();
  status = tp_read(tp_hand,"./tpp_examples/correct_range_list_1.tpp");
  status = tp_write(tp_hand,"./ctest.tpp");

  status = tp_currentNode(tp_hand,node);
  printf("%d %s\n",status,node);
  status = tp_changeNode(tp_hand,"config");
  status = tp_currentNode(tp_hand,node);
  printf("%d %s\n",status,node);
  printf("%d %s\n",status,node);
  printf("before strcmp \n");
  strcpy(label,"gridx3");
  printf("after strcmp \n");
  printf("%s",label);
  status = tp_getValue(tp_hand,label,value);  
  printf("%s %s",label,value);
  printf("%s %s",label,value);

  status = tp_splitRange(tp_hand,value,&from,&to,&step);

  printf("%lf %lf %lf",from,to,step);

  if( (from == 50.) && (to==89.4) &&(step==7) ){
    printf(" splitRange OK!\n");
  } else {
    printf(" splitRange not OK!\n");
  }

  status = tp_expandRange(tp_hand,value,expanded);
  
  check_count=0;
  for(i=0;i<6;++i){
    printf("%d %lf \n",i, expanded[i]);
    if(check[i]!=expanded[i]){check_count++;}

  }
  if (check_count ==0){
    printf("expandRange good\n");
  } else {
    printf("expandRange failed\n");
  }



  status = tp_getValue(tp_hand,"gridx4",value);
  status = tp_splitList(tp_hand,value,expanded,0);

  check_count=0;
  for(i=0;i<5;++i){
    printf("%d %lf \n",i, expanded[i]);
    if(check2[i]!=expanded[i]){check_count++;}

  }
  if (check_count ==0){
    printf("expandList good\n");
  } else {
    printf("expandList failed\n");
  }

  status = tp_splitList(tp_hand,value,expanded,1);
  check_count=0;
  for(i=0;i<5;++i){
    printf("%d %lf \n",i, expanded[i]);
    if(check3[i]!=expanded[i]){check_count++;}

  }
  if (check_count ==0){
    printf("expandList good\n");
  } else {
    printf("expandList failed\n");
  }
  status = tp_splitList(tp_hand,value,expanded,2);
  check_count=0;
  for(i=0;i<5;++i){
    printf("%d %lf \n",i, expanded[i]);
    if(check4[i]!=expanded[i]){check_count++;}

  }
  if (check_count ==0){
    printf("expandList good\n");
  } else {
    printf("expandList failed\n");
  }


  tp_deleteInstance(tp_hand);

}
