#pragma once
#include <vector>
#include <SDL.h>
#include <unordered_map>
#include <string>
#include <vector>

class Actor;

class Game
{
public:
	Game();

	// 게임 초기화
	bool Initialize();
    // 게임 루프
    void RunLoop();
    // 게임 종료
    void Shutdown();

    void AddActor(Actor* actor);
    void RemoveActor(Actor* actor);

    void LoadData();

    SDL_Texture* LoadTexture(const char* fileName);
    SDL_Texture* GetTexture(const std::string& fileName);

private:
    // 게임 루프를 위한 헬퍼 함수
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();


    std::vector<Actor*> mActors;
    std::vector<Actor*> mPendingActors;

    std::unordered_map<std::string, SDL_Texture*> mTextures;

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    Uint32 mTicksCount;

    bool mIsRunning;
    bool mUpdatingActors;
};