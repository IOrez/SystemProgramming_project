#include "../../stdafx.h"

extern SceneManager* g_sceneManager;
extern WindowManager* g_windowManager;

int makeMainScene(MainScene** ms){
    (*ms) = (MainScene*)malloc(sizeof(MainScene));
    if((*ms)==NULL)return 0;
    
    return 1;
}
int initMainScene(MainScene** ms){
    if(*ms==NULL)return 0;

    (*ms)->TB_cnt=0;
    
	tcgetattr( 0, &((*ms)->original_mode));		

    noecho();
    crmode();


    makeTextBlock(&((*ms)->MenuText[0]),"START GAME",60,15,COLOR_YELLOW,1,-1,NULL);
    makeTextBlock(&((*ms)->MenuText[1]),"SCORE",60,18,COLOR_RED,1,-1,NULL);
    makeTextBlock(&((*ms)->MenuText[2]),"EXIT",60,21,COLOR_GREEN,1,-1,NULL);
    makeTextBlock(&((*ms)->ArrowText),"!",58,15,COLOR_WHITE,1,-1,NULL);


    makeTextBlock(&((*ms)->TitleText[0]),"RRRRRRRRRRRR               AAAAA              IIIIIIIII        NNNN      NNNN",1,2,COLOR_CYAN,1,-1,NULL);
    makeTextBlock(&((*ms)->TitleText[1]),"RRRR     RRRR             AAAAAAA                III           NNNNNN    NNNN",1,3,COLOR_CYAN,1,-1,NULL);
    makeTextBlock(&((*ms)->TitleText[3]),"RRRR      RRRR           AAA   AAA               III           NNNN NNN  NNNN",1,4,COLOR_CYAN,1,-1,NULL);
    makeTextBlock(&((*ms)->TitleText[4]),"RRRRRRRRRRR             AAA     AAA              III           NNNN   NN NNNN",1,5,COLOR_CYAN,1,-1,NULL);
    makeTextBlock(&((*ms)->TitleText[5]),"RRRR     RRR           AAAAAAAAAAAAA             III           NNNN    NMNNNN",1,6,COLOR_CYAN,1,-1,NULL);
    makeTextBlock(&((*ms)->TitleText[6]),"RRRR      RRR         AAA         AAA         IIIIIIIII        NNNN      NNNN",1,7,COLOR_CYAN,1,-1,NULL);
    return 1;
}
int releaseMainScene(MainScene** ms){

    echo();
    tcsetattr( 0, TCSANOW, &((*ms)->original_mode));

    for(int i =0;i<(*ms)->TB_cnt;++i){
        if((*ms)->TB_Array[i]!=NULL){
            free((*ms)->TB_Array[i]);
            (*ms)->TB_Array[i]=NULL;
        }
    }

    for(int i =0;i<7;++i){
        if((*ms)->TitleText[i]!=NULL){
            free((*ms)->TitleText[i]);
            (*ms)->TitleText[i]=NULL;
        }
    }

    for(int i =0;i<3;++i){
        if((*ms)->MenuText[i]!=NULL){
            free((*ms)->MenuText[i]);
            (*ms)->MenuText[i]=NULL;
        }
    }

    free((*ms)->ArrowText);
    (*ms)->ArrowText=NULL;
    return 1;
}

int updateMainScene(MainScene** ms){
    if(*ms==NULL)return 0;
    delTextBlockMainScene(ms);

    TextBlock* tb;
    while((*ms)->TB_cnt<30){     
        makeTextBlock(&tb,"@",rand()%80,0,COLOR_BLUE,1,rand()%5000+2000,moveDown);
        addTextBlockMainScene(ms,tb);
    }

    int c = getch();
    for(int i =0;i<(*ms)->TB_cnt;++i){
        eraseTextBlock((*ms)->TB_Array[i]);
        updateTextBlock(&((*ms)->TB_Array[i]));
    }
    if(c!=EOF){
        if(c=='w'){
            if(--((*ms)->select)<0){
                (*ms)->select+=3;
            }
            eraseTextBlock((*ms)->ArrowText);
            setPos(&((*ms)->ArrowText),58,15+(*ms)->select*3);
        }
        else if(c=='s'){
            (*ms)->select= ((*ms)->select+1)%3;
            eraseTextBlock((*ms)->ArrowText);
            setPos(&((*ms)->ArrowText),58,15+(*ms)->select*3);
        }
        else if(c=='\n'){
            eraseTextBlock((*ms)->ArrowText);
            releaseMainScene(ms);
            switch((*ms)->select){
                case 0:
                    initGameScene(&(g_sceneManager->o_gameScene));
                    clear();
                    g_sceneManager->e_currentScene = GAME_SCENE;break;
                case 1:
                    initScoreScene(&(g_sceneManager->o_scoreScene));
                    clear();
                    g_sceneManager->e_currentScene = SCORE_SCENE;break;
                case 2:
                    g_sceneManager->e_currentScene= TERMINATE;break;
            }
        }
    }
    return 1;
}

int renderMainScene(MainScene** ms){
    if(*ms==NULL)return 0;
    if(g_sceneManager->e_currentScene==MAIN_SCENE){
        for(int i =0;i<(*ms)->TB_cnt;++i){
            printTextBlock((*ms)->TB_Array[i]);
        }
        printTextBlock((*ms)->ArrowText);
        for(int i =0;i<3;++i){
            printTextBlock((*ms)->MenuText[i]);
        }
        for(int i =0;i<7;++i){
            printTextBlock((*ms)->TitleText[i]);
        }
    }
    return 1;
}

int addTextBlockMainScene(MainScene** ms,TextBlock* tb){
    if(*ms==NULL)return 0;
    if((*ms)->TB_cnt==MAX_TEXTBLOCK_SIZE)return 0;
    (*ms)->TB_Array[((*ms)->TB_cnt)++] = tb;
    return 1;
}
int delTextBlockMainScene(MainScene** ms){
    if(*ms==NULL)return 0;
    int dispireCnt = 0;
    for(int i =0;i<(*ms)->TB_cnt;++i){
        if((*ms)->TB_Array[i]->dispire==1){
            dispireCnt++;
            eraseTextBlock((*ms)->TB_Array[i]);
            free((*ms)->TB_Array[i]);
            continue;
        }
        (*ms)->TB_Array[i-dispireCnt] = (*ms)->TB_Array[i];
    }
    for(int i =(*ms)->TB_cnt-dispireCnt;i<(*ms)->TB_cnt;++i){
        (*ms)->TB_Array[i]=NULL;
    }
    (*ms)->TB_cnt-=dispireCnt;
    return 1;
}

int moveDown(TextBlock* tb){
    if(tb==NULL)return 0;
    tb->posy+=1 ;
    if(tb->posy>LINES-1){
         tb->posy =0;
         tb->dispire = 1;
         tb->maxUpdateScale = rand()%10000+2000;
         tb->currentUpdateScale = tb->maxUpdateScale;
    }
}
