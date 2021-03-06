﻿/**
 * UVテクスチャのShader.
 */
#include "SolidTextureShader.h"
#include "StreamCtrl.h"

// SXULダイアログボックスでのイベントID.
enum
{
	dlg_octaves_id = 101,			// オクターブ.
	dlg_moveV_id = 201,				// 移動量.

	dlg_scale_height_id = 202,		// スケールの高さ.
	dlg_scale_pow_id = 203,			// スケールの強さ.
	dlg_scale_value_id = 204,		// スケール値.
};

CSolidTextureShaderInterface::CSolidTextureShaderInterface (sxsdk::shade_interface& _shade) : m_shade(_shade), sxsdk::shader_interface(_shade)
{
	m_solidScaleV = 1.0f / 100.0f;
}

CSolidTextureShaderInterface::~CSolidTextureShaderInterface ()
{
}

/**
 * シェーダが独自に使うデータ領域を生成.
 */
sxsdk::shader_info_base_class *CSolidTextureShaderInterface::new_shader_info (sxsdk::stream_interface *stream, void *)
{
	// streamから情報読み込み.
	CMoveTextureSolidShaderData data;
	if (stream) {
		StreamCtrl::LoadSolidTextureShaderData(stream, data);
		data.scaleValue = std::max(data.scaleValue, 0.01f);
	}

	return new ShaderInfoC(data);
}

/**
 * pの高さにより、乗算するスケール値を取得.
 */
float CSolidTextureShaderInterface::m_getScale (const sxsdk::vec3& p, const CMoveTextureSolidShaderData& data)
{
	// p.yにより、拡大率を変える.
	float scale = 10.0f;
	if (data.scaleValue != 1.0f) {
		const float fMin = (float)(1e-3);
		const float py = p.y / m_solidScaleV;
		const float scale2 = scale / data.scaleValue;
		if (py >= 0.0f && py < data.scaleHeight) {
			float fV = std::pow(py / data.scaleHeight, data.scalePow);
			scale = scale * (1.0f - fV) + scale2 * fV;
		} else if (py >= data.scaleHeight) {
			scale = scale2;
		}
	}
	return scale;
}

float CSolidTextureShaderInterface::evaluate (const sx::vec3& p, void*)
{
	// Shaderで参照する情報.
	CMoveTextureSolidShaderData data;
	try {
		ShaderInfoC* shaderInfo = (ShaderInfoC *)(get_shader_info());
		if (shaderInfo) {
			if ((shaderInfo->magic_number()) == SOLIDTEXTURE_SHADER_MAGIC_NUMBER) data = shaderInfo->data;
		}
	} catch (...) { }

	const float scale = m_getScale(p, data);
	return turbulence1(p * scale, data.octaves);
}

/**
 * Shaderとしての計算を行う.
 */
void CSolidTextureShaderInterface::shade (void *)
{
	// Shaderで参照する情報.
	CMoveTextureSolidShaderData data;
	try {
		ShaderInfoC* shaderInfo = (ShaderInfoC *)(get_shader_info());
		if (shaderInfo) {
			if ((shaderInfo->magic_number()) == SOLIDTEXTURE_SHADER_MAGIC_NUMBER) data = shaderInfo->data;
		}
	} catch (...) { }

	const sxsdk::vec3 p = get_P();
	sxsdk::vec3 p2 = p;

	// 移動量分を加算.
	if (!sx::zero(m_frameRate)) {
		p2 += ((-data.moveV * m_currentFrame) / (float)m_frameRate) * m_solidScaleV;
	}

	const float scale = m_getScale(p, data);
	const float eVal = turbulence1(p2 * scale, data.octaves);

	set_Ci(lerp(get_Cs(), get_mapping_color(), eVal));
}


/**
 * Shaderとしてのバンプ計算を行う.
 */
void CSolidTextureShaderInterface::bump (void*)
{
	// Shaderで参照する情報.
	CMoveTextureSolidShaderData data;
	try {
		ShaderInfoC* shaderInfo = (ShaderInfoC *)(get_shader_info());
		if (shaderInfo) {
			if ((shaderInfo->magic_number()) == SOLIDTEXTURE_SHADER_MAGIC_NUMBER) data = shaderInfo->data;
		}
	} catch (...) { }

	const sxsdk::vec3 p = get_P();
	sxsdk::vec3 p2 = p;

	// 移動量分を加算.
	if (!sx::zero(m_frameRate)) {
		p2 += ((-data.moveV * m_currentFrame) / (float)m_frameRate) * m_solidScaleV;
	}

	const float scaleV1 = 1.0f;
	const float scaleV2 = 0.2f;

	sxsdk::vec3 eValV = turbulence3(p2 * scaleV1, data.octaves);

	set_N(normalize(get_N() + eValV * scaleV2 * get_mapping()));
}

