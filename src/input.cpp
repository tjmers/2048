#include "input.h"

Input::KeyboardInput Input::keys[static_cast<int>(Key::COUNT)];


void Input::HandleKeyboardInput(UINT_PTR key_code, bool is_down) {
	switch (key_code) {
	case VK_LEFT:
		keys[static_cast<int>(Key::LEFT)].is_down = is_down;
		break;
	case VK_RIGHT:
		keys[static_cast<int>(Key::RIGHT)].is_down = is_down;
		break;
	case VK_UP:
		keys[static_cast<int>(Key::UP)].is_down = is_down;
		break;
	case VK_DOWN:
		keys[static_cast<int>(Key::DOWN)].is_down = is_down;
		break;

	}
}

void Input::Reset() {
	for (int i = 0; i < static_cast<int>(Key::COUNT); i++) {
		keys[i].is_down = false;
	}
}
