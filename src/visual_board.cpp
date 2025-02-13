#include "visual_board.h"

#include <Windows.h>

#include <unordered_map>
#include <iostream>

#include <d2d1.h>

#ifndef SOLVER
#include "input.h"
#endif

ID2D1Bitmap* VisualBoard::sprite = nullptr;
std::unordered_map<int, D2D1_RECT_F> VisualBoard::num_to_sprite_location;

VisualBoard::VisualBoard() : Board(), change_since_update(true) {

}

HRESULT VisualBoard::init(Graphics& g) {

    Board::init();

    int num = 2;
    float x = 0, y = 0;
    for (int i = 0; i < 16; i++) {
        
        num_to_sprite_location.insert({num, {x, y, x + 127, y + 127}});

        x += 128;

        if (x >= 511) {
            x = 0;
            y += 128;
        }

        num *= 2;
    }

    return g.LoadBitmapFromFile(L"./img/2048.png", &sprite);
}



void VisualBoard::draw(Graphics& g) const {

    if (!change_since_update)
        return;

    // Clear the screen
    g.ClearScreen(D2D1::ColorF::White);

    // Draw the boxes
    for (int i = 0; i < get_board().size(); ++i) {
        if (get_board()[i] != 0) {
            float x = (i % 4) * (SCREEN_WIDTH / 4);
            float y = (i / 4) * (SCREEN_HEIGHT / 4);
            g.DrawBitmap(sprite, num_to_sprite_location.at(get_board()[i]), {x, y, x + SCREEN_WIDTH / 4, y + SCREEN_HEIGHT / 4});
        }
    }

    // Draw the outline
    g.SetColor(D2D1::ColorF::Black);
    constexpr static float OUTLINE_THICKNESS = 5.0f;
    g.DrawRect({0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}, OUTLINE_THICKNESS);
    g.DrawLine({0, SCREEN_HEIGHT / 4}, {SCREEN_WIDTH, SCREEN_HEIGHT / 4}, OUTLINE_THICKNESS);
    g.DrawLine({0, SCREEN_HEIGHT / 2}, {SCREEN_WIDTH, SCREEN_HEIGHT / 2}, OUTLINE_THICKNESS);
    g.DrawLine({0, 3 * SCREEN_HEIGHT / 4}, {SCREEN_WIDTH, 3 * SCREEN_HEIGHT / 4}, OUTLINE_THICKNESS);
    g.DrawLine({SCREEN_WIDTH / 4, 0}, {SCREEN_WIDTH / 4, SCREEN_HEIGHT}, OUTLINE_THICKNESS);
    g.DrawLine({SCREEN_WIDTH / 2, 0}, {SCREEN_WIDTH / 2, SCREEN_HEIGHT}, OUTLINE_THICKNESS);
    g.DrawLine({3 * SCREEN_WIDTH / 4, 0}, {3 * SCREEN_WIDTH / 4, SCREEN_HEIGHT}, OUTLINE_THICKNESS);

    change_since_update = false;
}

#ifndef SOLVER
void VisualBoard::update() {
    // if a single key was not pressed, do nothing and return

    if (Input::GetKeyDown(Key::LEFT) + Input::GetKeyDown(Key::RIGHT) + 
        Input::GetKeyDown(Key::UP) + Input::GetKeyDown(Key::DOWN) != 1) return;

    if (Input::GetKeyDown(Key::LEFT)) {
        if (can_perform_left()) {
            perform_left();
            generate_new_square();
        }
        Input::SetKey(Key::LEFT, false);
    } else if (Input::GetKeyDown(Key::RIGHT)) {
        if (can_perform_right()) {
            perform_right();
            generate_new_square();
        }
        Input::SetKey(Key::RIGHT, false);
    } else if (Input::GetKeyDown(Key::UP)) {
        if (can_perform_up()) {
            perform_up(); 
            generate_new_square();
        } 
        Input::SetKey(Key::UP, false);
    } else {
        if (can_perform_down()) {
            perform_down();
            generate_new_square();
        }
        Input::SetKey(Key::DOWN, false);
    }

    change();

}
#endif