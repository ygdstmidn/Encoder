# Encoder

## 概要
STM32CubeHALのエンコーダ機能をラップして使いやすくしました．\
クラス内にint64_t型のカウンタを作り，HALのエンコーダ機能によって前回からの差分を加算していきます．

## ライセンス
このプロジェクトはMITライセンスの下で公開されています。詳細は[LICENSE](./LICENSE)ファイルを参照してください。

## 使用方法
### 初期化
```cpp
Encoder encoder(&htim);
```
TIM_HandleTypeDef型のポインタを引数に取ります．(エンコーダモードになっているタイマー)\
encoderという名前は好きに決めてください．
### 計測開始
```cpp
encoder.start();
```
startしてください
### 計測終了
```cpp
encoder.stop();
```
多分使わないです
### リセット
```cpp
encoder.reset();
```
クラス内のカウンタを0にリセットします．
### 位置取得
```cpp
int64_t pos = encoder.getPos();
```
現在の位置を取得します．
### 速度取得
```cpp
int32_t speed = encoder.getSpeed();
```
現在の速度を取得します．

## 注意点
getPos,getSpeed関数を呼び出すと，内部でエンコーダのカウンタがリセットされます
