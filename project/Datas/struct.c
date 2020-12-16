#include "../stdafx.h"

int makeTextBlock(TextBlock** tb,char* ptext,int posx,int posy,int color,int isVisible,int maxUpdateScale,int (*callbackfunc)(struct textblock*)){
        *tb = (TextBlock*)malloc(sizeof(TextBlock));
        if(*tb==NULL)return 0;

        (*tb)->posx=posx;
        (*tb)->posy=posy;
        if(ptext==NULL){
                (*tb)->textlen = 0;
                strcpy((*tb)->text,"");
                strcpy((*tb)->emptytext,"");
        }
        else{
                (*tb)->textlen = strlen(ptext);
                strcpy((*tb)->text,ptext);
                for(int i = 0;i<(*tb)->textlen;++i)
                        (*tb)->emptytext[i]=' ';
                (*tb)->emptytext[(*tb)->textlen]='\0'; 
        }

        (*tb)->color=color;
        (*tb)->dispire = 0;
        (*tb)->isVisible = isVisible;
        (*tb)->maxUpdateScale = maxUpdateScale;
        (*tb)->currentUpdateScale = maxUpdateScale;
        (*tb)->callbackFunc = callbackfunc;
        return 1;
}

int setPos(TextBlock** tb,int posx,int posy){
        if(*tb==NULL)return 0;
        (*tb)->posx = posx;
        (*tb)->posy = posy;
        return 1;
}

int setColor(TextBlock** tb,int color){
        if(*tb==NULL)return 0;
        (*tb)->color = color;
        return 1;
}

int setText(TextBlock** tb,char* ptext){
        if(*tb==NULL)return 0;
        if(ptext==NULL){
                (*tb)->textlen = 0;
                strcpy((*tb)->text,"");
                strcpy((*tb)->emptytext,"");
        }
        else{
                (*tb)->textlen = strlen(ptext);
                strcpy((*tb)->text,ptext);
                for(int i = 0;i<(*tb)->textlen;++i)
                        (*tb)->emptytext[i]=' ';
                (*tb)->emptytext[(*tb)->textlen]='\0'; 
        }
        return 1;
}

int addChar(TextBlock** tb,char ch){
        if(*tb==NULL)return 0;
        (*tb)->text[(*tb)->textlen]=ch;
        (*tb)->emptytext[(*tb)->textlen]=' ';
        (*tb)->text[++((*tb)->textlen)]='\0';
        (*tb)->emptytext[((*tb)->textlen)]='\0';
        return 1;
}

int delChar(TextBlock** tb){
        if(*tb==NULL)return 0;
        if((*tb)->textlen == 0) return 0;
        (*tb)->text[--((*tb)->textlen)]='\0';
        (*tb)->emptytext[((*tb)->textlen)]='\0';
        return 1;
}

int updateTextBlock(TextBlock** tb){
        if(*tb==NULL)return 0;
        if((*tb)->maxUpdateScale!=-1){
                (*tb)->currentUpdateScale--;
                if((*tb)->currentUpdateScale==0){
                        if((*tb)->callbackFunc!=NULL)(*tb)->callbackFunc(*tb);
                        (*tb)->currentUpdateScale = (*tb)->maxUpdateScale;
                }
        }
}