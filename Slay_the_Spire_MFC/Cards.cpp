#include "stdafx.h"
#include "StateVariables.h"

Cards::Cards(int cardnum, int Cost)
{
	CardsNum = cardnum;
	EnergyCost = Cost;
}

Cards::~Cards(void)
{
}

int Cards::EnergyConsume(int x, StateVariables* player)
{
	if (player->Energy < x)
		return 0;
	else
	{
		player->Energy -= x;
		return 1;
	}
}

void Cards::Damage(int damage, Enemy* target, int n)
{
	if (n)
	{
		int iter;
		for (iter = 0; iter < n; iter++)
		{
			if ((target + iter)->EnemyBlock >= damage)
			{
				(target + iter)->EnemyBlock -= damage;
			}
			else
			{
				(target + iter)->EnemyHP -= (damage - (target + iter)->EnemyBlock);
				(target + iter)->EnemyBlock = 0;
			}
		}
	}
	else
	{
		if (target->EnemyBlock >= damage)
		{
			target->EnemyBlock -= damage;
		}
		else
		{
			target->EnemyHP -= (damage - (target->EnemyBlock));
			target->EnemyBlock = 0;
		}
	}
}

void Cards::Defend(int defend, StateVariables* player, Enemy* target, int EnemyNum)
{
	player->Defend(defend, target, EnemyNum);
}