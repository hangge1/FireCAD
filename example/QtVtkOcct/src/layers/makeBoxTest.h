
#pragma once

#include "layers/occLayer.h"

class makeBoxTest : public occLayer
{
public:
    using occLayer::occLayer;

protected:
    void init() override;
    void makeBox();
};
