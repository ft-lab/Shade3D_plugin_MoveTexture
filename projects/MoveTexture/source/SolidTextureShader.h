/**
 * ソリッドテクスチャのShader.
 */
#ifndef _SOLIDTEXTURESHADER_H
#define _SOLIDTEXTURESHADER_H

#include "GlobalHeader.h"

#define SOLIDTEXTURE_SHADER_MAGIC_NUMBER 0x87ac798c

class CSolidTextureShaderInterface : public sxsdk::shader_interface
{
private:
	sxsdk::shade_interface &m_shade;
	CMoveTextureSolidShaderData m_data;				// ダイアログボックスでの設定で使うデータ.
	float m_frameRate;								// 1秒間のフレーム数.
	float m_currentFrame;							// カレントフレーム.
	float m_solidScaleV;							// ソリッドテクスチャ用の固定の倍率.

	/**
	 * Shaderで参照する情報.
	 */
	class ShaderInfoC : public sxsdk::shader_info_base_class {
	public:
		CMoveTextureSolidShaderData data;

		ShaderInfoC (CMoveTextureSolidShaderData& data) : data(data) { }
		unsigned magic_number () const { return SOLIDTEXTURE_SHADER_MAGIC_NUMBER; }		// 適当な数値.
	};

private:
	template<typename T> inline const T lerp (const T &a, const T &b, float t) {
		return (b - a) * t + a;
	}

	/**
	 * pの高さにより、乗算するスケール値を取得.
	 */
	float m_getScale (const sxsdk::vec3& p, const CMoveTextureSolidShaderData& data);

private:
	virtual sx::uuid_class get_uuid (void *) { return SOLIDTEXTURE_SHADER_ID; }
	virtual int get_shade_version () const { return SHADE_BUILD_NUMBER; }

	virtual bool supports_evaluate (void *) { return true; }
	virtual bool supports_shade (void *) { return true; }
	virtual bool needs_projection (void *aux=0) { return false; }
	virtual bool needs_uv (void*) { return false; }
	virtual bool needs_to_sample_image (void*) { return false; }
	//virtual bool needs_tangents (void*) { return true; }
	virtual bool supports_bump (void*) { return true; }

	/**
	 * シェーダが独自に使うデータ領域を生成.
	 */
	virtual sxsdk::shader_info_base_class *new_shader_info (sxsdk::stream_interface *stream, void *);

	virtual float evaluate (const sx::vec3& p, void* = 0);

	/**
	 * Shaderとしての計算を行う.
	 */
	virtual void shade (void *);

	/**
	 * Shaderとしてのバンプ計算を行う.
	 */
	virtual void bump (void*);

	/**
	 * 個々のフレームのレンダリング開始前に呼ばれる.
	 * @param[in] b 未使用.
	 * @param[in] rendering_context レンダリング情報クラスのポインタ.
	 */
	virtual void pre_rendering(bool &b, sxsdk::rendering_context_interface *rendering_context, void *aux = 0);

	/**
	 * レンダリング終了時に呼ばれる.
	 */
	virtual void post_rendering (bool &b, sxsdk::rendering_context_interface *rendering_context);

	/**
	 * パラメータの指定.
	 */
	virtual bool ask (sxsdk::stream_interface *stream, void *);

	//--------------------------------------------------//
	//	ダイアログのイベント処理用						//
	//--------------------------------------------------//
	/**
	 * ダイアログの初期化.
	 */
	virtual void initialize_dialog (sxsdk::dialog_interface &d, void * = 0);

	/** 
	 * ダイアログのイベントを受け取る.
	 */
	virtual bool respond (sxsdk::dialog_interface &d, sxsdk::dialog_item_class &item, int action, void * = 0);

	/**
	 * ダイアログのデータを設定する.
	 */
	virtual void load_dialog_data (sxsdk::dialog_interface &d, void * = 0);

	/**
	 * 値の変更を保存するときに呼ばれる.
	 */
	virtual void save_dialog_data (sxsdk::dialog_interface &d, void * = 0);

public:
	CSolidTextureShaderInterface (sxsdk::shade_interface& _shade);
	virtual ~CSolidTextureShaderInterface ();

	/**
	 * プラグイン名.
	 */
	static const char *name (sxsdk::shade_interface *_shade) {
		return _shade->gettext("solidTexture_shader_title");
	}
};

#endif
