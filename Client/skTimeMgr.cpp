#include "skTimeMgr.h"
#include "skApplication.h"

extern sk::Application application;

namespace sk
{
	LARGE_INTEGER TimeMgr::_mCpuFrequency = {};
	LARGE_INTEGER TimeMgr::_mPrevFrequency = {};
	LARGE_INTEGER TimeMgr::_mCurFrequency = {};
	float TimeMgr::_mDeltaTime = 0.0f;

	void TimeMgr::Initialize()
	{
		// CPU ���� ������
		QueryPerformanceFrequency(&_mCpuFrequency);

		// ���α׷��� ���۵����� ������
		QueryPerformanceCounter(&_mPrevFrequency);
	}

	void TimeMgr::Update()
	{
		QueryPerformanceCounter(&_mCurFrequency);

		float DifferenceFrequency
			= static_cast<float>(_mCurFrequency.QuadPart - _mPrevFrequency.QuadPart);

		_mDeltaTime = DifferenceFrequency / static_cast<float>(_mCpuFrequency.QuadPart);
		_mPrevFrequency.QuadPart = _mCurFrequency.QuadPart;
	}

	void TimeMgr::Render(HDC hdc)
	{
		//static float TimeCheck = 0.0f; // �ð� ����
		//
		//TimeCheck += _mDeltaTime; // 1�ʴ� ������ ���� üũ�ϱ�����
		//if (TimeCheck >= 1.0f)
		//{
		//	wchar_t szFloat[50] = {};
		//	float fps = 1.0f / _mDeltaTime; // fps = 1�ʴ� �����Ӽ�

		//	swprintf_s(szFloat, 50, L"fps : %f DT : %f", fps, _mDeltaTime);
		//	int strLen = wcsnlen_s(szFloat, 50);
		//	SetWindowText(application.GetHwnd(), szFloat);
		//	//TextOut(hdc, 10, 10, szFloat, strLen);

		//	TimeCheck = 0.0f;
		//}
	}
}