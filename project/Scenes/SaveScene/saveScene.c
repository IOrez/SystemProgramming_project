#include "../../stdafx.h"

extern SceneManager* g_sceneManager;
extern WindowManager* g_windowManager;

int makeSaveScene(SaveScene** sas){
    (*sas) = (SaveScene*)malloc(sizeof(SaveScene));
    if((*sas)==NULL)return 0;
    return 1;

}
int initSaveScene(SaveScene** sas){

     TextBlock* tb;

    FILE *score_fp;
    int temp_score, i, j, min_index;
    char temp_name[30];
    char cur_name[30];
    ranking temp;
    
    if(score_fp = fopen("score.txt", "r")){
        for(i=0; i<3; i++){
            if(EOF != fscanf(score_fp, "%d", &temp_score))
                (*sas)->ranking[i].score = temp_score;
            if(EOF != fscanf(score_fp, "%s", temp_name))
                strcpy((*sas)->ranking[i].name, temp_name);
        }
    }else{ // 완전 첫 실행이라 파일 없을 때 임의값 삽입
        for(i=0; i<3; i++){
            (*sas)->ranking[i].score = 0;
            strcpy((*sas)->ranking[i].name, "empty");
        }
    }
    fclose(score_fp);
    
    if((*sas)->ranking[2].score > g_sceneManager->o_gameScene->score){ // 순위권 밖
        g_sceneManager->e_currentScene = MAIN_SCENE;
        initMainScene(&(g_sceneManager->o_mainScene));
        return;
    }

    noecho();
    crmode();

    makeTextBlock(&((*sas)->scoreText),"-------- << GAME OVER >> -------- ",20,3,COLOR_YELLOW,1,-1,NULL);
    addTextBlockSaveScene(sas,(*sas)->scoreText);

    makeTextBlock(&((*sas)->scoreText),"Id : ",25,6,COLOR_YELLOW,1,-1,NULL);
    addTextBlockSaveScene(sas,(*sas)->scoreText);

    makeTextBlock(&((*sas)->Id),"",30,6,COLOR_YELLOW,1,-1,NULL);
    addTextBlockSaveScene(sas,(*sas)->Id);


    makeTextBlock(&((*sas)->scoreText),"Score : ",25,9,COLOR_YELLOW,1,-1,NULL);
    addTextBlockSaveScene(sas,(*sas)->scoreText);
    makeTextBlock(&((*sas)->scoreText),"--------------------------------- ",20,12,COLOR_YELLOW,1,-1,NULL);
    addTextBlockSaveScene(sas,(*sas)->scoreText);



}
int releaseSaveScene(SaveScene** sas){




}
int updateSaveScene(SaveScene** sas){

    if(*sas==NULL)return 0;

    int ch = getch();

    delTextBlockSaveScene(sas);
    for(int i =0;i<(*sas)->TB_cnt;++i){
        eraseTextBlock((*sas)->TB_Array[i]);
        updateTextBlock(&((*sas)->TB_Array[i]));

    }


    if(ch != EOF){
        addChar(&((*sas)->Id), ch);
        int temp_score, i, j, min_index;
        char temp_name[30];
        char cur_name[30] = "";
        FILE *score_fp;
        ranking temp;
        
        strcpy(cur_name, "test name ");

        if(ch=='\n'){
            (*sas)->ranking[2].score = g_sceneManager->o_gameScene->score;
            strcpy((*sas)->ranking[2].name, cur_name);

            for (i = 0; i < 2; i++) {
                min_index = i;
                for (j = i + 1; j < 3; j++)
                    if ((*sas)->ranking[j].score > (*sas)->ranking[min_index].score)
                        min_index = j;
                temp = (*sas)->ranking[i];
                (*sas)->ranking[i] = (*sas)->ranking[min_index];
                (*sas)->ranking[min_index] = temp;
            }

            score_fp = fopen("score.txt", "w");
            for(i=0; i<3; i++){
                fprintf(score_fp, "%d ", (*sas)->ranking[i].score);
                fprintf(score_fp, "%s ", (*sas)->ranking[i].name);
            }

            g_sceneManager->e_currentScene = MAIN_SCENE;
            initMainScene(&(g_sceneManager->o_mainScene));
            releaseSaveScene(&(g_sceneManager->o_saveScene));
            return;
        }
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

    if(*sas==NULL)return 0;
    if((*sas)->TB_cnt==MAX_TEXTBLOCK_SIZE)return 0;
    (*sas)->TB_Array[((*sas)->TB_cnt)++] = tb;
    return 1;

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