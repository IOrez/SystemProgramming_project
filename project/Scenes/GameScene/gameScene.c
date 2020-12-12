#include "../../stdafx.h"

extern SceneManager* g_sceneManager;
extern WindowManager* g_windowManager;

int makeGameScene(GameScene** gs){
    (*gs) = (GameScene*)malloc(sizeof(GameScene));
    if((*gs)==NULL)return 0;
    return 1;
}
int initGameScene(GameScene** gs){
    if(*gs==NULL)return 0;

    for(int i =0;i<(*gs)->TB_cnt;++i)
        free((*gs)->TB_Array[i]);
        
    (*gs)->TB_cnt=0;  
    return 1;
}
int releaseGameScene(GameScene** gs){

    return 1;
}

int updateGameScene(GameScene** gs){
    if(*gs==NULL)return 0;
    delTextBlockGameScene(gs);
    for(int i =0;i<(*gs)->TB_cnt;++i){
        eraseTextBlock((*gs)->TB_Array[i]);
        updateTextBlock(&((*gs)->TB_Array[i]));
    }
}

int renderGameScene(GameScene** gs){
    if(*gs==NULL)return 0;
    if(g_sceneManager->e_currentScene==GAME_SCENE){
        for(int i =0;i<(*gs)->TB_cnt;++i){
            printTextBlock((*gs)->TB_Array[i]);
        }
    }
    return 1;
}

int addTextBlockGameScene(GameScene** gs,TextBlock* tb){
    if(*gs==NULL)return 0;
    if((*gs)->TB_cnt==MAX_TEXTBLOCK_SIZE)return 0;
    (*gs)->TB_Array[++(*gs)->TB_cnt] = tb;
    return 1;
}
int delTextBlockGameScene(GameScene** gs){
    if(*gs==NULL)return 0;
    int dispireCnt = 0;
    for(int i =0;i<(*gs)->TB_cnt;++i){
        if((*gs)->TB_Array[i]->dispire==1){
            dispireCnt++;
            eraseTextBlock((*gs)->TB_Array[i]);
            free((*gs)->TB_Array[i]);
            continue;
        }
        (*gs)->TB_Array[i-dispireCnt] = (*gs)->TB_Array[i];
    }
    for(int i =(*gs)->TB_cnt-dispireCnt;i<(*gs)->TB_cnt;++i){
        (*gs)->TB_Array[i]=NULL;
    }
    (*gs)->TB_cnt-=dispireCnt;
    return 1;
}