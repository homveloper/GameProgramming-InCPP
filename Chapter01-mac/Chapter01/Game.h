//
//  Game.hpp
//  Chapter01
//
//  Created by 최범휘 on 2021/11/10.
//
#pragma once
#include <SDL.h>

struct Vector2D
{
    float x;
    float y;
};

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
    
private:
    // 게임 루프를 위한 헬퍼 함수
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    
    // SDL이 생성한 윈도우
    SDL_Window* mWindow;
    
    // SDL 렌더러
    SDL_Renderer* mRenderer;
    
    // 게임이 게속 실행되야 하는지 판단
    bool mIsRunning;
    
    //
    Uint32 mTicksCount;
    
    // 패들 위치, 공의 위치
    Vector2D mPaddlePos;
    Vector2D mBallPos;
    Vector2D mBallSpeed;
    
    // 패들 길이
    int paddleH;
    
    const int thickness;
    
    // 패들의 방향
    int mPaddleDir;
};
