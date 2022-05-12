#include "ModulePlayer.h"

#include "app.h"
#include "Textures.h"
#include "Input.h"
#include "GamepadInput.h"
#include "Render.h"
#include "EntityManager.h"
#include "Entity.h"
//#include "ModuleParticles.h"
#include "Audio.h"
#include "ModuleFadeToBlack.h"
#include "Window.h"
//#include "ModuleFonts.h"
#include "GameManager.h"
#include "Log.h"

#include "SceneMotel.h"
#include "SceneMainMap.h"
#include "SceneCave.h"
#include "SceneBase.h"
#include "Map.h"
#include "ModulePhysics.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "Audio.h"
#include "TitleScreen.h"
#include "InventoryMenu.h"
#include "ModuleFonts.h"
#include "QuestManager.h"

#include <stdio.h>
#include <time.h>
#include <SDL_mixer/include/SDL_mixer.h>
#include <iostream>
#include <Optick/include/optick.h>
using namespace std;

ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{
	name.Create("player");

	idleRightAnim.PushBack({ 136, 691, 84, 108 });
	idleRightAnim.loop = true;
	idleRightAnim.speed = 0.3f;

	idleLeftAnim.PushBack({ 136, 214, 84, 108 });
	idleLeftAnim.loop = true;
	idleLeftAnim.speed = 0.3f;

	idleDownAnim.PushBack({ 136, 925, 84, 108 });
	idleDownAnim.loop = true;
	idleDownAnim.speed = 0.3f;

	idleUpAnim.PushBack({ 141, 458, 84, 108 });
	idleUpAnim.loop = true;
	idleUpAnim.speed = 0.3f;

	idleUpLeftAnim.PushBack({ 136, 339, 84, 108 });
	idleUpLeftAnim.loop = true;
	idleUpLeftAnim.speed = 0.3f;

	idleUpRightAnim.PushBack({ 141, 573, 84, 108 });
	idleUpRightAnim.loop = true;
	idleUpRightAnim.speed = 0.3f;

	idleDownLeftAnim.PushBack({ 136, 95,84, 108 });
	idleDownLeftAnim.loop = true;
	idleDownLeftAnim.speed = 0.3f;

	idleDownRightAnim.PushBack({ 141, 808, 84, 108 });
	idleDownRightAnim.loop = true;
	idleDownRightAnim.speed = 0.3f;

	
	rightWalkAnim.PushBack({ 0, 472, 54, 60 });
	rightWalkAnim.loop = true;
	rightWalkAnim.speed = 0.3f;

	leftWalkAnim.PushBack({ 0, 472, 54, 60 });
	leftWalkAnim.loop = true;
	leftWalkAnim.speed = 0.3f;

	downWalkAnim.PushBack({ 0, 472, 54, 60 });
	downWalkAnim.loop = true;
	downWalkAnim.speed = 0.3f;

	upWalkAnim.PushBack({ 0, 472, 54, 60 });
	upWalkAnim.loop = true;
	upWalkAnim.speed = 0.3f;

	rightDownWalkAnim.PushBack({ 0, 472, 54, 60 });
	rightDownWalkAnim.loop = true;
	rightDownWalkAnim.speed = 0.3f;

	leftDownWalkAnim.PushBack({ 0, 472, 54, 60 });
	leftDownWalkAnim.loop = true;
	leftDownWalkAnim.speed = 0.3f;

	rightUpWalkAnim.PushBack({ 0, 472, 54, 60 });
	rightUpWalkAnim.loop = true;
	rightUpWalkAnim.speed = 0.3f;

	leftUpWalkAnim.PushBack({ 0, 472, 54, 60 });
	leftUpWalkAnim.loop = true;
	leftUpWalkAnim.speed = 0.3f;

	rightRunAnim.PushBack({ 0, 472, 54, 60 });
	rightRunAnim.loop = true;
	rightRunAnim.speed = 0.3f;

	leftRunAnim.PushBack({ 0, 472, 54, 60 });
	leftRunAnim.loop = true;
	leftRunAnim.speed = 0.3f;

	downRunAnim.PushBack({ 0, 472, 54, 60 });
	downRunAnim.loop = true;
	downRunAnim.speed = 0.3f;

	upRunAnim.PushBack({ 0, 472, 54, 60 });
	upRunAnim.loop = true;
	upRunAnim.speed = 0.3f;

	rightDownRunAnim.PushBack({ 0, 472, 54, 60 });
	rightDownRunAnim.loop = true;
	rightDownRunAnim.speed = 0.3f;

	leftDownRunAnim.PushBack({ 0, 472, 54, 60 });
	leftDownRunAnim.loop = true;
	leftDownRunAnim.speed = 0.3f;

	rightUpRunAnim.PushBack({ 0, 472, 54, 60 });
	rightUpRunAnim.loop = true;
	rightUpRunAnim.speed = 0.3f;

	leftUpRunAnim.PushBack({ 0, 472, 54, 60 });
	leftUpRunAnim.loop = true;
	leftUpRunAnim.speed = 0.3f;

	entityTurnPlayer = TurnState::NONE;
	entityStatePlayer = GameState::OutOfCombat;



}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Awake()
{
	return true;
}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;
	
	texture = app->tex->Load("Assets/textures/Character/SWAT_Character.png");
	doctorNote = app->tex->Load("Assets/textures/extras/doctor_note.png");

	playerHurtSound = app->audio->LoadFx("Assets/audio/fx/ZPlayer/player_damaged_1.wav");
	itemGrab = app->audio->LoadFx("Assets/audio/fx/ZPlayer/player_grab_finish_back_fast_begin_0.wav");

	if (app->sceneMainMap->sceneMainMap == true || app->sceneMotel->sceneMotel == true)
	{
		playerWalkSound[0] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Tile/FootstepTile01.wav");
		playerWalkSound[1] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Tile/FootstepTile02.wav");
		playerWalkSound[2] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Tile/FootstepTile03.wav");
		playerWalkSound[3] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Tile/FootstepTile04.wav");
		playerWalkSound[4] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Tile/FootstepTile05.wav");
		playerWalkSound[5] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Tile/FootstepTile06.wav");
		playerWalkSound[6] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Tile/FootstepTile07.wav");
	}

	if (app->sceneCave->sceneCave == true)
	{
		playerWalkSound[0] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Dirt/FootstepDirt01.wav");
		playerWalkSound[1] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Dirt/FootstepDirt02.wav");
		playerWalkSound[2] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Dirt/FootstepDirt03.wav");
		playerWalkSound[3] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Dirt/FootstepDirt04.wav");
		playerWalkSound[4] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Dirt/FootstepDirt05.wav");
		playerWalkSound[5] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Dirt/FootstepDirt06.wav");
		playerWalkSound[6] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Dirt/FootstepDirt07.wav");
	}

	if (app->sceneBase->sceneBase == true)
	{
		playerWalkSound[0] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Metal/FootstepMetal01.wav");
		playerWalkSound[1] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Metal/FootstepMetal02.wav");
		playerWalkSound[2] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Metal/FootstepMetal03.wav");
		playerWalkSound[3] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Metal/FootstepMetal04.wav");
		playerWalkSound[4] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Metal/FootstepMetal05.wav");
		playerWalkSound[5] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Metal/FootstepMetal06.wav");
		playerWalkSound[6] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Metal/FootstepMetal07.wav");
	}

	currentAnimation = &idleRightAnim;



	//laserFx = app->audio->LoadFx("Assets/Fx/laser.wav");
	//explosionFx = app->audio->LoadFx("Assets/Fx/explosion.wav");

	//position = app->map->MapToWorld(5, 21); // En el load objects
	b2VelocitySet.x = 0;
	b2VelocitySet.y = -0.5f;
	//position.x = 0;
	//position.y = 0;

	//scale = 1
	// ofset x = 500
	// ofset y = 50

	//scale = 2
	// ofset Px = 1 = Cx = 2 
	// ofset Py = 1 = Cy = 2

	//app->render->camera.x = app->map->MapToWorld(32, 4100).x;
	//app->render->camera.y = app->map->MapToWorld(32, 4100).y;

	destroyed = false;
	deletePlayer = false;
	checkPointReached = false;

	readingNote = false;

	collider = app->collisions->AddCollider({ position.x + 5, position.y - 56, 45, 56 }, Collider::Type::PLAYER, this); //{ position.x + 5, position.y + 3, 28, 33 
	

	Player = app->physics->CreatePlayerBox(position.x, position.y, 20, 5);
	//app->physics->CreateRectangleSensor(position.x, position.y + 16, 28, 1);
	//Player = app->physics->CreatePlayerCircle(position.x, position.y, 20);
	

	//TestingGround = app->physics->CreateColliderRectangle(app->map->MapToWorld(5, 26).x, app->map->MapToWorld(5, 26).y, 1000, 100); // Tendria que estar en Scene.cpp
	//TestingGround = app->physics->CreateColliderRectangle(0, 50, 1000, 100);

	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	//char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = app->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	//LOADING FONT FOR GAME
	char lookupTable[] = { "0123456789" };
	scoreFont = app->fonts->Load("Assets/textures/numbersV3.png", lookupTable, 1);

	PlayerLookingPosition = 2;

	playerTimer = 0;
	playerIdleAnimationTimer = 0;
	hoverTimer = 0;
	destroyedDelay = 0;
	winDelay = 0;
	gameOverDelay = 0;
	TransationToTilteDelay = 0;
	createPlayer = false;

	playerWin = false;

	layerZeroReveal = false;

	//srand(time(NULL));

	uint winWidth, winHeight;

	app->win->GetWindowSize(winWidth, winHeight);

	playerHP = 100;
	/*invincibleDelay = 120;*/
	playerFPS = 0;

	sceneTimer = 450;

	pauseMenu = false;

	exitActivated = false;
	talking = false;

	walkSoundID = 0;
	
	return ret;
}

