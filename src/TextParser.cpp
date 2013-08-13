/*
 * TextParser - Text Parsing Library
 *
 * Copyright (C) 2012-2013 Institute of Industrial Science, The University of Tokyo.
 * All rights reserved.
 *
 *

/** @file TextParser.cpp
 * ここには TextParser クラスと
 * C言語用APIが実装されています。
 *
 */

#ifdef HAVE_CONFIG_H
#include "../config.h"
#endif //HAVE_CONFIG_H



#ifdef ENABLE_MPI 
#ifdef BUILD_MPI
#include "mpi.h"
// nothig to do ...
#endif
#else
#endif

#include <regex.h>
#include <string.h>
#include "TextParser.h"
#include "TextParserTree.h"
#include "TextParserElement.h"


/** 
 * tree の status をよびだします。
 *
 * 
 * 
 */

void TextParser::status(){dataTree()->status();}
/** 
 * プロセス内唯一の TextParser インスタンスを返します。
 *
 * @return TextParser インスタンスのアドレス
 * 
 */

//TextParser* TextParser::get_instance(){
TextParser* TextParser::get_instance_singleton(){
#ifdef MYDEBUG
  TP_DBGOSH<< "TextParser::get_instance() called."<<std::endl;
#endif
  static TextParser instance;
  return &instance;
}

/** 
 * デフォルトコンストラクタで、
 * パラメータのデータ構造 TextParserTree へのインスタンスを取得します。
 *
 *
 */
TextParser::TextParser(){
   _data_tree=new TextParserTree;
   _data_tree->set_owner(this);
  //  TP_DBGOSH << __FUNCTION__ << " dataTree()=" <<dataTree() << std::endl;
}

/**  
 * デストラクタ. TextParserTreeのインスタンスを破棄します。
 *
 */

TextParser::~TextParser(){
  if( dataTree()!=0) remove();
  delete _data_tree;
  _data_tree=0;
}

/** 指定されたパラメータファイルを読み込み、字句解析を行って
 *  その結果をtree構造データとして格納します。
 *
 * @param[in] file 入力するパラメータファイル名
 * 
 * @return エラーコード 
 */

TextParserError TextParser::read(const std::string& file){
#ifdef MYDEBUG  
    TP_DBGOSH << "TextParser reading file " << file << std::endl;
#endif // MYDEBUG    
  TextParserError ret = TP_NO_ERROR;

  try {
    ret=dataTree()->readParameters(file);
  } catch (std::exception ex) {
    ret = TextParserErrorHandler(TP_FILEINPUT_ERROR, file);
  }
#ifdef MYDEBUG  
  TP_DBGOSH << "TextParser end reading file "<<file << std::endl;
#endif // MYDEBUG    
   return ret;
}


TextParserError TextParser::read_local(const std::string& file){
  TextParserError ret = TP_NO_ERROR;
#ifndef BUILD_MPI
  TP_DBGOSH << "ERROR - TextParser::read_local(const std::string file) is designed to be use d with MPI library. "<<std::endl;
  TP_DBGOSH << " Please USE TextParser::read(const std::stringfile)."<<std::endl;
  ret = TextParserErrorHandler(TP_FILEINPUT_ERROR, file);
  return ret;
#else

  try {
    ret=dataTree()->readParameters_local(file);
  } catch (std::exception ex) {
    ret = TextParserErrorHandler(TP_FILEINPUT_ERROR, file);
  }
  return ret;
#endif // BUILD_MPI
}


/** 指定されたファイルに現在保持しているtree構造を、
 *  パラメータファイルの書式で書き出します。
 *  依存関係付き値や、配列型ラベルの引数は、
 *  展開し確定した値を書き出します。
 *
 * @param[in] filename 出力するパラメータファイル名
 * @return エラーコード 
 *
 */

TextParserError TextParser::write(const std::string &file,int order)
{
    TextParserError ret = TP_NO_ERROR;

    try {
      dataTree()->writeParameters(file,order);
      
    } catch (std::exception ex) {
      ret = TextParserErrorHandler(TP_FILEOUTPUT_ERROR, file);
    }
    return ret;
    //    *error = ret;
}

/** 全てのパラメータのラベルパスを取得
 *
 * @param[out] labels 全てのパラメータへのラベルパス
 * @return エラーコード
 */
TextParserError TextParser::getAllLabels(std::vector<std::string>& labels)
{
  //    std::vector<std::string> labels;
  //    MgppError ret = MGPP_NO_ERROR;
  TextParserError ret = TP_NO_ERROR;
  
    try {
      if (!dataTree()->isReady()) {
	ret = TextParserErrorHandler(TP_DATABASE_NOT_READY_ERROR, "");
      } else {
	std::map<unsigned int, std::string>::iterator 
	  il = dataTree()->_leaf_paths.begin();
	while (il != dataTree()->_leaf_paths.end()) {
	  labels.push_back(il->second);
	  il++;
	}
      }
    } catch (std::exception ex) {
        ret = TextParserErrorHandler(TP_GET_PARAMETER_ERROR, "");
    }


    //    *error = ret;
     //    return labels;
    return ret;
}



/** リーフのラベルが示す値のタイプを返す関数
 * 
 *　@param[in] label リーフのラベル
 *  @param[out] error エラーコード
 *  @return labelが指す値のタイプ 型はTextParserValueType
 */
TextParserValueType TextParser::getType(const std::string& label, int *error)
{
    TextParserValueType returner;
    TextParserError ret = TP_NO_ERROR;

    try {
      if (!dataTree()->isReady()) {
	ret = TextParserErrorHandler(TP_DATABASE_NOT_READY_ERROR, "");
        } else {
            TextParserValue *value;
            ret = dataTree()->getLeafValue(label, &value);
            if (ret != TP_NO_ERROR) {
                if (ret == TP_MISSING_PATH_ELEMENT_ERROR)
		  TextParserErrorHandler(ret, label);
            } else {
                    returner = value->_value_type;
                if (value->_value_type == TP_UNDEFFINED_VALUE) {
                    //*type = 0;
                } else if (value->_value_type == TP_NUMERIC_VALUE) {
                    //*type = 1;
                } else if (value->_value_type == TP_STRING_VALUE) {
                    //*type = 2;
                } else if (value->_value_type == TP_VECTOR_UNDEFFINED) {
                        //*type = 4;
                } else if (value->_value_type == TP_VECTOR_NUMERIC) {
                        //*type = 5;
                } else if (value->_value_type == TP_VECTOR_STRING) {
                        //*type = 6;
                } else if (value->_value_type == TP_RANGE_NUMERIC) {
                        //*type = 7;
                } else if (value->_value_type == TP_LIST_NUMERIC) {
                        //*type = 8;
                } else {
                    ret = TextParserErrorHandler(TP_ILLEGAL_VALUE_TYPE_ERROR, "");
                }
            }
        }


    } catch (std::exception ex) {
      ret = TextParserErrorHandler(TP_GET_PARAMETER_ERROR, "");
    }
    
    *error = ret;
    
    return returner;
}




/** パラメータの値を取得
 *
 * @param[in] label リーフのラベルパス
 * @param[out] value_string リーフの値
 * @param[out] ierror エラーコード
 * 
 *
 */

void TextParser::getValue(const std::string& label,std::string& value_string,int* ierror)
{
  //  std::string value_string;
  TextParserError ret = TP_NO_ERROR;
  
  try {
    if (!dataTree()->isReady()) {
      ret = TextParserErrorHandler(TP_DATABASE_NOT_READY_ERROR, "");
    } else {
      TextParserValue *value;
      ret = dataTree()->getLeafValue(label, &value);
      if(ret==TP_NO_ERROR) {
        value_string = value->value();
      } else {
	    TextParserErrorHandler(ret, label);
      }
    }
    
  } catch (std::exception ex) {
    ret = TextParserErrorHandler(TP_GET_PARAMETER_ERROR, "");
  }

  //  return ret;
    *ierror = ret;
    
  //  return value_string;
}

/** パラメータの値を取得
 *
 * @param[in] label パラメータのラベルパス
 * @param[out] value_string パラメータの値
 * @return エラーコード
 *
 */

TextParserError TextParser::getValue(const std::string& label,std::string& value_string)
{
  //  std::string value_string;
  TextParserError ret = TP_NO_ERROR;
  
  try {
    if (!dataTree()->isReady()) {
      ret = TextParserErrorHandler(TP_DATABASE_NOT_READY_ERROR, "");
    } else {
      TextParserValue *tmpvalue;
      ret = dataTree()->getLeafValue(label, &tmpvalue);
      value_string = tmpvalue->value();
      if (ret == TP_MISSING_PATH_ELEMENT_ERROR)
	TextParserErrorHandler(ret, label);
    }
    
  } catch (std::exception ex) {
    ret = TextParserErrorHandler(TP_GET_PARAMETER_ERROR, "");
  }

  return ret;
    

}

/** 現在のノードの取得
 *
 * @param[out] returner ノードのパスラベル(std::string).
 * @return エラーコード.
 *
 */
TextParserError TextParser::currentNode(std::string& returner)
{
    TextParserError ret = TP_NO_ERROR;
    //    std::string returner = "";

    try {
        //! インスタンスの取得

        if (!dataTree()->isReady()) {
                ret = TextParserErrorHandler(TP_DATABASE_NOT_READY_ERROR, "");
        } else {
            if (dataTree()->_current_element == 0) {
                    // do nothing
                    //            *label = 0;
                    // is this right. Check this later.
	      //   returner = dataTree()->_label;
	      //  returner = dataTree()->_current_element->_label;
	      returner = "/";
            } else {
                    //*label = (char *)dataTree()->_current_element->_label.c_str();
	      returner = dataTree()->_current_element->_label;
            }
        }
    } catch (std::exception ex) {
        ret = TextParserErrorHandler(TP_GET_PARAMETER_ERROR, "");
    }

    //    *error = ret;
    return ret;
    //    return returner;
}


/** 現在のノード内の全ノードを取得
 *
 * @param[out] node_list 現在のノード内の全ノード std::vector<std::sring>型
 * @return error エラーコード
 */

TextParserError TextParser::getNodes(std::vector<std::string>& node_list,int oswitch){
  
  TextParserError ret = TP_NO_ERROR;
  
  try {
    
    if (!dataTree()->isReady()) {
      ret = TextParserErrorHandler(TP_DATABASE_NOT_READY_ERROR, "");
    } else {
      ret =dataTree()->getCurrentNodeLabels(node_list);
    }
  } catch (std::exception ex) {
    ret = TextParserErrorHandler(TP_GET_PARAMETER_ERROR, "");
  }
  
  if(oswitch!=0){
    std::vector< std::string> output;
  dataTree()->nodeSort(node_list,output,oswitch);
  node_list=output;
}
//  *error = ret;
//    return labels;
return ret;

}


