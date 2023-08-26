#pragma once
#include "CommonInclude.h"
#include "skCollider.h"

namespace sk
{
#define LAYER_MAX (UINT)eLayerType::End

	union COlliderID
	{
		struct
		{
			UINT left;
			UINT right;
		};
		UINT64 id;
	};

	using namespace enums;
	class CollisionMgr
	{
		public:
			static void Initialize();
			static void Update();
			static void Render(HDC hdc);
			static void Release();

			static void Clear();
			static void CollisionLayerCheck(eLayerType left, eLayerType right, bool enable);	// �浹 üũ �Ұ��� ���Ұ��� 
			static void LayerCollision(class Scene* scene, eLayerType left, eLayerType right);	// ���̾�� ���� �浹üũ
			static void ColliderCollision(Collider* left, Collider* right);						// �浹�� ����
			static bool Intersect(Collider* left, Collider* reight);							// �浹���� Ȯ��


		private:
			static std::map<UINT64, bool> _mCollisionMap;
			static std::bitset<LAYER_MAX> _mLayerMasks[LAYER_MAX];	//bitset = <> ����ŭ �޸� ����Ʈ
	};
}

