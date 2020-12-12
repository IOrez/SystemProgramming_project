typedef struct gameScene{

    TextBlock* TB_Array[MAX_TEXTBLOCK_SIZE];
    int TB_cnt;

    int termflags;
    struct termios	original_mode;
}GameScene;

int makeGameScene(GameScene** gs);
int initGameScene(GameScene** gs);
int releaseGameScene(GameScene** gs);
int updateGameScene(GameScene** gs);
int renderGameScene(GameScene** gs);

int addTextBlockGameScene(GameScene** gs,TextBlock* tb);
int delTextBlockGameScene(GameScene** gs);