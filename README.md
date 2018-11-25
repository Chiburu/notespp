# notespp
Notes C APIのC++/Qtによるラッピングライブラリと改訂版Notes CommandLineアプリです。

# History

## v0.0.6.1 - 2018-11-25

* ReactiveXで使用しているラムダ式のキャプチャ変数が、ネストが深くなると生存期間などの問題が解決しづらくなるため、GetServerLatency以外でのObservable仕様を控えるようにする。

## v0.0.6 - 2018-11-24

* コマンドラインの処理にReactiveXを導入します。

* ReactiveXで使用するラムダ式と変数の生存期間、サブスクライブが発火するタイミングで不具合があるので、引数の値をオブジェクトに取り込むようにする。

## v0.0.5 - 2018-11-23

* コマンドラインを処理するクラスを追加します。

* GetServerLatencyをコマンドライン化します。

## v0.0.4 - 2018-11-17

* NSFGetServerLatency関数オブジェクトを改良して、Enableにした値かどうか、戻り値でもわかるようにします。


## v0.0.3 - 2018-11-15

* LMBCS文字列を扱うクラス String を追加します。
* LMBCS文字列とQStringを相互に変換する機能を追加します。


## v0.0.2 - 2018-11-14

* Notes C API関数を別のライブラリとして構築します。
  * Statusクラス

    例外クラスとしても利用できます。

  * Mainクラス

    Notes C APIの初期化、終了処理を自動化します。

  * GetServerLatency関数オブジェクト

    NSFGetServerLatency関数をラッピングします。

* rxcpp(Reactive ExtensionsのCPPライブラリ)を導入します。


## v0.0.1 - 2018-11-14

* 改訂前のNotes CommandLineアプリを復元します。
