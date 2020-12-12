
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>	
#include <curses.h>
#include <termio.h>
#include <fcntl.h>
#include <time.h>
#include <sys/time.h>


/*custom define*/



#define MAX_TEXT_SIZE               1024
#define MAX_TEXTBLOCK_SIZE          1024
#define MAX_KEYBOARD_QUEUE_SIZE     256


#define UP      72
#define LEFT    75
#define RIGHT   77
#define DOWN    78

/*custom header*/
#include "Datas/struct.h"

#include "Util/util.h"

#include "Scenes/MainScene/mainScene.h"
#include "Scenes/GameScene/gameScene.h"
#include "Scenes/ScoreScene/scoreScene.h"
#include "Scenes/SaveScene/saveScene.h"


#include "Managers/sceneManager.h"
#include "Managers/keyboardManager.h"
#include "Managers/windowManager.h"