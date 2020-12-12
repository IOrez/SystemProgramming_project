#include "../../stdafx.h"

extern SceneManager* g_sceneManager;
extern WindowManager* g_windowManager;

int makeSaveScene(SaveScene** sas){
    (*sas) = (SaveScene*)malloc(sizeof(SaveScene));
    if((*sas)==NULL)return 0;
    return 1;

}
int initSaveScene(SaveScene** sas){

}
int releaseSaveScene(SaveScene** sas){
    
}
int updateSaveScene(SaveScene** sas){
    if(*sas==NULL)return 0;
    delTextBlockSaveScene(sas);
    for(int i =0;i<(*sas)->TB_cnt;++i){
        eraseTextBlock((*sas)->TB_Array[i]);
        updateTextBlock(&((*sas)->TB_Array[i]));
    }
}
int renderSaveScene(SaveScene** sas){
    if(*sas==NULL)return 0;
    if(g_sceneManager->e_currentScene==SAVE_SCENE){
        for(int i =0;i<(*sas)->TB_cnt;++i){
            printTextBlock((*sas)->TB_Array[i]);
        }
    }
    return 1;
}

int addTextBlockSaveScene(SaveScene** sas,TextBlock* tb){

}
int delTextBlockSaveScene(SaveScene** sas){
    if(*sas==NULL)return 0;
    int dispireCnt = 0;
    for(int i =0;i<(*sas)->TB_cnt;++i){
        if((*sas)->TB_Array[i]->dispire==1){
            dispireCnt++;
            eraseTextBlock((*sas)->TB_Array[i]);
            free((*sas)->TB_Array[i]);
            continue;
        }
        (*sas)->TB_Array[i-dispireCnt] = (*sas)->TB_Array[i];
    }
    for(int i =(*sas)->TB_cnt-dispireCnt;i<(*sas)->TB_cnt;++i){
        (*sas)->TB_Array[i]=NULL;
    }
    (*sas)->TB_cnt-=dispireCnt;
    return 1;
}
