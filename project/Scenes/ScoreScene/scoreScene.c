#include "../../stdafx.h"

extern SceneManager* g_sceneManager;
extern WindowManager* g_windowManager;

int makeScoreScene(ScoreScene** ss){
    (*ss) = (ScoreScene*)malloc(sizeof(ScoreScene));
    if((*ss)==NULL)return 0;
    return 1;
}
int initScoreScene(ScoreScene** ss){
    if(*ss==NULL)return 0;

    for(int i =0;i<(*ss)->TB_cnt;++i)
        free((*ss)->TB_Array[i]);

    (*ss)->TB_cnt=0;    
    return 1;
}
int releaseScoreScene(ScoreScene** ss){

}

int updateScoreScene(ScoreScene** ss){
    if(*ss==NULL)return 0;
    delTextBlockScoreScene(ss);
    for(int i =0;i<(*ss)->TB_cnt;++i){
        eraseTextBlock((*ss)->TB_Array[i]);
        updateTextBlock(&((*ss)->TB_Array[i]));
    }
}

int renderScoreScene(ScoreScene** ss){
    if(*ss==NULL)return 0;
    if(g_sceneManager->e_currentScene==SCORE_SCENE){
        for(int i =0;i<(*ss)->TB_cnt;++i){
            printTextBlock((*ss)->TB_Array[i]);
        }
    }
    return 1;
}

int addTextBlockScoreScene(ScoreScene** ss,TextBlock* tb){
    if(*ss==NULL)return 0;
    if((*ss)->TB_cnt==MAX_TEXTBLOCK_SIZE)return 0;
    (*ss)->TB_Array[++(*ss)->TB_cnt] = tb;
    return 1;
}
int delTextBlockScoreScene(ScoreScene** ss){
    if(*ss==NULL)return 0;
    int dispireCnt = 0;
    for(int i =0;i<(*ss)->TB_cnt;++i){
        if((*ss)->TB_Array[i]->dispire==1){
            dispireCnt++;
            eraseTextBlock((*ss)->TB_Array[i]);
            free((*ss)->TB_Array[i]);
            continue;
        }
        (*ss)->TB_Array[i-dispireCnt] = (*ss)->TB_Array[i];
    }
    for(int i =(*ss)->TB_cnt-dispireCnt;i<(*ss)->TB_cnt;++i){
        (*ss)->TB_Array[i]=NULL;
    }
    (*ss)->TB_cnt-=dispireCnt;
    return 1;
}