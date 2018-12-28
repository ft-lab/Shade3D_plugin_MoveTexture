For English documentation please see below.  
Sorry, I translated it into English with "Google Translate" so it may be difficult to read.  

https://github.com/ft-lab/Shade3D_plugin_MoveTexture/blob/master/README_en.md

# MoveTexture for Shade3D
アニメーションで移動するテクスチャ(UV、ソリッド)を表面材質のマッピングレイヤに割り当てるための、Shade3DのShaderプラグインです。  
UVマッピング用の「移動テクスチャ　(UV)」と、  
雲模様のソリッドテクスチャ「移動テクスチャ (ソリッド)」を  
マッピングレイヤのShader要素として追加できます。  

## 動作環境

* Windows 7/8/10以降のOS
* Mac 10.11以降のOS
* Shade3D ver.16 (64bit) 以降で、Standard/Professional版（Basic版では動作しません）

サンプルshdはver.16の機能を使用しているため、ver.16でないと正しくレンダリングできません。

## プラグインバイナリ
以下にプラグインのビルド済みのものを置いています。  

https://github.com/ft-lab/Shade3D_plugin_MoveTexture/releases

## ソースのビルド (開発向け)
WindowsはVisual Studio 2017を使用。  
MacはXcode 10.1を使用。  
Shade3D Plugin SDK ver.15.1が必要です ( https://shade3d.jp/community/sdn/sdk.html )。  

## ビルド方法 (開発向け)

Shade3D Plugin SDK ver.15.1をダウンロード。  
Shade3D_plugin_MoveTextureでダウンロードしたソースのMoveTextureディレクトリを、Shade3D Plugin SDKのplugin_projectsディレクトリ内に配置。  

### Windows

Visual Studio 2017で、MoveTexture/win/Template.slnを読み込みビルドします。  

### Mac

Xcode10.xで、MoveTexture/mac/plugins/Template.xcodeprojを読み込みビルドします。  

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
![MoveTexture_sample1_image](./wiki_images/MoveTexture_sample1_image.jpg)    

### MoveTexture_fire.shd
「移動テクスチャ　(ソリッド)」を表面材質のマッピングレイヤに割り当てて、アニメーションレンダリングで移動させるサンプルシーンです。  
複数を重ね合わせることで炎のような表現を行っています。  
![MoveTexture_fire_image](./wiki_images/MoveTexture_fire_image.jpg)    

### MoveTexture_water.shd
「移動テクスチャ　(UV)」を表面材質のマッピングレイヤに割り当てて、アニメーションレンダリングで移動させるサンプルシーンです。  
拡散反射とバンプの複数を重ね合わせることで水の流れのような表現を行っています。  
![MoveTexture_water_image](./wiki_images/MoveTexture_water_image.jpg)    

### MoveTexture_volume.shd
「移動テクスチャ　(ソリッド)」を表面材質のマッピングレイヤに割り当てて、ボリュームレンダリングのアニメーションを行うサンプルシーンです。    
![MoveTexture_volume_image](./wiki_images/MoveTexture_volume_image.jpg)    

## 使い方

ここでの「移動テクスチャ」は、マッピングされた画像/ノイズのソリッドテクスチャ（雲やスポットのような表現）がアニメーションレンダリングでシフト移動することを指します。  
このプラグインは表面材質のマッピングレイヤで指定する「Shaderプラグイン」になります。  
マッピングレイヤとして「移動テクスチャ　(UV)」「移動テクスチャ　(ソリッド)」が選択できます。　　

![mapping_layer_00](./wiki_images/mapping_layer_00.png)    

複数レイヤを重ね合わせることで、複雑な表現を行えます。　　

### 「移動テクスチャ　(UV)」
表面材質のマッピングレイヤで「移動テクスチャ　(UV)」を選択すると、イメージを指定した移動テクスチャ用レイヤが指定されます。　　
![mapping_layer_texture_uv](./wiki_images/mapping_layer_texture_uv.png)    

「イメージ編集」ボタンを押して、レイヤに参照する画像を追加するようにしてください。  
レイヤの色、「拡散反射」「バンプ」などの種類の切り替えと、「適用率」が使えます。  
「その他」ボタンを押すと、設定ダイアログボックスが開きます。  
「UV」は参照するUV層です(UV1/UV2のみ)。  
「反復」で縦横の繰り返し回数を指定します。  
「色反転」でテクスチャの色を反転させます。  
「UVオフセット」でレンダリング時にテクスチャをずらす量をUV座標（0.0-1.0）で指定します。  
オフセットをずらすことにより、同一テクスチャを参照している場合でも同じものを使っていることを目立ちにくくします。  
「UV移動量」は、アニメーションレンダリングで1秒経過したときのUV座標（0.0-1.0）でのずらす量です。これでシフト移動のアニメーションを行います。  

### 「移動テクスチャ　(ソリッド)」
表面材質のマッピングレイヤで「移動テクスチャ　(ソリッド)」を選択すると、雲模様のソリッドテクスチャ用レイヤが指定されます。    
![mapping_layer_texture_solid](./wiki_images/mapping_layer_texture_solid.png)    

「位置&サイズ」タブの「サイズ」「位置」の入力が使用できます。これにより、複数レイヤを重ねる場合の多様性を出します。  
レイヤの色、「拡散反射」「バンプ」などの種類の切り替えと、「適用率」が使えます。  
「その他」ボタンを押すと、設定ダイアログボックスが開きます。  
「オクターブ」は、ノイズのソリッドテクスチャの重ね合わせの数です(1-16)。これが大きいと細かいところまで表現されます。  
「移動量」は、アニメーションレンダリングで1秒経過したときのローカル座標でのずらす量です。これでシフト移動のアニメーションを行います。    

「スケール補正」グループは、ver.1.0.1.0で追加された機能です。    
Y方向に向かうにつれてソリッドテクスチャのサイズをスケーリングします。    
これにより、上に行くにつれてノイズ模様が大きくなる効果を表現します。   
「高さ」はスケール補正が有効な高さをmm単位で指定します。    
基準は、マッピングモードでの原点位置になります。0.0の位置から開始します。    
![mapping_layer_texture_solid_02](./wiki_images/mapping_layer_texture_solid_02.png)    
「高さに向かう強さ (Pow)」は、マッピングモードでの原点Yから「高さ」で指定した位置までを曲線的にスケーリングします。    
1.0の場合は直線的なスケーリングになり、2.0にすると高くなるにつれて急激にスケール値が大きくなります。    
「スケール値」は最大のスケール値です。    
指定の高さ以降は、「スケール値」で指定されたスケール値が採用されます。    

## 更新履歴

[2018/12/28]  ver.1.0.1.0  
* ソリッドテクスチャの属性指定が保存されない問題を修正    
* ソリッドテクスチャ使用時に、高さ位置によりスケーリングするオプション追加    
* サンプル「MoveTexture_volume.shd」を追加

[2017/02/25]  ver.1.0.0.0  
* 初回版
