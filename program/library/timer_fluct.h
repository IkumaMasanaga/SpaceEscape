#pragma once
#include "sequence.h"

namespace t2k {

	//------------------------------------------------------------------------------------------------------------
	//
	// 時間経過での数値変化
	// tips... このクラスを包含したクラスはポインタで生成すること
	//

    template< class T >
    class TimerFluct final {
	private:
		T start_ = T();
		T complete_ = T();
		T to_complete_normalize_ = T();
		T* origin_ = nullptr;
		float distance_ = 0;
		float fluctuation_ = 0;
		float complete_time_ = 0;
		float trigonometric_power_ = 1.0f;
		bool is_complete_ = false;
		Sequence<TimerFluct<T>*> sequence_ = Sequence<TimerFluct<T>*>( this, &TimerFluct<T>::seqIdle ) ;


		// すべての処理で共通する引数セット
		inline void setCommonArgument(T* origin, const T& complete, const float complete_time) {
			origin_ = origin;
			complete_ = complete;
			complete_time_ = complete_time;
		}

		// すべての処理で共通する記述
		inline bool seqCommonDescription() {
			if (sequence_.isStart()) { start_ = *origin_; }
			if (sequence_.getProgressTime() >= complete_time_) {
				*origin_ = complete_;
				return true;
			}
			return false;
		}

		// Accel と Brake の共通記述
		inline void setAccelBrakeDescription(const T& to_complete_normalize, const float distance) {
			distance_ = distance;
			to_complete_normalize_ = to_complete_normalize;
			// 自由落下の公式を利用して加速度を計算 
			// 公式 t = sqrt( 2h / g )
			// 変形して g = 2h / t^2
			// [ t:時間  h:高さ  g:重力加速度 ]
			fluctuation_ = (2.0f * distance_) / powf(complete_time_, 2.0f);
		}

		// 待機
		inline bool seqIdle() { return true; }

		// 等速直線運動
		inline bool seqLinear() {
			if (seqCommonDescription()) {
				sequence_.change(&TimerFluct::seqIdle);
				return true;
			}
			T v = static_cast<T>( (complete_ - start_) / complete_time_ * sequence_.getProgressTime() ) ;
			*origin_ = start_ + v ;
			return false;
		}

		// 等加速直線運動
		inline bool seqAccel() {
			if (seqCommonDescription()) {
				sequence_.change(&TimerFluct::seqIdle);
				return true;
			}
			// 等加速直線運動の公式 x = x0 + ( v0 * t ) + ( 1/2 * a * t^2 )
			// ( v0 * t ) は初速だが今回は使わないので省略
			// [ x:現在位置  x0:初期位置  t:時間  a:加速度 ]
			float a = fluctuation_;
			float t = sequence_.getProgressTime();
			T vn = to_complete_normalize_;
			*origin_ = start_ + vn * ( ( a * powf( t, 2 ) ) * 0.5f ) ;
			return false;
		}

		// 等減速直線運動
		inline bool seqBrake() {
			if (seqCommonDescription()) {
				sequence_.change( &TimerFluct::seqIdle );
				return true;
			}
			float a = fluctuation_;
			float t = sequence_.getProgressTime();
			T vn = to_complete_normalize_;
			*origin_ = complete_ - vn * ((a * powf(complete_time_ - t, 2)) * 0.5f);
			return false;
		}

		// sin波 0 ～ πの運動
		inline bool seqSin() {
			seqCommonDescription();
			T v = static_cast<T>(complete_ - start_) ;
			float t = sequence_.getProgressTime() / complete_time_ ;
			float s = sin( toRadian(t * 180.0f) ) ;
			float trigonometric = powf(s,trigonometric_power_) ;
			*origin_ = start_ + v * trigonometric ;
			return false;
		}

		// cos波 0 ～ πの運動
		inline bool seqCos() {
			seqCommonDescription();
			T v = static_cast<T>(complete_ - start_);
			float t = sequence_.getProgressTime() / complete_time_;
			float c = cos(toRadian(t * 180.0f));
			float trigonometric = powf(c, trigonometric_power_);
			*origin_ = start_ + v * trigonometric;
			return false;
		}

	public :
		TimerFluct<T>(){}
		~TimerFluct<T>(){}

		//==============================================================================================================
		// 等速直線運動を設定
		// arg1... 変動させるインスタンスへのポインタ
		// arg2... 完了値
		// arg3... 完了時間 (秒)
		//==============================================================================================================
		inline void setMethodLinear(T* origin, const T& complete, const float complete_time){
			setCommonArgument(origin, complete, complete_time);
			sequence_.immediatelyChange(&TimerFluct<T>::seqLinear);
		}

		//==============================================================================================================
		// 等加速直線運動を設定
		// arg1... 変動させるインスタンスへのポインタ
		// arg2... 完了値
		// arg3... arg1 -> arg2 への正規化値
		// arg4... arg1 -> arg2 への距離
		// arg5... 完了時間 (秒)
		//==============================================================================================================
		inline void setMethodAccel(T* origin, const T& complete, const T& to_complete_normalize, const float distance, const float complete_time) {
			setCommonArgument(origin, complete, complete_time);
			setAccelBrakeDescription(to_complete_normalize, distance);
			sequence_.immediatelyChange(&TimerFluct<T>::seqAccel);
		}

		//==============================================================================================================
		// 等減速直線運動を設定
		// arg1... 変動させるインスタンスへのポインタ
		// arg2... 完了値
		// arg3... arg1 -> arg2 への正規化値
		// arg4... arg1 -> arg2 の距離
		// arg5... 完了時間 (秒)
		//==============================================================================================================
		inline void setMethodBrake(T* origin, const T& complete, const T& to_complete_normalize, const float distance, const float complete_time) {
			setCommonArgument(origin, complete, complete_time);
			setAccelBrakeDescription(to_complete_normalize, distance);
			sequence_.immediatelyChange(&TimerFluct<T>::seqBrake);
		}

		//==============================================================================================================
		// sin波 0 ～ πの運動を設定
		// arg1... 変動させるインスタンスへのポインタ
		// arg2... 完了値
		// arg3... 完了時間 (秒)
		// arg4... 三角比の乗数 省略可
		//==============================================================================================================
		inline void setMethodSin(T* origin, const T& complete, const float complete_time, const float trigonometric_power = 1.0f) {
			trigonometric_power_ = trigonometric_power;
			setCommonArgument(origin, complete, complete_time);
			sequence_.immediatelyChange(&TimerFluct<T>::seqSin);
		}

		//==============================================================================================================
		// cos波 0 ～ πの運動を設定
		// arg1... 変動させるインスタンスへのポインタ
		// arg2... 完了値
		// arg3... 完了時間 (秒)
		// arg4... 三角比の乗数 省略可
		//==============================================================================================================
		inline void setMethodCos(T* origin, const T& complete, const float complete_time, const float trigonometric_power = 1.0f) {
			trigonometric_power_ = trigonometric_power;
			setCommonArgument(origin, complete, complete_time);
			sequence_.immediatelyChange(&TimerFluct<T>::seqCos);
		}

		//==============================================================================================================
		// 数値変動の更新
		// arg1... フレーム間のデルタタイム
		// ret.... [ true : 変動完了 ] [ false : 変動中 ]
		//==============================================================================================================
		inline bool isCompleteUpdate() {
			is_complete_ = sequence_.update();
			return is_complete_;
		}

		//==============================================================================================================
		// 変動完了したか
		// ret.... [ true : 変動完了 ] [ false : 変動中 ]
		//==============================================================================================================
		inline bool isComplete() const { return is_complete_; }

	};

}

