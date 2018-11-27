# notespp
Notes C APIのC++/Qtによるラッピングライブラリと改訂版Notes CommandLineアプリです。

# History

## v0.0.6.2 - 2018-11-26

* `Status`クラスを`std::exception`からの継承ではなく独立したクラスとする。

* `GetServerLatency`クラスの`operator()`の引数`serverName`を右辺値参照とする。

## v0.0.6.1 - 2018-11-25

* ReactiveXで使用しているラムダ式のキャプチャ変数が、ネストが深くなると生存期間などの問題が解決しづらくなるため、`GetServerLatency`以外でのObservable仕様を控えるようにする。

## v0.0.6 - 2018-11-24

* コマンドラインの処理にReactiveXを導入します。

* ReactiveXで使用するラムダ式と変数の生存期間、サブスクライブが発火するタイミングで不具合があるので、引数の値をオブジェクトに取り込むようにする。

## v0.0.5 - 2018-11-23

* コマンドラインを処理するクラスを追加します。

* `GetServerLatency`をコマンドライン化します。

## v0.0.4 - 2018-11-17

* NSFGetServerLatency関数オブジェクトを改良して、Enableにした値かどうか、戻り値でもわかるようにします。


## v0.0.3 - 2018-11-15

* LMBCS文字列を扱うクラス`String`を追加します。
* LMBCS文字列と`QString`を相互に変換する機能を追加します。


## v0.0.2 - 2018-11-14

* Notes C API関数を別のライブラリとして構築します。
  * `Status`クラス

    例外クラスとしても利用できます。

  * `Main`クラス

    Notes C APIの初期化、終了処理を自動化します。

  * `GetServerLatency`関数オブジェクト

    `NSFGetServerLatency`関数をラッピングします。

* rxcpp(Reactive ExtensionsのCPPライブラリ)を導入します。


## v0.0.1 - 2018-11-14

* 改訂前のNotes CommandLineアプリを復元します。