/** リーフのストリングをcharに変換
 * @param[in] value リーフの値（文字列).
 * @param[out] error エラーコード.
 * @return char に変換された値.
 */
char TextParser::convertChar(const std::string& value, int *error)
{
    *error = 0;

    char returner;
    int int_recieve;
    try {
      if(dataTree()->checkNumericalLimitsInt(value)){
	long long llreturner =convertLimitsIntx(value,error);
	returner= llreturner;
      }	else if(dataTree()->checkNumericalLimitsReal(value)){
	double dd =convertLimitsRealx(value,error);
	returner= dd;
      } else {
	std::string val = CorrectValueString(value);
	std::stringstream ss;
	ss << val;
	// ss >> (int_recieve);
	// returner=int_recieve;
	ss >> (returner);
      }
    } catch (std::exception ex) {
        *error = TextParserErrorHandler(TP_MEMORY_ALLOCATION_ERROR, value);
    }
  
    return returner;
}


/** リーフのストリングをshortに変換
 * @param[in] value リーフの値（文字列).
 * @param[out] error エラーコード.
 * @return short に変換された値.
 */
short TextParser::convertShort(const std::string& value, int *error)
{
    *error = 0;
    

    short returner;
    try {
      if(dataTree()->checkNumericalLimitsInt(value)){
	long long llreturner= convertLimitsIntx(value,error);
	returner=llreturner;
      } else if(dataTree()->checkNumericalLimitsReal(value)){
	double dd= convertLimitsRealx(value,error);
	returner=dd;
      } else {
        std::string val = CorrectValueString(value);
        std::stringstream ss;
        ss << val;
        ss >> (returner);
      }
    } catch (std::exception ex) {
        *error = TextParserErrorHandler(TP_MEMORY_ALLOCATION_ERROR, value);
    }
  
    return returner;
}



/** リーフのストリングをintに変換
 * @param[in] value リーフの値（文字列).
 * @param[out] error エラーコード.
 * @return int に変換された値.
 */
int TextParser::convertInt(const std::string& value, int *error)
{
    *error = 0;

    int returner;
    try {

      if(dataTree()->checkNumericalLimitsInt(value)){
	long long llreturner= convertLimitsIntx(value,error);
	returner= llreturner;
      }	else if(dataTree()->checkNumericalLimitsReal(value)){
	double dd = convertLimitsRealx(value,error);
	returner=dd;
      } else {
        std::string val = CorrectValueString(value);
        std::stringstream ss;
        ss << val;
        ss >> (returner);
      }
    } catch (std::exception ex) {
        *error = TextParserErrorHandler(TP_MEMORY_ALLOCATION_ERROR, value);
    }
  
    return returner;
}

/** リーフのストリングをlongに変換
 * @param[in] value リーフの値（文字列).
 * @param[out] error エラーコード.
 * @return long に変換された値.
 */
long TextParser::convertLong(const std::string& value, int *error)
{
    *error = 0;

    long returner;
    try {
      if(dataTree()->checkNumericalLimitsInt(value)){
	long long llreturner= convertLimitsIntx(value,error);
	returner= llreturner;
      }else if(dataTree()->checkNumericalLimitsReal(value)){
	double dd = convertLimitsRealx(value,error);
	returner=dd;
      } else {
        std::string val = CorrectValueString(value);
        std::stringstream ss;
        ss << val;
        ss >> (returner);
      }
    } catch (std::exception ex) {
        *error = TextParserErrorHandler(TP_MEMORY_ALLOCATION_ERROR, value);
    }
  
    return returner;
}


/** リーフのストリングをlong longに変換
 * @param[in] value リーフの値（文字列).
 * @param[out] error エラーコード.
 * @return long longに変換された値.
 */

long long TextParser::convertLongLong(const std::string& value, int *error)
{
    *error = 0;

    long long returner;
    try {

      if(dataTree()->checkNumericalLimitsInt(value)){
	long long llreturner= convertLimitsIntx(value,error);
	returner= llreturner;
      }else if(dataTree()->checkNumericalLimitsReal(value)){
	double dd = convertLimitsRealx(value,error);
	returner= dd;
      } else {

        std::string val = CorrectValueString(value);
        std::stringstream ss;
        ss << val;
        ss >> (returner);
      }
    } catch (std::exception ex) {
        *error = TextParserErrorHandler(TP_MEMORY_ALLOCATION_ERROR, value);
    }
  
    return returner;
}



/** リーフのストリングをfloatに変換
 * @param[in] value リーフの値（文字列).
 * @param[out] error エラーコード.
 * @return float に変換された値.
 */

float TextParser::convertFloat(const std::string& value, int *error)
{
    *error=0;

    float returner;
    try {

      if(dataTree()->checkNumericalLimitsReal(value)){
	double dreturn = convertLimitsRealx(value,error);
	returner = dreturn;
      }else if(dataTree()->checkNumericalLimitsInt(value)){
	long long lreturn = convertLimitsIntx(value,error);
	returner = lreturn;
      }else {
        std::string val = CorrectValueString(value);
        std::stringstream ss;
        ss << val;
        ss >> (returner);
	}
    } catch (std::exception ex) {
        *error = TextParserErrorHandler(TP_MEMORY_ALLOCATION_ERROR, value);
    }
  
    return returner;
}


/** リーフのストリングをdoubleに変換
 * @param[in] value リーフの値（文字列).
 * @param[out] error エラーコード.
 * @return double に変換された値.
 */
double TextParser::convertDouble(const std::string& value, int *error)
{
    *error=0;
    double returner;
    try {
      if(dataTree()->checkNumericalLimitsReal(value)){
	returner = convertLimitsRealx(value,error);
      } else if(dataTree()->checkNumericalLimitsInt(value)){
	long long lret=convertLimitsIntx(value,error);
	returner = lret;
      }else {
        std::string val = CorrectValueString(value);
        std::stringstream ss;
        ss << val;
        ss >> (returner);
      }
    } catch (std::exception ex) {
        *error = TextParserErrorHandler(TP_MEMORY_ALLOCATION_ERROR, value);
    }
  
    return returner;
}
/** リーフのストリングをboolに変換
 *
 * true : "true"(大文字小文字は関係無し)  
 * false : "false"（大文字小文字は関係無し）  
 * 上記を満たさない文字列の場合は、falseを返す。
 *
 * @param[in] value リーフの値（文字列).
 * @param[out] error エラーコード.
 * @return bool に変換された値.
 */
bool TextParser::convertBool(const std::string& value, int *error)
{
   *error=0;
    bool returner=false;
#ifdef MYDEBUG3
    TP_DBGOSH << "ConvertBool" << " value |" << value << "|"<<std::endl;
#endif 
    std::string tstring="true";
    if(TextParserStringCompare(value,tstring)){
      returner=true;
      return returner;
    }
    tstring="1";
    if(TextParserStringCompare(value,tstring)){
      returner=true;
      return returner;
    }
    tstring="false";
    if(TextParserStringCompare(value,tstring)){
      return returner;
    }
    tstring="0";
    if(TextParserStringCompare(value,tstring)){
      return returner;
    }
    return returner;
}


/** ベクトル値を要素ごとに文字列に分割する。
 * @param[in] vector_value ベクトル値.
 * @param[out] velem 分離された値の文字列のベクトル
 * @return エラーコード.
 */
TextParserError TextParser::splitVector(const std::string& vector_value,
					std::vector<std::string>& velem )
{
    TextParserError ret = TP_NO_ERROR;

    try {
      if (!dataTree()->isReady()) {
       	  ret = TextParserErrorHandler(TP_DATABASE_NOT_READY_ERROR, "");
       } else {
	 ret = dataTree()->splitVectorValue(vector_value, velem);
       }
      //      ret = dataTree()->splitVectorValue(vector_value, velem);
    } catch (std::exception ex) {
        ret = TextParserErrorHandler(TP_GET_PARAMETER_ERROR, "");
    }
    //    TP_DBGOSH << velem.size() <<std::endl;
    return ret;
}




/** パラメータの削除
 *
 * @return エラーコード
 *
 */
TextParserError TextParser::remove()
{
    TextParserError ret = TP_NO_ERROR;
    try {
        ret = dataTree()->removeElement();
    } catch (std::exception ex) {
        ret = TextParserErrorHandler(TP_REMOVE_ELEMENT_ERROR, "");
    }
    
    return ret;
}
/** ノードの移動
 *
 * @param[in] label ノードのパスラベル.
 * @return エラーコード.
 *
 */
TextParserError TextParser::changeNode(const std::string& label)
{
    TextParserError ret = TP_NO_ERROR;

    try {
        //! インスタンスの取得

        if (!dataTree()->isReady()) {
                ret = TextParserErrorHandler(TP_DATABASE_NOT_READY_ERROR, "");
        } else {
            ret = dataTree()->changeNode(label);
        }
    } catch (std::exception ex) {
        ret = TextParserErrorHandler(TP_GET_PARAMETER_ERROR, "");
    }
    return ret;

}


/** 現在のノード内の全ラベルを取得
 *
 * @param[out] labels 現在のディレクトリ内の全ラベル std::vector<std::sring>型
 * @return エラーコード
 */
TextParserError TextParser::getLabels(std::vector<std::string>& labels,int oswitch)
{
  //    std::vector<std::string> labels;
    TextParserError ret = TP_NO_ERROR;
  
    try {
        //! インスタンスの取得
        if (!dataTree()->isReady()) {
            ret = TextParserErrorHandler(TP_DATABASE_NOT_READY_ERROR, "");
        } else {
            ret = dataTree()->getCurrentLeafLabels(labels);
        }
    } catch (std::exception ex) {
        ret = TextParserErrorHandler(TP_GET_PARAMETER_ERROR, "");
    }

    if(oswitch!=0){
      std::vector<std::string> output;
      //    dataTree()->labelSort(labels,output,0);
      dataTree()->labelSort(labels,output,oswitch);
      labels=output;
    }
    return ret;
    //    *error = ret;
    
    //    return labels;
}


/**パラメータリーフ　のvalue変更
 *
 * @param[in] label 対応するパラメータへのラベル
 * @param[in] value 更新する値
 * @return エラーコード
 */

TextParserError TextParser::updateValue(const std::string& label,const std::string& value){

  TextParserError error=TP_NO_ERROR;
  error = dataTree()->updateValue(label,value);
  return error;
}



/**　パラメータリーフの削除
 * @param[in] label 削除するリーフへのラベル
 * @return エラーコード
 */

TextParserError TextParser::deleteLeaf(const std::string& label){ 
  TextParserError error=TP_NO_ERROR;
  error = dataTree()->deleteLeaf(label);
  return error;
}



