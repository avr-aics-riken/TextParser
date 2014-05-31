/*
 * TextParser - Text Parsing Library
 *
 * Copyright (C) 2012-2014 Institute of Industrial Science, The University of Tokyo.
 * All rights reserved.
 *
 * Copyright (c) 2014 Advanced Institute for Computational Science, RIKEN.
 * All rights reserved.
 */

#include <iostream>
#include <string>
#include <vector>
#include "TextParser.h"

int main(int argc, char** argv){

  std::string filename = "tpp_examples/correct_range_list_1.tpp";

  TextParser* tp=TextParser::get_instance_singleton();
  tp->read(filename);
  filename="test.tpp"; //check this file to be sure.
  tp->write(filename);

  tp->changeNode("config");
  
  std::string label="gridx1";
  std::string value;
  int ierror;
  TextParserValueType vtype ;
  std::vector<double> expand;

  tp->getValue(label,value);
  std::cout << "label "<< label 
	    << " value " << value ;
  vtype = tp->getType(label,&ierror);
  std::cout << " type "<< vtype <<std::endl;

  double from,to,step;
  double a_from = 0;
  double a_to = 5;
  double a_step = 1;
  
  tp->splitRange(value,&from,&to,&step);
  std::cout << "from "<< from
	    << " to "<< to
	    << " step "<< step <<std::endl;
  if (a_from==from) std::cout << "from is correct." <<std::endl;
  if (a_to==to) std::cout << "to is correct." <<std::endl;
  if (a_step==step) std::cout << "step is correct." <<std::endl;
  int errorcount=0;
  double answer[6]={0,1,2,3,4,5};
  tp->expandRange(value,expand);
  for(int i=0;i<expand.size();++i){
    std::cout << i <<" "<<expand[i] << " "<< answer[i] <<std::endl;
    if(expand[i]!=answer[i]) errorcount++;
  }
  if(errorcount!=0){ std::cout << "not good"<<std::endl;}
  else {std::cout << " good"<<std::endl;}


  label="gridx2";
  tp->getValue(label,value);
  std::cout << "label "<< label 
	    << " value " << value ;
  vtype = tp->getType(label,&ierror);
  std::cout << " type "<< vtype <<std::endl;

  a_from = 5;
  a_to = 0;
  a_step = -1;

  tp->splitRange(value,&from,&to,&step);
  std::cout << "from "<< from
	    << " to "<< to
	    << " step "<< step <<std::endl;
  if (a_from==from) std::cout << "from is correct." <<std::endl;
  if (a_to==to) std::cout << "to is correct." <<std::endl;
  if (a_step==step) std::cout << "step is correct." <<std::endl;

  tp->expandRange(value,expand);

  errorcount=0;
  double answer2[6]={5,4,3,2,1,0};

  for(int i=0;i<expand.size();++i){
    std::cout << i <<" "<<expand[i] << " "<< answer2[i] <<std::endl;
    //    std::cout << i <<" "<<expand[i] <<std::endl;
    if(expand[i]!=answer2[i]) errorcount++;
  }
  if(errorcount!=0){ std::cout << "not good"<<std::endl;}
  else {std::cout << " good"<<std::endl;}

  label="gridx3";
  tp->getValue(label,value);
  std::cout << "label "<< label 
	    << " value " << value ;
  vtype = tp->getType(label,&ierror);
  std::cout << " type "<< vtype <<std::endl;
  

  tp->splitRange(value,&from,&to,&step);
  std::cout << "from "<< from
	    << " to "<< to
	    << " step "<< step <<std::endl;
  tp->expandRange(value,expand);
  double test[3] ={50,89.4,7};
  double test2[6] = {50, 57, 64, 71, 78, 85};
  errorcount=0;
  for(int i=0;i<expand.size();++i){
    std::cout << i <<" "<<expand[i] <<" "<< test2[i]<<std::endl;
    if(expand[i]!=test2[i]) errorcount++;
  }
  //  std::cout << "should be (50,89,4,7)"<<std::endl;
  if(errorcount!=0){ std::cout << "not good"<<std::endl;}
  else {std::cout << " good"<<std::endl;}

  label="gridx31";
  tp->getValue(label,value);
  std::cout << "label "<< label 
	    << " value " << value ;
  vtype = tp->getType(label,&ierror);
  std::cout << " type "<< vtype <<std::endl;

  tp->splitRange(value,&from,&to,&step);
  std::cout << "from "<< from
	    << " to "<< to
	    << " step "<< step <<std::endl;
  tp->expandRange(value,expand);

  double answer3[6];
  for(int i=0;i<6;++i)answer3[i]=from+i*step;
      
  errorcount=0;

  for(int i=0;i<expand.size();++i){
    std::cout << i <<" "<<expand[i] <<" "<<answer3[i] <<std::endl;
    if(expand[i]!=answer3[i]){
      errorcount++;
      std::cout <<i<< "not good"<<std::endl;
    }  
  }
  if(errorcount!=0){ std::cout << "not good"<<std::endl;}
  else {std::cout << " good"<<std::endl;}

  label="gridx32";
  tp->getValue(label,value);
  std::cout << "label "<< label 

	    << " value " << value ;
  vtype = tp->getType(label,&ierror);
  std::cout << " type "<< vtype <<std::endl;

  tp->splitRange(value,&from,&to,&step);
  std::cout << "from "<< from
	    << " to "<< to
	    << " step "<< step <<std::endl;
  tp->expandRange(value,expand);
  double answer4[6];
  for(int i=0;i<6;++i)answer4[i]=from+i*step;

  errorcount=0;

  for(int i=0;i<expand.size();++i){
    std::cout << i <<" "<<expand[i] <<std::endl;
    if(expand[i]!=answer4[i]) errorcount++;
  }
  if(errorcount!=0){ std::cout << "not good"<<std::endl;}
  else {std::cout << " good"<<std::endl;}

  label="gridx33";
  tp->getValue(label,value);
  std::cout << "label "<< label 
	    << " value " << value ;
  vtype = tp->getType(label,&ierror);
  std::cout << " type "<< vtype <<std::endl;

  tp->splitRange(value,&from,&to,&step);
  std::cout << "from "<< from
	    << " to "<< to
	    << " step "<< step <<std::endl;
  double answer5[6];
  for(int i=0;i<6;++i)answer5[i]=from+i*step;
  errorcount=0;

  tp->expandRange(value,expand);
  for(int i=0;i<expand.size();++i){
    std::cout << i <<" "<<expand[i] <<std::endl;
    if(expand[i]!=answer5[i]) errorcount++;
  }
  if(errorcount!=0){ std::cout << "not good"<<std::endl;}
  else {std::cout << " good"<<std::endl;}

  label="gridx34";
  tp->getValue(label,value);
  std::cout << "label "<< label 
	    << " value " << value ;
  vtype = tp->getType(label,&ierror);
  std::cout << " type "<< vtype <<std::endl;

  tp->splitRange(value,&from,&to,&step);
  std::cout << "from "<< from
	    << " to "<< to
	    << " step "<< step <<std::endl;
  tp->expandRange(value,expand);
  double answer6[6];
  for(int i=0;i<6;++i)answer6[i]=from+i*step;

  errorcount=0;

  for(int i=0;i<expand.size();++i){
    std::cout << i <<" "<<expand[i] <<std::endl;
    if(expand[i]!=answer6[i]) errorcount++;
  }
  if(errorcount!=0){ std::cout << "not good"<<std::endl;}
  else {std::cout << " good"<<std::endl;}

  label="gridx4";
  tp->getValue(label,value);
  std::cout << "label "<< label 
	    << " value " << value ;
  vtype = tp->getType(label,&ierror);
  std::cout << " type "<< vtype <<std::endl;

  tp->splitList(value,expand);
  double test3[5]={ 19, .4, -3, 10.3, -3,};
  errorcount=0;
  for(int i=0;i<expand.size();++i){
    std::cout << i <<" "<<expand[i]<<" "<<test3[i]<<std::endl;
    if( expand[i]!=test3[i]) errorcount++;
  }
  if(errorcount!=0){ std::cout << "not good"<<std::endl;}
  else {std::cout << " good"<<std::endl;}

  tp->splitList(value,expand,TP_SORT_NONE);

  errorcount=0;
  for(int i=0;i<expand.size();++i){
    std::cout << i <<" "<<expand[i] << " "<< test3[i]<<std::endl;
    //    std::cout << i <<" "<<expand[i] <<std::endl;
    if( expand[i]!=test3[i]) errorcount++;
  }
  if(errorcount!=0){ std::cout << "not good"<<std::endl;}
  else {std::cout << " good"<<std::endl;}

  tp->splitList(value,expand,TP_SORT_ASCENDING);
  double test4[5]={ -3,-3, .4, 10.3, 19,};
  errorcount=0;
  for(int i=0;i<expand.size();++i){
    std::cout << i <<" "<<expand[i] << " "<<test4[i]<<std::endl;
    //    std::cout << i <<" "<<expand[i] <<std::endl;
    if( expand[i]!=test4[i]) errorcount++;
  }
  if(errorcount!=0){ std::cout << "not good"<<std::endl;}
  else {std::cout << " good"<<std::endl;}


  tp->splitList(value,expand,TP_SORT_DESCENDING);
  double test5[5]={19,10.3,0.4,-3,-3};
  errorcount=0;

  for(int i=0;i<expand.size();++i){
    std::cout << i <<" "<<expand[i] << " "<<test5[i]<<std::endl;
    //    std::cout << i <<" "<<expand[i] <<std::endl;
    if( expand[i]!=test5[i]) errorcount++;
  }
  if(errorcount!=0){ std::cout << "not good"<<std::endl;}
  else {std::cout << " good"<<std::endl;}


  // char
  label="test_char_min";
  tp->getValue(label,value);
  std::cout << "label "<< label 
	    << " value " << value ;
  vtype = tp->getType(label,&ierror);
  std::cout << " type "<< vtype ;
  char tmpchar =  tp->convertChar(value,&ierror);
  long long tmpcharint =  tp->convertChar(value,&ierror);
  std::cout << " converted "<< tmpchar ;
  std::cout << " converted "<< tmpcharint <<std::endl;  
  //  std::cout << " converted "<< tmpchar <<std::endl;  

  label="test_char_max";
  tp->getValue(label,value);
  std::cout << "label "<< label 
	    << " value " << value ;
  vtype = tp->getType(label,&ierror);
  std::cout << " type "<< vtype ;
  tmpchar =  tp->convertChar(value,&ierror);
   tmpcharint =  tp->convertChar(value,&ierror);
   std::cout << " converted "<< tmpchar ;
   std::cout << " converted "<< tmpcharint <<std::endl;  
   //  std::cout << " converted "<< tmpchar <<std::endl;  

  // short
  label="test_short_min";
  tp->getValue(label,value);
  std::cout << "label "<< label 
	    << " value " << value ;
  vtype = tp->getType(label,&ierror);
  std::cout << " type "<< vtype ;
  short tmpshort =  tp->convertShort(value,&ierror);
  // tmpcharint =  tp->convertShort(value,&ierror);
  // std::cout << " converted "<< tmpshort ;
  // std::cout << " converted "<< tmpcharint <<std::endl;  
  std::cout << " converted "<< tmpshort <<std::endl;  

  label="test_short_max";
  tp->getValue(label,value);
  std::cout << "label "<< label 
	    << " value " << value ;
  vtype = tp->getType(label,&ierror);
  std::cout << " type "<< vtype ;
  tmpshort =  tp->convertShort(value,&ierror);
  // tmpcharint =  tp->convertShort(value,&ierror);
  // std::cout << " converted "<< tmpshort ;
  // std::cout << " converted "<< tmpcharint <<std::endl;  
  std::cout << " converted "<< tmpshort <<std::endl;  


  // int  
  label="test_int_min";
  tp->getValue(label,value);
  std::cout << "label "<< label 
	    << " value " << value ;
  vtype = tp->getType(label,&ierror);
  std::cout << " type "<< vtype ;
  int tmpint  =  tp->convertInt(value,&ierror);
  // tmpcharint =  tp->convertInt(value,&ierror);
  // std::cout << " converted "<< tmpint ;
  // std::cout << " converted "<< tmpcharint <<std::endl;  
  std::cout << " converted "<< tmpint <<std::endl;  

  label="test_int_max";
  tp->getValue(label,value);
  std::cout << "label "<< label 
	    << " value " << value ;
  vtype = tp->getType(label,&ierror);
  std::cout << " type "<< vtype ;
  tmpint =  tp->convertInt(value,&ierror);
  // tmpcharint =  tp->convertInt(value,&ierror);
  // std::cout << " converted "<< tmpint ;
  // std::cout << " converted "<< tmpcharint <<std::endl;  
  std::cout << " converted "<< tmpint <<std::endl;  

  // long
  label="test_long_min";
  tp->getValue(label,value);
  std::cout << "label "<< label 
	    << " value " << value ;
  vtype = tp->getType(label,&ierror);
  std::cout << " type "<< vtype ;
  long tmplong =  tp->convertLong(value,&ierror);
  // tmpcharint =  tp->convertLong(value,&ierror);
  // std::cout << " converted "<< tmplong ;
  // std::cout << " converted "<< tmpcharint <<std::endl;  
  std::cout << " converted "<< tmplong <<std::endl;  

  label="test_long_max";
  tp->getValue(label,value);
  std::cout << "label "<< label 
	    << " value " << value ;
  vtype = tp->getType(label,&ierror);
  std::cout << " type "<< vtype ;
  tmplong =  tp->convertLong(value,&ierror);
  // tmpcharint =  tp->convertLong(value,&ierror);
  // std::cout << " converted "<< tmplong ;
  // std::cout << " converted "<< tmpcharint <<std::endl;  
  std::cout << " converted "<< tmplong <<std::endl;  

  // long long
  label="test_longlong_min";
  tp->getValue(label,value);
  std::cout << "label "<< label 
	    << " value " << value ;
  vtype = tp->getType(label,&ierror);
  std::cout << " type "<< vtype ;
  long long tmplonglong =  tp->convertLongLong(value,&ierror);
  // tmpcharint =  tp->convertLongLong(value,&ierror);
  // std::cout << " converted "<< tmplonglong ;
  // std::cout << " converted "<< tmpcharint <<std::endl;  
  std::cout << " converted "<< tmplonglong <<std::endl;

  label="test_longlong_max";
  tp->getValue(label,value);
  std::cout << "label "<< label 
	    << " value " << value ;
  vtype = tp->getType(label,&ierror);
  std::cout << " type "<< vtype ;
  tmplonglong =  tp->convertLongLong(value,&ierror);
  // tmpcharint =  tp->convertLongLong(value,&ierror);
  // std::cout << " converted "<< tmplonglong ;
  // std::cout << " converted "<< tmpcharint <<std::endl; 
  std::cout << " converted "<< tmplonglong <<std::endl;



  // float
  label="test_float_min";
  tp->getValue(label,value);
  std::cout << "label "<< label 
	    << " value " << value ;
  vtype = tp->getType(label,&ierror);
  std::cout << " type "<< vtype ;
  float tmpfloat = tp->convertFloat(value,&ierror);
  std::cout << " converted "<< tmpfloat <<std::endl;

  label="test_float_max";
  tp->getValue(label,value);
  std::cout << "label "<< label 
	    << " value " << value ;
  vtype = tp->getType(label,&ierror);
  std::cout << " type "<< vtype ;
  tmpfloat = tp->convertFloat(value,&ierror);
  std::cout << " converted "<< tmpfloat <<std::endl;


  // double
  label="test_double_min";
  tp->getValue(label,value);
  std::cout << "label "<< label 
	    << " value " << value ;
  vtype = tp->getType(label,&ierror);
  std::cout << " type "<< vtype ;
  double tmpdouble = tp->convertDouble(value,&ierror);
  std::cout << " converted "<< tmpdouble <<std::endl;

  label="test_double_max";
  tp->getValue(label,value);
  std::cout << "label "<< label 
	    << " value " << value ;
  vtype = tp->getType(label,&ierror);
  std::cout << " type "<< vtype ;
  tmpdouble = tp->convertDouble(value,&ierror);
  std::cout << " converted "<< tmpdouble <<std::endl;


  std::vector<std::string> svec;
  label="minivec";
  tp->getValue(label,value);
  std::cout << "label "<< label 
	    << " value " << value ;
  vtype = tp->getType(label,&ierror);
  std::cout << " type "<< vtype ;
  tp->splitVector(value,svec);
  std::cout << "( ";
  for(int i=0;i<svec.size();++i){
    tmplonglong =  tp->convertLongLong(svec[i],&ierror);    
    std::cout << tmplonglong<<",";
  }
  std::cout << ")" <<std::endl;
  svec.clear();

  label="maxivec";
  tp->getValue(label,value);
  std::cout << "label "<< label 
	    << " value " << value ;
  vtype = tp->getType(label,&ierror);
  std::cout << " type "<< vtype ;
  tp->splitVector(value,svec);
  std::cout << "( ";
  for(int i=0;i<svec.size();++i){
    tmplonglong =  tp->convertLongLong(svec[i],&ierror);    
    std::cout << tmplonglong<<",";
  }
  std::cout << ")" <<std::endl;
  svec.clear();

  //minfvec
  label="minfvec";
  tp->getValue(label,value);
  std::cout << "label "<< label 
	    << " value " << value ;
  vtype = tp->getType(label,&ierror);
  std::cout << " type "<< vtype ;
  tp->splitVector(value,svec);
  std::cout << "( ";
  for(int i=0;i<svec.size();++i){
    tmpdouble =  tp->convertDouble(svec[i],&ierror);    
    std::cout << tmpdouble<<",";
  }
  std::cout << ")" <<std::endl;
  svec.clear();

  //maxfvec
  label="maxfvec";
  tp->getValue(label,value);
  std::cout << "label "<< label 
	    << " value " << value ;
  vtype = tp->getType(label,&ierror);
  std::cout << " type "<< vtype ;
  tp->splitVector(value,svec);
  std::cout << "( ";
  for(int i=0;i<svec.size();++i){
    tmpdouble =  tp->convertDouble(svec[i],&ierror);    
    std::cout << tmpdouble<<",";
  }
  std::cout << ")" <<std::endl;
  svec.clear();

  //  limit_grid_range 

  label="limit_grid_range";
  tp->getValue(label,value);
  std::cout << "label "<< label 
	    << " value " << value ;
  vtype = tp->getType(label,&ierror);
  std::cout << " type "<< vtype ;

  tp->splitRange(value,&from,&to,&step);
  std::cout << "from "<< from
	    << " to "<< to
	    << " step "<< step <<std::endl;
  if(from==std::numeric_limits<double>::min()) std::cout << "from is correct."<<std::endl;
  if(to==std::numeric_limits<double>::max()) std::cout << "to is correct."<<std::endl;
  if(step==std::numeric_limits<double>::min()) std::cout << "step is correct."<<std::endl;

  //  limit_grid_list 

  label="limit_grid_list";
  tp->getValue(label,value);
  std::cout << "label "<< label 
	    << " value " << value ;
  vtype = tp->getType(label,&ierror);
  std::cout << " type "<< vtype <<std::endl;
  std::vector<double> limit_list;

  tp->splitList(value,limit_list);

  if(limit_list[0]==std::numeric_limits<double>::min()) 
    std::cout << "list id 0  is correct."<<std::endl;
  if(limit_list[1]==std::numeric_limits<float>::min()) 
    std::cout << "list id 1  is correct."<<std::endl;
  if(limit_list[2]==std::numeric_limits<double>::max()) 
    std::cout << "list id 2  is correct."<<std::endl;
  if(limit_list[3]==std::numeric_limits<char>::min()) 
    std::cout << "list id 2  is correct."<<std::endl;

  return 0;
}
