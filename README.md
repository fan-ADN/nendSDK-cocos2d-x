nendSDK-cocos2d-x Sample Project
==================
## Overview
cocos2d-xでNendSDKを利用するサンプルプロジェクトになります。  

## Requirement

* cocos2d-x-3.10

* nendSDK Cocos2d-x module ver1.2.5

## Usage
[nend管理画面](https://www.nend.net/admin/login)からcocos2d-xモジュール 3.x用をダウンロードし、以下の手順でプロジェクトにSDKとモジュールの追加及び設定を行ってください。  

#### 複数の広告枠IDをサンプルで利用する場合
広告枠ID ( apikey と spotID )を複数利用する場合は、サンプルプロジェクト内の apiKey と spotID の定義箇所を書き換えてご利用ください。

### iOS  

#### 1 NendSDK と cocos2d-x モジュールの組み込み
[組込み方法](https://github.com/fan-ADN/nendSDK-cocos2d-x/wiki/組込み方法) の説明に従って行ってください。


#### 2 XcodeでプロジェクトをCleanしてRunする。

### Android  

事前にAndroid StudioまたはEclipseの環境でcocos2d-x-3.10のセットアップが完了している必要があります。

#### Android Studioの場合

1. ダウンロードした`CocosNendSample`の`proj.android-studio`をAndroid Studioで開きます。

2. cocos2d-x モジュールの組み込み  
[組込み方法](https://github.com/fan-ADN/nendSDK-cocos2d-x/wiki/組込み方法/) の説明に従って行ってください。

2. Android StudioでプロジェクトをCleanしてRunする。  
または、ターミナルから`proj.android-studio`ディレクトリに移動し、
```
$ cocos compile -p android --android-studio
```
を実行後、Android StudioでRunする。

#### Eclipseの場合

1. Eclipse > File > Import > Android / Existing Android Code Into Workspace  
ダウンロードしたCocosNendSampleのproj.androidをインポートする。

2. インポートしたCocosNendSampleを右クリック> Properties  
![image](https://raw.github.com/wiki/fan-ADN/nendSDK-cocos2d-x/images/readme_img/sc1.png)

Android > Library > Add...をクリックし、Eclipseにインポート済みのlibcocos2dxを選択する。
![image](https://raw.github.com/wiki/fan-ADN/nendSDK-cocos2d-x/images/readme_img/sc2.png)

![image](https://raw.github.com/wiki/fan-ADN/nendSDK-cocos2d-x/images/readme_img/sc3.png)

#### 1 NendSDK の組み込み
jar ファイルの追加  と Google Play services を追加します。  
[組込み方法](https://github.com/fan-ADN/nendSDK-cocos2d-x/wiki/組込み方法) の説明に従って行ってください。  

#### 2 cocos2d-x モジュールの組み込み
[組込み方法](https://github.com/fan-ADN/nendSDK-cocos2d-x/wiki/組込み方法/) の説明に従って行ってください。

#### 3 EclipseでプロジェクトをCleanしてRunする。  
   または、ターミナルからproj.androidディレクトリに移動し、
   ```
   $ cocos compile -p android
   ```
   を実行後、EclipseでプロジェクトをCleanしてRunする。