/**　パラメータリーフ追加
 *
 * @param[in] label 対応するパラメータへのラベル
 * @param[in] value 更新する値
 * @return エラーコード
 */
TextParserError TextParser::createLeaf(const std::string& label,const std::string& value){
  TextParserError error=TP_NO_ERROR;
  error = dataTree()->createLeaf(label,value);
  return error;
}




/////-------------------------------------------------------
/////-------------------------------------------------------
/////-------------------------------------------------------
/////-------------------------------------------------------

 // global functions for C API 

/**
 *  TextParser シングルトンインスタンスへのポインタを取得します。
 * @return TextParser シングルトンオブジェクトへのポインタ
 */

TP_HANDLE tp_getInstanceSingleton(){
  return static_cast<void*>( TextParser::get_instance_singleton());
} 
/**
 * TextParser インスタンスを生成してそのポインタを取得します。
 * @return TextParser オブジェクトへのポインタ
 */

TP_HANDLE tp_createInstance(){
  return static_cast<void*> (new TextParser);
}

/**
 * TextParser インスタンスを削除します。
 * @param[in] tp_hand TextParser オブジェクト
 *　@return エラーコード現在は常にゼロが帰る
 */



int tp_deleteInstance(TP_HANDLE tp_hand){
  TextParser* tp_ptr=static_cast<TextParser*> (tp_hand);
  int error=0;
  tp_ptr->remove();
  delete tp_ptr;
  return error;
}



 /** 入力ファイルを読み込み、各パラメータをtree構造のデータとして格納する。C用API
  * 
  * @param[in] tp_hand TextParser オブジェクトハンドル
  * @param[in] cfile 入力ファイル名
  * @return エラーコード、TextParserErrorによる。intで取得。
  */

int tp_read(TP_HANDLE tp_hand,char* cfile){
  std::string filestring(cfile);
  TextParser* tp_ptr= static_cast<TextParser*>(tp_hand);
  int error = tp_ptr->read(filestring);
  return  error;
}


 /** 入力ファイルを読み込み、各パラメータをtree構造のデータとして格納する。C用API
  *  すべてのランクで指定されたファイルを読み込む。
  * 
  * @param[in] tp_hand TextParser オブジェクトハンドル
  * @param[in] cfile 入力ファイル名
  * @return エラーコード、TextParserErrorによる。intで取得。
  */

int tp_read_local(TP_HANDLE tp_hand,char* cfile){
  std::string filestring(cfile);
  TextParser* tp_ptr= static_cast<TextParser*>(tp_hand);
  int error = tp_ptr->read_local(filestring);
  return  error;
}

 /** ファイルにデータ構造を格納する。C用API
  * 
  * @param[in] tp_hand TextParser オブジェクトハンドル
  * @param[in] cfile 出力ファイル名
  * @return エラーコード、TextParserErrorによる。intで取得。
  */
int tp_write(TP_HANDLE tp_hand,char* cfile){
  std::string filestring(cfile);
  //  TextParser* tp_ptr=TextParser::get_instance();
  TextParser* tp_ptr= static_cast<TextParser*>(tp_hand);
  int error = tp_ptr->write(filestring);
  return  error;
}

 /** ファイルにデータ構造を破棄する。C用API
  * 
  * @param[in] tp_hand TextParser オブジェクトハンドル
  * @return エラーコード、TextParserErrorによる。intで取得。
  */

int tp_remove(TP_HANDLE tp_hand){
  //  TextParser* tp_ptr=TextParser::get_instance();
  TextParser* tp_ptr= static_cast<TextParser*>(tp_hand);
  int error = tp_ptr->remove();
  return  error;
}


 /** リーフの総数を取得する。C用API
  *
  * @param[in] tp_hand TextParser オブジェクトハンドル
  * @param[out] Nleaves リーフの総数
  * @return エラーコード、TextParserErrorによる。intで取得。
  */

int tp_getNumberOfLeaves(TP_HANDLE tp_hand,unsigned int* Nleaves){
  //  TextParser* tp_ptr=TextParser::get_instance();
  TextParser* tp_ptr= static_cast<TextParser*>(tp_hand);
  int error = 0;
  if( !tp_ptr->dataTree()->isReady() ){
    error=tp_ptr->TextParserErrorHandler(TP_DATABASE_NOT_READY_ERROR, "");
    //error=TextParserErrorHandler(TP_DATABASE_NOT_READY_ERROR, "");
  } else {
    int size= tp_ptr->dataTree()->_leaf_paths.size();
    *Nleaves = size;
  }
  return error;
}


 /** ラベルの取得。C用API
  *
  * @param[in] tp_hand TextParser オブジェクトハンドル
  * @param[in] ilabel 取得するラベルの番号
  * @param[out] label ラベル
  * @return エラーコード、TextParserErrorによる。intで取得。
  */

int tp_getLabel(TP_HANDLE tp_hand,int ilabel,char* label){

  //  TextParser* tp_ptr=TextParser::get_instance();
  TextParser* tp_ptr= static_cast<TextParser*>(tp_hand);
  int error = 0;
  if( !tp_ptr->dataTree()->isReady() ){
    error=tp_ptr->TextParserErrorHandler(TP_DATABASE_NOT_READY_ERROR, "");
  } else {
    if (ilabel >= tp_ptr->dataTree()->_leaf_paths.size() ) {
      error = tp_ptr->TextParserErrorHandler(TP_ID_OVER_ELEMENT_NUMBER_ERROR, "");
    } else {
      std::map<unsigned int, std::string>::iterator
	il = tp_ptr->dataTree()->_leaf_paths.find(ilabel);
      strcpy(label,il->second.c_str());
    }
  }
  return error;
}

 /** 値の取得。C用API
  *
  * @param[in] tp_hand TextParser オブジェクトハンドル
  * @param[in] label typeを取得するラベル
  * @param[out] value 値 
  * @return エラーコード、TextParserErrorによる。intで取得。
  */

int tp_getValue(TP_HANDLE tp_hand,char* label,char* value){

  //  TextParser* tp_ptr=TextParser::get_instance();
  TextParser* tp_ptr= static_cast<TextParser*>(tp_hand);
  int error = 0;
  std::string slabel(label);
  std::string svalue;
  error=tp_ptr->getValue(slabel,svalue);
  strcpy(value,svalue.c_str());
  return error;
}

 /** タイプの取得。C用API
  *
  * @param[in] tp_hand TextParser オブジェクトハンドル
  * @param[in] label typeを取得するラベル
  * @param[out] type 値のタイプ。TextParserValuetype による。int で取得。
  * @return エラーコード、TextParserErrorによる。intで取得。
  */

int tp_getType(TP_HANDLE tp_hand,char* label,int* type){
  *type=-10;
  //  TextParser* tp_ptr=TextParser::get_instance();
  TextParser* tp_ptr= static_cast<TextParser*>(tp_hand);
  int error = 0;
  std::string slabel(label);
  *type=tp_ptr->getType(slabel,&error);
  return error;
}

int typeToInt(TextParserValueType type){
  int ret=-1;
  
  switch(type){
    
  TP_UNDEFFINED_VALUE:
    ret = 0; break;  //!< 不定
  TP_NUMERIC_VALUE:
    ret = 1; break;     //!< 数値
  TP_STRING_VALUE:
    ret = 2; break;      //!< 文字列
  TP_DEPENDENCE_VALUE:
    ret = 3; break;  //!< 依存関係付き値
  TP_VECTOR_UNDEFFINED:
    ret = 4; break; //!< ベクトル型不定
  TP_VECTOR_NUMERIC:
    ret = 5; break;    //!< ベクトル型数値
  TP_VECTOR_STRING:
    ret = 6; break;     //!< ベクトル型文字列
  default:
    break;
  }
  return ret;
}

/** パラメータの値を文字列から char 型へ変換します。C用API.
 *
 * @param[in] tp_hand TextParser オブジェクトハンドル
 * @param[in] value 値の文字列
 * @param[out] error エラーコード
 * @return char型への変換値
 */

char tp_convertChar(TP_HANDLE tp_hand,char* value,int *error){
  //  TextParser* tp_ptr=TextParser::get_instance();
  TextParser* tp_ptr= static_cast<TextParser*>(tp_hand);

  std::string svalue(value);

  int int_recieve=tp_ptr->convertInt(svalue,error);
  char returner = int_recieve;
  //  TP_DBGOSH << __FUNCTION__ << svalue  << " int "<< int_recieve<< " char "<< (int)returner <<std::endl; 
  return returner;

}
/** パラメータの値を文字列から short 型へ変換します。C用API.
 *
 * @param[in] tp_hand TextParser オブジェクトハンドル
 * @param[in] value 値の文字列
 * @param[out] error エラーコード
 * @return short型への変換値
 */

short tp_convertShort(TP_HANDLE tp_hand,char* value,int *error){
  //  TextParser* tp_ptr=TextParser::get_instance();
  TextParser* tp_ptr= static_cast<TextParser*>(tp_hand);
  std::string svalue(value);
  return tp_ptr->convertShort(svalue,error);
}
/** パラメータの値を文字列から int 型へ変換します。C用API.
 *
 * @param[in] tp_hand TextParser オブジェクトハンドル
 * @param[in] value 値の文字列
 * @param[out] error エラーコード
 * @return short型への変換値
 */

int tp_convertInt(TP_HANDLE tp_hand,char* value,int *error){
  //  TextParser* tp_ptr=TextParser::get_instance();
  TextParser* tp_ptr= static_cast<TextParser*>(tp_hand);
  std::string svalue(value);
  return tp_ptr->convertInt(svalue,error);
}

/** パラメータの値を文字列から long 型へ変換します。C用API.
 *
  * @param[in] tp_hand TextParser オブジェクトハンドル
 * @param[in] value 値の文字列
 * @param[out] error エラーコード
 * @return short型への変換値
 */

long tp_convertLong(TP_HANDLE tp_hand,char* value,int *error){
  //  TextParser* tp_ptr=TextParser::get_instance();
  TextParser* tp_ptr= static_cast<TextParser*>(tp_hand);
  std::string svalue(value);
  return tp_ptr->convertLong(svalue,error);
}

/** パラメータの値を文字列から long long 型へ変換します。C用API.
 *
 * @param[in] tp_hand TextParser オブジェクトハンドル
 * @param[in] value 値の文字列
 * @param[out] error エラーコード
 * @return short型への変換値
 */

long long tp_convertLongLong(TP_HANDLE tp_hand,char* value,int *error){

  //  TextParser* tp_ptr=TextParser::get_instance();
  TextParser* tp_ptr= static_cast<TextParser*>(tp_hand);

  std::string svalue(value);
  return tp_ptr->convertLongLong(svalue,error);
}