bool ModulePlayer::PreUpdate()
{

	return true;
}

bool ModulePlayer::Update(float dt)
{
	
	if (pauseMenu==true)
	{
		iPoint NewPosition = position;
		collider->SetPos(NewPosition.x, NewPosition.y);
		//colliderFeet->SetPos(NewPosition.x + 5, NewPosition.y + 23);
		return true;
	}

	if (pauseMenu == false && app->inventoryMenu->showInventory == false)
	{
		playerFPS++;
		

		//OPTICK_EVENT();
		collider->SetPos(position.x + 5, position.y - 56);
		
		playerTimer++;
		//------------------------------------------------------------------------------------------------------------------------------------------
		if (talking == false && entityStatePlayer == GameState::OutOfCombat)
		{
			showCombatHUD = false;

			if (destroyed == false && playerWin == false && app->sceneCave->godMode == false && app->sceneMainMap->godMode == false)
			{
				if (app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_REPEAT
					|| app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_REPEAT
					|| app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_REPEAT
					|| app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_REPEAT)
				{
					if (run == false)
					{
						if (playerFPS % 40 == 0)
						{
							app->audio->PlayFx(playerWalkSound[walkSoundID]);
							walkSoundID++;

							if (walkSoundID > 6) walkSoundID = 0;
						}
					}
					if (run == true)
					{
						if (playerFPS % 20 == 0)
						{
							app->audio->PlayFx(playerWalkSound[walkSoundID]);
							walkSoundID++;

							if (walkSoundID > 6) walkSoundID = 0;
						}
					}
				}

				if (app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_REPEAT
					&& app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_IDLE)
				{
					if (run == false)Player->body->SetLinearVelocity({ -2.0f,0.0f });
					if (run == true)Player->body->SetLinearVelocity({ -4.0f,0.0f });
				}
				else if (app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_REPEAT
					&& app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_IDLE)
				{
					if (run == false)Player->body->SetLinearVelocity({ 2.0f,0.0f });
					if (run == true)Player->body->SetLinearVelocity({ 4.0f,0.0f });
				}
				else if (app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_REPEAT
					&& app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_IDLE)
				{
					if (run == false)Player->body->SetLinearVelocity({ 0.0f,-2.0f });
					if (run == true)Player->body->SetLinearVelocity({ 0.0f,-4.0f });
				}
				else if (app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_REPEAT)
				{
					if (run == false)Player->body->SetLinearVelocity({ 0.0f,2.0f });
					if (run == true)Player->body->SetLinearVelocity({ 0.0f,4.0f });
				}
				else if (app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_REPEAT
					&& app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_REPEAT
					&& app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_IDLE)
				{
					if (run == false)Player->body->SetLinearVelocity({ -2.0f,-2.0f });
					if (run == true)Player->body->SetLinearVelocity({ -4.0f,-4.0f });
				}
				else if (app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_REPEAT
					&& app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_REPEAT)
				{
					if (run == false)Player->body->SetLinearVelocity({ -2.0f,2.0f });
					if (run == true)Player->body->SetLinearVelocity({ -4.0f,4.0f });
				}
				else if (app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_REPEAT
					&& app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_REPEAT
					&& app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_IDLE)
				{
					if (run == false)Player->body->SetLinearVelocity({ 2.0f,-2.0f });
					if (run == true)Player->body->SetLinearVelocity({ 4.0f,-4.0f });
				}
				else if (app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_REPEAT
					&& app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_REPEAT)
				{
					if (run == false)Player->body->SetLinearVelocity({ 2.0f,2.0f });
					if (run == true)Player->body->SetLinearVelocity({ 4.0f,4.0f });
				}


				if (app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_REPEAT)
				{
					if (run == false)
					{
						if (currentAnimation != &leftWalkAnim)
						{
							leftWalkAnim.Reset();
							currentAnimation = &leftWalkAnim;
						}
					}
					else if (run == true)
					{
						if (currentAnimation != &leftRunAnim)
						{
							leftRunAnim.Reset();
							currentAnimation = &leftRunAnim;
						}
					}

					PlayerLookingPosition = 1;

				}

				if (app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_REPEAT)
				{
					if (run == false)
					{
						if (currentAnimation != &upWalkAnim)
						{
							upWalkAnim.Reset();
							currentAnimation = &upWalkAnim;
							PlayerLookingPosition = 4;
						}
					}
					else if (run == true)
					{
						if (currentAnimation != &upRunAnim)
						{
							upRunAnim.Reset();
							currentAnimation = &upRunAnim;
							PlayerLookingPosition = 4;
						}
					}

				}

				if (app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_REPEAT)
				{

					if (run == false)
					{
						if (currentAnimation != &rightWalkAnim)
						{
							rightWalkAnim.Reset();
							currentAnimation = &rightWalkAnim;
						}
					}
					else if (run == true)
					{
						if (currentAnimation != &rightRunAnim)
						{
							rightRunAnim.Reset();
							currentAnimation = &rightRunAnim;
						}
					}
					PlayerLookingPosition = 2;

				}

				if (app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_REPEAT)
				{
					if (run == false)
					{

						if (currentAnimation != &downWalkAnim)
						{
							downWalkAnim.Reset();
							currentAnimation = &downWalkAnim;
							PlayerLookingPosition = 3;
						}
					}
					else if (run == true)
					{

						if (currentAnimation != &downRunAnim)
						{
							downRunAnim.Reset();
							currentAnimation = &downRunAnim;
							PlayerLookingPosition = 3;
						}
					}

				}

				if (app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_REPEAT && app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_REPEAT)
				{
					if (run == false)
					{
						if (currentAnimation != &leftDownWalkAnim)
						{
							leftDownWalkAnim.Reset();
							currentAnimation = &leftDownWalkAnim;
							PlayerLookingPosition = 5;
						}
					}
					else if (run == true)
					{
						if (currentAnimation != &leftDownRunAnim)
						{
							leftDownRunAnim.Reset();
							currentAnimation = &leftDownRunAnim;
							PlayerLookingPosition = 5;
						}
					}

				}

				if (app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_REPEAT && app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_REPEAT)
				{
					if (run == false)
					{
						if (currentAnimation != &rightDownWalkAnim)
						{
							rightDownWalkAnim.Reset();
							currentAnimation = &rightDownWalkAnim;
							PlayerLookingPosition = 6;
						}
					}
					else if (run == true)
					{
						if (currentAnimation != &rightDownRunAnim)
						{
							rightDownRunAnim.Reset();
							currentAnimation = &rightDownRunAnim;
							PlayerLookingPosition = 6;
						}
					}
				}

				if (app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_REPEAT && app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_REPEAT)
				{
					if (run == false)
					{
						if (currentAnimation != &leftUpWalkAnim)
						{
							leftUpWalkAnim.Reset();
							currentAnimation = &leftUpWalkAnim;
							PlayerLookingPosition = 7;
						}
					}
					else if (run == true)
					{
						if (currentAnimation != &leftUpRunAnim)
						{
							leftUpRunAnim.Reset();
							currentAnimation = &leftUpRunAnim;
							PlayerLookingPosition = 7;
						}
					}
				}

				if (app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_REPEAT && app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_REPEAT)
				{
					if (run == false)
					{
						if (currentAnimation != &rightUpWalkAnim)
						{
							rightUpWalkAnim.Reset();
							currentAnimation = &rightUpWalkAnim;
							PlayerLookingPosition = 8;
						}
					}
					else if (run == true)
					{
						if (currentAnimation != &rightUpRunAnim)
						{
							rightUpRunAnim.Reset();
							currentAnimation = &rightUpRunAnim;
							PlayerLookingPosition = 8;
						}
					}
				}

				if (app->input->keys[SDL_SCANCODE_Z] == KeyState::KEY_DOWN)
				{
					// To implement: interact with the environment (examples: grab an object, press a switch�)/select item/select options
				}

				if (app->input->keys[SDL_SCANCODE_X] == KeyState::KEY_DOWN)
				{
					//Grab items from the floor
					app->particles->AddParticle(app->particles->PlayerPickUpRadius, position.x-10, position.y, Collider::Type::PLAYER_PICKUP_RADIUS);
				}

				if (app->input->keys[SDL_SCANCODE_C] == KeyState::KEY_DOWN)
				{
					// To implement: throw things away
				}

				if ((app->input->keys[SDL_SCANCODE_LSHIFT] == KeyState::KEY_REPEAT))
				{
					run = true;
				}
				else
				{
					run = false;
				}


				

				// If no up/down movement detected, set the current animation back to idle
				if (app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_IDLE)
				{
					Player->body->SetLinearVelocity({ 0.0f,0.0f });

					playerIdleAnimationTimer++;
					speed = 0;

					switch (PlayerLookingPosition)
					{
					case 1:
						if (currentAnimation != &idleLeftAnim)
						{
							idleLeftAnim.Reset();
							currentAnimation = &idleLeftAnim;
						}

						break;
					case 2:
						if (currentAnimation != &idleRightAnim)
						{
							idleRightAnim.Reset();
							currentAnimation = &idleRightAnim;
						}

						break;

					case 3:
						if (currentAnimation != &idleDownAnim)
						{
							idleDownAnim.Reset();
							currentAnimation = &idleDownAnim;
						}

						break;

					case 4:
						if (currentAnimation != &idleUpAnim)
						{
							idleUpAnim.Reset();
							currentAnimation = &idleUpAnim;
						}

						break;

					case 5:
						if (currentAnimation != &idleDownLeftAnim)
						{
							idleDownLeftAnim.Reset();
							currentAnimation = &idleDownLeftAnim;
						}

						break;

					case 6:
						if (currentAnimation != &idleDownRightAnim)
						{
							idleDownRightAnim.Reset();
							currentAnimation = &idleDownRightAnim;
						}

						break;

					case 7:
						if (currentAnimation != &idleUpLeftAnim)
						{
							idleUpLeftAnim.Reset();
							currentAnimation = &idleUpLeftAnim;
						}

						break;

					case 8:
						if (currentAnimation != &idleUpRightAnim)
						{
							idleUpRightAnim.Reset();
							currentAnimation = &idleUpRightAnim;
						}

						break;
					}

				}
			}
			//------------------------------------------------------------------------------------------------------------------------------------------
			if (destroyed == false && playerWin == false && (app->sceneCave->godMode == true || app->sceneMainMap->godMode == true))
			{
				//Aqu� no hace falta
			}

		}
		if (entityStatePlayer == GameState::InCombat)
		{
			showCombatHUD = true;


			if (entityTurnPlayer == TurnState::NONE)
			{
				counter = 0;
				iPoint NewPosition = position;
				collider->SetPos(position.x + 5, position.y - 56);
				//colliderFeet->SetPos(NewPosition.x + 5, NewPosition.y + 23);
				Player->body->SetLinearVelocity({ 0.0f,0.0f });
				
			}
			if (entityTurnPlayer == TurnState::StartOfTurn)
			{
				counter = 0;
				iPoint NewPosition = position;
				collider->SetPos(position.x + 5, position.y - 56);
				//colliderFeet->SetPos(NewPosition.x + 5, NewPosition.y + 23);
				Player->body->SetLinearVelocity({ 0.0f,0.0f });
				entityTurnPlayer = TurnState::MidOfTurn;
				playerAttacked = false;
			}
			if (entityTurnPlayer == TurnState::MidOfTurn)
			{
				
				
				if(app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_DOWN)
				{
					counter++;
					Player->body->SetLinearVelocity({ -45.0f,21.0f });
				}
				else Player->body->SetLinearVelocity({ 0.0f,0.0f });
				if (app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_DOWN)
				{
					counter++;
					Player->body->SetLinearVelocity({ 45.0f,-21.0f });
				}
				if (app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_DOWN)
				{
					counter++;
					Player->body->SetLinearVelocity({ 45.0f,21.0f });
				}
				if (app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_DOWN)
				{
					counter++;
					Player->body->SetLinearVelocity({ -45.0f,-21.0f });
				}

				if (app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_IDLE)
				{
					Player->body->SetLinearVelocity({ 0.0f,0.0f });
				}

				if (counter > 6)
				{
					Player->body->SetLinearVelocity({ 0.0f,0.0f });
					entityTurnPlayer = TurnState::FinishTurn;
				}
			}
			if (entityTurnPlayer == TurnState::FinishTurn)
			{
				Player->body->SetLinearVelocity({ 0.0f,0.0f });

				//Attack methodology, after attacking the player goes to wait turn
				int mousePosX, mousePosY;
				app->input->GetMouseMotion(mousePosX, mousePosY);
				

				if (playerAttacked == true)
				{
					entityTurnPlayer = TurnState::WaitTurn;
				}

			}
			if (entityTurnPlayer == TurnState::WaitTurn)
			{
				iPoint NewPosition = position;
				Player->body->SetLinearVelocity({ 0.0f,0.0f });
				collider->SetPos(position.x + 5, position.y - 56);
				//colliderFeet->SetPos(NewPosition.x + 5, NewPosition.y + 23);
				counter = 0;
				
				if (playerHP <= 0)
				{
					/*invincibleDelay = 121;*/
					playerHP = 0;
					//app->audio->PlayFx(dead);
					destroyed = true;

				}
				if (destroyed == true)
				{
					if (destroyedDelay < 1)
					{
						//Mix_PauseMusic();
						
						app->audio->PlayFx(dead);
						//lives--;
						app->sceneMainMap->playerRestart = true;
						
					}
					if (destroyedDelay < 60) Player->body->SetLinearVelocity({ 0, 0 });

					if (currentAnimation != &die)
					{
						die.Reset();
						currentAnimation = &die;
					}
				}

			}
		}
		//Escape Combat
		if (escapeCombat == true)
		{
			escapeCombatCounterToReset++;

			if ((escapeCombatCounterToReset / 300) % 2 == 0)
			{
				escapeCombat = false;
			}
		}

		//  //TODO: Para la alpha mejorar el dialog system
		// 
		//else if (talking == true)
		//{
		//	//Cosas comentadas ya que a�n no han sido implementadas --> To implement: Dialog manager <-- Es un handout de una presentaci�n de clase
		//	
		//	if (app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_DOWN)
		//	{
		//		//selection--;
		//	}
		//	if (app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_DOWN)
		//	{
		//		//selection++;
		//	}

		//	/*
		//	if(selection > totalSelectionsAvailable) selection = 0;
		//	if(selection < 0) selection = totalSelectionsAvailable;
		//	*/

		//	if (app->input->keys[SDL_SCANCODE_Z] == KeyState::KEY_DOWN)
		//	{
		//		//select answer/continue reading
		//	}
		//}
		//------------------------------------------------------------------------------------------------------------------------------------------
		
		//------------------------------------------------------------------------------------------------------------------------------------------
		/*
		if ((PlayerLookingPosition == 1) && (position.x < app->render->camera.x / app->win->GetScale() + 190))
		{
			app->render->camera.x -= 5;
		}
		if ((PlayerLookingPosition == 2) && (position.x > app->render->camera.x / app->win->GetScale() + 140))
		{
			app->render->camera.x += 5;
		}
		*/
		
		/*
		if (lives == 0)
		{
		
			
			app->titleScreen->SavedGame = false;
			app->titleScreen->Enable();
			app->CheckGameRequest();
			app->titleScreen->MainMenu = true;
			
			app->map->Disable();
			app->collisions->Disable();
			app->particles->Disable();
			app->sceneMainMap->Disable();
			app->player->Disable();
			app->enemies->Disable();
			app->fonts->Disable();
			
		}
		*/

		currentAnimation->Update();

		Player->GetPosition(position.x, position.y);


		
	}
	
	
	if ((app->input->keys[SDL_SCANCODE_P] == KEY_DOWN || app->input->keys[SDL_SCANCODE_ESCAPE] == KEY_DOWN) && app->player->destroyed == false && app->player->playerWin == false)
	{
		app->audio->PlayFx(paused);
		pauseMenu = !pauseMenu;
	}

	if ((app->input->keys[SDL_SCANCODE_I] == KEY_DOWN) && app->player->destroyed == false && app->player->playerWin == false)
	{
		/*app->audio->PlayFx(paused);*/
		app->inventoryMenu->showInventory = !app->inventoryMenu->showInventory;
	}

	
	//------------------------------------------------------------------------------------------------------------------------------------------
	return true;
}

