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
    (*gs)->TB_cnt=0;
    noecho();
    crmode();
    
    FILE* fp = fopen("Scenes/GameScene/words.txt","r");
    int i = 0;

    (*gs)->TB_cnt=0;
    (*gs)->score = 0;
    (*gs)->frameCount = 100000;
    while(fgets((*gs)->words[i],MAX_TEXT_SIZE,fp)!=NULL){
        (*gs)->words[i][strlen((*gs)->words[i])-1]='\0';
        i++;
    }
    makeTextBlock(&((*gs)->ansTB),"",40,10,COLOR_WHITE,1,-1,NULL);

    makeTextBlock(&(*gs)->scoreTB,"SCORE: 0",60,1,COLOR_MAGENTA,1,-1,NULL);
    fclose(fp);
    return 1;
}
int releaseGameScene(GameScene** gs){
    echo();
    tcsetattr( 0, TCSANOW, &((*gs)->original_mode));

    for(int i =0;i<(*gs)->TB_cnt;++i){
        if((*gs)->TB_Array[i]!=NULL){
            free((*gs)->TB_Array[i]);
            (*gs)->TB_Array[i]=NULL;
        }
    }
    return 1;
}

int updateGameScene(GameScene** gs){
    if(*gs==NULL)return 0;
    int ch = getch();
    delTextBlockGameScene(gs);
    for(int i =0;i<(*gs)->TB_cnt;++i){
        eraseTextBlock((*gs)->TB_Array[i]);
        updateTextBlock(&((*gs)->TB_Array[i]));
        if(g_sceneManager->e_currentScene!=GAME_SCENE){
            echo();
            releaseGameScene(gs);
            initSaveScene(&(g_sceneManager->o_saveScene));
            clear();
            return 1;
        }
    }

    TextBlock* tb;
    if((*gs)->frameCount==0){
        int urate = 5000-((*gs)->score);
        if(urate<10)urate=10;
        makeTextBlock(&tb,(*gs)->words[rand()%6],rand()%60+10,0,rand()%6,0,rand()%urate+2000,textItemMoveDown);
        addTextBlockGameScene(gs,tb);
        (*gs)->frameCount=800000-10000*(*gs)->score;
        if((*gs)->frameCount<100)(*gs)->frameCount=100;
    }
    (*gs)->frameCount--;
    
    if(ch!=EOF){
        if(ch==' '){
            int a = 1;
            eraseTextBlock((*gs)->ansTB);
            delChar(&((*gs)->ansTB));
         }
        else if(ch=='\n'){
            for(int i = 0;i<(*gs)->TB_cnt;++i){
                if(strcmp((*gs)->TB_Array[i]->text,(*gs)->ansTB->text)==0){
                    (*gs)->TB_Array[i]->dispire=1;
                    (*gs)->score+=10;
                    char buf[MAX_TEXT_SIZE] = "";
                    sprintf(buf,"SCORE: %d",(*gs)->score);
                    eraseTextBlock((*gs)->scoreTB);
                    setText(&((*gs)->scoreTB),buf);
                    eraseTextBlock((*gs)->ansTB);
                    setText(&((*gs)->ansTB),NULL);
                }
            }
        }
        else {
            if(isalnum(ch))
                addChar(&((*gs)->ansTB),ch);
        }
    }
    updateTextBlock(&((*gs)->ansTB));
    updateTextBlock(&((*gs)->scoreTB));
}

int renderGameScene(GameScene** gs){
    if(*gs==NULL)return 0;
    if(g_sceneManager->e_currentScene==GAME_SCENE){
        for(int i =0;i<(*gs)->TB_cnt;++i){
            printTextBlock((*gs)->TB_Array[i]);
        }
    }
    printTextBlock((*gs)->ansTB);
    printTextBlock((*gs)->scoreTB);
    return 1;
}

int addTextBlockGameScene(GameScene** gs,TextBlock* tb){
    if(*gs==NULL)return 0;
    if((*gs)->TB_cnt==MAX_TEXTBLOCK_SIZE)return 0;
    (*gs)->TB_Array[(*gs)->TB_cnt++] = tb;
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

int textItemMoveDown(TextBlock* tb){
    if(tb==NULL)return 0;
    tb->posy+=1 ;
    if(tb->posy>LINES-1){
        if(tb->isVisible==1){
            g_sceneManager->e_currentScene = SAVE_SCENE;
            return 1;
        }
         tb->posy =0;
         tb->isVisible=1;
         tb->maxUpdateScale = rand()%3000+100000;
         tb->currentUpdateScale = tb->maxUpdateScale;
    }
}