/** パラメータの値を文字列から float 型へ変換します。C用API.
 *
 * @param[in] tp_hand TextParser オブジェクトハンドル
 * @param[in] value 値の文字列
 * @param[out] error エラーコード
 * @return short型への変換値
 */
float tp_convertFloat(TP_HANDLE tp_hand,char* value,int *error){
  //  TextParser* tp_ptr=TextParser::get_instance();
  TextParser* tp_ptr= static_cast<TextParser*>(tp_hand);
  std::string svalue(value);
  return tp_ptr->convertFloat(svalue,error);
}

/** パラメータの値を文字列から double 型へ変換します。C用API.
 *
 * @param[in] tp_hand TextParser オブジェクトハンドル
 * @param[in] value 値の文字列
 * @param[out] error エラーコード
 * @return short型への変換値
 */
double tp_convertDouble(TP_HANDLE tp_hand,char* value,int *error){
  //  TextParser* tp_ptr=TextParser::get_instance();
  TextParser* tp_ptr= static_cast<TextParser*>(tp_hand);
  std::string svalue(value);
  return tp_ptr->convertDouble(svalue,error);
}

/** パラメータの値を文字列から bool型をint 型の形式で変換します。C用API.
 *
 * true --> 1 
 * false --> 0
 *
 * @param[in] tp_hand TextParser オブジェクトハンドル
 * @param[in] value 値の文字列
 * @param[out] error エラーコード
 * @return int型への変換値
 */
int tp_convertBool(TP_HANDLE tp_hand, char* value,int *error){
  //  TextParser* tp_ptr=TextParser::get_instance();
  TextParser* tp_ptr= static_cast<TextParser*>(tp_hand);
  std::string svalue(value);
  int ret =0;
  if(tp_ptr->convertBool(svalue,error)) ret=1;
  return ret ;
}

/** ベクトル型の値の要素数を取得する。C用API.
 *
 * @param[in] tp_hand TextParser オブジェクトハンドル
 * @param[in] vector_value ベクトル型の値（文字列）
 * @param[out] nvec 要素数 
 * @return エラーコード、TextParserErrorによる。intで取得。
 *
 */
int tp_getNumberOfElements(TP_HANDLE tp_hand,char* vector_value,unsigned int* nvec ){

  //  TextParser* tp_ptr=TextParser::get_instance();
  TextParser* tp_ptr= static_cast<TextParser*>(tp_hand);
  std::string svalue(vector_value);
  std::vector<std::string> tmp_vector_string;
  int error=tp_ptr->splitVector(svalue,tmp_vector_string);
  int size=tmp_vector_string.size();
  *nvec =  size;
  return error;
}

/** 指定したindexのベクトル型の値の要素を取得する. C用API.
 *
 * @param[in] tp_hand TextParser オブジェクトハンドル
 * @param[in] vector_value ベクトル型の値（文字列）
 * @param[in] ivec 取得する要素のインデックス
 * @param[out] velem ベクトル値の要素（文字列）
 * @return エラーコード、TextParserErrorによる。intで取得。
 *
 */
int tp_getIthElement(TP_HANDLE tp_hand,char* vector_value,unsigned int ivec,char* velem){
  //  TextParser* tp_ptr=TextParser::get_instance();
  TextParser* tp_ptr= static_cast<TextParser*>(tp_hand);
  std::string svalue(vector_value);
  std::vector<std::string> tmp_vector_string;
  int error=tp_ptr->splitVector(svalue,tmp_vector_string);
  strcpy(velem,tmp_vector_string[ivec].c_str());
  return error;
}

 /** カレントノードを取得します。C用API
  *
  * @param[in] tp_hand TextParser オブジェクトハンドル
  * @param[out] label ノードのラベルが返ります。
  * @return エラーコード、TextParserErrorによる。intで取得。
  */
int tp_currentNode(TP_HANDLE tp_hand,char* label){

  //  TextParser* tp_ptr=TextParser::get_instance();
  TextParser* tp_ptr= static_cast<TextParser*>(tp_hand);
  int error = 0;
  std::string slabel(label);
  error=tp_ptr->currentNode(slabel);
  strcpy(label,slabel.c_str());
  return error;
}
 /** labelで指定されたノードをカレントノードに設定します。C用API
  *
  * @param[in] tp_hand TextParser オブジェクトハンドル
  * @param[in] label 移動するノード
  * @return エラーコード、TextParserErrorによる。intで取得。
  */
int tp_changeNode(TP_HANDLE tp_hand,char* label){
#ifdef MYDEBUG
  TP_DBGOSH <<__func__ <<" "<<label<<std::endl;
#endif // MYDEBUG
  TextParser* tp_ptr= static_cast<TextParser*>(tp_hand);
  int error = 0;
  std::string slabel(label);

#ifdef MYDEBUG
  TP_DBGOSH <<__func__<<" "<<slabel<<std::endl;
#endif // MYDEBUG

  error=tp_ptr->changeNode(slabel);

#ifdef MYDEBUG
  TP_DBGOSH <<slabel<<" "<<__func__<<std::endl;
#endif // MYDEBUG
  return error;
}

 /** カレントノードの子ノードの数を取得します。C用API
  *
  * @param[in] tp_hand TextParser オブジェクトハンドル
  * @param[out] nnodes 子ノードの数
  * @return エラーコード、TextParserErrorによる。intで取得。
  */
int tp_getNumberOfCNodes(TP_HANDLE tp_hand,int* nnodes){
  //  TextParser* tp_ptr=TextParser::get_instance();
  TextParser* tp_ptr= static_cast<TextParser*>(tp_hand);
  int error = 0;
  std::vector<std::string> node_labels;
  error=tp_ptr->getNodes(node_labels);
  *nnodes=node_labels.size();
  return error;
}

 /** カレントノードのリーフの数を取得します。C用API
  *
  * @param[in] tp_hand TextParser オブジェクトハンドル
  * @param[out] nleaves リーフの数
  * @return エラーコード、TextParserErrorによる。intで取得。
  */
int tp_getNumberOfCLeaves(TP_HANDLE tp_hand,int* nleaves){
  //  TextParser* tp_ptr=TextParser::get_instance();
  TextParser* tp_ptr= static_cast<TextParser*>(tp_hand);
  int error = 0;
  std::vector<std::string> leaf_labels;
  error=tp_ptr->getLabels(leaf_labels);
  *nleaves=leaf_labels.size();
  return error;
}

 /** カレントノードにあるインデックスで指定したノードのラベルを取得します。C用API
  * 
  * @param[in] tp_hand TextParser オブジェクトハンドル
  * @param[in] inode ノードのインデックス
  * @param[out] node ノードのラベル
  * @return エラーコード、TextParserErrorによる。intで取得。
  */
int tp_getIthNode(TP_HANDLE tp_hand,int inode,char* node){

  //  TextParser* tp_ptr=TextParser::get_instance();
  TextParser* tp_ptr= static_cast<TextParser*>(tp_hand);
  int error = 0;
  std::vector<std::string> node_labels;
  error=tp_ptr->getNodes(node_labels);
  strcpy(node,node_labels[inode].c_str());
  return error;
}
 /** カレントノードにあるインデックスで指定したノードのラベルを取得します。C用API
  * 
  * @param[in] tp_hand TextParser オブジェクトハンドル
  * @param[in] inode ノードのインデックス
  * @param[out] node ノードのラベル
  * @param[in] order ラベルの出力順　0:getIthNode 同様　1:配列型ラベルのインデックス順　2:ラベルの出現順.
  * @return エラーコード、TextParserErrorによる。intで取得。
  */
int tp_getIthNodeOrder(TP_HANDLE tp_hand,int inode,char* node,int order){


  //  TextParser* tp_ptr=TextParser::get_instance();
  TextParser* tp_ptr= static_cast<TextParser*>(tp_hand);
  int error = 0;
  std::vector<std::string> node_labels;
  error=tp_ptr->getNodes(node_labels,order);
  strcpy(node,node_labels[inode].c_str());
  return error;
}

 /** カレントノードにあるインデックスで指定したリーフを取得します。C用API
  * 
  * @param[in] tp_hand TextParser オブジェクトハンドル
  * @param[in] ileaf リーフのインデックス
  * @param[out] leaf リーフのラベル
  * @return エラーコード、TextParserErrorによる。intで取得。
  */
int tp_getIthLeaf(TP_HANDLE tp_hand,int ileaf,char* leaf){
  TextParser* tp_ptr= static_cast<TextParser*>(tp_hand);
  //  TextParser* tp_ptr=TextParser::get_instance();
  int error = 0;
  std::vector<std::string> leaf_labels;
  error=tp_ptr->getLabels(leaf_labels);
  strcpy(leaf,leaf_labels[ileaf].c_str());
  return error;
}

 /** カレントノードにあるインデックスで指定したリーフを取得します。C用API
  * 
  * @param[in] tp_hand TextParser オブジェクトハンドル
  * @param[in] ileaf リーフのインデックス
  * @param[out] leaf リーフのラベル
  * @param[in] order ラベルの出力順　0:getIthNode 同様　1:配列型ラベルのインデックス順　2:ラベルの出現順.
  * @return エラーコード、TextParserErrorによる。intで取得。
  */
int tp_getIthLeafOrder(TP_HANDLE tp_hand,int ileaf,char* leaf,int order){
  TextParser* tp_ptr= static_cast<TextParser*>(tp_hand);
  //  TextParser* tp_ptr=TextParser::get_instance();
  int error = 0;
  std::vector<std::string> leaf_labels;
  error=tp_ptr->getLabels(leaf_labels,order);
  strcpy(leaf,leaf_labels[ileaf].c_str());
  return error;
}



  // tree modify 用関数　C用API

/**  リーフの値を更新する.
 *
 * @param[in] tp_hand TextParser オブジェクトハンドル
 * @param[in] label ラベルパス
 * @param[in] value 値(string)
 * @return エラーコード
 */

int tp_updateValue(TP_HANDLE tp_hand,char* label,char*value){
  int error = 0;
  std::string slabel(label);
  std::string svalue(value);
  error=static_cast<TextParser*>(tp_hand)->dataTree()->updateValue(slabel,svalue);
  return error;
}


/**  リーフを削除する.
 *
 * @param[in] tp_hand TextParser オブジェクトハンドル
 * @param[in] label ラベルパス
 * @return エラーコード
 */

int tp_deleteLeaf(TP_HANDLE tp_hand,char* label){
  int error = 0;
  std::string slabel(label);
  error=static_cast<TextParser*>(tp_hand)->dataTree()->deleteLeaf(slabel);
  return error;
}

