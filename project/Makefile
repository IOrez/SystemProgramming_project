CC = gcc
CFLAGS = -c -g
LDFLAGS = -lncurses
OBJECTS = main.o sceneManager.o keyboardManager.o windowManager.o struct.o util.o mainScene.o gameScene.o scoreScene.o saveScene.o



main : $(OBJECTS)
	$(CC) -o ./main $(OBJECTS) $(LDFLAGS) 

main.o : stdafx.h main.c
	$(CC) $(CFLAGS) main.c 

sceneManager.o : stdafx.h ./Managers/sceneManager.c
	$(CC) $(CFLAGS) ./Managers/sceneManager.c

keyboardManager.o : stdafx.h ./Managers/keyboardManager.c
	$(CC) $(CFLAGS) ./Managers/keyboardManager.c

windowManager.o : stdafx.h ./Managers/windowManager.c
	$(CC) $(CFLAGS) ./Managers/windowManager.c

struct.o : stdafx.h ./Datas/struct.c
	$(CC) $(CFLAGS) ./Datas/struct.c

util.o : stdafx.h ./Util/util.c
	$(CC) $(CFLAGS) ./Util/util.c

mainScene.o : stdafx.h ./Scenes/MainScene/mainScene.c
	$(CC) $(CFLAGS) ./Scenes/MainScene/mainScene.c

gameScene.o : stdafx.h ./Scenes/GameScene/gameScene.c
	$(CC) $(CFLAGS) ./Scenes/GameScene/gameScene.c

scoreScene.o : stdafx.h ./Scenes/ScoreScene/scoreScene.c
	$(CC) $(CFLAGS) ./Scenes/ScoreScene/scoreScene.c

saveScene.o : stdafx.h ./Scenes/SaveScene/saveScene.c
	$(CC) $(CFLAGS) ./Scenes/SaveScene/saveScene.c