# TextParser - Text Parsing Library

## Python interface



1. 動作環境

	以下の環境で動作確認済み(Python 2.7)。
	* Linux
	* cygwin
	* mac OSX

  	windowsのネイティブ環境では未確認。
  	TextParaerとpython2が動く環境であればLinuxに限らず動作するはず。

2. ビルド方法
  
  以下のコマンドを実行。

    `$ python setup.py install --prefix={PATH_TO_INSTALL}`

  python2系列がpython2という名前でインストールされている環境では
  上記の入力例の"python"の部分を"python2"に置き換えてください。


3. 使い方

  test.pyを参考にしてください。


4. 対応するTextParserのメソッドについて

  ユーザマニュアルに記載されているC++版のメソッドのうち、以下のものを除いて用意しています。
  	* read_local()
  	* 型変換に関するメソッド
  	* getInspectedVector()
  	
  また、 C版のinstance生成/削除, シングルトン版instance取得関数 に相当するメソッドも対応しています。


5. エラーコードについて
  
  TextParserの内部でエラーが発生した場合は、ライブラリ内でエラーメッセージを出力するのでラッパールーチン内ではメッセージは出力しません。
  また、TextParserのエラーには回復可能なものも多いので、Python用の例外も送出していません。
  各メソッドが返すエラーコードは戻り値として、呼び出し元に返しているので
  必要に応じて、呼び出し元で対応を行なってください。


6. 戻り値について

	6.1 全般的なルール
  
  * 出力引数を持たないメソッドに対するラッパールーチンは、TextParserのメソッドが返すエラーコードを、intオブジェクトとして返します。
  * 出力引数を持つメソッドに対するラッパールーチンは、エラーコードを1番目の要素、
  出力引数を2番目以降の要素とするタプルを返します。

	6.2 例外ケース
  
  * createInstance, getInstanceSingletonは戻り値として
  TextParserのインスタンスへのポインタを返します。
  * getTypeは、1番目の要素にエラーコード、 2番目の要素にTextParserValueTypeを整数値として扱った値を格納したタプルを返します。C#のAPIに準じた形です。
