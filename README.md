nendSDK-cocos2d-x Sample Project
==================
## Overview
cocos2d-xでNendSDKを利用するサンプルプロジェクトになります。  
サンプルに含まれているNendModuleはver1.2.0を利用しています。

## Requirement

* cocos2d-x-3.6

* NendSDK  
iOS: ver2.7.0  
Android: ver2.6.1

## Usage
nendの管理画面から各OSのSDKをダウンロードし、以下の手順でプロジェクトにSDKの追加と設定を行ってください。
### iOS  
1. CocosNendSample.xcodeprojをXcodeで開く。
2. CocosNendSample/proj.ios_mac/ios のディレクトリにSDKのNendAdフォルダごと追加する。
3. XcodeでプロジェクトをCleanしてRunする。

### Android  
事前にEclipse環境でcocos2d-x-3.6のセットアップ、Google Play servicesの追加が完了している必要があります。

1. Eclipse > File > Import > Android / Existing Android Code Into Workspace  
ダウンロードしたCocosNendSampleのproj.androidをインポートする。

2. インポートしたCocosNendSampleを右クリック > Properties > Android > Library  
参照がエラーになっているcocos2dxの項目を一旦Removeする。  
Add...をクリックし、Eclipseにインポート済みのlibcocos2dxを選択する。  
この時点で、google-play-services_libとlibcocos2dxのLibraryプロジェクトへの参照が有効になっている必要があります。

3. CocosNendSampleプロジェクトのlibsフォルダにSDKのnendSDK-x.x.x.jarを追加する。

4. EclipseでプロジェクトをCleanしてRunする。  
   または、  
   ターミナルからproj.androidディレクトリに移動し、
   ```
   $ cocos compile -p android
   ```
   を実行後、EclipseでプロジェクトをCleanしてRunする。
