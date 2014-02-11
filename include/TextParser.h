// -*- mode: c++ -*-
/*
 * TextParser - Text Parsing Library
 *
 * Copyright (C) 2012-2014 Institute of Industrial Science, The University of Tokyo.
 * All rights reserved.
 *
 */

/** @file TextParser.h
 * ここには TextParser クラス　と C用 Fortran 用 API 関数が定義されています。
 *
 */

#ifndef __TEXTPARSER_H__
#define __TEXTPARSER_H__


//# define TP_FORTRAN_BUFFER_SIZE 128
# define TP_FORTRAN_BUFFER_SIZE 1024
//#include <varargs.h>
//#include <stdarg.h>

// for Debug or On-Error output
#define TP_DBGOS	std::cout
#define TP_DBGOSH	std::cout<<"TP:"
#define TP_ERROS	std::cerr
#define TP_ERROSH	std::cerr<<"TP:"


#include "TextParserCommon.h"
#ifdef __cplusplus
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>
#include <math.h>
#include <limits>
#include <vector>
//#include "TextParserElement.h"
//#include "TextParserTree.h"
#endif // __cplusplus

#ifdef __cplusplus

#include "Version.h"

class TextParserTree;

/** 
 * @class TextParser TextParser.h
 * @brief TextParserライブラリのAPIクラス TextParser が定義されています.
 * パラメータのファイルからの読み込み、
 * パラメータのデータ構造のファイルへの書き出し、
 * パラメータのデータ構造へのアクセス、
 * パラメータ（文字列）の変換、
 * 及びそのヘルパー関数が定義されています。
 * 現時点ではSingletonパターンで実装されています。
 */


class TextParser{

  // basic functions for object manipulation.
public:
  void status();
public:
  static TextParser* get_instance_singleton(); //!< TextParser のインスタンスを取得します。
public:
  TextParserError read(const std::string& file); //!< file からパラメータを読み込みます。MPI利用時は、rank数=0 のプロセスでのみファイル内容を読み込み、各ノードに分配後、各ノードでパラメータの解析を行います。
public:
  TextParserError read_local(const std::string& file); //!< MPI利用時に各ノードがそれぞれのファイルからパラメータを読み込みます。 MPIを利用しない場合は、エラーを返します。  
public:
  TextParserError write(const std::string& file,int order=0); //!< file にパラメータのデータ構造全体を書き込みます。
public:
  TextParserError remove();//!< 格納しているパラメータのデータを破棄します。

  // functions for operation of information in tree.

public:
  TextParserError getAllLabels(std::vector<std::string>& labels);//!< 格納されているパラメータへの(リーフへの)全てのラベルを取得します。
public:
  TextParserValueType getType(const std::string& label, int *error);//!<ラベルで示されるパラメータの値のタイプを返します。（TextParserError参照） 
public:
  TextParserError getValue(const std::string& label,std::string& value);//!< ラベルで示されるパラメータの値を取得します。
public:
  void getValue(const std::string& label,std::string& value, int*ierror);//!< ラベルで示されるパラメータの値を取得します。
public:
  TextParserError currentNode(std::string& returner); //!<現在のカレントノードを取得します。
public:
  TextParserError getNodes(std::vector<std::string>& node_list,int oswitch=0);//!<カレントノード内の子ノードのラベル（相対パス）のリストを取得します。
public:
  TextParserError getLabels(std::vector<std::string>& labels,int oswitch=0);//!<カレントノード内のリーフのラベル（相対パス）のリストを取得します。
  // 名前はこちらの方がよい？
public:
  TextParserError getLeaves(std::vector<std::string>& labels,int oswitch=0){
    return getLabels(labels,oswitch);
  }//!<カレントノード内のリーフのラベル（相対パス）のリストを取得します。
public:
  TextParserError changeNode(const std::string& label);//!< ラベルで指定したノードをカレントノードにします。


  //convertion funcitons for value string you obtained.
public:
  char convertChar(const std::string& value, int *error); //!< パラメータの値を文字列から char 型へ変換します。 
public:
  short convertShort(const std::string& value, int *error);//!< パラメータの値を文字列から short 型へ変換します。 
public:
  int convertInt(const std::string& value, int *error); //!< パラメータの値を文字列から int 型へ変換します。 
public:
  long convertLong(const std::string& value, int *error); //!< パラメータの値を文字列から long 型へ変換します。 
public:
  long long convertLongLong(const std::string& value, int *error);//!< パラメータの値を文字列から long long 型へ変換します。 
public:
  float convertFloat(const std::string& value, int *error);//!< パラメータの値を文字列から float 型へ変換します。 
public:
  double convertDouble(const std::string& value, int *error);//!< パラメータの値を文字列から double 型へ変換します。 
public:
  bool convertBool(const std::string& value, int *error);//!< パラメータの値を文字列から bool 型へ変換します。 
public:
  TextParserError splitVector(const std::string& vector_value,
			      std::vector<std::string>& velem );//!<ベクトル値を分割する。
private:
  long long convertLimitsIntx(const std::string& value, int *error);//!< 整数のlimit値の変換
private:
  double convertLimitsRealx(const std::string& value, int *error);//!< 実数のlimit値の変換

public:
 TextParserTree* dataTree() const {return _data_tree;} //!< パラメータデータ構造へのポインタ。