bool ModulePlayer::PostUpdate()
{
	
		if (destroyed == true)
		{
			destroyedDelay++;
		}
		if (playerWin == true)
		{
			winDelay++;
		}

		/* Desplazado a Map.cpp para que se dibuje en orden
		if (invincibleDelay <= 120)
		{
			if ((playerFPS / 5) % 2 == 0)
			{
				SDL_Rect rect = currentAnimation->GetCurrentFrame();
				app->render->DrawTexture(texture, position.x, position.y, &rect);
			}
		}
		else
		{
			SDL_Rect rect = currentAnimation->GetCurrentFrame();
			app->render->DrawTexture(texture, position.x, position.y, &rect);
		}
		*/

		// Draw UI (score) --------------------------------------
		sprintf_s(scoreText, 10, "%5d", score);
		sprintf_s(lifeText, 10, "%1d", lives);
		sprintf_s(timerText, 10, "%3d", sceneTimer);


		SDL_Rect quad;
		quad = { 5, 10, playerHP, 10 };

		SDL_Rect quad2;
		quad2 = { 5, 10, 100, 10 };

		SDL_Rect bgquad;
		bgquad = { 3, 8, 104, 14 };
		app->render->DrawRectangle2(bgquad, 255, 255, 255, 255, 0.0f, true);
		app->render->DrawRectangle2(quad2, 200, 200, 200, 255, 0.0f, true);
		//app->render->DrawRectangle(bgquad, 255, 255, 255, 165, true, true);
		if (playerHP >= 100)
		{
			playerHP = 100;
			app->render->DrawRectangle2(quad, 0, 255, 0, 255, 0.0f, true);
		}
		else if (playerHP > 50)
		{
			app->render->DrawRectangle2(quad, 120, 255, 0, 255, 0.0f, true);
		}
		else if (playerHP > 20 && playerHP <= 50)
		{
			app->render->DrawRectangle2(quad, 255, 255, 0, 255, 0.0f, true);
		}
		else
		{
			if ((playerFPS / 5) % 2 == 0)
			{
				app->render->DrawRectangle2(quad, 255, 0, 0, 255, 0.0f, true);
			}
			else
			{
				app->render->DrawRectangle2(quad, 255, 150, 0, 255, 0.0f, true);
			}

		}

		if (app->sceneCave->playerRestart == true)
		{
			//horizontalCB = true;
			app->sceneCave->sceneTimer = 0;

			//if (checkPointReached == false) position = app->map->MapToWorld(32, 14);
				//if (checkPointReached == true) position = app->map->MapToWorld(32, 14);
			score = 0;
			app->player->Disable();
			app->sceneCave->Disable();
			app->collisions->Disable();
			app->map->Disable();
			app->entity_manager->Disable();
			app->particles->Disable();
			app->fonts->Disable();

			if (checkPointReached == false) position = app->map->playerStartPos;
			if (checkPointReached == true) position = app->map->playerCheckPointPos;

			app->player->Enable();
			app->sceneCave->Enable();
			app->collisions->Enable();
			app->map->Enable();
			app->entity_manager->Enable();
			app->particles->Enable();
			app->fonts->Enable();

			app->sceneCave->playerRestart = false;
		}

		
		if (app->sceneMainMap->playerRestart == true)
		{
			//horizontalCB = true;
			app->sceneMainMap->sceneTimer = 0;

			//if (checkPointReached == false) position = app->map->MapToWorld(32, 14);
				//if (checkPointReached == true) position = app->map->MapToWorld(32, 14);
			app->player->Disable();
			app->sceneMainMap->Disable();
			app->collisions->Disable();
			app->map->Disable();
			app->entity_manager->Disable();
			app->particles->Disable();
			app->fonts->Disable();

			if (checkPointReached == false) position = app->map->playerStartPos;
			if (checkPointReached == true) position = app->map->playerCheckPointPos;

			app->player->Enable();
			app->sceneMainMap->Enable();
			app->collisions->Enable();
			app->map->Enable();
			app->entity_manager->Enable();
			app->particles->Enable();
			app->fonts->Enable();

			app->sceneMainMap->playerRestart = false;
			entityStatePlayer = GameState::OutOfCombat;
			entityTurnPlayer = TurnState::NONE;
		}
		

		if (app->titleScreen->toTitleScreen == true)
		{
			gameOverDelay++;

			app->render->DrawTexture2(gameOverScreen, 0, 0, NULL, 0.0f);

			if (gameOverDelay > 1 && gameOverDelay <= 2) app->audio->PlayFx(gameOverfx);

			if (gameOverDelay > 600 && gameOverDelay <= 601)
			{
				app->titleScreen->SavedGame = false;
				app->titleScreen->Enable();
				app->CheckGameRequest();

				app->map->Disable();
				app->collisions->Disable();
				app->particles->Disable();
				app->sceneMainMap->Disable();
				app->player->Disable();
				app->entity_manager->Disable();
				app->fonts->Disable();

				app->titleScreen->toTitleScreen = false;
			}
		}

		// TODO 3: Blit the text of the score in at the bottom of the screen
		app->render->DrawTexture2(ptsScore, 400, 15, NULL);
		app->fonts->BlitText(320, 10, scoreFont, scoreText);
		app->fonts->BlitText(30, 30, scoreFont, lifeText);
		app->fonts->BlitText(350, 30, scoreFont, timerText);

		//app->fonts->BlitText(150, 248, scoreFont, "this is just a font test message");

		if(readingNote == true) app->render->DrawTexture2(doctorNote, 0, 0, NULL);

		return true;
	
	
}

