#pragma once

#include <Windows.h>

#include <utility>

enum class Key {
	UP, DOWN, LEFT, RIGHT, COUNT
};



class Input {
	struct KeyboardInput {
		bool is_down = false;
	};

	static KeyboardInput keys[];
public:
	inline static bool GetKeyDown(Key key) { return keys[static_cast<int>(key)].is_down; }
	inline static void SetKey(Key key, bool is_down) { keys[static_cast<int>(key)].is_down = is_down; }
	static void HandleKeyboardInput(UINT_PTR key_code, bool is_down);
	static void Reset();
};