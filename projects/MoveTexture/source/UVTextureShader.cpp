/**
 * UVテクスチャのShader.
 */
#include "UVTextureShader.h"
#include "StreamCtrl.h"

// SXULダイアログボックスでのイベントID.
enum
{
	dlg_uvIndex_id = 101,			// UV.
	dlg_repeatX_id = 102,			// 反復 - 横.
	dlg_repeatY_id = 103,			// 反復 - 縦.
	dlg_flipColor_id = 104,			// 色反転.
	dlg_offsetV_id = 105,			// オフセット.
	dlg_moveV_id = 201,				// 移動量.
};

CUVTextureShaderInterface::CUVTextureShaderInterface (sxsdk::shade_interface& _shade) : m_shade(_shade), sxsdk::shader_interface(_shade)
{
}

CUVTextureShaderInterface::~CUVTextureShaderInterface ()
{
}

/**
 * シェーダが独自に使うデータ領域を生成.
 */
sxsdk::shader_info_base_class *CUVTextureShaderInterface::new_shader_info (sxsdk::stream_interface *stream, void *)
{
	// streamから情報読み込み.
	CMoveTextureUVShaderData data;
	if (stream) {
		StreamCtrl::LoadUVTextureShaderData(stream, data);
	}

	return new ShaderInfoC(data);
}

/**
 * Shaderとしての計算を行う.
 */
void CUVTextureShaderInterface::shade (void *)
{
	// UVを持たない場合.
	if (!has_uv()) {
		set_Ci(get_mapping_color());
		return;
	}

	// Shaderで参照する情報.
	CMoveTextureUVShaderData data;
	try {
		ShaderInfoC* shaderInfo = (ShaderInfoC *)(get_shader_info());
		if (shaderInfo) {
			if ((shaderInfo->magic_number()) == UVTEXTURE_SHADER_MAGIC_NUMBER) data = shaderInfo->data;
		}
	} catch (...) { }

	// UV値を取得.
	sxsdk::vec2 uv(0, 0);
	if (data.uvIndex == 0) {
		uv = sxsdk::vec2(get_s(), get_t());		// 距離UV.
	} else {
		uv = sxsdk::vec2(get_u(), get_v());		// パラメータUV.
	}

	// オフセット分を加算.
	uv += data.offsetV;

	// 移動量分を加算.
	if (!sx::zero(m_frameRate)) {
		uv += (data.moveV * m_currentFrame) / (float)m_frameRate;
	}

	// 反復回数を考慮.
	if (data.repeatX >= 1 && data.repeatY >= 1) {
		uv.x *= (float)data.repeatX;
		uv.y *= (float)data.repeatY;
	}

	// テクスチャ上の色.
	const sxsdk::rgba_class tCol = sample_image(uv.x, uv.y);
	sxsdk::rgba_class col = tCol;

	// 色を反転.
	if (data.flipColor) {
		col.red   = 1.0f - std::max(std::min(col.red  , 1.0f), 0.0f);
		col.green = 1.0f - std::max(std::min(col.green, 1.0f), 0.0f);
		col.blue  = 1.0f - std::max(std::min(col.blue , 1.0f), 0.0f);
	}

	set_Ci(sx::rgb(col));
}

/**
 * Shaderとしてのバンプ計算を行う.
 */
void CUVTextureShaderInterface::bump (void*)
{
	// UVを持たない場合.
	if (!has_uv()) return;

	// Shaderで参照する情報.
	CMoveTextureUVShaderData data;
	try {
		ShaderInfoC* shaderInfo = (ShaderInfoC *)(get_shader_info());
		if (shaderInfo) {
			if ((shaderInfo->magic_number()) == UVTEXTURE_SHADER_MAGIC_NUMBER) data = shaderInfo->data;
		}
	} catch (...) { }

	// UV値を取得.
	sxsdk::vec2 uv(0, 0);
	if (data.uvIndex == 0) {
		uv = sxsdk::vec2(get_s(), get_t());		// 距離UV.
	} else {
		uv = sxsdk::vec2(get_u(), get_v());		// パラメータUV.
	}

	// オフセット分を加算.
	uv += data.offsetV;

	// 移動量分を加算.
	if (!sx::zero(m_frameRate)) {
		uv += (data.moveV * m_currentFrame) / (float)m_frameRate;
	}

	// 反復回数を考慮.
	if (data.repeatX >= 1 && data.repeatY >= 1) {
		uv.x *= (float)data.repeatX;
		uv.y *= (float)data.repeatY;
	}

	sx::vec2 d = sample_bump(uv.x, uv.y);

	// 反転.
	if (data.flipColor) d = -d;

	set_N(normalize(get_N() + (get_dPdu() * d.x + get_dPdv() * d.y) * get_mapping()));
}