  // TextParserTree データ書き換え用API
public:
  TextParserError updateValue(const std::string& label,const std::string& value); //!< パラメータリーフ　のvalue変更
public:
  TextParserError deleteLeaf(const std::string& label); //!< パラメータリーフの削除
public:
  TextParserError createLeaf(const std::string& label,const std::string& value); //!< パラメータリーフ追加

  // @range 
public:
  TextParserError splitRange(const std::string & value,
			     double *from,double *to,double *step);

public:
  TextParserError expandRange(const std::string & value,
			      std::vector<double>& expanded);
  
  // @list
public:
  TextParserError splitList(const std::string & value,std::vector<double>& list,
			    TextParserSortOrder order=TP_SORT_NONE);

  
  /**
   * @brief バージョン番号の文字列を返す
   */
public:
  std::string getVersionInfo()
  {
    std::string str(TP_VERSION_NO);
    return str;
  }

  /**
   * @brief 指定ラベルのベクトル値を取得する（整数型）
   * @param [int] label 取得するベクトルのラベル（絶対パス）
   * @param [out] vec   ベクトル格納配列ポインタ
   * @param [in]  nvec  ベクトルサイズ
   * @note ラベルに配列的表現を含む場合、必ず実indexを指定すること。
   */
public:
	bool getInspectedVector(const std::string label, int *vec, const int nvec );
  
  /**
   * @brief 指定ラベルのベクトル値を取得する（double型）
   * @param [in]  label  取得するベクトルのラベル（絶対パス）
   * @param [out] vec    ベクトル格納配列ポインタ
   * @param [in]  nvec   ベクトルサイズ
   * @note ラベルに配列的表現を含む場合、必ず実indexを指定すること。
   */
public:
	bool getInspectedVector(const std::string label, double *vec, const int nvec );
  
  
  /**
   * @brief 指定ラベルのベクトル値を取得する（float型）
   * @param [in]  label  取得するベクトルのラベル（絶対パス）
   * @param [out] vec    ベクトル格納配列ポインタ
   * @param [in]  nvec   ベクトルサイズ
   * @note ラベルに配列的表現を含む場合、必ず実indexを指定すること。
   */
public:
	bool getInspectedVector(const std::string label, float *vec, const int nvec );
  
  
  /**
   * @brief 指定ラベルのベクトル値を取得する（文字列型）
   * @param [in]  label  取得するベクトルのラベル（絶対パス）
   * @param [out] vec    ベクトル格納配列ポインタ
   * @param [in]  nvec   ベクトルサイズ
   * @note ラベルに配列的表現を含む場合、必ず実indexを指定すること。
   */
public:
	bool getInspectedVector(const std::string label, std::string *vec, const int nvec );
  
  /**
   * @brief 指定ラベルの変数を取得する（整数型）
   * @param [in]  label 取得する変数のラベル（絶対パス）
   * @param [out] ct    変数返却用
   * @note ラベルに配列的表現を含む場合、必ず実indexを指定すること。
   */
public:
	bool getInspectedValue(const std::string label, int &ct );
  
  /**
   * @brief 指定ラベルの変数を取得する（double実数型）
   * @param [in]  label 取得する変数のラベル（絶対パス）
   * @param [out] ct    変数返却用
   * @note ラベルに配列的表現を含む場合、必ず実indexを指定すること。
   */
public:
	bool getInspectedValue(const std::string label, double &ct );
  
  /**
   * @brief 指定ラベルの変数を取得する（float実数型）
   * @param [in]  label 取得する変数のラベル（絶対パス）
   * @param [out] ct    変数返却用
   * @note ラベルに配列的表現を含む場合、必ず実indexを指定すること。
   */
public:
	bool getInspectedValue(const std::string label, float &ct );
  
