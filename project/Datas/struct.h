typedef struct textblock{
        int posx,posy;
        int textlen;
        int color;

        int dispire;
        int isVisible;
        char text[MAX_TEXT_SIZE];
        char emptytext[MAX_TEXT_SIZE];

        int maxUpdateScale;
        int currentUpdateScale;

        int (*callbackFunc)(struct textblock* me);
}TextBlock;



int makeTextBlock(TextBlock** tb,char* ptext,int posx,int posy,int color,int isVisible,int maxUpdateScale,int (*callbackfunc)(struct textblock*));
int setPos(TextBlock** tb,int posx,int posy);
int setColor(TextBlock** tb,int color);
int setText(TextBlock** tb,char* ptext);
int addChar(TextBlock** tb,char ch);
int delChar(TextBlock** tb);

int updateTextBlock(TextBlock** tb);

typedef struct{
    int score;
    char name[30];
}ranking;
