#pragma once

enum button_type {
    BUTTON_KEY_SPACE,
    BUTTON_KEY_ESCAPE,
    BUTTON_KEY_SHIFT,

    BUTTON_KEY_W,
    BUTTON_KEY_A,
    BUTTON_KEY_S,
    BUTTON_KEY_D,

    BUTTON_KEY_LEFT,
    BUTTON_KEY_RIGHT,
    BUTTON_KEY_UP,
    BUTTON_KEY_DOWN,

    BUTTON_MOUSE_LEFT,
    BUTTON_MOUSE_RIGHT,

    BUTTON_TYPE_MAX_COUNT
};

struct button_state {
    b8 Pressed;
    b8 Released;
    b8 Down;
};

struct program_input {
    button_state Buttons[BUTTON_TYPE_MAX_COUNT];
};

static inline void UpdateButton(button_type Type, program_input *Input, b8 IsUp) {
    Input->Buttons[Type].Pressed = !IsUp;
    Input->Buttons[Type].Down = !IsUp;
    Input->Buttons[Type].Released = IsUp;
}

static inline b32 ButtonPressed(program_input *Input, button_type Type) {
    return Input->Buttons[Type].Pressed;
}

static inline b32 ButtonDown(program_input *Input, button_type Type) {
    return Input->Buttons[Type].Down;
}

static inline b32 ButtonUp(program_input *Input, button_type Type) {
    return !Input->Buttons[Type].Down;
}

static inline b32 ButtonReleased(program_input *Input, button_type Type) {
    return Input->Buttons[Type].Released;
}