/** リーフを作成する.
 *
 * @param[in] tp_hand TextParser オブジェクトハンドル
 * @param[in] label ラベルパス
 * @param[in] value 値(string)
 * @return エラーコード
 */

int tp_createLeaf(TP_HANDLE tp_hand,char* label,char*value){
  int error = 0;
  std::string slabel(label);
  std::string svalue(value);
  error=static_cast<TextParser*>(tp_hand)->dataTree()->createLeaf(slabel,svalue);
  return error;
}


/** @range を展開する
 *
 * @param[in] tp_hand TextParser オブジェクトハンドル
 * @param[in] value 文字列.
 * @param[out] from 開始値
 * @param[out] to 終了値
 * @param[out] step ステップ
 * @return エラーコード
 */
int tp_splitRange(TP_HANDLE tp_hand,char* value,
		  double *from,double *to,double *step){
  int error = 0;
  std::string svalue(value);
  error=static_cast<TextParser*>(tp_hand)->splitRange(svalue,from,to,step);
  return error;
}


int tp_expandRange(TP_HANDLE tp_hand,char* value,
		   double* expanded){
  int error = 0;
  std::string svalue(value);
  std::vector<double> vexpanded;
  error=static_cast<TextParser*>(tp_hand)->expandRange(svalue,vexpanded);
  for(int i=0;i<vexpanded.size();++i){
    *(expanded+i) = vexpanded[i];
  }



    return error;
}
  // @list
int tp_splitList(TP_HANDLE tp_hand,char* value,
		 double* list,
		 int order){


    int error = 0;
    std::string svalue(value);
    std::vector<double> vexpanded;
    error=static_cast<TextParser*>(tp_hand)->splitList(svalue,vexpanded,(TextParserSortOrder)order);
  for(int i=0;i<vexpanded.size();++i){
    *(list+i) = vexpanded[i];
  }
    return error;
}



// Fortran 用API

/**
 * TextParser シングルトンインスタンスへのポインタを取得します。 Fortran 用API
 *
 * @param[out] ptr
 * @return エラーコード　現時点では、常にTP_NO_ERROR.
 */

int tp_get_instance_singleton_fort_(long* ptr){
  *ptr = reinterpret_cast<long>(TextParser::get_instance_singleton());
  int error=TP_NO_ERROR;
  return error;
} 
/** TextParser インスタンスを生成してそのポインタを取得します。  Fortran 用API
 *
 * @param[out] ptr
 * @return エラーコード 現時点では、常にTP_NO_ERROR.
 *
 */
int tp_create_instance_fort_(long* ptr){
*ptr= reinterpret_cast<long>(TextParser::get_instance_singleton());
 int error=TP_NO_ERROR;
 return error;
}

/** TextParser インスタンスを削除します.  Fortran 用API
 *
 * @param[out] ptr
 * @return エラーコード 現時点では、常にTP_NO_ERROR.
 *
 */
int tp_delete_instance_fort_(long* ptr){
TextParser* tp_ptr=reinterpret_cast<TextParser*>(*ptr);
if(tp_ptr!=TextParser::get_instance_singleton()&&tp_ptr !=0 )delete tp_ptr;
int error=TP_NO_ERROR;
return error;
}


/** ファイルからパラメータを読み込む.　Fortran用API
 *
 * @param[in] ptr TextParser インスタンスへのポインタ
 * @param[in] file ファイル名
 * @param[in] length ファイル名文字列の長さ
 * @return エラーコード、TextParserErrorによる。intで取得。
 */

int tp_read_fort_(long* ptr,char* file,int* length){
 return tp_read(reinterpret_cast<void*>(*ptr),file);
}


/** ファイルからパラメータを読み込む.　Fortran用API
 * すべてのノードで指定されたファイルを読み込む。
 *
 * @param[in] ptr TextParser インスタンスへのポインタ
 * @param[in] file ファイル名
 * @param[in] length ファイル名文字列の長さ
 * @return エラーコード、TextParserErrorによる。intで取得。
 */

int tp_read_local_fort_(long* ptr,char* file,int* length){
 return tp_read_local(reinterpret_cast<void*>(*ptr),file);
}

/** パラメータをファイルに書き出す.　Fortran用API
 *
 * @param[in] file ファイル名
 * @param[in] length ファイル名の長さ 
 * @return エラーコード、TextParserErrorによる。intで取得。
 */
int tp_write_fort_(long* ptr,char* file,int* length){
  return tp_write(reinterpret_cast<void*>(*ptr),file);
}
/** パラメータデータをメモリから消去　Fortran用API
 *
 * @return エラーコード、TextParserErrorによる。intで取得。
 */
int tp_remove_fort_(long* ptr){
  return tp_remove(reinterpret_cast<void*>(*ptr));
}

/** リーフの総数を取得する.　Fortran用API
 *
 * @param[out] nleaves リーフの総数
 * @return エラーコード、TextParserErrorによる。intで取得。
 */
int tp_get_number_of_leaves_fort_(long* ptr,int* nleaves ){
  unsigned int i;
  //  TP_DBGOSH << "tp_get_number_of_leaves_fort_"<< std::endl;
  int error=tp_getNumberOfLeaves(reinterpret_cast<void*>(*ptr),&i);
  //  TP_DBGOSH << "tp_get_number_of_leaves_fort_"<< std::endl;
  *nleaves=i;

  return error;
}


/** リーフのラベルを取得する.　Fortran用API
 *
 * @param[in] ileaf インデックス
 * @param[out] label リーフのラベル
 * @param[out] length 文字列長
 * @return エラーコード、TextParserErrorによる。intで取得。
 */
int tp_get_label_fort_(long* ptr,int* ileaf ,char* label,int* length){

  unsigned int i;
  i=*ileaf;
  int j;
  char tmp_label[TP_FORTRAN_BUFFER_SIZE];
  int error = tp_getLabel(reinterpret_cast<void*>(*ptr),i,tmp_label);
  int llength = strlen(tmp_label);
  for (j=0;j<llength;j++){
    label[j]=tmp_label[j];
  }

    //return error;

  return error;
}

/** リーフの値を取得する.　Fortran用API
 *
 * @param[in] label リーフのラベル
 * @param[in] label_length 文字列長
 * @param[out] value 値
 * @param[out] value_length 文字列長
 * @return エラーコード、TextParserErrorによる。intで取得。
 */
int tp_get_value_fort_(long* ptr,char* label,char* value,int* label_length,int* value_length){

  char tmp_value[TP_FORTRAN_BUFFER_SIZE];
  int error=tp_getValue(reinterpret_cast<void*>(*ptr),label,tmp_value);
  int vlen=strlen(tmp_value);
  int j;

  //  TP_DBGOSH <<error<<"length "<<vlen<< "|"<<tmp_value<<"|"<<std::endl;

  for (j=0;j<vlen;j++){
    value[j]=tmp_value[j];
  }
  //  for (j=vlen;j<*value_length;j++){
    //    value[j]=' ';
    //    TP_DBGOSH<<j<<std::endl;
  //  }
  return error;
}
/** 値のタイプを取得する.　Fortran用API
 *
 * @param[in] label リーフのラベル
 * @param[in] label_length 文字列長
 * @param[out] type
 * @return エラーコード、TextParserErrorによる。intで取得。
 */
int tp_get_type_fort_(long* ptr,char* label,int* type,int* label_length){

  return tp_getType(reinterpret_cast<void*>(*ptr),label,type);
}



/** パラメータの値を文字列から char 型へ変換します。fortran 用API.
 *
 * @param[in] value 値の文字列
 * @param[out] error エラーコード
 * @param[out] value_length 文字列長
 * @return char型への変換値
 */

char tp_convert_char_fort_(long* ptr,char* value,int *error,int* value_length){
  
  return tp_convertChar(reinterpret_cast<void*>(*ptr),value,error);
  
}

/** パラメータの値を文字列から short 型へ変換します。fortran 用API.
 *
 * @param[in] value 値の文字列
 * @param[out] error エラーコード
 * @param[out] value_length 文字列長
 * @return short型への変換値
 */

short tp_convert_short_fort_(long* ptr,char* value,
			     int *error,int* value_length){
  return tp_convertShort(reinterpret_cast<void*>(*ptr),value,error);
}

/** パラメータの値を文字列から int 型へ変換します。fortran 用API.
 *
 * @param[in] value 値の文字列
 * @param[out] error エラーコード
 * @param[out] value_length 文字列長
 * @return int型への変換値
 */

int tp_convert_int_fort_(long* ptr,char* value,
			 int *error,int* value_length){
  return tp_convertInt(reinterpret_cast<void*>(*ptr),value,error);
  
} 

/** パラメータの値を文字列から long 型へ変換します。fortran 用API.
 *
 * @param[in] value 値の文字列
 * @param[out] error エラーコード
 * @param[out] value_length 文字列長
 * @return long型への変換値
 */

long tp_convert_long_fort_(long* ptr,char* value,
			  int *error,int* value_length){
  return tp_convertLong(reinterpret_cast<void*>(*ptr),value,error);
} 

/** パラメータの値を文字列から long long 型へ変換します。fortran 用API.
 *
 * @param[in] value 値の文字列
 * @param[out] error エラーコード
 * @param[out] value_length 文字列長
 * @return long long型への変換値
 */

long long tp_convert_long_long_fort_(long* ptr,char* value,
				     int *error,int* value_length){
  return tp_convertLongLong(reinterpret_cast<void*>(*ptr),value,error);
}
/** パラメータの値を文字列から float 型へ変換します。fortran 用API.
 *
 * @param[in] value 値の文字列
 * @param[out] error エラーコード
 * @param[out] value_length 文字列長
 * @return float型への変換値
 */

float tp_convert_float_fort_(long* ptr,char* value,
			     int *error,int* value_length){
  return tp_convertFloat(reinterpret_cast<void*>(*ptr),value,error);
}
/** パラメータの値を文字列から double 型へ変換します。fortran 用API.
 *
 * @param[in] value 値の文字列
 * @param[out] error エラーコード
 * @param[out] value_length 文字列長
 * @return double型への変換値
 */

double tp_convert_double_fort_(long* ptr,char* value,
			       int *error,int* value_length){
  return tp_convertDouble(reinterpret_cast<void*>(*ptr),value,error);
}

/** パラメータの値を文字列から int(boolian) 型へ変換します。fortran 用API.
 *
 * @param[in] value 値の文字列
 * @param[out] error エラーコード
 * @param[out] value_length 文字列長
 * @return int 型への変換値
 */
int tp_convert_logical_fort_(long* ptr,char* value,
			     int *error,int* value_length){
  return tp_convertBool(reinterpret_cast<void*>(*ptr),value,error);
}


