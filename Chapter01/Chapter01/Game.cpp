//
//  Game.cpp
//  Chapter01
//
//  Created by 최범휘 on 2021/11/10.
//

#include "Game.h"
#include <math.h>

Game::Game():
    mWindow(nullptr),
    mRenderer(nullptr),
    mIsRunning(true),
    thickness(15),
    paddleH(100.0f),
    mTicksCount(0)
{

}

bool Game::Initialize() { 
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);

    
    if(sdlResult != 0){
        SDL_Log("Unable to initialize SDL : %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow("Game Programming in C++ Chapter 01",
                               100,
                               100,
                               1024,
                               768,
                               0);
    
    if (nullptr == mWindow)
    {
        SDL_Log("Failed to create window : %s", SDL_GetError());
        return false;
    }
    
    mRenderer = SDL_CreateRenderer(
                                   mWindow,
                                   -1,
                                   SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
                                   );
    
    if( nullptr == mRenderer)
    {
        return false;
    }
    
    
    mPaddlePos.x = 10.0f;
    mPaddlePos.y = 768.0f / 2.0f;
    
    mBallPos.x = 1024.0f / 2.0f;
    mBallPos.y = 768.0f / 2.0f;
    
    mBallSpeed.x = -200.0f;
    mBallSpeed.y = 235.0f;
    
    return true;
}

void Game::RunLoop(){
    while(mIsRunning){
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::GenerateOutput() {
    // 후면 버퍼를 비울 단색 지정
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
    // 후면 버퍼를 지움
    SDL_RenderClear(mRenderer);
    
    // 그리기 코드 작성
    
    // 흰색 벽 드로우
    SDL_SetRenderDrawColor(mRenderer, 255,255,255,255);
    
    SDL_Rect topWall{0,0,1024,thickness};
    SDL_RenderFillRect(mRenderer, &topWall);
    
    SDL_Rect rightWall{1024-thickness,0,thickness,768};
    SDL_RenderFillRect(mRenderer, &rightWall);
    
    SDL_Rect bottomWall{0,768-thickness,1024,thickness};
    SDL_RenderFillRect(mRenderer, &bottomWall);
    
    // 패들 드로우
    SDL_Rect paddle{
        static_cast<int>(mPaddlePos.x - thickness/2),
        static_cast<int>(mPaddlePos.y - paddleH/2),
        thickness,
        paddleH
    };
    SDL_RenderFillRect(mRenderer, &paddle);
    
    // 공 드로우
    SDL_Rect ball{
        static_cast<int>(mBallPos.x - thickness/2),
        static_cast<int>(mBallPos.y - thickness/2),
        thickness,
        thickness
    };
    SDL_RenderFillRect(mRenderer, &ball);
    
    // 전면 버퍼와 후면 버퍼를 교환
    SDL_RenderPresent(mRenderer);
}


void Game::UpdateGame() {
    // 마지막 프레임 이후로 16ms가 경과할때 까지 대기
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
    
    // 델타 타임 = 현재 프레임 틱 - 이전 프레임 틱
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    
    // 델타 타임 최대 시간 고정
    if(deltaTime > 0.05f){
        deltaTime = 0.05f;
    }
    
    // 다음 프레임을 위해 틱 갱신
    mTicksCount = SDL_GetTicks();
    
    // 게임 세계 갱신
    if(mPaddleDir != 0)
    {
        mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
        
        if(mPaddlePos.y < (paddleH/2.0f + thickness)){
            mPaddlePos.y =paddleH/2.0f + thickness;
        }else if(mPaddlePos.y > (768.0f - paddleH/2.0f - thickness))
        {
            mPaddlePos.y = 768.0f - paddleH/2.0f - thickness;
        }
    }
    
    mBallPos.x += mBallSpeed.x * deltaTime;
    mBallPos.y += mBallSpeed.y * deltaTime;
    
    if((mBallPos.y <= thickness && mBallSpeed.y < 0.0f) ||
       (mBallPos.y >= 768-thickness && mBallSpeed.y > 0.0f))
    {
        mBallSpeed.y *= -1;
    }
    
    if(mBallPos.x >= 1024-thickness && mBallSpeed.x > 0.0f)
    {
        mBallSpeed.x *= -1;
    }
    
    float diff = abs(mBallPos.y - mPaddlePos.y);
    
    if(
        // y값의 차이가 충분히 작고
        diff <= paddleH / 2.0f &&
        // 공이 올바른 x 값을 갖고 있고
        mBallPos.x <= 25.0f && mBallPos.x>=20.0f&&
        // 공이 왼쪽으로 이동하고 있다면
        mBallSpeed.x < 0.0f){
        
        mBallSpeed.x *= -1.0f;
    }
}


void Game::ProcessInput() { 
    SDL_Event event;
    
    // 큐에 이벤트가 남아 있는 동안;
    while(SDL_PollEvent(&event))
    {
        switch (event.type) {
            case SDL_QUIT:
                mIsRunning = false;
                break;
        }
    }
    
    // 키보드 상태 얻기
    const Uint8* state = SDL_GetKeyboardState(NULL);
    // 이스케이프 키를 눌렀다면 루프 종료
    if(state[SDL_SCANCODE_ESCAPE]){
        mIsRunning = false;
    }
    
    mPaddleDir = 0;
    
    // W와 S를 동시에 누르면 0이 되서 움직이지않음
    if(state[SDL_SCANCODE_W]){
        mPaddleDir -= 1;
    }
    
    if(state[SDL_SCANCODE_S]){
        mPaddleDir += 1;
    }
}


void Game::Shutdown() { 
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    SDL_Quit();
}





