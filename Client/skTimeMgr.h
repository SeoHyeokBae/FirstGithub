#pragma once
#include "CommonInclude.h"

namespace sk
{
	class TimeMgr
	{
	public:
		void static Initialize();
		void static Update();
		void static Render(HDC hdc);

		__forceinline static float DeltaTime() { return _mDeltaTime; }

		void static Delay();
	private:
		static LARGE_INTEGER _mCpuFrequency; // LARGE_INTEGER 16����Ʈ
		static LARGE_INTEGER _mPrevFrequency;
		static LARGE_INTEGER _mCurFrequency;
		static float _mDeltaTime; // DeltaTime 1�����Ӵ� �ð�

		static bool _mbDelay;
		static float _mfDelayTime;
		static float _mfDelayAcc;
	};
}