/**
 * 個々のフレームのレンダリング開始前に呼ばれる.
 * @param[in] b 未使用.
 * @param[in] rendering_context レンダリング情報クラスのポインタ.
 */
void CSolidTextureShaderInterface::pre_rendering (bool &b, sxsdk::rendering_context_interface *rendering_context, void *aux)
{
	// フレームレートを取得.
	m_frameRate    = 0.0f;
	m_currentFrame = 0.0f;
	try {
		compointer<sxsdk::scene_interface> scene(rendering_context->get_scene_interface());
		if (scene) {
			if (!sx::zero(scene->get_step_frames())) {
				m_frameRate = (float)(scene->get_frame_rate()) / (float)(scene->get_step_frames());
			}
		}
		m_currentFrame = rendering_context->get_current_frame();
	} catch (...) { }
}

/**
 * レンダリング終了時に呼ばれる.
 */
void CSolidTextureShaderInterface::post_rendering (bool &b, sxsdk::rendering_context_interface *rendering_context)
{
}

/**
 * パラメータの指定.
 */
bool CSolidTextureShaderInterface::ask (sxsdk::stream_interface *stream, void *)
{
	compointer<sxsdk::dialog_interface> dlg(m_shade.create_dialog_interface_with_uuid(SOLIDTEXTURE_SHADER_ID));
	dlg->set_resource_name("moveTexture_solid_dlg");

	dlg->set_responder(this);
	this->AddRef();			// set_responder()に合わせて、参照カウンタを増やす。 .

	// streamから情報を読み込み.
	StreamCtrl::LoadSolidTextureShaderData(stream, m_data);

	// ダイアログの表示.
	if (dlg->ask()) {
		// streamに情報を保持.
		StreamCtrl::SaveSolidTextureShaderData(stream, m_data);
		return true;
	}

	return false;
}

//--------------------------------------------------//
//	ダイアログのイベント処理用						//
//--------------------------------------------------//
/**
 * ダイアログの初期化.
 */
void CSolidTextureShaderInterface::initialize_dialog (sxsdk::dialog_interface &d, void *)
{
}

/** 
 * ダイアログのイベントを受け取る.
 */
bool CSolidTextureShaderInterface::respond (sxsdk::dialog_interface &d, sxsdk::dialog_item_class &item, int action, void *)
{
	const int id = item.get_id();		// アクションがあったダイアログアイテムのID.

	if (id == sx::iddefault) {
		m_data.Clear();					// パラメータを初期化.
		load_dialog_data(d);			// ダイアログのパラメータを更新.https://www.assetstore.unity3d.com/en/#!/content/22369
		return true;
	}

	if (id == dlg_octaves_id) {
		m_data.octaves = std::min(std::max(item.get_int(), 1), 16);
	}
	if (id == dlg_moveV_id) {
		m_data.moveV = item.get_vec3();
		return true;
	}

	if (id == dlg_scale_height_id) {
		m_data.scaleHeight = item.get_float();
		return true;
	}
	if (id == dlg_scale_pow_id) {
		m_data.scalePow = item.get_float();
		return true;
	}
	if (id == dlg_scale_value_id) {
		m_data.scaleValue = item.get_float();
		return true;
	}

	return false;
}

/**
 * ダイアログのデータを設定する.
 */
void CSolidTextureShaderInterface::load_dialog_data (sxsdk::dialog_interface &d, void *)
{
	{
		sxsdk::dialog_item_class* item;
		item = &(d.get_dialog_item(dlg_octaves_id));
		item->set_int(m_data.octaves);
	}
	{
		sxsdk::dialog_item_class* item;
		item = &(d.get_dialog_item(dlg_moveV_id));
		item->set_vec3(m_data.moveV);
	}

	{
		sxsdk::dialog_item_class* item;
		item = &(d.get_dialog_item(dlg_scale_height_id));
		item->set_float(m_data.scaleHeight);
	}
	{
		sxsdk::dialog_item_class* item;
		item = &(d.get_dialog_item(dlg_scale_pow_id));
		item->set_float(m_data.scalePow);
	}
	{
		sxsdk::dialog_item_class* item;
		item = &(d.get_dialog_item(dlg_scale_value_id));
		item->set_float(m_data.scaleValue);
	}
}

/**
 * 値の変更を保存するときに呼ばれる.
 */
void CSolidTextureShaderInterface::save_dialog_data (sxsdk::dialog_interface &d, void *)
{
}



