#pragma once

#include "../../../define.h"

class Building {
public:
    Building(uint type);

    ~Building() {};

    virtual void OnOpen()  {};

    virtual void Tick(float delta) {};

    virtual void Draw(Vector2 pos) {};

    vec2int pos;

private:

    uint type;
};