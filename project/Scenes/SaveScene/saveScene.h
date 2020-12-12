typedef struct saveScene{

    TextBlock* TB_Array[MAX_TEXTBLOCK_SIZE];
    int TB_cnt;
    int select;

    int termflags;
    struct termios	original_mode;
}SaveScene;


int makeSaveScene(SaveScene** sas);
int initSaveScene(SaveScene** sas);
int releaseSaveScene(SaveScene** sas);
int updateSaveScene(SaveScene** sas);
int renderSaveScene(SaveScene** sas);

int addTextBlockSaveScene(SaveScene** sas,TextBlock* tb);
int delTextBlockSaveScene(SaveScene** sas);


