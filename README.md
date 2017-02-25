# Shade3D_plugin_MoveTexture
アニメーションで移動するテクスチャ(UV、ソリッド)をマッピングレイヤに割り当てるためのShade3DのShaderプラグインです。  
UVマッピング用の「移動テクスチャ　(UV)」と、  
雲模様のソリッドテクスチャ「移動テクスチャ (ソリッド)」を  
マッピングレイヤのShader要素として追加できます。  

# 動作環境

Shade3D ver.15/16で動作します。プラグインのためStandard/Professional版が必要です。Basic版では動作しません。  
サンプルshdはver.16の機能を使用しているため、ver.16でないと正しくレンダリングできません。

# サンプルshd

アニメーションレンダリングすることで、行える効果のサンプルシーンです。  
https://github.com/ft-lab/Shade3D_plugin_MoveTexture/tree/master/samples  
にサンプルshdを置いています。  

## MoveTexture_sample1.shd
「移動テクスチャ　(UV)」をマッピングレイヤに割り当てて、アニメーションレンダリングで移動させるサンプルシーンです。
<img src="https://github.com/ft-lab/Shade3D_plugin_MoveTexture/blob/master/wiki_images/MoveTexture_sample1_image.jpg"/>

## MoveTexture_fire.shd
「移動テクスチャ　(ソリッド)」をマッピングレイヤに割り当てて、アニメーションレンダリングで移動させるサンプルシーンです。　　
複数を重ね合わせることで炎のような表現を行っています。
<img src="https://github.com/ft-lab/Shade3D_plugin_MoveTexture/blob/master/wiki_images/MoveTexture_fire_image.jpg"/>

## MoveTexture_water.shd
「移動テクスチャ　(UV)」をマッピングレイヤに割り当てて、アニメーションレンダリングで移動させるサンプルシーンです。　　
拡散反射とバンプの複数を重ね合わせることで水の流れのような表現を行っています。
<img src="https://github.com/ft-lab/Shade3D_plugin_MoveTexture/blob/master/wiki_images/MoveTexture_water_image.jpg"/>

# 使い方

# 更新履歴

[2017/02/25]  ver.1.0.0.0  
* 初回版
