typedef struct gameScene{

    TextBlock* TB_Array[MAX_TEXTBLOCK_SIZE];
    int TB_cnt;
    char words[6][MAX_TEXT_SIZE];

    TextBlock* Line;
    TextBlock* Caution;
    TextBlock* tbword[6];
    TextBlock* ansblock[4];
    TextBlock* ansTB;
    TextBlock* scoreTB;
    int termflags;
    int score;
    struct termios	original_mode;
    int frameCount;
}GameScene;

int makeGameScene(GameScene** gs);
int initGameScene(GameScene** gs);
int releaseGameScene(GameScene** gs);
int updateGameScene(GameScene** gs);
int renderGameScene(GameScene** gs);

int addTextBlockGameScene(GameScene** gs,TextBlock* tb);
int delTextBlockGameScene(GameScene** gs);

int textItemMoveDown(TextBlock* tb);