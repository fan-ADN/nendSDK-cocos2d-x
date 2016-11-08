nendSDK-cocos2d-x Sample Project
==================
## Overview
cocos2d-xでNendSDKを利用するサンプルプロジェクトになります。  

## Requirement

* cocos2d-x-3.13.1

* nendSDK Cocos2d-x module ver2.1.2

## Usage
[nend管理画面](https://www.nend.net/admin/login)からcocos2d-xモジュール 3.x用をダウンロードし、以下の手順でプロジェクトにSDKとモジュールの追加及び設定を行ってください。  

#### 複数の広告枠IDをサンプルで利用する場合
広告枠ID ( apikey と spotID )を複数利用する場合は、サンプルプロジェクト内の apiKey と spotID の定義箇所を書き換えてご利用ください。

### iOS  

#### 1 NendSDK と cocos2d-x モジュールの組み込み
[組込み方法](https://github.com/fan-ADN/nendSDK-cocos2d-x/wiki/組込み方法) の説明に従って行ってください。


#### 2 XcodeでプロジェクトをCleanしてRunする。

### Android  

事前にAndroid Studio環境でcocos2d-x-3.13.1のセットアップが完了している必要があります。

#### Android Studio

1. ダウンロードした`CocosNendSample`の`proj.android-studio`をAndroid Studioで開きます。

2. cocos2d-x モジュールの組み込み  
[組込み方法](https://github.com/fan-ADN/nendSDK-cocos2d-x/wiki/組込み方法/) の説明に従って行ってください。

2. Android StudioでプロジェクトをCleanしてRunする。  
または、ターミナルから`proj.android-studio`ディレクトリに移動し、
```
$ cocos compile -p android --android-studio
```
を実行後、Android StudioでRunする。
