#include "skInput.h"

namespace sk
{
	std::vector<Input::Key> Input::_mKeys = {};

	int ASCII[(UINT)eKeyCode::End] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
		VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT,VK_LSHIFT,VK_SPACE,VK_RETURN,
	};

	void Input::Initialize()
	{
		for (size_t i = 0; i < (UINT)eKeyCode::End; i++)
		{
			Key key = {};
			key.code = (eKeyCode)i;
			key.state = eKeyState::None;
			key.bPressed = false;

			_mKeys.push_back(key);
		}
	}

	void Input::Update()
	{
		for (size_t i = 0; i < (UINT)eKeyCode::End; i++)
		{
			// Ű�� �����ִ�
			if (GetAsyncKeyState(ASCII[i]) & 0x8000)
			{
				if (_mKeys[i].bPressed == true)			// �������� �����־���
					_mKeys[i].state = eKeyState::Pressed;
				else
					_mKeys[i].state = eKeyState::Down; // �������� �������� �ʾҴ�

				_mKeys[i].bPressed = true;
			}
			else // Ű�� �ȴ����־���
			{
				if (_mKeys[i].bPressed == true)
					_mKeys[i].state = eKeyState::Up;
				else
					_mKeys[i].state = eKeyState::None;

				_mKeys[i].bPressed = false;
			}
		}
	}
}