// -*- mode : c++ -*- 
/****************************************************************************
**
** Copyright (C) 2012 Tokyo University.
**
****************************************************************************/
/** @file TextParserElement.h
 * ここには TextParserElement クラス及びその派生クラスTextParserNode、TextParserLeafが
 * 定義されています。
 *
 */

#ifndef __TEXTPARSER_ELEMENT_H__
#define __TEXTPARSER_ELEMENT_H__

#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "TextParserCommon.h"


class TextParserNode;
class TextParserLeaf;
class TextParserValue;


class TextParser;
class TextParserTree;

/** TextParserElementクラスはパラメータデータの要素を保持します
 *
 * パラメータの要素としてはノード（TextParserNodeクラス）、
 * リーフ（TextParserLeafクラス）、値（TextParserValueクラス）が有ります
 *
 */
class TextParserElement
{
public:
  //  TextParserElement(TextParserTree* tpt_ptr=TextParser::get_instance_singleton()->dataTree()); 
  TextParserElement(TextParserTree* tpt_ptr); 
  TextParserElement(); 

//private:
public:
    std::string _label; //!< ラベル.
    TextParserElementType _type;   //!< エレメントのタイプ.
    TextParserElement *_parent;   //!< 親のTextParserElementへのポインタ.
    std::vector<TextParserElement *>_return_elements;    //!< 戻り先のエレメントのスタック.

    void setLineN(int nline){_nline=nline;} //!< パラメータファイルでの行数を設定する。
    int line(){return _nline;} //!< パラメータファイルの行数を返す。
    TextParserTree* owner_tree(){return _tpt_ptr;} //!< 自分が所属する。　TPTree pointer 

    std::string GetElementAbsolutePath(TextParserElement* element);
    void SetTree(TextParserTree* tp){_tpt_ptr=tp;}
    TextParserTree* _tpt_ptr; //!< 自分が所属する。　TPTree pointer 

 private :
    int  _nline; //!< line# in text file.

    
 public:
    TextParserError element_node_sort(const std::vector<std::string>& input,
				      std::vector<std::string>& output,
				      int order);
    TextParserError element_label_sort(const std::vector<std::string>& input,
				       std::vector<std::string>& output,
				       int order);
    TextParserError element_labelSort_1(const std::vector<std::string>& input,
					std::vector<std::string>& output);

    int element_array_label_test(const std::string& label,std::string& key);

};

/** TextParserNodeクラスはパラメータデータのノードを保持します
 *
 */
class TextParserNode : public TextParserElement
{
public:
    TextParserNode(const std::string label);
    TextParserNode(const std::string label,TextParserTree* tpt_ptr);

public:
    TextParserError addElement(TextParserNode *node);
    TextParserError addElement(TextParserLeaf *leaf,unsigned int id);
    TextParserError removeElement();
    TextParserError removeLeaf(TextParserLeaf* delleaf);
    TextParserNode *getNode(const std::string& label);
    TextParserLeaf *getLeaf(const std::string& label);
    //    TextParserError setArrayLabelIndex(std::string& label);
    TextParserError writeNode(std::ostream& ofs, unsigned int level,int order=0);
    TextParserError getLeafLabels(std::map<unsigned int, std::string>& labels);

//private:
public:
    std::map<std::string, TextParserNode *>_nodes;     //!< TextParserNodeクラスのキー付き配列
    std::map<std::string, TextParserLeaf *>_leaves;               //!< TextParserLeafクラスのキー付き配列
    std::map<std::string, unsigned int> _array_label_number;//!< 配列形式ラベルの使用数
};

/** TextParserLeafクラスはパラメータデータのリーフを保持します
 *
 */
class TextParserLeaf : public TextParserElement
{
public:
    TextParserLeaf(const std::string label);

public:
    TextParserError setElement(TextParserValue *value);
    TextParserError removeElement();
    TextParserError writeLeaf(std::ostream& ofs,unsigned int level);
    

//private:
//private:

public:
    TextParserValueType _value_type; //!< 値のタイプ
    TextParserValue *_value;  //!< 値
    unsigned int _id; //!< リーフのID
};

/** TextParserValueクラスはリーフの値を保持します
 *
 */
class TextParserValue : public TextParserElement
{
public:
    TextParserValue(const std::string& value, const TextParserValueType& type);

//private:
public:
  TextParserValueType _value_type; //!< 値のタイプ(privateにするのが望ましい。).
  std::string _value; //!< 値 (privateにするのが望ましい。).

/** 値のタイプを返す関数.
 *
 *  @return 値のタイプ
 */

  TextParserValueType value_type(){return _value_type;}; 

  /** 値(string)を返す関数.
   *
   * @return 値（string型）
   */

  std::string value(){return _value;} 
    
};

typedef std::pair<std::string, TextParserNode *> str_node; //!< stringとTextParserNodeのpair
typedef std::pair<std::string, TextParserLeaf *> str_leaf; //!< stringとTextParserLeafのpair
typedef std::pair<std::string, unsigned int> str_int; //!< stringとunsigned intのpair
typedef std::pair<unsigned int, std::string> int_str; //!< stringとunsigned intのpair
typedef std::pair<unsigned int, TextParserLeaf *> uint_leaf; //!< unsigned intとTextParserLeafのpair




#endif //__TEXTPARSER_ELEMENT_H__

