#include "skCutSceneCollider.h"
#include "skPlayer.h"
#include "skCollider.h"
#include "skRigidbody.h"
#include "skTransform.h"
#include "skSceneMgr.h"
#include "skTimeMgr.h"
#include "skCamera.h"
#include "skInput.h"
#include"skSceneMgr.h"
#include "skElderBroPrivateCutScene.h"
#include "skAnimator.h"

#include "skFirstBossScene.h"

namespace sk
{
	CutSceneCollider::CutSceneCollider()
		: _mTime(0.f)
		, _mPlayer(nullptr)
		, _mStart(false)
	{
	}
	CutSceneCollider::~CutSceneCollider()
	{
	}
	void CutSceneCollider::Initialize()
	{
	}
	void CutSceneCollider::Update()
	{
		GameObject::Update();

		if (_mStart)
		{
			_mTime += TimeMgr::DeltaTime();
		}

		if (_mTime > 6.0f)
		{
			if (_mPlayer != nullptr)
			{
				_mPlayer->SetState(Player::eState::IDLE);
			}

			Destroy(this);
		}
	}
	void CutSceneCollider::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}


	void CutSceneCollider::PlayFirstBossScene()
	{
		Camera::SetTarget(nullptr);						// ī�޶� ���� ����
		Camera::SetPrvLookPos(Camera::GetLookPos());	// ī�޶� ����ġ ����
		FirstBossScene::_mbCutSceneOn = true;			// ������ �ƾ� ���
		Camera::SetLookPosTime(Vector2(1420.f, 360.f));	// �ƾ� Ÿ���������� ī�޶��̵� ���
		Camera::SetCutSceneMode(true);					// ī�޶󿡼� �ƾ� ��� ����
		ElderBroPrivateCutScene::SetCanPlay(true);		// �ƽ� ������Ʈ play
	}


	void CutSceneCollider::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		_mPlayer = player;

		_mStart = true;

		if (player != nullptr)
		{
			Transform* tr = player->GetComponent<Transform>();

			float len = fabs(other->GetPosition().x - this->GetComponent<Collider>()->GetPosition().x);
			float scale = fabs(other->GetSize().x / 2.0f + this->GetComponent<Collider>()->GetSize().x / 2.0f);

			if (len < scale)
			{
				Vector2 playerPos = tr->GetPosition();
				playerPos.x -= (scale - len) + 1.f;
				tr->SetPosition(playerPos);
			}

			if (SceneMgr::GetActiveScene()->GetName() == L"FirstBossScene")
			{
				// TODO
				player->GetComponent<Animator>()->PlayAnimation(L"Idle_right", true);
				player->SetState(Player::eState::CUTSCENE);
				PlayFirstBossScene();
			}
		}
	}
	void CutSceneCollider::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			Transform* tr = player->GetComponent<Transform>();

			float len = fabs(other->GetPosition().x - this->GetComponent<Collider>()->GetPosition().x);
			float scale = fabs(other->GetSize().x / 2.0f + this->GetComponent<Collider>()->GetSize().x / 2.0f);

			if (len < scale)
			{
				Vector2 playerPos = tr->GetPosition();
				playerPos.x -= (scale - len) + 1.f;
				tr->SetPosition(playerPos);
			}
			player->GetComponent<Animator>()->PlayAnimation(L"Idle_right",true);
			
		}
	}
	void CutSceneCollider::OnCollisionExit(Collider* other)
	{
	}
}

