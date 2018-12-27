/**
 *  @file   GlobalHeader.h
 *  @brief  共通して使用する変数など.
 */

#ifndef _GLOBALHEADER_H
#define _GLOBALHEADER_H

#include "sxsdk.cxx"

/**
 * shader_interfaceのプラグインID.
 */
#define UVTEXTURE_SHADER_ID sx::uuid_class("EE00204E-8833-479D-98FC-1BCFE9154A22")
#define SOLIDTEXTURE_SHADER_ID sx::uuid_class("0907C1BA-3FF8-4950-9508-645777D983A6")

/**
 * streamに保存するバージョン.
 */
#define MOVETEXTURE_UV_STREAM_VERSION			0x100		// UVテクスチャのShaderバージョン.

#define MOVETEXTURE_SOLID_STREAM_VERSION		0x101		// ソリッドテクスチャのShaderバージョン.
#define MOVETEXTURE_SOLID_STREAM_VERSION_100	0x100
#define MOVETEXTURE_SOLID_STREAM_VERSION_101	0x101
 
/**
 * UVテクスチャのShader情報.
 */
class CMoveTextureUVShaderData
{
public:
	sxsdk::vec2 moveV;			// 移動量.
	sxsdk::vec2 offsetV;		// オフセット量.
	int uvIndex;				// UV層番号.
	int repeatX, repeatY;		// 反復.
	bool flipColor;				// 色反転.

public:
	CMoveTextureUVShaderData () {
		Clear();
	}

	void Clear () {
		moveV     = sxsdk::vec2(0, 0);
		offsetV   = sxsdk::vec2(0, 0);
		uvIndex   = 0;
		flipColor = false;
		repeatX = repeatY = 1;
	}
};

/**
 * ソリッドテクスチャのShader情報.
 */
class CMoveTextureSolidShaderData
{
public:
	sxsdk::vec3 moveV;			// 移動量.
	int octaves;				// オクターブ.

	float scaleHeight;			// 高さ.
	float scalePow;				// 高さに向かう強さ.
	float scaleValue;			// スケール値.

public:
	CMoveTextureSolidShaderData () {
		Clear();
	}

	void Clear () {
		moveV     = sxsdk::vec3(0, 0, 0);
		octaves   = 5;

		scaleHeight = 100.0f;
		scalePow    = 2.0f;
		scaleValue  = 1.0f;
	}
};
#endif
