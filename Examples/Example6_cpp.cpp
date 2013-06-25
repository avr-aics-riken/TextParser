#include <iostream>
#include <string>
#include <vector>
#include "TextParser.h"


int main(){
  TextParser* tp=new TextParser;
  std::string file;
  std::string label,value;
  int i;
  TextParserError error;
  TextParserValueType type;
  

file="./tpp_examples/correct_cond_1.txt";
 tp->read(file);
 label="/Average_operation/start_time";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);
 std::cout << file << std::endl;
 std::cout << label << " " << type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;
 tp->remove();

file="./tpp_examples/correct_cond_2.txt";

 tp->read(file);
 std::cout << file << std::endl;
 label="/Average_operation/start_time1";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);
 std::cout << label << " " << type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;

 label="/Average_operation/start_time2";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);
 std::cout << label << " " << type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;
 tp->remove();



file="./tpp_examples/correct_cond_3.txt";

 tp->read(file);
 std::cout << file << std::endl;
 label="/Average_operation/vector0";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);
 std::cout << label << " " << type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;

 label="/Average_operation/vector1";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);
 std::cout << label << " " << type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;
 tp->remove();


file="./tpp_examples/correct_cond_4.txt";

 tp->read(file);
 std::cout << file << std::endl;
 label="/Average_operation/vector0";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);
 std::cout << label << " " << type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;

 label="/Average_operation/vector1";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);
 std::cout << label << " " << type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;

 label="/Average_operation/vector2";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);
 std::cout << label << " " << type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;

 label="/Average_operation/vector3";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);
 std::cout << label << " " << type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;
 tp->remove();

file="./tpp_examples/correct_cond_5.txt";


 tp->read(file);
 std::cout << file << std::endl;
 label="/Average_operation/value0";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);
 std::cout << label << " " << type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;

 label="/Average_operation/value1";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);
 std::cout << label << " " << type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;

 tp->remove();

file="./tpp_examples/correct_cond_6.txt";
 tp->read(file);
 std::cout << file << std::endl;
 label="/Average_operation/value0";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);
 std::cout << label << " " << type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;

 label="/Average_operation/value1";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);
 std::cout << label << " " << type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;

 tp->remove();

file="./tpp_examples/correct_cond_7.txt";

 tp->read(file);
 label="/Average_operation/start_time";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);
 std::cout << file << std::endl;
 std::cout << label << " " << type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;
 tp->remove();

file="./tpp_examples/correct_cond_8.txt";

 tp->read(file);
 //----------------------------------
 label="/Average_operation/start_time";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);
 std::cout << file << std::endl;
 std::cout << label << " " << type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;
 //----------------------------------
 tp->remove();


