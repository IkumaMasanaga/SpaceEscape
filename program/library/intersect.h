#pragma once

namespace t2k {

	//-----------------------------------------------------------------------------------------------------
	// 点と矩形(正方形)のの衝突検知
	// arg1...点のｘ座標
	// arg2...点のｙ座標
	// arg3...矩形の中心ｘ座標
	// arg4...矩形の中心ｙ座標
	// arg5...矩形のサイズ
	// ret....[ 衝突している : true ]   [ 衝突していない : false ]
	bool isIntersectPointRect(const int point_x, const int point_y, const int rect_x, const int rect_y, const int rect_size);

	//-----------------------------------------------------------------------------------------------------
	// 矩形と矩形の衝突検知 ※矩形の左上・右下の頂点座標指定
	// arg1...矩形Aの左のｘ座標
	// arg2...矩形Aの右のｘ座標
	// arg3...矩形Aの上のｙ座標
	// arg4...矩形Aの下のｙ座標
	// arg5...矩形Bの左のｘ座標
	// arg6...矩形Bの右のｘ座標
	// arg7...矩形Bの上のｙ座標
	// arg8...矩形Bの下のｙ座標
	// ret....[ 衝突している : true ]   [ 衝突していない : false ]
	bool isIntersectRectPrimitive(const int a_left, const int a_right, const int a_top, const int a_bottom,
		const int b_left, const int b_right, const int b_top, const int b_bottom);

	//-----------------------------------------------------------------------------------------------------
	// 矩形と矩形の衝突検知　※矩形の中心と幅高さ指定
	// arg1...矩形Aのｘ座標
	// arg2...矩形Aのｙ座標
	// arg3...矩形Aの幅
	// arg4...矩形Aの高さ
	// arg5...矩形Bのｘ座標
	// arg6...矩形Bのｙ座標
	// arg7...矩形Bの幅
	// arg8...矩形Bの高さ
	// ret....[ 衝突している : true ]   [ 衝突していない : false ]
	bool isIntersectRect(const int a_rect_x, const int a_rect_y, const int a_rect_size_w, const int a_rect_size_h,
		const int b_rect_x, const int b_rect_y, const int b_rect_size_w, const int b_rect_size_h);

	//-----------------------------------------------------------------------------------------------------
	// 矩形と矩形の衝突検知　※矩形の中心と幅高さ指定
	// arg1...矩形Aの座標
	// arg2...矩形Aの幅
	// arg3...矩形Aの高さ
	// arg4...矩形Bの座標
	// arg5...矩形Bの幅
	// arg6...矩形Bの高さ
	// ret....[ 衝突している : true ]   [ 衝突していない : false ]
	inline bool isIntersectRect(const t2k::Vector3& a, const int a_rect_size_w, const int a_rect_size_h,
		const t2k::Vector3& b, const int b_rect_size_w, const int b_rect_size_h) {
		return isIntersectRect((int)a.x, (int)a.y, a_rect_size_w, a_rect_size_h, (int)b.x, (int)b.y, b_rect_size_w, b_rect_size_h);
	}
 
	//-----------------------------------------------------------------------------------------------------
	// 矩形と矩形の衝突検知 & 座標補正
	// arg1 ...矩形Aの現在座標( 補正対象の座標変数 )
	// arg2 ...矩形Aの移動前の座標
	// arg3 ...矩形Aの幅
	// arg4 ...矩形Aの高さ
	// arg5 ...矩形Bの座標
	// arg6 ...矩形Bの幅
	// arg7 ...矩形Bの高さ
	// arg8 ...上補正の追加スペース( 省略可 デフォルト 1.0f )
	// arg9 ...下補正の追加スペース( 省略可 デフォルト 1.0f )
	// arg10...左補正の追加スペース( 省略可 デフォルト 1.0f )
	// arg11...右補正の追加スペース( 省略可 デフォルト 1.0f )
	// ret....[ 衝突していない : 0 ] 
	//        [ 対象を左に補正 : 1 ] 
	//        [ 対象を右に補正 : 2 ]
	//        [ 対象を上に補正 : 3 ]
	//        [ 対象を下に補正 : 4 ]
	// tips...矩形Aが補正対象のオブジェクト
	//        矩形Bは壁等の移動しないオブジェクトを想定しています
	int isIntersectRectToCorrectPosition( t2k::Vector3& a_now, const t2k::Vector3 &a_prev, const int a_rect_size_w, const int a_rect_size_h,
		const t2k::Vector3& b, const int b_rect_size_w, const int b_rect_size_h,
		const float correct_space_up = 1.0f, const float correct_space_down = 1.0f, const float correct_space_left = 1.0f, const float correct_space_right = 1.0f);

	//-----------------------------------------------------------------------------------------------------
	// 矩形と矩形の衝突検知 & 座標補正(オフセット値指定)
	// arg1 ...矩形Aの現在座標( 補正対象の座標変数 )
	// arg2 ...矩形Aの衝突検知矩形までのオフセット値
	// arg3 ...矩形Aの移動前の座標
	// arg4 ...矩形Aの幅
	// arg5 ...矩形Aの高さ
	// arg6 ...矩形Bの座標
	// arg7 ...矩形Bの衝突検知矩形までのオフセット値
	// arg8 ...矩形Bの幅
	// arg9 ...矩形Bの高さ
	// arg10...上補正の追加スペース( 省略可 デフォルト 1.0f )
	// arg11...下補正の追加スペース( 省略可 デフォルト 1.0f )
	// arg12...左補正の追加スペース( 省略可 デフォルト 1.0f )
	// arg13...右補正の追加スペース( 省略可 デフォルト 1.0f )
	// ret....[ 衝突していない : 0 ] 
	//        [ 対象を左に補正 : 1 ] 
	//        [ 対象を右に補正 : 2 ]
	//        [ 対象を上に補正 : 3 ]
	//        [ 対象を下に補正 : 4 ]
	// tips...矩形Aが補正対象のオブジェクト
	//        矩形Bは壁等の移動しないオブジェクトを想定しています
	int isIntersectRectToCorrectPositionOffset(t2k::Vector3& a_now, const t2k::Vector3& a_offset, const t2k::Vector3& a_prev, const int a_rect_size_w, const int a_rect_size_h,
		const t2k::Vector3& b, const t2k::Vector3& b_offset, const int b_rect_size_w, const int b_rect_size_h,
		const float correct_space_up = 1.0f, const float correct_space_down = 1.0f, const float correct_space_left = 1.0f, const float correct_space_right = 1.0f);

	//-----------------------------------------------------------------------------------------------------
	// 円と円の衝突検知
	// arg1...円Aの中心座標
	// arg2...円Aの半径
	// arg3...円Bの中心座標
	// arg4...円Bの半径
	// ret....[ 衝突している : true ]   [ 衝突していない : false ]
	bool isIntersectCircle(const t2k::Vector3& a, float a_radius, const t2k::Vector3& b, float b_radius);



}
