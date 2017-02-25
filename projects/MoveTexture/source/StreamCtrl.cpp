/**
 * Streamに情報を保持するクラス.
 */

#include "StreamCtrl.h"

/**
 * UVテクスチャのカスタムレイヤ(Shader)情報として保存.
 */
void StreamCtrl::SaveUVTextureShaderData (sxsdk::stream_interface* stream, const CMoveTextureUVShaderData& data)
{
	try {
		if (!stream) return;

		stream->set_size(0);
		stream->set_pointer(0);

		int iVersion = MOVETEXTURE_UV_STREAM_VERSION;
		stream->write_int(iVersion);

		int iDat = 0;
		stream->write_int(data.uvIndex);
		stream->write_int(data.repeatX);
		stream->write_int(data.repeatY);

		iDat = data.flipColor ? 1 : 0;
		stream->write_int(iDat);

		{
			sxsdk::vec3 v3(data.moveV, 0.0f);
			stream->write_vec3(v3);
		}
		{
			sxsdk::vec3 v3(data.offsetV, 0.0f);
			stream->write_vec3(v3);
		}
	} catch (...) { }
}

/**
 * UVテクスチャのカスタムレイヤ(Shader)情報として読み込み.
 */
bool StreamCtrl::LoadUVTextureShaderData (sxsdk::stream_interface* stream, CMoveTextureUVShaderData& data)
{
	data.Clear();
	if (!stream) return false;
	try {
		stream->set_pointer(0);

		int iVersion = 0;
		stream->read_int(iVersion);

		int iDat = 0;
		stream->read_int(data.uvIndex);
		stream->read_int(data.repeatX);
		stream->read_int(data.repeatY);

		stream->read_int(iDat);
		data.flipColor = (iDat) ? true : false;

		{
			sxsdk::vec3 v3;
			stream->read_vec3(v3);
			data.moveV = sxsdk::vec2(v3.x, v3.y);
		}
		{
			sxsdk::vec3 v3;
			stream->read_vec3(v3);
			data.offsetV = sxsdk::vec2(v3.x, v3.y);
		}

		return true;
	} catch (...) { }

	return false;
}

/**
 * ソリッドテクスチャのカスタムレイヤ(Shader)情報として保存.
 */
void StreamCtrl::SaveSolidTextureShaderData (sxsdk::stream_interface* stream, const CMoveTextureSolidShaderData& data)
{
	try {
		if (!stream) return;

		stream->set_size(0);
		stream->set_pointer(0);

		int iVersion = MOVETEXTURE_SOLID_STREAM_VERSION;
		stream->write_int(iVersion);

		stream->write_int(data.octaves);
		stream->write_vec3(data.moveV);

	} catch (...) { }
}

/**
 * ソリッドテクスチャのカスタムレイヤ(Shader)情報として読み込み.
 */
bool StreamCtrl::LoadSolidTextureShaderData (sxsdk::stream_interface* stream, CMoveTextureSolidShaderData& data)
{
	data.Clear();
	try {
		if (!stream) return false;

		stream->set_pointer(0);

		int iVersion;
		stream->read_int(iVersion);

		stream->read_int(data.octaves);
		stream->read_vec3(data.moveV);

		return true;
	} catch (...) { }

	return false;
}
