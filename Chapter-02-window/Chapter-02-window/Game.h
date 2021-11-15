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

	// ���� �ʱ�ȭ
	bool Initialize();
    // ���� ����
    void RunLoop();
    // ���� ����
    void Shutdown();

    void AddActor(Actor* actor);
    void RemoveActor(Actor* actor);

    void LoadData();

    SDL_Texture* LoadTexture(const char* fileName);
    SDL_Texture* GetTexture(const std::string& fileName);

private:
    // ���� ������ ���� ���� �Լ�
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