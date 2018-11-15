# notespp
Notes C APIのC++/Qtによるラッピングライブラリと改訂版Notes CommandLineアプリです。

# History

* v0.0.3

  * LMBCS文字列を扱うクラス String を追加します。
  * LMBCS文字列とQStringを相互に変換する機能を追加します。


* v0.0.2 - 2018-11-14

  * Notes C API関数を別のライブラリとして構築します。
    * Statusクラス

      例外クラスとしても利用できます。

    * Mainクラス

      Notes C APIの初期化、終了処理を自動化します。

    * GetServerLatency関数オブジェクト

      NSFGetServerLatency関数をラッピングします。

  * rxcpp(Reactive ExtensionsのCPPライブラリ)を導入します。


* v0.0.1 - 2018-11-14

  * 改訂前のNotes CommandLineアプリを復元します。
