
enum CURRNET_SCENE{
    MAIN_SCENE,GAME_SCENE,SCORE_SCENE,SAVE_SCENE,TERMINATE
};

typedef struct sceneManager{

    enum CURRNET_SCENE   e_currentScene;

    MainScene*   o_mainScene;
    GameScene*   o_gameScene;
    ScoreScene*  o_scoreScene;
    SaveScene*   o_saveScene;

}SceneManager;


int makeSceneManager(SceneManager** sm);
int initSceneManager(SceneManager** sm);
int releaseSceneManager(SceneManager** sm);
int updateSceneManager(SceneManager** sm);
int renderSceneManager(SceneManager** sm);