/** ベクトル型の値の要素数を取得する。Fortrean用API.
 *
 * @param[in] vector_value ベクトル型の値（文字列）
 * @param[out] nvec 要素数 
 * @param[in] vector_length 文字列長
 * @return エラーコード、TextParserErrorによる。intで取得。
 *
 */
int tp_get_number_of_elements_fort_(long* ptr,char* vector_value,unsigned int* nvec,int* vector_length){
  return tp_getNumberOfElements(reinterpret_cast<void*>(*ptr),vector_value,nvec);
} 


/** 指定したindexのベクトル型の値の要素を取得する. Fortran用API.
 *
 * @param[in] vector_value ベクトル型の値（文字列）
 * @param[in] ivec 取得する要素のインデックス
 * @param[out] velem ベクトル値の要素（文字列）
 * @param[in] vector_value_length ベクトル値の文字列長
 * @param[out] velem_length ベクトル値の要素の文字列長
 * @return エラーコード、TextParserErrorによる。intで取得。
 *
 */
int tp_get_ith_element_fort_(long* ptr,char* vector_value,
			     int* ivec,
			     char* velem,
			     int* vector_value_length,
			     int* velem_length){

  unsigned int id_vec;
  char tmp_velem[TP_FORTRAN_BUFFER_SIZE];
  int i;
  int error;
  id_vec=*ivec;
  error = tp_getIthElement(reinterpret_cast<void*>(*ptr),vector_value,id_vec,tmp_velem);
  for(i=0;i<strlen(tmp_velem);++i){
    velem[i]=tmp_velem[i];
  }
  

  return error;

}


  // 
  //カレントノードの取得、ノードの移動 fortran　用 API


int tp_current_node_fort_(long* ptr,char* label,int* label_length){
  return tp_currentNode(reinterpret_cast<void*>(*ptr),label);
}
int tp_change_node_fort_(long* ptr,char* label,int* label_length){
  return tp_changeNode(reinterpret_cast<void*>(*ptr),label);
}
int tp_get_number_of_cnodes_fort_(long* ptr,int* nnodes){
  return tp_getNumberOfCNodes(reinterpret_cast<void*>(*ptr),nnodes);
}
int tp_get_number_of_cleaves_fort_(long* ptr,int* nleaves){
  return tp_getNumberOfCLeaves(reinterpret_cast<void*>(*ptr),nleaves);
}
int tp_get_ith_node_fort_(long* ptr,int* inode,char* node,int* node_length){
  //  TP_DBGOSH << "tp_get_ith_node_fort_" << *inode << std::endl;
  char tmp_node[TP_FORTRAN_BUFFER_SIZE];
  int i;
  int error=tp_getIthNode(reinterpret_cast<void*>(*ptr),*inode,tmp_node);
  for(i=0;i<strlen(tmp_node);++i){
    node[i]=tmp_node[i];
  }

  return error;
}

int tp_get_ith_node_order_fort_(long* ptr,int* inode,char* node,int* order,int* node_length){
  //  TP_DBGOSH << "tp_get_ith_node_fort_" << *inode << std::endl;
  char tmp_node[TP_FORTRAN_BUFFER_SIZE];
  int i;
  int error=tp_getIthNodeOrder(reinterpret_cast<void*>(*ptr),*inode,tmp_node,*order);
  for(i=0;i<strlen(tmp_node);++i){
    node[i]=tmp_node[i];
  }

  return error;
}

int tp_get_ith_leaf_fort_(long* ptr,int* ileaf,char* leaf,int* leaf_length){

  char tmp_leaf[TP_FORTRAN_BUFFER_SIZE];
  int i;
  int error=tp_getIthLeaf(reinterpret_cast<void*>(*ptr),*ileaf,tmp_leaf);
  for(i=0;i<strlen(tmp_leaf);++i){
    leaf[i]=tmp_leaf[i];
  }

  return error;
}
int tp_get_ith_leaf_order_fort_(long* ptr,int* ileaf,char* leaf,int* order,int* leaf_length){

  char tmp_leaf[TP_FORTRAN_BUFFER_SIZE];
  int i;
  int error=tp_getIthLeafOrder(reinterpret_cast<void*>(*ptr),*ileaf,tmp_leaf,*order);
  for(i=0;i<strlen(tmp_leaf);++i){
    leaf[i]=tmp_leaf[i];
  }

  return error;
}


  // tree modify 用関数　Fortran API 用関数

//!< リーフの値を更新する.
  int tp_update_value_fort_(long* ptr,char* label,char*value,
			    int* n_label,int* n_value){

    int error=tp_updateValue(reinterpret_cast<void*>(*ptr),label,value);
    return error;
}
/** リーフを削除する.
 *
 *
 */

  int tp_delete_leaf_fort_(long* ptr,char* label,
			   int* n_label){
    int error=tp_deleteLeaf(reinterpret_cast<void*>(*ptr),label);
    return error;
  }

/** リーフを作成する.
 *
 *
 */
int tp_create_leaf_fort_(long* ptr,char* label,char*value,
			 int* n_label,int* n_value){
  int error=tp_createLeaf(reinterpret_cast<void*>(*ptr),label,value);
  return error;
}



// moved to TextParser class. 30th-July-2012 
/** エラーメッセージを表示する
 *
 * @param[in] error_code エラーコード
 * @param[in] sub_message サブメッセージ
 * @return エラーコード
 *
 */
TextParserError TextParser::TextParserErrorHandler(const TextParserError error_code, const std::string& sub_message)
{
#ifdef MYDEBUG    
  TP_DBGOSH<< "TextParserErrorHandler() start"<<std::endl;
  TP_DBGOSH<< "error_code " <<error_code <<" submessage " <<sub_message<< std::endl;
#endif // MYDEBUG    


  if (error_code > TP_NO_ERROR) {
    if (error_code < TP_WARNING ) {
      TP_ERROSH << "*Error #" << error_code << ": ";
    } else {
      TP_ERROSH << "*Warning #" << error_code << ": ";
    }
    switch (error_code) {
    case TP_DATABASE_NOT_READY_ERROR:
      TP_ERROS << "Database is not ready";
      break;
    case TP_DATABASE_ALREADY_SET_ERROR:
      TP_ERROS << "Database has been already set";
      break;
    case TP_FILEOPEN_ERROR:
      TP_ERROS << "File open failed";
      break;
    case TP_FILEINPUT_ERROR:
      TP_ERROS << "File input failed";
      break;
    case TP_FILEOUTPUT_ERROR:
      TP_ERROS << "File outnput failed";
      break;
    case TP_ENDOF_FILE_ERROR:
      TP_ERROS << "End of file";
      break;
    case TP_ILLEGAL_TOKEN_ERROR:
      TP_ERROS << "Illegal token";
      break;
    case TP_MISSING_LABEL_ERROR:
      TP_ERROS << "Missing label";
      break;
    case TP_ILLEGAL_LABEL_ERROR:
      TP_ERROS << "Illegal label";
      break;
    case TP_ILLEGAL_ARRAY_LABEL_ERROR:
      TP_ERROS << "Illegal array type label";
      break;
    case TP_MISSING_ELEMENT_ERROR:
      TP_ERROS << "Missing element";
      break;
    case TP_ILLEGAL_ELEMENT_ERROR:
      TP_ERROS << "Illegal element";
      break;
    case TP_NODE_END_ERROR:
      TP_ERROS << "too much Node end";
      break;
    case TP_NODE_END_MISSING_ERROR:
      TP_ERROS << "Node termination is Missing";
      break;
    case TP_NODE_NOT_FOUND_ERROR:
      TP_ERROS << "The Node is not found";
      break;
    case TP_LABEL_ALREADY_USED_ERROR:
      TP_ERROS << "Label is already used";
      break;
    case TP_LABEL_ALREADY_USED_PATH_ERROR:
      TP_ERROS << "Label is already used in path";
      break;
    case TP_ILLEGAL_CURRENT_ELEMENT_ERROR:
      TP_ERROS << "Illegal current element ";
      break;
    case TP_ILLEGAL_PATH_ELEMENT_ERROR:
      TP_ERROS << "Illegal path element ";
      break;
    case TP_MISSING_PATH_ELEMENT_ERROR:
      TP_ERROS << "Missing path element";
      break;
    case TP_ILLEGAL_LABEL_PATH_ERROR:
      TP_ERROS << "Illegal label path";
      break;
    case TP_UNKNOWN_ELEMENT_ERROR:
      TP_ERROS << "Unknown element";
      break;
    case TP_MISSING_EQUAL_NOT_EQUAL_ERROR:
      TP_ERROS << "Missing both == and !=";
      break;
    case TP_MISSING_AND_OR_ERROR:
      TP_ERROS << "Missing both && and ||";
      break;
    case TP_MISSING_CONDITION_EXPRESSION_ERROR:
      TP_ERROS << "Missing condition expression";
      break;
    case TP_ILLEGAL_DEPENDENCE_EXPRESSION_ERROR:
      TP_ERROS << "Illegal dependence expression";
      break;
    case TP_MISSING_CLOSED_BRANCKET_ERROR:
      TP_ERROS << "Missing closed brancket";
      break;
    case TP_ILLEGAL_CONDITION_EXPRESSION_ERROR:
      TP_ERROS << "Illegal condition expression";
      break;
    case TP_MISSING_VALUE_ERROR:
      TP_ERROS << "Missing value";
      break;
    case TP_ILLEGAL_VALUE_ERROR:
      TP_ERROS << "Illegal value";
      break;
    case TP_ILLEGAL_NUMERIC_VALUE_ERROR:
      TP_ERROS << "Illegal numeric value";
      break;
    case TP_ILLEGAL_VALUE_TYPE_ERROR:
      TP_ERROS << "Illegal value type";
      break;
    case TP_MISSING_VECTOR_END_ERROR:
      TP_ERROS << "Missing vector end";
      break;
    case TP_VALUE_CONVERSION_ERROR:
      TP_ERROS << "Value conversion failed";
      break;
    case TP_MEMORY_ALLOCATION_ERROR:
      TP_ERROS << "Memory allocation failed";
      break;
    case TP_MISSING_COMMENT_END_ERROR:
      TP_ERROS << "Missing comment end";
      break;
    case TP_ID_OVER_ELEMENT_NUMBER_ERROR:
      TP_ERROS << "ID is over the element number";
      break;
    case TP_GET_PARAMETER_ERROR:
      TP_ERROS << "Get parameter failed";
      break;
    case TP_RANGE_STEP_SIGN_ERROR:
      TP_ERROS << "Wrong sign of step at @range";
      break;
    case  TP_ILLEGAL_RANGE_ERROR:
      TP_ERROS << "Illegal expression of @range";
      break;
    case  TP_ILLEGAL_LIST_ERROR:
      TP_ERROS << "Illegal expression of @list";
      break;
    case TP_UNSUPPORTED_ERROR:
      TP_ERROS << "Unsupported function";
      break;
    case TP_UNDEFINED_VALUE_USED_WARNING:
      TP_ERROS << "Undefined value used";
      break;
    case TP_UNRESOLVED_LABEL_USED_WARNING:
      TP_ERROS << "Unresolved label used";
      break;
    default:
      TP_ERROS << "Undefined error code";
      break;
    }
    //    unsigned int current_line = (TextParserTree::get_instance())->_current_line;
    unsigned int current_line = dataTree()->current_line();
    //unsigned int current_line = TextParserTree::getInstance()->_current_line;
    if (sub_message.size() > 0) TP_ERROS << " : " + sub_message;
    if (current_line > 0) TP_ERROS << " : line " << current_line;
    TP_ERROS << std::endl;
  }


#ifdef MYDEBUG    
  TP_DBGOSH<< "TextParserErrorHandler() end"<<std::endl;
#endif // MYDEBUG    

  return error_code;
}