bool ModulePlayer::CleanUp()
{
	app->tex->UnLoad(texture);
	app->tex->UnLoad(doctorNote);

	//deletePlayer = true;
	app->player->Player->body->DestroyFixture(app->player->Player->body->GetFixtureList());
	//app->collisions->RemoveCollider(app->player->collider);
	//app->collisions->RemoveCollider(app->player->colliderFeet);

	return true;
}

bool ModulePlayer::LoadState(pugi::xml_node& data)
{
	position.x = data.child("position").attribute("x").as_int();
	position.y = data.child("position").attribute("y").as_int();

	score = data.child("atributes").attribute("score").as_int();
	playerHP = data.child("atributes").attribute("hp").as_int();
	lives = data.child("atributes").attribute("lives").as_int();
	sceneTimer = data.child("atributes").attribute("timer").as_int();
	//entranceID = data.child("atributes").attribute("entranceID").as_int();
	//app->sceneMainMap->sceneMainMap = data.child("atributes").attribute("sceneMainMap").as_bool();
	//app->sceneCave->sceneCave = data.child("atributes").attribute("sceneCave").as_bool();
	//app->sceneBase->sceneBase = data.child("atributes").attribute("sceneBase").as_bool();

	if (app->player->IsEnabled() == true)
	{
		app->player->Player->body->DestroyFixture(app->player->Player->body->GetFixtureList());

		Player = app->physics->CreatePlayerBox(position.x, position.y, 20, 5);
	}
	
	
	//b2Filter b;
	//b.categoryBits = 0x0001;
	//b.maskBits = 0x0001 | 0x0002;
	//Player->body->GetFixtureList()->SetFilterData(b);
	createPlayer = false;

	//if (app->player->horizontalCB == false && app->sceneCave->sceneTimer > 1) app->render->camera.x = -(app->player->Player->body->GetPosition().x * 100) + 630;

	return true;
}

