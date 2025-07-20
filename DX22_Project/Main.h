#ifndef __MAIN_H__
#define __MAIN_H__

#include <Windows.h>
#include <string>
#include "Scene.h"

HRESULT Init(HWND hWnd, UINT width, UINT height);
void Uninit();
void Update();
void Draw();

void AppEnd();

CScene* GetScene();
void ChangeScene(CScene* inScene);

#endif // __MAIN_H__