  /**
   * @brief 指定ラベルの変数を取得する（文字列型）
   * @param [in]  label 取得する変数のラベル（絶対パス）
   * @param [out] ct    変数返却用
   * @note ラベルに配列的表現を含む場合、必ず実indexを指定すること。
   */
public:
	bool getInspectedValue(const std::string label, std::string &ct );
  
  
  /**
   * @brief ラベルリストを作成し，重複をチェックする
   * @param [in] root  テストするパラメータディレクトリ
   * @param [in] nodes ラベルvector
   */
public:
  bool getLabelVector(const std::string root, std::vector<std::string>& nodes);
  
	
  /**
   * @brief ラベルの有無をチェック
   * @param [in] label チェックするラベル（絶対パス）
   * @note ラベルに配列的表現を含む場合、必ず実indexを指定すること。
   */
public:
	bool chkLabel(const std::string label);
  
  /**
   * @brief ノードの有無をチェック
   * @param [in] label チェックするノード（絶対パス）
   * @note ラベルに配列的表現を含む場合、必ず実indexを指定すること。
   */
public:
	bool chkNode(const std::string label);
  
  /**
   * @brief ノード以下のnnode番目の文字列を取得する
   * @param [in]  label ノードの絶対パス
   * @param [in]  nnode 取得する文字列が現れる順番
   * @param [out] ct    取得した文字列
   * @note ラベルに配列的表現を含む場合、必ず実indexを指定すること。
   */
public:
	bool getNodeStr(const std::string label, const int nnode, std::string &ct);
  
  /**
   * @brief 指定ノード直下のラベルの数を数える
   * @param [in] label ラベルを数えるノードの絶対パス
   * @retval ラベルの数（エラー、もしくはない場合は-1を返す）
   * @note ラベルに配列的表現を含む場合、必ず実indexを指定すること。
   */
public:
  int countLabels(const std::string label);

  /**
   * @brief 指定ノードのラベル文字列を作成。
   *        引数labelに配列的表現([@])を含むと一致する全てのラベル文字列を返す
   * @param [in] label ノードの絶対パス
   * @param [out] labels ラベル文字列のリスト
   * @retval ラベルの数（エラーの場合は-1を返す）
   */
public:
  int getArrayLabels(const std::string label, std::vector<std::string> &labels);



private:
  TextParserTree* _data_tree; //!< パラメータデータ構造へのポインタ。

 public:
   TextParser(); //!< デフォルトコンストラクタ 
 public:
  ~TextParser();//!< デストラクタ。パラメータデータ構造を消去します。
 public:
  //ERRORHANDLER
  TextParserError TextParserErrorHandler(const TextParserError error_code, const std::string& sub_message);

};


#endif /* __cplusplus */


