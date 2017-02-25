/**
 * Streamに情報を保持するクラス.
 */
#ifndef _STREAMCTRL_H
#define _STREAMCTRL_H

#include "GlobalHeader.h"

namespace StreamCtrl {
	/**
	 * UVテクスチャのカスタムレイヤ(Shader)情報として保存.
	 */
	void SaveUVTextureShaderData (sxsdk::stream_interface* stream, const CMoveTextureUVShaderData& data);

	/**
	 * UVテクスチャのカスタムレイヤ(Shader)情報として読み込み.
	 */
	bool LoadUVTextureShaderData (sxsdk::stream_interface* stream, CMoveTextureUVShaderData& data);

	/**
	 * ソリッドテクスチャのカスタムレイヤ(Shader)情報として保存.
	 */
	void SaveSolidTextureShaderData (sxsdk::stream_interface* stream, const CMoveTextureSolidShaderData& data);

	/**
	 * ソリッドテクスチャのカスタムレイヤ(Shader)情報として読み込み.
	 */
	bool LoadSolidTextureShaderData (sxsdk::stream_interface* stream, CMoveTextureSolidShaderData& data);
}

#endif
