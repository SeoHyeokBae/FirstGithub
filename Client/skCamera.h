#pragma once
#include "CommonInclude.h"
#include "skGameObject.h"

namespace sk
{
	using namespace math;
	class Camera
	{
	public:
		static void Initialize();
		static void Update();

		// ī�޶� ��ġ�Ѹ�ŭ ȭ����� �ٸ� ������Ʈ���� �����ġ�� ���� ��� 
		//static Vector2 CalculatePosition(Vector2 pos) { return pos - _mDistance; }
		static Vector2 CalculatePosition(Vector2 pos,Vector2 CameraRatio = Vector2::One) { return pos - (_mDistance / CameraRatio); }

		static GameObject* GetTarget() { return _mTarget; }
		static void SetTarget(GameObject* target) { _mTarget = target; }

		static void SetLookPos(Vector2 look) { _mTargetPosition = look; }
		static void SetLookPosTime(Vector2 look)	// ��ǥ�������� �ð���� �̵��ϱ�����
		{
			_mTargetPosition = look;
			float MovDistance = (_mTargetPosition - _mPrvLookPosition).length();
			_mSpeed = MovDistance / _mTime;
			_mAccTime = 0.f;
		}
		static void SetPrvLookPos(Vector2 look) { _mPrvLookPosition = look; } // ������ġ ����

		static Vector2 GetLookPos() { return _mLookPosition; }
		static Vector2 GetPrvLookPos() { return _mPrvLookPosition; }
		static void SetCameraLimit_Right(float right) { _mLimitRightX = right; }
		static void SetCameraLimit_Left(float left) { _mLimitLeftX = left; }
		static void SetCameraLimit_Y(float y) { _mLimitY = y; }
		
		static void SetPlayMode(bool on) { _mbPlayMode = on; }
		static void SetCutSceneMode(bool on) { _mbCutSceneMode = on; }
		static bool GetColliderRender() { return _mbCollider; }

	private:
		static Vector2 _mResolution;
		static Vector2 _mLookPosition;	 // ī�޶� �ٶ󺸰� �ִ� ��ġ
		static Vector2 _mTargetPosition;	// ī�޶� Ÿ�� ��ġ
		static Vector2 _mPrvLookPosition;	// ī�޶� ������ġ
		static Vector2 _mDistance;		// �ػ� ��� ��ǥ�� ī�޶� ������ǥ�� �Ÿ�
		static GameObject* _mTarget;	/// ī�޶� �ٶ󺸴� ���� ������Ʈ
		
		static float _mLimitRightX;
		static float _mLimitLeftX;
		static float _mTime;
		static float _mAccTime;
		static float _mSpeed;
		static float _mLimitY;
		static bool _mbPlayMode;
		static bool _mbCutSceneMode;
		static bool _mbCollider;
	};

}