// C / Fortran 用　API 関数 

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
  typedef void* TP_HANDLE;

  // for c_interfaces
  TP_HANDLE tp_getInstanceSingleton(); //!< TextParser シングルトンインスタンスへのポインタを取得します。
  TP_HANDLE tp_createInstance(); //!< TextParser インスタンスを生成してそのポインタを取得します。
  int tp_deleteInstance(TP_HANDLE tp_hand); //!< TextParser インスタンスをdeleteします。

  int tp_read(TP_HANDLE tp_hand,char* file); //!< file からパラメータを読み込みます.  C用API.
  int tp_read_local(TP_HANDLE tp_hand,char* file); //!< file からパラメータを読み込みます.  C用API.
  int tp_write(TP_HANDLE tp_hand,char* file); //!< file にパラメータのデータ構造全体を書き込みます. C用API.
  int tp_remove(TP_HANDLE tp_hand);//!< 格納しているパラメータのデータを破棄します。 C用API.
  // full path access
  int tp_getNumberOfLeaves(TP_HANDLE tp_hand,unsigned int* Nleaves);//!< リーフの総数を取得します。C用API.
  int tp_getLabel(TP_HANDLE tp_hand,int ilabel,char* label);//!< インデックスで指定したリーフのラベルを取得します。C用API.

  // value and value type
  int tp_getType(TP_HANDLE tp_hand,char* label,int* type);//!< ラベルで指定したリーフのタイプを取得します。C用API.
  int tp_getValue(TP_HANDLE tp_hand,char* label,char* value);//!< ラベルで指定したリーフの値を取得します。C用API.

  //値の変換
  char tp_convertChar(TP_HANDLE tp_hand,char* value,
		      int *error); //!< パラメータの値を文字列から char 型へ変換します。C用API.
  short tp_convertShort(TP_HANDLE tp_hand,char* value,
			int *error);//!< パラメータの値を文字列から short 型へ変換します。 C用API.
  int tp_convertInt(TP_HANDLE tp_hand,char* value,
		    int *error); //!< パラメータの値を文字列から int 型へ変換します。C用API. 
  long tp_convertLong(TP_HANDLE tp_hand,char* value,
		      int *error); //!< パラメータの値を文字列から long 型へ変換します。 C用API.
  long long tp_convertLongLong(TP_HANDLE tp_hand,char* value,
			       int *error);//!< パラメータの値を文字列から long long 型へ変換します。C用API. 
  float tp_convertFloat(TP_HANDLE tp_hand,char* value,
			int *error);//!< パラメータの値を文字列から float 型へ変換します。 C用API.
  double tp_convertDouble(TP_HANDLE tp_hand,char* value,
			  int *error);//!< パラメータの値を文字列から double 型へ変換します。 C用API.
  int tp_convertBool(TP_HANDLE tp_hand,char* value,
		     int *error);//!< パラメータの値を文字列から int 型 でbool型を表現したものへ変換します。 C用API.

  //ベクトル値の操作
  int tp_getNumberOfElements(TP_HANDLE tp_hand,char* vector_value,unsigned int* nvec ); //!<ベクトル値の要素数　C用API.
  int tp_getIthElement(TP_HANDLE tp_hand,char* vector_value,unsigned int ivec,char* velem );//!<ベクトル値のivec番目の要素を取得する。C用API.

  //カレントノードの取得、ノードの移動
  int tp_currentNode(TP_HANDLE tp_hand,char*); //!<現在のカレントノードを取得します。C用API.
  int tp_changeNode(TP_HANDLE tp_hand,char*);//!< ラベルで指定したノードをカレントノードにします。C用API.
  int tp_getNumberOfCNodes(TP_HANDLE tp_hand,int* nnodes);//!< カレントノードにある子ノードの数を取得します。C用API.
  int tp_getNumberOfCLeaves(TP_HANDLE tp_hand,int* nleaves);//!< カレントノードにあるリーフの数を取得します。C用API.
  int tp_getIthNode(TP_HANDLE tp_hand,int inode,char* node);//!< カレントノードにあるinode番目のノードのラベルを取得します。C用API.
  int tp_getIthLeaf(TP_HANDLE tp_hand,int ileaf,char* leaf);//!< カレントノードにあるileaf番目のリーフのラベルを取得します。C用API.
  int tp_getIthNodeOrder(TP_HANDLE tp_hand,int inode,char* node,int order);//!< カレントノードにあるinode番目のノードのラベルを取得します。C用API.
  int tp_getIthLeafOrder(TP_HANDLE tp_hand,int ileaf,char* leaf,int order);//!< カレントノードにあるileaf番目のリーフのラベルを取得します。C用API.


  // tree modify 用関数　C用API
  int tp_updateValue(TP_HANDLE tp_hand,char* label,char*value); //!< リーフの値を更新する.
  int tp_deleteLeaf(TP_HANDLE tp_hand,char* label); //!< リーフを削除する.
  int tp_createLeaf(TP_HANDLE tp_hand,char* label,char*value); //!< リーフを作成する.


  //
  // @range @list 用API
  //@range 
  int tp_splitRange(TP_HANDLE tp_hand,char* value,double *from,double *to,double *step);
  int tp_expandRange(TP_HANDLE tp_hand,char* value,double* expanded);
    // @list
  int tp_splitList(TP_HANDLE tp_hand,char* value, double *list,int order);


  //fortran 用 API

  int tp_get_instance_singleton_fort_(long* ptr); //!< TextParser シングルトンインスタンスへのポインタを取得します。 Fortran 用API
  int tp_create_instance_fort_(long* ptr); //!< TextParser インスタンスを生成してそのポインタを取得します。  Fortran 用API
  int tp_delete_instance_fort_(long* ptr); //!< TextParser インスタンスを削除します.  Fortran 用API

  int tp_read_fort_(long* ptr,char* file,int* length);//!< file からパラメータを読み込みます. Fortran用API.
  int tp_read_local_fort_(long* ptr,char* file,int* length);//!< file からパラメータを読み込みます. Fortran用API.
  int tp_write_fort_(long* ptr,char* file,int* length);//!< file にパラメータのデータ構造全体を書き込みます. Fortran用API. 
  int tp_remove_fort_(long* ptr);//!< 格納しているパラメータのデータを破棄します。 Fortran用API. 
  int tp_get_number_of_leaves_fort_(long* ptr,int* nleaves );//!< リーフの総数を取得します。 Fortran用API. 
  int tp_get_label_fort_(long* ptr,int* ileaf,char* label,int* length);//!< インデックスで指定したリーフのラベルを取得します。 Fortran用API. 

  int tp_get_type_fort_(long* ptr,char* label,int* type,int* label_length);//!< ラベルで指定したリーフのタイプを取得します。 Fortran用API. 
  int tp_get_value_fort_(long* ptr,char* label,char* value,int* label_length,int* value_length);//!< ラベルで指定したリーフの値を取得します。 Fortran用API. 

  // 型変換用関数
  char tp_convert_char_fort_(long* ptr,char* value,
			     int *error,int* value_length); //!< パラメータの値を文字列から char 型へ変換します。Fortran用API.
  short tp_convert_short_fort_(long* ptr,char* value,
			int *error,int* value_length);//!< パラメータの値を文字列から short 型へ変換します。 Fortran用API.
  int tp_convert_int_fort_(long* ptr,char* value,
		     int *error,int* value_length); //!< パラメータの値を文字列から int 型へ変換します。Fortran用API. 
  long tp_convert_long_fort_(long* ptr,char* value,
		      int *error,int* value_length); //!< パラメータの値を文字列から long 型へ変換します。 Fortran用API.
   long long tp_convert_long_long_fort_(long* ptr,char* value,
  			       int *error,int* value_length);//!< パラメータの値を文字列から long long 型へ変換します。Fortran用API. 
  float tp_convert_float_fort_(long* ptr,char* value,
			       int *error,int* value_length);//!< パラメータの値を文字列から float 型へ変換します。 Fortran用API.
  double tp_convert_double_fort_(long* ptr,char* value,
			  int *error,int* value_length);//!< パラメータの値を文字列から double 型へ変換します。 Fortran用API.
  int tp_convert_logical_fort_(long* ptr,char* value,
		     int *error,int* value_length);//!< パラメータの値を文字列から int 型 でbool型を表現したものへ変換します。 Fortran用API.
  //ベクトル値の操作
  int tp_get_number_of_elements_fort_(long* ptr,char* vector_value,unsigned int* nvec,int* vector_length); //!<ベクトル値の要素数の取得  Fortran用API. 
  int tp_get_ith_element_fort_(long* ptr,char* vector_value, int* ivec,char* velem ,int* vector_value_length,int* velem_length);//!<ベクトル値のivec番目の要素を取得する。 Fortran用API. 

  //カレントノードの取得、ノードの移動 fortran　用 API
  int tp_current_node_fort_(long* ptr,char* label,int* label_length); //!<現在のカレントノードを取得します。 Fortran用API. 
  int tp_change_node_fort_(long* ptr,char* lable,int* label_length);//!< ラベルで指定したノードをカレントノードにします。 Fortran用API. 
  int tp_get_number_of_cnodes_fort_(long* ptr,int* nnodes);//!< カレントノードにある子ノードの数を取得します。 Fortran用API. 
  int tp_get_number_of_cleaves_fort_(long* ptr,int* nleaves);//!< カレントノードにあるリーフの数を取得します。 Fortran用API. 
  int tp_get_ith_node_fort_(long* ptr,int* inode,char* node,int* node_length);//!< カレントノードにあるinode番目のノードのラベルを取得します。 Fortran用API. 
  int tp_get_ith_leaf_fort_(long* ptr,int* ileaf,char* leaf,int* leaf_length);//!< カレントノードにあるileaf番目のリーフのラベルを取得します。 Fortran用API. 

  int tp_get_ith_node_order_fort_(long* ptr,int* inode,char* node,int* order,int* node_length);//!< カレントノードにあるinode番目のノードのラベルを取得します。 Fortran用API. 
  int tp_get_ith_leaf_order_fort_(long* ptr,int* ileaf,char* leaf,int* order,int* leaf_length);//!< カレントノードにあるileaf番目のリーフのラベルを取得します。 Fortran用API. 

  // tree modify 用関数　Fortran API 用関数
  int tp_update_value_fort_(long* ptr,char* label,char* value,
			    int* n_label,int* n_value); //!< リーフの値を更新する.
  int tp_delete_leaf_fort_(long* ptr,char* label,
			   int* n_label); //!< リーフを削除する.
  int tp_create_leaf_fort_(long* ptr,char* label,char* value,
			    int* n_label,int* n_value); //!< リーフを作成する.

 // @range @list 用API
  //@range 
  int tp_split_range_fort_(long* ptr,char* value,double *from,double *to,double *step,
			   int* nvalue);
  int tp_expand_range_fort_(long* ptr,char* value,double* expanded,int* nvalue);
    // @list
  int tp_split_list_fort_(long* ptr,char* value, double *list,int* order,int* nvalue);


#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif // __TEXTPARSER_H__


