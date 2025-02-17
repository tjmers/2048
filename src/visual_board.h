#pragma once

#include "board.h"

#include <Windows.h>

#include <unordered_map>

#include <d2d1.h>

#include "graphics.h"

class VisualBoard : public Board {

private:

    static ID2D1Bitmap* sprite;
    static std::unordered_map<int, D2D1_RECT_F> num_to_sprite_location;

    mutable bool change_since_update;

public:

    VisualBoard();

    inline void change() const { change_since_update = true; }

    static HRESULT init(Graphics& g);

    void draw(Graphics& g) const;

    #ifndef SOLVER
    void update();
    #endif
};