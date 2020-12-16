#include "../stdafx.h"

int makeSceneManager(SceneManager** sm){
    if((*sm)!=NULL)free(*sm);
    (*sm) = (SceneManager*)malloc(sizeof(SceneManager));
    if(*sm==NULL)return 0;
    return 1;
}

int initSceneManager(SceneManager** sm){
    if((*sm)==NULL)return 0;
    makeMainScene(&((*sm)->o_mainScene));
    makeGameScene(&((*sm)->o_gameScene));
    makeScoreScene(&((*sm)->o_scoreScene));
    makeSaveScene(&((*sm)->o_saveScene));

    (*sm)->e_currentScene  = MAIN_SCENE;
    initMainScene(&((*sm)->o_mainScene));
    initSaveScene(&((*sm)->o_saveScene));
    initGameScene(&((*sm)->o_gameScene));
    initScoreScene(&((*sm)->o_scoreScene));
    return 1;
}

int releaseSceneManager(SceneManager** sm){
    if((*sm)!=NULL){
        releaseMainScene(&((*sm)->o_mainScene));
        releaseGameScene(&((*sm)->o_gameScene));
        releaseScoreScene(&((*sm)->o_scoreScene));
        releaseSaveScene(&((*sm)->o_saveScene));


        free((*sm)->o_mainScene);
        free((*sm)->o_gameScene);
        free((*sm)->o_scoreScene);
        free((*sm)->o_saveScene);

        free(*sm);
        *sm = NULL;
    }
    return 1;
}

int updateSceneManager(SceneManager** sm){
    if((*sm)==NULL)return 0;
    SceneManager* psm = *sm;
    switch(psm->e_currentScene){
        case MAIN_SCENE:
            updateMainScene(&(psm->o_mainScene));
            break;
        case GAME_SCENE:
            updateGameScene(&(psm->o_gameScene));
            break;
        case SCORE_SCENE:
            updateScoreScene(&(psm->o_scoreScene));
            break;
        case SAVE_SCENE:
            updateSaveScene(&(psm->o_saveScene));
            break;
        case TERMINATE:
            return 0;
            break;
    }
    return 1;
}
int renderSceneManager(SceneManager** sm){
    if((*sm)==NULL)return 0;
    SceneManager* psm = *sm;
    switch(psm->e_currentScene){
        case MAIN_SCENE:
            renderMainScene(&(psm->o_mainScene));
            break;
        case GAME_SCENE:
            renderGameScene(&(psm->o_gameScene));
            break;
        case SCORE_SCENE:
            renderScoreScene(&(psm->o_scoreScene));
            break;
        case SAVE_SCENE:
            renderSaveScene(&(psm->o_saveScene));
            break;
    }
}