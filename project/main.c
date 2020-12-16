#include "stdafx.h"

SceneManager*      g_sceneManager;
KeyboardManager*   g_keyboardManager;
WindowManager*     g_windowManager;

int main()
{
    //FILE* fp = fopen("Scenes/GameScene/words.txt","r");
    makeWindowManager(&g_windowManager);
    makeSceneManager(&g_sceneManager);
    makeKeyboardManager(&g_keyboardManager);

    initWindowManager(&g_windowManager);
    initSceneManager(&g_sceneManager);
    initKeyboardManager(&g_keyboardManager);

    while(updateSceneManager(&g_sceneManager)){
        renderSceneManager(&g_sceneManager);
        refresh();
    }
    
    releaseKeyboardManager(&g_keyboardManager);
    releaseSceneManager(&g_sceneManager);
    releaseWindowManager(&g_windowManager);
}