// @range 
/** 範囲指定 @range で指定された値を取得します。
 *  
 *　@param[in] value 値の文字列(@range 型)
 *　@param[out] from 範囲の始点
 *　@param[out] to 　範囲の終点
  *　@param[out] step　範囲内でのステップ
 *  @return エラーコード
 *
 * "@range" に続く数値が２つのとき、ステップは
 * from < to で step=1
 * from > to で step=-1
*/


TextParserError TextParser::splitRange(const std::string & value,
				       double *from,double *to,double *step){

    TextParserError ret = TP_NO_ERROR;
    std::string vcopy = value;
 
    int pos = vcopy.find("@range");
    if(pos==std::string::npos) {
      ret = TextParserErrorHandler(TP_ILLEGAL_VALUE_TYPE_ERROR, vcopy);      
      return ret;
    } 

    pos = vcopy.find("(");
    if(pos==std::string::npos) {
      ret = TextParserErrorHandler(TP_ILLEGAL_VALUE_TYPE_ERROR, vcopy);      
      return ret;
    } 

    vcopy=vcopy.substr(pos);
    //    TP_DBGOSH << __func__ << " pos " << pos << " vcopy " <<vcopy << std::endl;
    std::vector<std::string> string_content;
    ret = splitVector(vcopy,string_content);
    int ierror;
   
    if(string_content.size()==2||string_content.size()==3){
      *from=convertDouble(string_content[0],&ierror);
      if(ierror != 0) ret = (TextParserError) ierror;
      *to=convertDouble(string_content[1],&ierror);
      if(ierror != 0) ret = (TextParserError) ierror;
      if(string_content.size()==2){
	*step=1.;
	if(*from>*to) *step=-1.;
      }else if(string_content.size()==3){
	*step=convertDouble(string_content[2],&ierror);
	if(ierror != 0) ret = (TextParserError) ierror;
      } else { //something wrong
      }
    }



    return ret;
}

/** 範囲指定 @range で指定された値を展開します。
 *  戻り値expanded は、展開値を入力する直前に clear() されます。
 *　@param[in] value 値の文字列(@range 型)
 *　@param[out] 展開した値　
 *  @return エラーコード
 */


TextParserError TextParser::expandRange(const std::string & value,
					std::vector<double>& expanded){

  TextParserError ret = TP_NO_ERROR;
  double from,to,step;

  ret = splitRange(value,&from,&to,&step);


  double element=from;
  double sign = 1.0;
  if(from > to) { 
    if(step<0){
      sign = -1;
    } else {
      return TextParserErrorHandler(TP_RANGE_STEP_SIGN_ERROR," @range step sign is wrong.");
    }
  }
  else if(from < to) {
    if(step>0){
      // do nothing
    } else {
      return TextParserErrorHandler(TP_RANGE_STEP_SIGN_ERROR," @range step sign is wrong.");
    }
  } else {
      return TextParserErrorHandler(TP_ILLEGAL_RANGE_ERROR," @range expression is wrong.");
  }

  expanded.clear();

  while(element*sign<=to*sign){
    // TP_DBGOSH << element <<std::endl;
    expanded.push_back(element);
    element += step;
  }

  //    TP_RANGE_STEP_SIGN_ERROR
  //    TP_ILLEGAL_RANGE_ERROR

  return TP_NO_ERROR;
}
  
/** 範囲指定 @list で指定された値を展開します。
 *
 *　@param[in] value 値の文字列(@list 型)
 *　@param[out] list 展開する値
 *　@param[out] order リスト内の順序
 *  @return エラーコード
 */

  // @list
TextParserError TextParser::splitList(const std::string & value,std::vector<double>& list,
				      TextParserSortOrder order){
    TextParserError ret = TP_NO_ERROR;
    std::string vcopy = value;
 
    int pos = vcopy.find("@list");
    if(pos==std::string::npos) {
      ret = TextParserErrorHandler(TP_ILLEGAL_VALUE_TYPE_ERROR, vcopy);      
      return ret;
    } 

    pos = vcopy.find("(");
    if(pos==std::string::npos) {
      ret = TextParserErrorHandler(TP_ILLEGAL_VALUE_TYPE_ERROR, vcopy);      
      return ret;
    } 

    vcopy=vcopy.substr(pos);
    //    TP_DBGOSH << __func__ << " pos " << pos << " vcopy " <<vcopy << std::endl;
    std::vector<std::string> string_content;
    ret = splitVector(vcopy,string_content);
    int ierror;

    list.clear();


    for(std::vector<std::string>::iterator it=string_content.begin();
	it!=string_content.end(); ++it){
      list.push_back(convertDouble((*it),&ierror));
      if(ierror != 0) ret = (TextParserError) ierror;
    }

    switch(order){

    case TP_SORT_ASCENDING:
      std::sort(list.begin(),list.end()); 
      break;
    case TP_SORT_DESCENDING:
      std::sort(list.begin(),list.end(),std::greater<double>()); 
      break;
    case TP_SORT_NONE:
      break;
    default:
      break;
    }

     return ret;
  }

/** 整数のlimit 指定の変換.
 *　
 * @param[in] value 値の文字列.
 * @param[out] ierror エラーステータス.
 * @return 変換後のlimit値 long long.
 *
 */

 
long long TextParser::convertLimitsIntx(const std::string& value,int* ierror){

  long long returner;

      if(dataTree()->checkNumericalLimits(value)){

	if ( value== "CHAR_MIN"){
	  returner = std::numeric_limits<char>::min();
	}else if ( value== "CHAR_MAX"){
	  returner = std::numeric_limits<char>::max();
	}else if ( value== "SHORT_MIN"){
	  returner = std::numeric_limits<short>::min();
	}else if ( value== "SHORT_MAX"){
	  returner = std::numeric_limits<short>::max();
	}else if ( value== "INT_MIN"){
	  returner = std::numeric_limits<int>::min();
	}else if ( value== "INT_MAX"){
	  returner = std::numeric_limits<int>::max();
	}else if ( value== "LONG_MIN"){
	  returner = std::numeric_limits<long>::min();
	}else if ( value== "LONG_MAX"){
	  returner = std::numeric_limits<long>::max();
	}else if ( value== "LONGLONG_MIN"){
	  returner = std::numeric_limits<long long>::min();
	}else if ( value== "LONGLONG_MAX"){
	  returner = std::numeric_limits<long long>::max();
	} else {
	  *ierror = 130;
	  returner = 0;
	}
      } else {
	  *ierror = 130;
	  returner = 0;
      }

      //      TP_DBGOSH << __func__ << returner <<std::endl;
      return returner;
}

/** 実数のlimit 指定の変換.
 *　
 * @param[in] value 値の文字列.
 * @param[out] ierror エラーステータス.
 * @return 変換後のlimit値 double.
 *
 */

 
double TextParser::convertLimitsRealx(const std::string& value,int* ierror){

  double returner;

      if(dataTree()->checkNumericalLimits(value)){

	if ( value== "FLOAT_MIN"){
	  returner = std::numeric_limits<float>::min();
	}else if ( value== "FLOAT_MAX"){
	  returner = std::numeric_limits<float>::max();
	}else if ( value== "DOUBLE_MIN"){
	  returner = std::numeric_limits<double>::min();
	}else if ( value== "DOUBLE_MAX"){
	  returner = std::numeric_limits<double>::max();
	} else {
	  *ierror = 130;
	  returner = 0;
	}
      } else {
	  *ierror = 130;
	  returner = 0;
      }

      //      TP_DBGOSH << __func__ << returner <<std::endl;
      return returner;
}



// @range @list 用API
//@range 
int tp_split_range_fort_(long* ptr,char* value,double *from,double *to,double *step, int* nvalue){
  return tp_splitRange(reinterpret_cast<void*>(*ptr),value,from,to,step);
}
int tp_expand_range_fort_(long* ptr,char* value,double* expanded,int* nvalue){
  return tp_expandRange(reinterpret_cast<void*>(*ptr),value,expanded);
}
// @list
int tp_split_list_fort_(long* ptr,char* value, double *list,int* order,int* nvalue){
  return tp_splitList(reinterpret_cast<void*>(*ptr),value,list,(*order));
}


//---------------------------------------------------
// C++便利メソッド群
//---------------------------------------------------
// ラベルの有無をチェック
bool TextParser::chkLabel(const std::string label)
{
  int ierror;
  std::string value;
  
  // ラベルがあるかチェック
  std::vector<std::string> labels;
  ierror=getAllLabels(labels);
  if (ierror != 0)
  {
    TP_ERROSH << __func__ << " getAllLabels(" << label << ") failed." << std::endl;
    return false;
  }
  
  int flag=0;
  for (int i = 0; i < labels.size(); i++)
  {
	if( !strcasecmp(label.c_str(), labels[i].c_str()) )
    {
      flag=1;
      break;
    }
  }
  
  if (flag==0)
  {
    TP_ERROSH << __func__ << " label:" << label << " is not available." << std::endl;
    return false;
  }
  return true;
}

// ノードの有無をチェック
bool TextParser::chkNode(const std::string label)
{
  int ierror;
  std::string node;
  std::vector<std::string> labels;
  int len=label.length();
  
  // Nodeがあるかチェック
  ierror = getAllLabels(labels);
  if (ierror != 0)
  {
    TP_ERROSH << __func__ << " getAllLabels(" << label << ") failed." << std::endl;
    return false;
  }
  
  int flag=0;
  for (int i = 0; i < labels.size(); i++) {
	  node = labels[i].substr(0,len);
    if ( !strcasecmp(node.c_str(), label.c_str()) )
    {
      flag=1;
      break;
    }
  }
  
  if (flag==0)
  {
    TP_ERROSH << __func__ << " label:" << label << " is not available." << std::endl;
    return false;
  }
  return true;
}

