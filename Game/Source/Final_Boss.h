#ifndef __FINAL_BOSS_H__
#define __FINAL_BOSS_H__

#include "Entity.h"
#include "Point.h"
#include "DynArray.h"


class Final_Boss : public Entity
{
public:

	Final_Boss(int x, int y);


	void Update(float dt) override;



private:

	Animation fenceOne;
	Animation fenceTwo;
	Animation fenceThree;

	int counter;
};

#endif 