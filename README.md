# MoveTextureプラグイン for Shade3D
アニメーションで移動するテクスチャ(UV、ソリッド)を表面材質のマッピングレイヤに割り当てるための、Shade3DのShaderプラグインです。  
UVマッピング用の「移動テクスチャ　(UV)」と、  
雲模様のソリッドテクスチャ「移動テクスチャ (ソリッド)」を  
マッピングレイヤのShader要素として追加できます。  

## 動作環境

* Windows 7/8/10以降のOS
* Mac 10.9以降のOS
* Shade3D ver.15/16以降で、Standard/Professional版（Basic版では動作しません）

サンプルshdはver.16の機能を使用しているため、ver.16でないと正しくレンダリングできません。

## ソースのビルド

WindowsはVisual Studio 2013を使用。  
MacはXcode 6.4を使用。  
Shade3D Plugin SDK ver.15.1が必要です ( https://shade3d.jp/community/sdn/sdk.html )。  

## ビルド方法

Shade3D Plugin SDK ver.15.1をダウンロード。  
Shade3D_plugin_MoveTextureでダウンロードしたソースのMoveTextureディレクトリを、Shade3D Plugin SDKのplugin_projectsディレクトリ内に配置。  

### Windows

Visual Studio 2013で、MoveTexture/win/Template.slnを読み込みビルドします。  

### Mac

Xcode6.xで、MoveTexture/mac/plugins/Template.xcodeprojを読み込みビルドします。  

## 実行方法

### Windows

ビルドされた MoveTexture64.dll (32bits版の場合はMoveTexture.dll)をShade3Dのpluginsディレクトリに格納してShade3Dを起動。  
表面材質のマッピングレイヤに「移動テクスチャ (UV)」「移動テクスチャ (ソリッド)」があることを確認。  

### Mac

ビルドされた MoveTexture.shdpluginをShade3Dのpluginsディレクトリに格納してShade 3Dを起動。  
表面材質のマッピングレイヤに「移動テクスチャ (UV)」「移動テクスチャ (ソリッド)」があることを確認。  

## サンプルshd

テクスチャの移動を使ったサンプルシーンです。アニメーションレンダリングすることで確認します。    
https://github.com/ft-lab/Shade3D_plugin_MoveTexture/tree/master/samples  
にサンプルshdを置いています。  

### MoveTexture_sample1.shd
「移動テクスチャ　(UV)」を表面材質のマッピングレイヤに割り当てて、アニメーションレンダリングで移動させるサンプルシーンです。
<img src="https://github.com/ft-lab/Shade3D_plugin_MoveTexture/blob/master/wiki_images/MoveTexture_sample1_image.jpg"/>

### MoveTexture_fire.shd
「移動テクスチャ　(ソリッド)」を表面材質のマッピングレイヤに割り当てて、アニメーションレンダリングで移動させるサンプルシーンです。  
複数を重ね合わせることで炎のような表現を行っています。  
<img src="https://github.com/ft-lab/Shade3D_plugin_MoveTexture/blob/master/wiki_images/MoveTexture_fire_image.jpg"/>

### MoveTexture_water.shd
「移動テクスチャ　(UV)」を表面材質のマッピングレイヤに割り当てて、アニメーションレンダリングで移動させるサンプルシーンです。  
拡散反射とバンプの複数を重ね合わせることで水の流れのような表現を行っています。  
<img src="https://github.com/ft-lab/Shade3D_plugin_MoveTexture/blob/master/wiki_images/MoveTexture_water_image.jpg"/>

## 使い方

## 更新履歴

[2017/02/25]  ver.1.0.0.0  
* 初回版
