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

    (*ss)->TB_cnt=0;    

    makeTextBlock(&((*ss)->scoreTitleText[0]),"OOOOO    O    O   O  O   O  OOOOO  O   O   OOO   ",15,2,COLOR_CYAN,1,-1,NULL);
    makeTextBlock(&((*ss)->scoreTitleText[1]),"O  O    O O   OO  O  O  O     O    OO  O  O      ",15,3,COLOR_CYAN,1,-1,NULL);
    makeTextBlock(&((*ss)->scoreTitleText[2]),"OOOO   OOOOO  O O O  OOO      O    O O O  O OOO  ",15,4,COLOR_CYAN,1,-1,NULL);
    makeTextBlock(&((*ss)->scoreTitleText[3]),"O  O   O   O  O  OO  O  O     O    O  OO  O   O  ",15,5,COLOR_CYAN,1,-1,NULL);
    makeTextBlock(&((*ss)->scoreTitleText[4]),"O   O  O   O  O   O  O   O  OOOOO  O   O   OOO   ",15,6,COLOR_CYAN,1,-1,NULL);

    makeTextBlock(&((*ss)->scoreRankingText[0]),"-----------------------------------------------",15,10,COLOR_CYAN,1,-1,NULL);
    makeTextBlock(&((*ss)->scoreRankingText[1]),"-                                             -",15,11,COLOR_CYAN,1,-1,NULL);
    makeTextBlock(&((*ss)->scoreRankingText[2]),"",15,12,COLOR_CYAN,1,-1,NULL);
    makeTextBlock(&((*ss)->scoreRankingText[3]),"-                                             -",15,13,COLOR_CYAN,1,-1,NULL);
    makeTextBlock(&((*ss)->scoreRankingText[4]),"",15,14,COLOR_CYAN,1,-1,NULL);
    makeTextBlock(&((*ss)->scoreRankingText[5]),"-                                             -",15,15,COLOR_CYAN,1,-1,NULL);
    makeTextBlock(&((*ss)->scoreRankingText[6]),"",15,16,COLOR_CYAN,1,-1,NULL);
    makeTextBlock(&((*ss)->scoreRankingText[7]),"-                                             -",15,17,COLOR_CYAN,1,-1,NULL);
    makeTextBlock(&((*ss)->scoreRankingText[8]),"-----------------------------------------------",15,18,COLOR_CYAN,1,-1,NULL);

    int i, temp_score;
    char temp_name[30];
    char buf[MAX_TEXT_SIZE]="";
    FILE *score_fp;

    score_fp = fopen("score.txt", "r");
    for(i=0; i<3; i++){
        fscanf(score_fp, "%d", &temp_score);
        fscanf(score_fp, "%s", temp_name);
        switch(i){
            case 0:
                sprintf(buf,"          [Gold] : %s - <%d>",temp_name, temp_score);
                makeTextBlock(&((*ss)->scoreRankingText[2]),buf,15,12,COLOR_WHITE,1,-1,NULL);
                break;
            case 1:
                sprintf(buf,"          [Silver] : %s - <%d>",temp_name, temp_score);
                makeTextBlock(&((*ss)->scoreRankingText[4]),buf,15,14,COLOR_WHITE,1,-1,NULL);            
                break;
            case 2:
                sprintf(buf,"          [Copper] : %s - <%d>",temp_name, temp_score);
                makeTextBlock(&((*ss)->scoreRankingText[6]),buf,15,16,COLOR_WHITE,1,-1,NULL);            
                break;
        }
    }


    
    return 1;
}
int releaseScoreScene(ScoreScene** ss){
    echo();
    tcsetattr( 0, TCSANOW, &((*ss)->original_mode));

    for(int i =0;i<(*ss)->TB_cnt;++i){
        if((*ss)->TB_Array[i]!=NULL){
            free((*ss)->TB_Array[i]);
            (*ss)->TB_Array[i]=NULL;
        }
    }
}

int updateScoreScene(ScoreScene** ss){
    if(*ss==NULL)return 0;
    delTextBlockScoreScene(ss);
    for(int i =0;i<(*ss)->TB_cnt;++i){
        eraseTextBlock((*ss)->TB_Array[i]);
        updateTextBlock(&((*ss)->TB_Array[i]));
    }
    for(int i =0;i<5;++i){
        eraseTextBlock((*ss)->scoreTitleText[i]);
        updateTextBlock(&((*ss)->scoreTitleText[i]));
    }
    for(int i =0;i<9;++i){
        eraseTextBlock((*ss)->scoreRankingText[i]);
        updateTextBlock(&((*ss)->scoreRankingText[i]));
    }
}

int renderScoreScene(ScoreScene** ss){
    if(*ss==NULL)return 0;
    if(g_sceneManager->e_currentScene==SCORE_SCENE){
        for(int i =0;i<(*ss)->TB_cnt;++i){
            printTextBlock((*ss)->TB_Array[i]);
        }

        for(int i =0;i<5;++i){
            printTextBlock((*ss)->scoreTitleText[i]);
        }
        for(int i =0;i<9;++i){
            printTextBlock((*ss)->scoreRankingText[i]);
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