/**
 * 個々のフレームのレンダリング開始前に呼ばれる.
 * @param[in] b 未使用.
 * @param[in] rendering_context レンダリング情報クラスのポインタ.
 */
void CUVTextureShaderInterface::pre_rendering (bool &b, sxsdk::rendering_context_interface *rendering_context, void *aux)
{
	// フレームレートを取得.
	m_frameRate    = 0.0f;
	m_currentFrame = 0.0f;
	try {
		compointer<sxsdk::scene_interface> scene(rendering_context->get_scene_interface());
		if (scene) {
			if (!sx::zero(scene->get_step_frames())) {
				m_frameRate = (float)(scene->get_frame_rate());
			}
		}
		m_currentFrame = rendering_context->get_current_frame();
	} catch (...) { }
}

/**
 * レンダリング終了時に呼ばれる.
 */
void CUVTextureShaderInterface::post_rendering (bool &b, sxsdk::rendering_context_interface *rendering_context)
{
}

/**
 * パラメータの指定.
 */
bool CUVTextureShaderInterface::ask (sxsdk::stream_interface *stream, void *)
{
	compointer<sxsdk::dialog_interface> dlg(m_shade.create_dialog_interface_with_uuid(UVTEXTURE_SHADER_ID));
	dlg->set_resource_name("moveTexture_uvTexture_dlg");

	dlg->set_responder(this);
	this->AddRef();			// set_responder()に合わせて、参照カウンタを増やす。 .

	// streamから情報を読み込み.
	StreamCtrl::LoadUVTextureShaderData(stream, m_data);

	// ダイアログの表示.
	if (dlg->ask()) {
		// streamに情報を保持.
		StreamCtrl::SaveUVTextureShaderData(stream, m_data);
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
void CUVTextureShaderInterface::initialize_dialog (sxsdk::dialog_interface &d, void *)
{
}

/** 
 * ダイアログのイベントを受け取る.
 */
bool CUVTextureShaderInterface::respond (sxsdk::dialog_interface &d, sxsdk::dialog_item_class &item, int action, void *)
{
	const int id = item.get_id();		// アクションがあったダイアログアイテムのID.

	if (id == sx::iddefault) {
		m_data.Clear();				// パラメータを初期化.
		load_dialog_data(d);		// ダイアログのパラメータを更新.https://www.assetstore.unity3d.com/en/#!/content/22369
		return true;
	}

	if (id == dlg_uvIndex_id) {
		m_data.uvIndex = item.get_selection();
		return true;
	}

	if (id == dlg_repeatX_id) {
		m_data.repeatX = std::max(1, item.get_int());
		return true;
	}

	if (id == dlg_repeatY_id) {
		m_data.repeatY = std::max(1, item.get_int());
		return true;
	}

	if (id == dlg_flipColor_id) {
		m_data.flipColor = item.get_bool();
		return true;
	}

	if (id == dlg_offsetV_id) {
		m_data.offsetV = item.get_vec2();
		return true;
	}

	if (id == dlg_moveV_id) {
		m_data.moveV = item.get_vec2();
		return true;
	}

	return false;
}

/**
 * ダイアログのデータを設定する.
 */
void CUVTextureShaderInterface::load_dialog_data (sxsdk::dialog_interface &d, void *)
{
	{
		sxsdk::dialog_item_class* item;
		item = &(d.get_dialog_item(dlg_uvIndex_id));
		item->set_selection(m_data.uvIndex);
	}
	{
		sxsdk::dialog_item_class* item;
		item = &(d.get_dialog_item(dlg_repeatX_id));
		item->set_int(m_data.repeatX);
	}
	{
		sxsdk::dialog_item_class* item;
		item = &(d.get_dialog_item(dlg_repeatY_id));
		item->set_int(m_data.repeatY);
	}
	{
		sxsdk::dialog_item_class* item;
		item = &(d.get_dialog_item(dlg_flipColor_id));
		item->set_bool(m_data.flipColor);
	}
	{
		sxsdk::dialog_item_class* item;
		item = &(d.get_dialog_item(dlg_offsetV_id));
		item->set_vec2(m_data.offsetV);
	}
	{
		sxsdk::dialog_item_class* item;
		item = &(d.get_dialog_item(dlg_moveV_id));
		item->set_vec2(m_data.moveV);
	}
}

/**
 * 値の変更を保存するときに呼ばれる.
 */
void CUVTextureShaderInterface::save_dialog_data (sxsdk::dialog_interface &d, void *)
{
}



