#include "Zombie_Spitter.h"

#include "App.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "EntityManager.h"
//#include "ModuleParticles.h"
#include "Audio.h"
#include "Point.h"
#include "DynArray.h"
#include "Input.h"
#include "Map.h"
#include "Pathfinding.h"
#include "SceneMainMap.h"
#include "Render.h"
#include "Textures.h"
#include "Log.h"
#include "ModulePhysics.h"
#include "ModuleParticles.h"

#include "Defs.h"

Zombie_Spitter::Zombie_Spitter(int x,int y) : Entity(x,y)
{	
	EntityHP = 1;
	EntityAP = 5;
	EntityMP = 3;
	entityState = GameState::OutOfCombat;

	counter = 0;
	//HERE WE ADD THE ANIMATIONS WITH GIMP
	
	
	Idle_Enemy.PushBack({24,45,25,56});
	Idle_Enemy.loop = true;
	Idle_Enemy.speed = 0.3f;

	

	position.x = x;
	position.y = y;

	collider = app->collisions->AddCollider({ position.x, position.y, 25, 56 }, Collider::Type::ENEMY, (Module*)app->entity_manager);

	Spitter_Zombie_List.add(app->physics->CreateWalkingEnemyBox(position.x, position.y, 25, 10));
	
	
	
}

