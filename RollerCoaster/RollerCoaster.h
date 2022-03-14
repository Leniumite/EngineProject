#pragma once

#include "resource.h"

class App;

void initD3D(HWND hWnd);
void render_frame();
void cleanD3D(void);

void init_graphics(void);
void init_light(void);


App* GetApp();