file="./tpp_examples/correct_cond_9.txt";


 tp->read(file);
 //----------------------------------
   std::cout << file << std::endl;
 for(int j=0;j<16;j++){
   label="/Average_operation/Result[";
   std::stringstream ss;
   std::string number;
   ss << j ;
   ss>>number;
   label+=number;
   label+="]";
   std::cout << j << label << number <<std::endl;
   error = tp->getValue(label,value);
   type = tp->getType(label,&i);

   std::cout << label << " " << type <<std::endl;
   if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
   if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;

 }
 //----------------------------------
 // file="tmp.tpp";
 // tp->write(file,1);
 tp->remove();


 file="./tpp_examples/correct_cond_10.txt";
 std::cout << file << std::endl;
 tp->read(file);
 std::cout << file << std::endl;
 //----------------------------------
 label="/Average_operation/value0";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);
 std::cout << file << std::endl;
 std::cout << label << " " << type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;

 label="/Average_operation/value1";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);
 std::cout << file << std::endl;
 std::cout << label << " " << type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;
 //----------------------------------

 // file="tmp.tpp";
 // tp->write(file,1);
 tp->remove();


 file="./tpp_examples/correct_cond_11.txt";
 tp->read(file);
 //------------------------------------------------------------------------
 label="/Average_operation/switch3";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);
 std::cout << file << std::endl;

 std::cout << label << " " << value << " "<< type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;

 label="/Average_operation/switch4";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);
 std::cout << file << std::endl;

 std::cout << label << " " << value << " "<< type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;

 label="/Average_operation/result";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);
 std::cout << file << std::endl;
 std::cout << label << " " << value << " "<< type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;
 //------------------------------------------------------------------------
 tp->remove();

 file="./tpp_examples/correct_cond_12.txt";
 tp->read(file);
 std::cout << file << std::endl;
 //------------------------------------------------------------------------
 label="/Average_operation/switch3";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);

 std::cout << label << " " << value << " "<< type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;

 label="/Average_operation/switch4";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);

 std::cout << label << " " << value << " "<< type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;

 label="/Average_operation/result";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);

 std::cout << label << " " << value << " "<< type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;
 //------------------------------------------------------------------------
 tp->remove();



 file="./tpp_examples/correct_cond_13.txt";

 tp->read(file);
 std::cout << file << std::endl;
 //------------------------------------------------------------------------
 label="/Average_operation/Directory1/value0";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);

 std::cout << label << " " << value << " "<< type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;

 label="/Average_operation/Directory1/value1";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);

 std::cout << label << " " << value << " "<< type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;
 //------------------------------------------------------------------------
 tp->remove();



 file="./tpp_examples/correct_cond_14.txt";
 tp->read(file);
 //----------------------------------
 label="/Average_operation/start_time";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);
 std::cout << file << std::endl;
 std::cout << label << " " << value<<" "<<type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;
 //----------------------------------
 tp->remove();


 file="./tpp_examples/correct_cond_15.txt";
 tp->read(file);
 std::cout << file << std::endl;
 //----------------------------------
 label="/Average_operation/start_time1";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);
 std::cout << label << " " << value<<" "<<type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;

 label="/Average_operation/start_time2";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);
 std::cout << label << " " << value<<" "<<type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;
 //----------------------------------
 tp->remove();


 file="./tpp_examples/correct_cond_16.txt";
 tp->read(file);
 std::cout << file << std::endl;
 //----------------------------------
 label="/Average_operation/value0";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);
 std::cout << label << " " << value<<" "<<type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;

 label="/Average_operation/value1";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);
 std::cout << label << " " << value<<" "<<type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;
 //----------------------------------
 tp->remove();


 file="./tpp_examples/correct_cond_17.txt";
 tp->read(file);
 std::cout << file << std::endl;
 //----------------------------------
 label="/Average_operation/value0";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);
 std::cout << label << " " << value<<" "<<type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;

 label="/Average_operation/value1";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);
 std::cout << label << " " << value<<" "<<type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;
 //----------------------------------
 tp->remove();

 file="./tpp_examples/correct_cond_18.txt";
 tp->read(file);
 //----------------------------------
 label="/Average_operation/start_time";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);
 std::cout << file << std::endl;
 std::cout << label << " " << value<<" "<<type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;
 //----------------------------------
 tp->remove();

 file="./tpp_examples/correct_cond_19.txt";

 tp->read(file);
 //----------------------------------
   std::cout << file << std::endl;
 for(int j=0;j<16;j++){
   label="/Average_operation/Result[";
   std::stringstream ss;
   std::string number;
   ss << j ;
   ss>>number;
   label+=number;
   label+="]";
   std::cout << j << label << number <<std::endl;
   error = tp->getValue(label,value);
   type = tp->getType(label,&i);

   std::cout << label << " " << type <<std::endl;
   if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
   if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;

 }
 //----------------------------------
 // file="tmp.tpp";
 // tp->write(file,1);
 tp->remove();

 file="./tpp_examples/correct_cond_20.txt";

 tp->read(file);
 std::cout << file << std::endl;
 //------------------------------------------------------------------------
 label="/Average_operation/switch3";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);

 std::cout << label << " " << value << " "<< type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;

 label="/Average_operation/switch4";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);

 std::cout << label << " " << value << " "<< type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;

 label="/Average_operation/result";
 error = tp->getValue(label,value);
 type = tp->getType(label,&i);

 std::cout << label << " " << value << " "<< type <<std::endl;
 if(type==TP_UNDEFFINED_VALUE) std::cout << "!!! UNDEF !!!"<< std::endl;
 if(type==TP_VECTOR_UNDEFFINED) std::cout << "!!! Vector UNDEF !!!"<< std::endl;
 //------------------------------------------------------------------------
 tp->remove();

 return 0;
}