bool Zombie_Spitter::Update(float dt)
{
	//ADD THE PATHFINDING LOGIC FOR MOVEMENT
	
	if (app->player->pauseMenu == true)
	{
		iPoint NewPosition = position;
		collider->SetPos(NewPosition.x, NewPosition.y);
		Spitter_Zombie_List.end->data->GetPosition(NewPosition.x, NewPosition.y);
		currentAnim = &Idle_Enemy;
		currentAnim->loop = false;

		return true;
	}
	if (app->player->pauseMenu == false)
	{
		Spitter_Zombie_List.end->data->GetPosition(position.x, position.y);

		if (entityState == GameState::OutOfCombat)
		{
			//move normally


			if (position.DistanceTo(app->player->position) < 150)
			{
				collider->SetPos(position.x, position.y);
				Spitter_Zombie_List.end->data->GetPosition(position.x, position.y);
				currentAnim = &Idle_Enemy;
				currentAnim->loop = true;

				if (position.x > app->player->position.x) Spitter_Zombie_List.end->data->body->SetLinearVelocity({ -0.5f, 0.0f });
				if (position.x < app->player->position.x) Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.5f, 0.0f });
				if (position.y > app->player->position.y) Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.0f, -0.5f });
				if (position.y < app->player->position.y) Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.0f, 0.5f });

				if ((app->player->position.y > position.y) && (app->player->position.x > position.x))
				{
					Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.5f, 0.5f });
				}
				if ((app->player->position.x < position.x) && (app->player->position.y > position.y))
				{
					Spitter_Zombie_List.end->data->body->SetLinearVelocity({ -0.5f, 0.5f });
				}
				if ((app->player->position.y < position.y) && (app->player->position.x < position.x))
				{
					Spitter_Zombie_List.end->data->body->SetLinearVelocity({ -0.5f, -0.5f });
				}
				if ((app->player->position.x > position.x) && (app->player->position.y < position.y))
				{
					Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.5f, -0.5f });
				}
			}
			else
			{
				collider->SetPos(position.x, position.y);
				Spitter_Zombie_List.end->data->GetPosition(position.x, position.y);
				currentAnim = &Idle_Enemy;
				currentAnim->loop = true;

				Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.0f,0.0f });

			}

			return true;

		}

		if (entityState == GameState::InCombat)
		{

			if (EntityHP > 0)
			{
				if (entityTurn == TurnState::NONE)
				{
					//Assigning order of turns
					collider->SetPos(position.x, position.y);
					Spitter_Zombie_List.end->data->GetPosition(position.x, position.y);
					currentAnim = &Idle_Enemy;
					currentAnim->loop = true;

					Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.0f,0.0f });

				}
				if (entityTurn == TurnState::StartOfTurn)
				{
					collider->SetPos(position.x, position.y);
					currentAnim = &Idle_Enemy;
					currentAnim->loop = false;
					counter++;
					Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.0f, 0.0f }); //movimiento contrario a la direccion del jugador cuando nos chocamos con el

					if (counter == 50) entityTurn = TurnState::MidOfTurn;

				}
				if (entityTurn == TurnState::MidOfTurn)
				{

					collider->SetPos(position.x, position.y);
					Spitter_Zombie_List.end->data->GetPosition(position.x, position.y);
					currentAnim = &Idle_Enemy;
					currentAnim->loop = true;
					counter++;

					if (position.x > app->player->position.x) Spitter_Zombie_List.end->data->body->SetLinearVelocity({ -0.5f, 0.0f });
					if (position.x < app->player->position.x) Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.5f, 0.0f });
					if (position.y > app->player->position.y) Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.0f, -0.5f });
					if (position.y < app->player->position.y) Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.0f, 0.5f });

					if ((app->player->position.y > position.y) && (app->player->position.x > position.x))
					{
						Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.5f, 0.5f });
					}
					if ((app->player->position.x < position.x) && (app->player->position.y > position.y))
					{
						Spitter_Zombie_List.end->data->body->SetLinearVelocity({ -0.5f, 0.5f });
					}
					if ((app->player->position.y < position.y) && (app->player->position.x < position.x))
					{
						Spitter_Zombie_List.end->data->body->SetLinearVelocity({ -0.5f, -0.5f });
					}
					if ((app->player->position.x > position.x) && (app->player->position.y < position.y))
					{
						Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.5f, -0.5f });
					}

					if (counter == 150) entityTurn = TurnState::FinishTurn;

				}
				if (entityTurn == TurnState::FinishTurn)
				{
					//Change turn from enemy to player turn still have to develop a way to do it correctly
					Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.0f, 0.0f });
					collider->SetPos(position.x, position.y);
					Spitter_Zombie_List.end->data->GetPosition(position.x, position.y);

					currentAnim = &Idle_Enemy;
					currentAnim->loop = true;

					if (position.DistanceTo(app->player->position) < 150)
					{
						if ((position.x == app->player->position.x) && (position.y < app->player->position.y))
						{
							app->particles->RangedAttack.speed.y = 5;
							app->particles->AddParticle(app->particles->RangedAttack, position.x, position.y + 60, Collider::Type::ENEMY_RANGED_ATTACK);

						}
						if ((position.x == app->player->position.x) && (position.y > app->player->position.y))
						{
							app->particles->RangedAttack.speed.y = -5;
							app->particles->AddParticle(app->particles->RangedAttack, position.x, position.y - 60, Collider::Type::ENEMY_RANGED_ATTACK);

						}
						if ((position.x < app->player->position.x) && (position.y == app->player->position.y))
						{

							app->particles->AddParticle(app->particles->RangedAttack, position.x + 30, position.y, Collider::Type::ENEMY_RANGED_ATTACK);


						}
						if ((position.x > app->player->position.x) && (position.y == app->player->position.y))
						{
							app->particles->RangedAttack.speed.x *= -1;
							app->particles->AddParticle(app->particles->RangedAttack, position.x - 30, position.y, Collider::Type::ENEMY_RANGED_ATTACK);


						}

						if ((position.x > app->player->position.x) && (position.y   > app->player->position.y))
						{
							app->particles->RangedAttack.speed.x *= -1;
							app->particles->RangedAttack.speed.y = ((app->player->position.y - position.y) / ((app->player->position.x - position.x) / app->particles->RangedAttack.speed.x));
							app->particles->AddParticle(app->particles->RangedAttack, position.x - 30, position.y - 30, Collider::Type::ENEMY_RANGED_ATTACK);


						}
						if ((position.x > app->player->position.x) && (position.y   < app->player->position.y))
						{
							app->particles->RangedAttack.speed.x *= -1;
							app->particles->RangedAttack.speed.y = ((app->player->position.y - position.y) / ((app->player->position.x - position.x) / app->particles->RangedAttack.speed.x));
							app->particles->AddParticle(app->particles->RangedAttack, position.x - 30, position.y + 30, Collider::Type::ENEMY_RANGED_ATTACK);


						}
						if ((position.x < app->player->position.x) && (position.y   > app->player->position.y))
						{
							app->particles->RangedAttack.speed.y = ((app->player->position.y - position.y) / ((app->player->position.x - position.x) / app->particles->RangedAttack.speed.x));
							app->particles->AddParticle(app->particles->RangedAttack, position.x + 30, position.y - 30, Collider::Type::ENEMY_RANGED_ATTACK);


						}
						if ((position.x < app->player->position.x) && (position.y   < app->player->position.y))
						{
							app->particles->RangedAttack.speed.y = ((app->player->position.y - position.y) / ((app->player->position.x - position.x) / app->particles->RangedAttack.speed.x));
							app->particles->AddParticle(app->particles->RangedAttack, position.x + 30, position.y + 30, Collider::Type::ENEMY_RANGED_ATTACK);


						}


						entityTurn = TurnState::WaitTurn;
					}
					else
					{
						entityTurn = TurnState::WaitTurn;
					}


				}
				if (entityTurn == TurnState::WaitTurn)
				{
					//Change turn from enemy to player turn still have to develop a way to do it correctly
					collider->SetPos(position.x, position.y);
					Spitter_Zombie_List.end->data->GetPosition(position.x, position.y);
					currentAnim = &Idle_Enemy;
					currentAnim->loop = true;



				}

			}


			if (EntityHP == 0)
			{
				SetToDelete();
			}
			return true;

		}



		return true;
	}
}
	




/*
iPoint Origin = app->render->ScreenToWorld(position.x, position.y);
iPoint Destination = app->render->ScreenToWorld(app->player->position.x, app->player->position.y);


const DynArray<iPoint>* path = { nullptr };
app->pathfinding->CreatePath(Origin, Destination);

path = app->pathfinding->GetLastPath();

for (uint i = 0; i < path->Count(); ++i)
{
	iPoint NextPos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);

	app->render->DrawRectangle({ NextPos.x,NextPos.y,10,10 }, 255, 0, 0, 255);

	if (NextPos.x > position.x) entityBody->body->SetLinearVelocity({ -0.5f, 0.0f });
	if (NextPos.x < position.x) entityBody->body->SetLinearVelocity({ 0.5f, 0.0f });
	if (NextPos.y > position.y) entityBody->body->SetLinearVelocity({ 0.0f, -0.5f });
	if (NextPos.y < position.y) entityBody->body->SetLinearVelocity({ 0.0f, 0.5f });



}
*/