// L02: DONE 8: Create a method to save the state of the renderer
// Save Game State
bool ModulePlayer::SaveState(pugi::xml_node& data) const
{
	pugi::xml_node playerpos = data.append_child("position");
	pugi::xml_node playerAtributes = data.append_child("atributes");
	
	playerpos.append_attribute("x") = position.x;
	playerpos.append_attribute("y") = position.y;
	playerAtributes.append_attribute("score") = score;
	playerAtributes.append_attribute("hp") = playerHP;
	playerAtributes.append_attribute("lives") = lives;
	playerAtributes.append_attribute("timer") = sceneTimer;
	playerAtributes.append_attribute("entranceID") = entranceID;
	playerAtributes.append_attribute("sceneMainMap") = app->sceneMainMap->sceneMainMap;
	playerAtributes.append_attribute("sceneCave") = app->sceneCave->sceneCave;
	playerAtributes.append_attribute("sceneBase") = app->sceneBase->sceneBase;

	return true;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (app->sceneCave->godMode == false && app->sceneMainMap->godMode == false && destroyed == false && playerWin == false)
	{
		if ((c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ENEMY_ATTACK ))/* && invincibleDelay >= 120*/
		{
			app->audio->PlayFx(playerHurtSound, 0);
			playerHP -= 10;
			


		}
		
		//				--Esto no sirve para nada aqu�. Lo he movido al entity.cpp--

		/*if ((c1->type == Collider::Type::PLAYER_PICKUP_RADIUS && c2->type == Collider::Type::ITEM_FOOD))
		{
			app->inventoryMenu->AddItemToInventory(EntityType::OBJECT_FOOD, true, false);
			app->audio->PlayFx(itemGrab);
		}

		if ((c1->type == Collider::Type::PLAYER_PICKUP_RADIUS && c2->type == Collider::Type::ITEM_HEALTH_PACK))
		{
			app->inventoryMenu->AddItemToInventory(EntityType::OBJECT_HEALTH_PACK, true, false);
			app->audio->PlayFx(itemGrab);
		}

		if ((c1->type == Collider::Type::PLAYER_PICKUP_RADIUS && c2->type == Collider::Type::ITEM_RADIO))
		{
			app->inventoryMenu->AddItemToInventory(EntityType::OBJECT_RADIO, true, false);
			app->audio->PlayFx(itemGrab);
		}
		
		if ((c1->type == Collider::Type::PLAYER_PICKUP_RADIUS && c2->type == Collider::Type::ITEM_DEFAULT_GUN))
		{
			app->inventoryMenu->AddItemToInventory(EntityType::OBJECT_DEFAULT_GUN, false, true);
			app->audio->PlayFx(itemGrab);
		}

		if ((c1->type == Collider::Type::PLAYER_PICKUP_RADIUS && c2->type == Collider::Type::ITEM_KNIFE))
		{
			app->inventoryMenu->AddItemToInventory(EntityType::OBJECT_KNIFE, false, true);
			app->audio->PlayFx(itemGrab);
		}

		if ((c1->type == Collider::Type::PLAYER_PICKUP_RADIUS && c2->type == Collider::Type::ITEM_SUIT))
		{
			app->inventoryMenu->AddItemToInventory(EntityType::OBJECT_SUIT, false, true);
			app->audio->PlayFx(itemGrab);
		}

		if ((c1->type == Collider::Type::PLAYER_PICKUP_RADIUS && c2->type == Collider::Type::ITEM_LONG_RANGE_GUN))
		{
			app->inventoryMenu->AddItemToInventory(EntityType::OBJECT_lONG_SCOPE_GUN, false, true);
			app->audio->PlayFx(itemGrab);
		}

		if ((c1->type == Collider::Type::PLAYER_PICKUP_RADIUS && c2->type == Collider::Type::ITEM_SHORT_RANGE_GUN))
		{
			app->inventoryMenu->AddItemToInventory(EntityType::OBJECT_SHORT_SCOPE_GUN, false, true);
			app->audio->PlayFx(itemGrab);
		}

		if ((c1->type == Collider::Type::PLAYER_PICKUP_RADIUS && c2->type == Collider::Type::ITEM_CARD))
		{
			app->inventoryMenu->AddItemToInventory(EntityType::OBJECT_CARD, true, false);
			app->audio->PlayFx(itemGrab);
			app->questManager->SwitchMainQuest(LOOK_FOR_THE_COMPUTER_2);
		}

		if ((c1->type == Collider::Type::PLAYER_PICKUP_RADIUS && c2->type == Collider::Type::ITEM_GRENADE))
		{
			app->inventoryMenu->AddItemToInventory(EntityType::OBJECT_GRENADE, true, false);
			app->audio->PlayFx(itemGrab);
		}*/

		if ((c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ENEMY_RANGED_ATTACK)) /*&& invincibleDelay >= 120)*/
		{
			app->audio->PlayFx(playerHurtSound, 0);
			playerHP -= 10;
			


		}
		/*if ((c1->type == Collider::Type::PLAYER_ATTACK && c2->type == Collider::Type::ENEMY))
		{

			playerHP -= 10;
			
		}*/

		if ((c1->type == Collider::Type::PLAYER) && c2->type == Collider::Type::EXIT_1)
		{
			exitActivated = true;

			entranceID = 1;
		}

		if ((c1->type == Collider::Type::PLAYER) && c2->type == Collider::Type::EXIT_2)
		{
			exitActivated = true;
			entranceID = 2;
		}

		if ((c1->type == Collider::Type::PLAYER) && c2->type == Collider::Type::EXIT_3)
		{
			exitActivated = true;
			entranceID = 3;
		}

		if ((c1->type == Collider::Type::PLAYER) && c2->type == Collider::Type::LAYER_ZERO)
		{
			if (layerZeroReveal == false)
			{
				layerZeroReveal = true;
			}
		}
		else if ((c1->type == Collider::Type::PLAYER) && c2->type != Collider::Type::LAYER_ZERO)
		{
			if (layerZeroReveal == true)
			{
				layerZeroReveal = false;
			}
		}
		
		if ((c1->type == Collider::Type::PLAYER) && c2->type == Collider::Type::INSTANT_DEATH)
		{
			playerHP -= 100;
			if (playerHP < 0) playerHP = 0;
			invincibleDelay = 0;
			if (playerHP != 0) app->audio->PlayFx(damaged);

			if (playerHP <= 0)
			{
				invincibleDelay = 121;
				playerHP = 0;
				//app->audio->PlayFx(dead);
				destroyed = true;

			}
		}

		if ((c1->type == Collider::Type::PLAYER) && c2->type == Collider::Type::ENABLE_FINAL_BATTLE)
		{

		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::DOCTOR_NOTE_MESSAGE)
		{
			if (layerZeroReveal == false)
			{
				layerZeroReveal = true;
			}

			if (app->input->keys[SDL_SCANCODE_X] == KeyState::KEY_DOWN)
			{
				app->player->readingNote = !app->player->readingNote;
				app->audio->PlayFx(app->player->itemGrab);
			}
		}

		if ((c2->type == Collider::Type::PLAYER) && collider->type == Collider::Type::BASE_COMPUTER)
		{
			if (app->input->keys[SDL_SCANCODE_X] == KeyState::KEY_DOWN)
			{
				
			}
		}

		if ((c2->type == Collider::Type::PLAYER) && collider->type == Collider::Type::TNT_SWITCH)
		{

		}

		if ((c2->type == Collider::Type::PLAYER) && collider->type == Collider::Type::SWITCH)
		{

		}
	}
}

iPoint ModulePlayer::GetLastPosition()
{
	iPoint NewPosition = position;

	return NewPosition;
}


void ModulePlayer::RangedAttack()
{
	//Add logic for ranged attack

	//
}
void ModulePlayer::MeleeAttack()
{
	//Add logic for attack

	//Example of addition of particles for melee
	//app->particles->AddParticle(app->particles->playerAttack, app->player->position.x + 30, app->player->position.y + 12, Collider::Type::PLAYER_ATTACK);

	app->particles->AddParticle(app->particles->playerAttack, enemyPosition.x, enemyPosition.y, Collider::Type::PLAYER_ATTACK);

	playerAttacked = true;
}