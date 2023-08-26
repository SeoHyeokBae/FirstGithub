#include "skRigidbody.h"
#include "skTimeMgr.h"
#include "skGameObject.h"
#include "skTransform.h"

namespace sk
{
	Rigidbody::Rigidbody()
		:Component(eComponentType::Rigidbody)
		, _mMass(1.0f)
		, _mFriction(850.0f)
		, _mbGround(false)
	{
		_mLimitedVelocity.x = 500.0f;
		_mLimitedVelocity.y = 5000.0f;
		_mGravity = Vector2(0.0f, 1500.0f);
	}
	Rigidbody::~Rigidbody()
	{
	}
	void Rigidbody::Initialize()
	{
	}
	void Rigidbody::Update()
	{
		//F= ma
		_mAccelation = _mForce / _mMass;
		
		// �ӵ��� ���ӵ��� ������� �Ѽӵ�
		_mVelocity += _mAccelation * TimeMgr::DeltaTime();

		if (_mbGround)
		{
			// ���� �پ�������
			Vector2 gravity = _mGravity;
			gravity.normalize();
			float dot = sk::math::Dot(_mVelocity, gravity);	// ����� �߷� ���� ����
			_mVelocity -= gravity * dot;
		}
		else
		{
			// ���߿� ���� ��
			_mVelocity += _mGravity * TimeMgr::DeltaTime();
		}

		/////////////////////////////////////////////////////////////
		// �ִ� �ӵ�����
		Vector2 gravity = _mGravity;
		gravity.normalize();
		float dot = sk::math::Dot(_mVelocity, gravity);
		gravity = gravity * dot;

		Vector2 sideVelocity = _mVelocity - gravity;
		if (_mLimitedVelocity.y < gravity.length())
		{
			gravity.normalize();
			gravity *= _mLimitedVelocity.y;
		}
		
		if (_mLimitedVelocity.x < sideVelocity.length())
		{
			sideVelocity.normalize();
			sideVelocity *= _mLimitedVelocity.x;
		}
		_mVelocity = gravity + sideVelocity;


		if (!(_mVelocity == Vector2::Zero))
		{
			// �ӵ��� �ݴ� �������� ������ ����
			Vector2 friction = - _mVelocity;
			friction = friction.normalize() * _mFriction * _mMass * TimeMgr::DeltaTime();

			// ���������� ���� �ӵ� ���ҷ��� ���� �ӵ����� ū ���

			if (_mVelocity.length() < friction.length())
			{
				// ����
				_mVelocity = Vector2(0.f,0.f);
			}
			else
			{
				// ���������� �ӵ� ����
				_mVelocity += friction;
			}
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		pos = pos + _mVelocity * TimeMgr::DeltaTime();
		tr->SetPosition(pos);
		_mForce.clear();
	}
	void Rigidbody::Render(HDC hdc)
	{
	}
}