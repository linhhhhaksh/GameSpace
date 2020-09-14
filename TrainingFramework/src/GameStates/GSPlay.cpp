#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include <math.h>

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	_endGame = false;
	_score = 0;
		_randPosition_Y = (rand() % 10 > 5);
	_canMoveY = false;

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);


	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("slkscr");
	m_score = std::make_shared< Text>(shader, font, "SCORE: " + std::to_string(_score), TEXT_COLOR::WHILE, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));

	
	// btn
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("gameover");
	m_gameOverBtn = std::make_shared<GameButton>(model, shader, texture);
	m_gameOverBtn->Set2DPosition(screenWidth / 2, -screenHeight);
	m_gameOverBtn->SetSize(200, 50);
	m_gameOverBtn->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		});

	//Ship
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("Ship1");
	
	m_Ship = std::make_shared<Space>(model, shader, texture);
	m_Ship->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_Ship->SetSize(100, 100);
	m_Ship->SetTextureState(nullptr, nullptr, texture);
	m_Ship->AddForce(1400);

	//
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		return;
	wingSound = Mix_LoadWAV("hit.wav");
	
}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{
	
}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	if (bIsPressed && !_endGame) {
		Mix_PlayChannel(-1, wingSound, 0);
		m_Ship->AddForce(1400);
	}
	m_gameOverBtn->HandleTouchEvents(x, y, bIsPressed);
}

void GSPlay::Update(float deltaTime)
{
	m_Ship->Update(deltaTime);
	if (!_endGame) {
		//if (_score % 2 == 0) {
			//_randPosition_Y = (rand() % 10 > 5);
		//}
		UpdatePipePosition(deltaTime);
		//_pipeSpeed += deltaTime;
	}
	else {
		float y = m_gameOverBtn->Get2DPosition().y;
		y += 1500 * deltaTime;
		y = y >= screenHeight / 2 ? screenHeight / 2 : y;
		m_gameOverBtn->Set2DPosition(m_gameOverBtn->Get2DPosition().x, y);
	}
	//m_score->setText("SCORE: " + std::to_string(_score) + " - SPEED: " + std::to_string(_pipeSpeed));
	
}

void GSPlay::Draw()
{
	m_BackGround->Draw();
	
	m_Ship->Draw();
	m_score->Draw();
	m_gameOverBtn->Draw();
}

void GSPlay::SetNewPostionForBullet()
{
}
void GSPlay::CheckScore() {
	
}
void GSPlay::DrawPipe() 
{
	
}

void GSPlay::UpdatePipePosition(float deltaTime)
{
	//

}
void GSPlay::EndGame() {
	Mix_PlayChannel(1, hitSound, 0);
	m_Ship->SetDie();
	int max_score = ResourceManagers::GetInstance()->GetScore();
	if (_score > max_score)
		ResourceManagers::GetInstance()->SetScore(_score);

	_endGame = true;
}
bool GSPlay::CheckCollision(Vector2 pipePosition) {
	/*int w = screenWidth / 8;
	int h = screenHeight / 1.3;

	float min_w = pipePosition.x - w / 2;
	float max_w = pipePosition.x + w / 2;
	float min_h = pipePosition.y - h / 2;
	float max_h = pipePosition.y + h / 2;

	std::shared_ptr<Vector2> b_upRight = std::make_shared<Vector2>(m_Ship->Get2DPosition().x + 25, m_Bird->Get2DPosition().y - 25);
	std::shared_ptr<Vector2> b_upLeft = std::make_shared<Vector2>(m_Bird->Get2DPosition().x - 25, m_Bird->Get2DPosition().y - 25);
	std::shared_ptr<Vector2> b_downRight = std::make_shared<Vector2>(m_Bird->Get2DPosition().x + 25, m_Bird->Get2DPosition().y + 25);
	std::shared_ptr<Vector2> b_downLeft = std::make_shared<Vector2>(m_Bird->Get2DPosition().x - 25, m_Bird->Get2DPosition().y + 25);

	if (b_upRight->x >= min_w && b_upRight->x <= max_w && b_upRight->y >= min_h && b_upRight->y <= max_h) return true;
	if (b_upLeft->x >= min_w && b_upLeft->x <= max_w && b_upLeft->y >= min_h && b_upLeft->y <= max_h) return true;
	if (b_downRight->x >= min_w && b_downRight->x <= max_w && b_downRight->y >= min_h && b_downRight->y <= max_h) return true;
	if (b_downLeft->x >= min_w && b_downLeft->x <= max_w && b_downLeft->y >= min_h && b_downLeft->y <= max_h) return true;
	if (m_Bird->Get2DPosition().y >= screenHeight - 10) return true;
	if (m_Bird->Get2DPosition().y <= 10) return true;

	return false;*/
}