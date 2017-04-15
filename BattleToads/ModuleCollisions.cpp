#include "ModuleCollisions.h"
#include "Application.h"
#include "Enemy.h"



ModuleCollisions::ModuleCollisions()
{
	// Level Layout
	enemiesControler = new ModuleControlEnemies;
	SDL_Rect auxRect;
	auxRect.x = 0;
	auxRect.y = 110;
	auxRect.w = 465;
	auxRect.h = 50;
	Hitbox* auxHitBox = new Hitbox(auxRect,1.0f);
	levelLayout.push_back(auxHitBox);

	auxRect.x = 560;
	auxRect.y = 110;
	auxRect.w = 165;
	auxRect.h = 50;
	auxHitBox = new Hitbox(auxRect, 1.0f);
	levelLayout.push_back(auxHitBox);

	auxRect.x = 815;
	auxRect.y = 110;
	auxRect.w = 230;
	auxRect.h = 50;
	auxHitBox = new Hitbox(auxRect, 1.0f);
	levelLayout.push_back(auxHitBox);

	auxRect.x = 1260;
	auxRect.y = 110;
	auxRect.w = 40;
	auxRect.h = 50;
	auxHitBox = new Hitbox(auxRect, 1.0f);
	levelLayout.push_back(auxHitBox);

	auxRect.x = 1515;
	auxRect.y = 110;
	auxRect.w = 40;
	auxRect.h = 50;
	auxHitBox = new Hitbox(auxRect, 1.0f);
	levelLayout.push_back(auxHitBox);

	auxRect.x = 1770;
	auxRect.y = 110;
	auxRect.w = 1000;
	auxRect.h = 50;
	auxHitBox = new Hitbox(auxRect, 1.0f);
	levelLayout.push_back(auxHitBox);

	

}


ModuleCollisions::~ModuleCollisions()
{
}
bool ModuleCollisions::CleanUp()
{
	LOG("Unloading hitboxes");

	levelLayout.clear();
	enemies.clear();
	
	return true;
}
bool ModuleCollisions::Start()
{
	LOG("Loading enemies");

	enemiesControler->Start();

	return true;
}
void ModuleCollisions::drawEnemiesBehind()
{
	std::list<Enemy*>::const_iterator it2;

	for (it2 = enemies.begin(); it2 != enemies.end(); ++it2)
	{
		if ((*it2)->CoordZ < App->player->coordZ)
		{
			LOG("CoordZ Enemy: %f \n", (*it2)->CoordZ);
			LOG("CoordZ Player: %f \n", App->player->coordZ);
			(*it2)->Draw();
		}

	}
}
update_status ModuleCollisions::Update()
{
	drawHitboxes();
	std::list<Hitbox*>::const_iterator it;
	//draw hitboxes
	/*for (it = levelLayout.begin(); it != levelLayout.end(); ++it)
	{
		(*it)->checkIntersection(App->player->playerHitbox->hitBox);
	}*/

	//Draw enemies
	std::list<Enemy*>::const_iterator it2;

	for (it2 = enemies.begin(); it2 != enemies.end(); ++it2)
	{
		if ((*it2)->CoordZ >= App->player->coordZ)
		{
			LOG("CoordZ Enemy: %f \n", (*it2)->CoordZ);
			LOG("CoordZ Player: %f \n", App->player->coordZ);
			(*it2)->Draw();
		}

	}
	return UPDATE_CONTINUE;
}
void ModuleCollisions::drawHitboxes()
{
	std::list<Hitbox*>::const_iterator it;

	for (it = levelLayout.begin();it != levelLayout.end(); ++it)
	{
		(*it)->draw(App->renderer->renderer);
	}
}
void ModuleCollisions::addHitbox(Hitbox* hitBox) 
{
	levelLayout.push_back(hitBox);
}
bool ModuleCollisions::checkIfOnFloor() 
{
	std::list<Hitbox*>::const_iterator it;

	for (it = levelLayout.begin(); it != levelLayout.end(); ++it)
	{
		if ((*it)->checkIntersection(App->player->playerHitbox->hitBox)) return true;
	}
	return false;
}
void ModuleCollisions::addEnemy(Enemy* enemy) 
{
	enemies.push_back(enemy);
}
