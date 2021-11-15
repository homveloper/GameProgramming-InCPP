#include "Game.h"
#include "SDL_image.h"
#include "Actor.h"

Game::Game() :
	mWindow(nullptr),
	mRenderer(nullptr),
	mIsRunning(true),
	mUpdatingActors(false)
{

}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("Game Programming in C++ (Chapter 2)", 100, 100, 1024, 768, 0);
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	mTicksCount = SDL_GetTicks();

	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown()
{
	// ~Actor �Լ��� RemoveActor�� ȣ���ϹǷ� �ٸ� ��Ÿ���� ������ ����Ѵ�.
	while (!mActors.empty())
	{
		delete mActors.back();
	}
}

void Game::AddActor(Actor* actor)
{
	// ���͸� ���� ���̶�� ��� ���Ϳ� ���͸� �߰�
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else 
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end()) {
		std::iter_swap(iter, mPendingActors.end()-1);
		mPendingActors.pop_back();
	}

	auto iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end()) {
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::LoadData()
{
	Actor* temp = new Actor(this);
	temp->SetPosition(Vector2(512.0f, 384.0f));
}

SDL_Texture* Game::LoadTexture(const char* fileName)
{
	// ���Ϸ� ���� �ε�
	SDL_Surface* surf = IMG_Load(fileName);
	if (!surf)
	{
		SDL_Log("Failed to load texture file %s", fileName);
		return nullptr;
	}

	// �ؽ�ó ����
	SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surf);
	SDL_FreeSurface(surf);
	if (!texture)
	{
		SDL_Log("Failed to convert surface to texture for %s", fileName);
		return nullptr;
	}	

	return texture;
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	SDL_Texture* texture = nullptr;

	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		texture = iter->second;
	}
	else
	{
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}

		// �ؽ�ó ����
		texture = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!texture)
		{
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}

		mTextures.emplace(fileName.c_str(), texture);
	}

	return texture;
}

void Game::ProcessInput()
{
}

void Game::UpdateGame()
{
	// ��Ÿ�ð� ���
	while(!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 50));

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	mTicksCount = SDL_GetTicks();

	// ��� ���͸� ����
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	// ��� ���� ���͸� mActors�� �̵�
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	// ���� ���͸� �ӽ� ���Ϳ� �߰�
	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	// ���� ���� ����(mActors���� �߷��� ���͵�)
	for (auto actor : deadActors)
	{
		delete actor;
	}

}

void Game::GenerateOutput()
{
}