// ノード以下のラベルの数を数える
int TextParser::countLabels(const std::string label)
{
  int ierror;
  std::string node,str,chkstr="";
  std::vector<std::string> labels;
  int len=label.length();
  int flag=0;
  int inode=0;
  int next=0;
  
  // Nodeがあるかチェック
  ierror=getAllLabels(labels);
  if (ierror != 0){
    return -1;
  }
  
  for (int i = 0; i < labels.size(); i++) {
    node=labels[i].substr(0,len);
 
    if( !strcasecmp(node.c_str(), label.c_str()) ){
      str=labels[i].substr(len+1);
      next=str.find("/");
      if(next==0) inode++;
      else{
        if(chkstr!=str.substr(0,next)){
          chkstr=str.substr(0,next);
          inode++;
        }
      }
    }
  }
  return inode;
}

// ノード以下のnnode番目の文字列を取得する
bool TextParser::getNodeStr(const std::string label, const int nnode, std::string &ct)
{
  int ierror;
  int len=label.length();
  int flag=0;
  int inode=0;
  int next=0;
  
  std::string node;
  std::string str;
  std::string chkstr="";
  std::vector<std::string> labels;

  // Nodeがあるかチェック
  ierror = getAllLabels(labels);
  if (ierror != 0)
  {
    return false;
  }
  
  for (int i = 0; i < labels.size(); i++) {
    node = labels[i].substr(0, len);
    if ( !strcasecmp(node.c_str(), label.c_str()) )
    {
      str = labels[i].substr(len+1);
      next = str.find("/");
      if ( next == 0 )
      {
        inode++;
      }
      else
      {
        if ( chkstr != str.substr(0, next) )
        {
          chkstr = str.substr(0, next);
          inode++;
        }
      }
      if ( inode == nnode )
      {
        ct = chkstr;
        return true;
      }
    }
  }
  return false;
}

// ベクトル値を取得する（整数型）
bool TextParser::getInspectedVector(const std::string label, int *vec, const int nvec)
{
  int ierr = TP_NO_ERROR;
  std::string value;

  // ラベルがあるかチェック
  if( !chkLabel(label)){
	  return false;
  }

  // get value
  if( (ierr = getValue(label, value)) != TP_NO_ERROR ) return false;

  // get type
  TextParserValueType type = getType(label, &ierr);
  if( ierr != TP_NO_ERROR ) return false;
  if( type != TP_VECTOR_NUMERIC ) return false;

  // split
  std::vector<std::string> vec_value;
  if( (ierr = splitVector(value, vec_value)) != TP_NO_ERROR ) return false;

  // check number of vector element
  if( vec_value.size() != nvec ) return false;

  // string to real
  for(int i=0; i<vec_value.size(); i++ )
  {
    vec[i] = convertInt(vec_value[i], &ierr);
    if( ierr != TP_NO_ERROR ) return false;
  }

  return true;
}


// ベクトル値を取得する（double型）
bool TextParser::getInspectedVector(const std::string label, double *vec, const int nvec)
{
  int ierr = TP_NO_ERROR;
  std::string value;

  // ラベルがあるかチェック
  if( !chkLabel(label)){
    return false;
  }

  // get value
  if ( (ierr = getValue(label, value)) != TP_NO_ERROR )
  {
    return false;
  }

  // get type
  TextParserValueType type = getType(label, &ierr);
  if( ierr != TP_NO_ERROR ) return false;
  if( type != TP_VECTOR_NUMERIC ) return false;

  // split
  std::vector<std::string> vec_value;
  if( (ierr = splitVector(value, vec_value)) != TP_NO_ERROR ) return false;

  // check number of vector element
  if( vec_value.size() != nvec ) return false;

  // string to real
  for(int i=0; i<vec_value.size(); i++ )
  {
    vec[i] = convertDouble(vec_value[i], &ierr);
    if( ierr != TP_NO_ERROR ) return false;
  }

  return true;
}

// ベクトル値を取得する（float型）
bool TextParser::getInspectedVector(const std::string label, float *vec, const int nvec)
{
  int ierr = TP_NO_ERROR;
  std::string value;
  
  // ラベルがあるかチェック
  if( !chkLabel(label)){
    return false;
  }
  
  // get value
  if ( (ierr = getValue(label, value)) != TP_NO_ERROR )
  {
    return false;
  }
  
  // get type
  TextParserValueType type = getType(label, &ierr);
  if( ierr != TP_NO_ERROR ) return false;
  if( type != TP_VECTOR_NUMERIC ) return false;
  
  // split
  std::vector<std::string> vec_value;
  if( (ierr = splitVector(value, vec_value)) != TP_NO_ERROR ) return false;
  
  // check number of vector element
  if( vec_value.size() != nvec ) return false;
  
  // string to real
  for(int i=0; i<vec_value.size(); i++ )
  {
    vec[i] = convertFloat(vec_value[i], &ierr);
    if( ierr != TP_NO_ERROR ) return false;
  }
  
  return true;
}


// ベクトル値を取得する（文字列型）
bool TextParser::getInspectedVector(std::string label, std::string *vec, const int nvec)
{
  int ierr = TP_NO_ERROR;
  std::string value;

  // ラベルがあるかチェック
  if( !chkLabel(label)){
	  return false;
  }

  // get value
  if( (ierr = getValue(label, value)) != TP_NO_ERROR ) return false;

  // get type
  TextParserValueType type = getType(label, &ierr);
  if( ierr != TP_NO_ERROR ) return false;
  if( type != TP_VECTOR_NUMERIC ) return false;

  // split
  std::vector<std::string> vec_value;
  if( (ierr = splitVector(value, vec_value)) != TP_NO_ERROR ) return false;

  // check number of vector element
  if( vec_value.size() != nvec ) return false;

  // string to string
  for(int i=0;i<vec_value.size();i++ )
  {
    vec[i] = vec_value[i];
  }

  return true;
}

// 変数を取得する（整数型）
bool TextParser::getInspectedValue(const std::string label, int &ct )
{
  int ierror;
  std::string value;
  
  // ラベルがあるかチェック
  if( !chkLabel(label)){
	  return false;
  }

  //値の取得
  ierror=getValue(label,value);//labelは絶対パスを想定
  if (ierror != TP_NO_ERROR){
    return false;
  }

  //型の取得
  TextParserValueType type = getType(label, &ierror);
  if (ierror != TP_NO_ERROR){
    return false;
  }
  if( type != TP_NUMERIC_VALUE ){
    return false;
  }

  // string to int
  int val = convertInt(value, &ierror);
  if (ierror != TP_NO_ERROR){
    return false;
  }
  ct=val;
  return true;
}

// 変数を取得する（double実数型）
bool TextParser::getInspectedValue(const std::string label, double &ct )
{
  int ierror;
  std::string value;
  std::string node;

  // ラベルがあるかチェック
  if( !chkLabel(label)){
	  return false;
  }

  //値の取得
  ierror=getValue(label,value);//labelは絶対パスを想定
  if (ierror != TP_NO_ERROR){
	return false;
  }

  //型の取得
  TextParserValueType type = getType(label, &ierror);
  if (ierror != TP_NO_ERROR){
	return false;
  }
  if( type != TP_NUMERIC_VALUE ){
	return false;
  }

  // string to real
  double val = convertDouble(value, &ierror);
  if (ierror != TP_NO_ERROR){
	return false;
  }
  ct=val;
  return true;
}

// 変数を取得する（float実数型）
bool TextParser::getInspectedValue(const std::string label, float &ct )
{
  double dval;
  bool res = getInspectedValue( label, dval );
  if ( res ) {
    ct = (float)dval;
  }
  return res;
}

// 変数を取得する（文字列型）
bool TextParser::getInspectedValue(const std::string label, std::string &ct )
{
  int ierror;
  std::string value;
  
  // ラベルがあるかチェック
  if ( !chkLabel(label) )
  {
    return false;
  }
  
  //値の取得
  ierror = getValue(label, value); //labelは絶対パスを想定
  
  if (ierror != TP_NO_ERROR)
  {
    return false;
  }
  
  //型の取得
  TextParserValueType type = getType(label, &ierror);
  if (ierror != TP_NO_ERROR)
  {
    return false;
  }
  
  if( type != TP_STRING_VALUE )
  {
    return false;
  }
  ct=value;
  return true;
}


// ラベルリストを作成する
// @note ラベルはパラメータファイルの出現順(2)
bool TextParser::getLabelVector(const std::string root, std::vector<std::string>& nodes)
{
  if ( changeNode(root) ) return false; // 0 - no error
  
  getNodes(nodes, 2);
  
  return true;
}


// 指定ノードのラベル文字列を作成
int TextParser::getArrayLabels(const std::string label, std::vector<std::string> &labels)
{
  int ierror;
  std::vector<std::string> all_labels;
  int count=0;

  // labelを正規表現文字列に
  std::string regex_label = label;
  // /,[,]をエスケープ
  size_t pos=0;
  while( (pos=regex_label.find('/', pos))!=std::string::npos ) {
	regex_label.replace( pos, 1, "\\/" );
    pos+=2;
  }
  pos=0;
  while( (pos=regex_label.find('[', pos))!=std::string::npos ) {
	regex_label.replace( pos, 1, "\\[" );
    pos+=2;
  }
  pos=0;
  while( (pos=regex_label.find(']', pos))!=std::string::npos ) {
	regex_label.replace( pos, 1, "\\]" );
    pos+=2;
  }
  // @を正規表現に変換
  while( (pos=regex_label.find('@'))!=std::string::npos ) {
	// [[:digit:]]+ に置換
	regex_label.replace( pos, 1, "[[:digit:]]+" );
  }
  // 正規表現コンパイル
  regex_t preg;
  if(regcomp( &preg, regex_label.c_str(), REG_EXTENDED|REG_ICASE ) != 0) {
    return -1;
  };

  ierror=getAllLabels(all_labels);
  if (ierror != 0){
    regfree(&preg);
    return -1;
  }
  
  size_t nmatch = 1;
  regmatch_t pmatch[nmatch];
  for (int i = 0; i < all_labels.size(); i++) {
    // 正規表現で一致したラベルのみ
    if( regexec( &preg, all_labels[i].c_str(), nmatch, pmatch, 0 ) == 0 ) {
      std::string matched = all_labels[i].substr( pmatch[0].rm_so, pmatch[0].rm_eo );
      // 重複した一致結果は追加しない
      bool found = false;
      for( int j=0; j<labels.size(); j++ ) {
        if( labels[j].compare(matched)==0 ) {
          found = true;
          break;
        }
      }
      if( !found ) {
        labels.push_back( matched );
        count++;
      }
    }
  }
  regfree(&preg);
  return count;
}

