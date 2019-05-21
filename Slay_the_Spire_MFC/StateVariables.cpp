#include "StdAfx.h"
#include "StateVariables.h"
#include <time.h>
#define random(x) (rand()%x)

StateVariables::StateVariables(void)
{
	Block = 0;
	Dexterity = 0;
	Energy = 3;
	EnergyMax = 3;
	Gold = 99;
	HP = 70;
	HPMax = 70;
	Deck[0] = GameDeck[1];
	Deck[1] = GameDeck[1];
	Deck[2] = GameDeck[1];
	Deck[3] = GameDeck[1];
	Deck[4] = GameDeck[1];
	Deck[5] = GameDeck[3];
	Deck[6] = GameDeck[3];
	Deck[7] = GameDeck[3];
	Deck[8] = GameDeck[3];
	Deck[9] = GameDeck[2];//����ֻ��ʮ�ų�ʼ�Ƶ��ƿ�
	int i;
	for (i = 10; i <= 99; i++)
	{
		Deck[i] = 0;//ʣ�µĿ�λ��0��ʾ
	}
	DrawNum = 5;//ÿ�غϳ�5����
	DeckPoint = 10;
	DeckPtr = &DeckPoint;
	DrawPoint = 0;
	DrawPtr = &DrawPoint;
	DiscardPoint = 0;
	DiscardPtr = &DiscardPoint;
	HandPoint = 0;
	HandPtr = &HandPoint;
	Vulnerable = 0;
	Weak = 0;
	Strength = 0;
	StrengthUp = 0;
	StrengthUpTemp = 0;
	Dexterity = 0;
	DexterityUpTemp = 0;
	CanDraw = 1;
	FlameBarrier = 0;
	Berserk = 0;
	Juggernaut = 0;//JuggernautЧ��
	Combust = 0;//CombustЧ��
	Metallicize = 0;//MetallicizeЧ��
	RampageTime = 0;//Rampageʹ�ô���
	Barricade = 0;//BarricadeЧ��
	Brutality = 0;//BrutalityЧ��
	EnemyNum = 0;
}

StateVariables::~StateVariables(void)
{
}


void StateVariables::draw(int drawnum)
{
	for (int i = 0; i < drawnum; i++)
	{
		Hand[*HandPtr + i + 1] = DrawPile[*DrawPtr - i];
		DrawPile[*DrawPtr - i] = 0;
	}
	*HandPtr = *HandPtr + drawnum;
	*DrawPtr = *DrawPtr - drawnum;
};

void StateVariables::addTo(int cardnum, int PileExample[], int* pilePoint)
{
	srand((unsigned int)(time(NULL)));
	int i = random(*pilePoint);
	int j;
	for (j = *pilePoint - 1; j > i; j--)
	{
		PileExample[j + 1] = PileExample[j];
	}
	PileExample[i] = cardnum;
	*pilePoint += 1;
}

void StateVariables::usecard(int cardnum, Enemy* target = NULL, int n = 0, Cards* GameDeck[] = NULL, StateVariables* player = NULL)
{
	addTo(cardnum, DiscardPile, DiscardPtr);
	switch (cardnum)
	{
	    case 1: //ʹ��
	    {
		    if (GameDeck[cardnum]->EnergyConsume(GameDeck[cardnum]->EnergyCost, player))
		    {
		    	GameDeck[cardnum]->Damage(8, player, target, 0);
			    target->State_Vulnerable += 2;
			    break;
		    }
		    else
			    return;
	    }

	    case 201: //ʹ��+
	    {
		    if (GameDeck[cardnum]->EnergyConsume(GameDeck[cardnum]->EnergyCost, player))
		    {
			    GameDeck[cardnum]->Damage(11, player, target, 0);
			    target->State_Vulnerable += 10;
			    break;
		    }
		    else
			    return;
	    }

	    case 2: //����
	    {
		    if (GameDeck[cardnum]->EnergyConsume(GameDeck[cardnum]->EnergyCost, player))
		    {
		    	GameDeck[cardnum]->Defence(5, player, NULL);
				break;
		    }
		    else
			    return;
	    }

		case 202: //����+
		{
			if (GameDeck[cardnum]->EnergyConsume(GameDeck[cardnum]->EnergyCost, player))
			{
				GameDeck[cardnum]->Defence(8, player, NULL);
				break;
			}
			else
				return;
		}

		case 3: //���
		{
			if (GameDeck[cardnum]->EnergyConsume(GameDeck[cardnum]->EnergyCost, player))
			{
				GameDeck[cardnum]->Damage(6, player, target, 0);
				break;
			}
			else
				return;
		}

		case 203: //���+
		{
			if (GameDeck[cardnum]->EnergyConsume(GameDeck[cardnum]->EnergyCost, player))
			{
				GameDeck[cardnum]->Damage(9, player, target, 0);
				break;
			}
			else
				return;
		}

		case 4: //��ŭ
		{
			if (GameDeck[cardnum]->EnergyConsume(GameDeck[cardnum]->EnergyCost, player))
			{
				GameDeck[cardnum]->Damage(6, player, target, 0);
				addTo(4, DiscardPile, DiscardPtr);
				break;
			}
			else
				return;
		}

		case 204: // ��ŭ+
		{
			if (GameDeck[cardnum]->EnergyConsume(GameDeck[cardnum]->EnergyCost, player))
			{
				GameDeck[cardnum]->Damage(9, player, target, 0);
				addTo(204, DiscardPile, DiscardPtr);
				break;
			}
			else
				return;
		}
		//case 5:

		case 6: //ȫ��ײ��
		{
			if (GameDeck[cardnum]->EnergyConsume(GameDeck[cardnum]->EnergyCost, player))
			{
				GameDeck[cardnum]->Damage(player->Block, player, target, 0);
				break;
			}
			else
				return;
		}

		case 206: //ȫ��ײ��+
		{
			if (GameDeck[cardnum]->EnergyConsume(GameDeck[cardnum]->EnergyCost, player))
			{
				GameDeck[cardnum]->Damage(player->Block, player, target, 0);
				break;
			}
			else
				return;
		}
		//case 7

		case 8: //
		{
			if (GameDeck[cardnum]->EnergyConsume(GameDeck[cardnum]->EnergyCost, player))
			{
				GameDeck[cardnum]->Damage(8, player, target, EnemyNum);
				break;
			}
			else
				return;
		}

		case 208: //
		{
			if (GameDeck[cardnum]->EnergyConsume(GameDeck[cardnum]->EnergyCost, player))
			{
				GameDeck[cardnum]->Damage(11, player, target, EnemyNum);
				break;
			}
			else
				return;
		}

		case 9: //��ձ�
		{
			if (GameDeck[cardnum]->EnergyConsume(GameDeck[cardnum]->EnergyCost, player))
			{
				GameDeck[cardnum]->Damage(12, player, target, 0);
				target->State_Weak += 2;
				break;
			}
			else
				return;
		}

		case 209: //��ձ�+
		{
			if (GameDeck[cardnum]->EnergyConsume(GameDeck[cardnum]->EnergyCost, player))
			{
				GameDeck[cardnum]->Damage(14, player, target, 0);
				target->State_Weak += 3;
				break;
			}
			else
				return;
		}

		case 10: //�����
		{
			if (GameDeck[cardnum]->EnergyConsume(GameDeck[cardnum]->EnergyCost, player))
			{
				player->Strength += 2;
				player->StrengthUpTemp += 2;
				break;
			}
			else
				return;
		}

		case 210: //�����+
		{
			if (GameDeck[cardnum]->EnergyConsume(GameDeck[cardnum]->EnergyCost, player))
			{
				player->Strength += 4;
				player->StrengthUpTemp += 4;
				break;
			}
			else
				return;
		}

		case 11: //����
		{
			if (GameDeck[cardnum]->EnergyConsume(GameDeck[cardnum]->EnergyCost, player))
			{
				usecard(DrawPile[DrawPoint - 1], target, n); //���Ĺ���ûʵ��
				DrawPile[DrawPoint - 1] = 0;
				*DrawPtr -= 1;
				break;
			}
			else
				return;
		}

		case 211: //����+
		{
			if (GameDeck[cardnum]->EnergyConsume(GameDeck[cardnum]->EnergyCost, player))
			{
				usecard(DrawPile[DrawPoint - 1], target, n); //���Ĺ���ûʵ��
				DrawPile[DrawPoint - 1] = 0;
				*DrawPtr -= 1;
				break;
			}
			else
				return;
		}

		//case 12

		case 13: //����
		{
			if (GameDeck[cardnum]->EnergyConsume(GameDeck[cardnum]->EnergyCost, player))
			{
				GameDeck[cardnum]->Damage(9 + player->Strength * 2, player, target, 0);
				break;
			}
			else
				return;
		}

		case 213: //����+
		{
			if (GameDeck[cardnum]->EnergyConsume(GameDeck[cardnum]->EnergyCost, player))
			{
				GameDeck[cardnum]->Damage(12 + player->Strength * 4, player, target, 0);
				break;
			}
			else
				return;
		}

		case 14: //��ն��
		{
			if (GameDeck[cardnum]->EnergyConsume(GameDeck[cardnum]->EnergyCost, player))
			{
				GameDeck[cardnum]->Defence(5, player, NULL);
				GameDeck[cardnum]->Damage(5, player, target, 0);
				break;
			}
			else
				return;
		}
		case 214: //��ն��+
		{
			if (GameDeck[cardnum]->EnergyConsume(GameDeck[cardnum]->EnergyCost, player))
			{
				GameDeck[cardnum]->Defence(7, player, NULL);
				GameDeck[cardnum]->Damage(7, player, target, 0);
				break;
			}
			else
				return;
		}

		/*case 15 //�������
		{
		    if (GameDeck[cardnum]->EnergyConsume(GameDeck[cardnum]->EnergyCost, player))
			{
				int strikeSum;
				for (int i = 0; i < DeckPoint; i++)
				{
					if (ifstrike(Deck[i]))  //ifstrike�ж��ƴ��������������δʵ��
					{
						sumStrike += 1;
					}
				}
				GameDeck[cardnum]->Damage(6 + sumStrike * 2, player, target, 0);
				break;
			}
			else
				return;
		}
		*/

		case 16: //�������
		{
			if (GameDeck[cardnum]->EnergyConsume(GameDeck[cardnum]->EnergyCost, player))
			{
				GameDeck[cardnum]->Damage(9, player, target, 0);
				draw(1);
				break;
			}
			else
				return;
		}
		case 216: //�������+
		{
			if (GameDeck[cardnum]->EnergyConsume(GameDeck[cardnum]->EnergyCost, player))
			{
				GameDeck[cardnum]->Damage(10, player, target, 0);
				draw(2);
				break;
			}
			else
				return;
		}

     


	}
}

void StateVariables::Dexup(int DexupVal, Enemy* target = NULL, int EnemyNum = 0)
{
	if (Frail)
	{
		Block += int((DexupVal + Dexterity) * 0.75);
	}
	else
	{
		Block += DexupVal + Dexterity;
	}
	if (Juggernaut)
	{
		randomDamage(Juggernaut, target, EnemyNum);
	}
}

void StateVariables::randomDamage(int damage, Enemy * target, int n)
{
	srand((unsigned int)(time(NULL)));
	int t = random(n);
	if ((target + t)->EnemyBlock >= damage)
	{
		(target + t)->EnemyBlock -= damage;
	}
	else
	{
		(target + t)->EnemyHP -= (damage - (target->EnemyBlock));
		(target + t)->EnemyBlock = 0;
	}
}

void StateVariables::combust(Enemy * target, int EnemyNum)
{
	if (Combust)
	{
		int iter;
		for (iter = 0; iter < EnemyNum; iter++)
		{
			if ((target + iter)->EnemyBlock >= Combust)
			{
				(target + iter)->EnemyBlock -= Combust;
			}
			else
			{
				(target + iter)->EnemyHP -= (Combust - (target + iter)->EnemyBlock);
				(target + iter)->EnemyBlock = 0;
			}
		}
	}
}

void StateVariables::metallicize(Enemy * target = NULL, int EnemyNum = 0)
{
	if (Metallicize)
	{
		Dexup(Metallicize, target, EnemyNum);
	}
}

/*void StateVariables::usecard(int cardnum, Enemy* target = NULL, int n = 0)
{
	switch (cardnum)
	{
	case 3:
	{
		if (Deck[cardnum]->EnergyConsume(1, this))
			target->EnemyBlock -= int((6 + Strength) * WeakCoefficient * target->Vulnerable);
	}break;
	case 1003:
	{
		if (Deck[cardnum]->EnergyConsume(1, this))
			target->EnemyBlock -= int((9 + Strength) * WeakCoefficient * target->Vulnerable);
	}break;
	case 1:
	{
		if (Deck[cardnum]->EnergyConsume(2, this))
		{
			target->EnemyBlock -= int((8 + Strength) * WeakCoefficient * target->Vulnerable);
			target->State_Vulnerable += 2;
		}
	}break;
	case 1001:
	{
		if(Deck[cardnum]->EnergyConsume(2, this))
		target->EnemyBlock -= int((10 + Strength) * WeakCoefficient * target->Vulnerable);
		target->State_Vulnerable += 3;
	}break;
	case 2:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		Block += (5 + Dexterity);
	}break;
	case 1002:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		Block += (8 + Dexterity);
	}break;
	case 6:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		target->EnemyBlock -= int((Block + Strength) * WeakCoefficient * target->Vulnerable);
	}break;
	case 1006:
	{
		target->EnemyBlock -= int((Block + Strength) * WeakCoefficient * target->Vulnerable);
	}break;
	case 16:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		target->EnemyBlock -= int((9 + Strength) * WeakCoefficient * target->Vulnerable);
		draw(1);
	}break;
	case 1016:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		target->EnemyBlock -= int((10 + Strength) * WeakCoefficient * target->Vulnerable);
		draw(2);
	}break;
	case 21:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		target->EnemyBlock -= int((5 + Strength) * WeakCoefficient * target->Vulnerable);
		target->EnemyBlock -= int((5 + Strength) * WeakCoefficient * target->Vulnerable);
	}break;
	case 1021:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		target->EnemyBlock -= int((7 + Strength) * WeakCoefficient * target->Vulnerable);
		target->EnemyBlock -= int((7 + Strength) * WeakCoefficient * target->Vulnerable);
	}break;
	case 4:
	{
		target->EnemyBlock -= int((5 + Strength) * WeakCoefficient * target->Vulnerable);
		DiscardPile[DiscardPoint] = 4;
		DiscardPoint++;
	}break;
	case 1004:
	{
		target->EnemyBlock -= int((7 + Strength) * WeakCoefficient * target->Vulnerable);
		DiscardPile[DiscardPoint] = 1004;
		DiscardPoint++;
	}break;
	case 23:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		damage(12);
		addToDrawPile(131);
	}break;
	case 1023:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		damage(17);
		addToDrawPile(131);
	}break;
	case 17:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		Block += (8 + Dexterity);
		draw(1);
	}break;
	case 1017:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		Block += (11 + Dexterity);
		draw(1);
	}break;
	case 13:
	{
		if(Deck[cardnum]->EnergyConsume(2, this))
		target->EnemyBlock -= int((14 + 3 * Strength) * WeakCoefficient * target->Vulnerable);
	}break;
	case 1013:
	{
		if(Deck[cardnum]->EnergyConsume(2, this))
		target->EnemyBlock -= int((14 + 5 * Strength) * WeakCoefficient * target->Vulnerable);
	}break;
	case 9:
	{
		if(Deck[cardnum]->EnergyConsume(2, this))
		target->EnemyBlock -= int((12 + Strength) * WeakCoefficient * target->Vulnerable);
		target->State_Weak += 2;
	}break;
	case 1009:
	{
		if(Deck[cardnum]->EnergyConsume(2, this))
		target->EnemyBlock -= int((14 + Strength) * WeakCoefficient * target->Vulnerable);
		target->State_Weak += 3;
	}break;
	case 14:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		damage(5);
		Block += (5 + Dexterity);
	}break;
	case 1014:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		damage(7);
		Block += (7 + Dexterity);
	}break;
	case 58:
	{
		if(Deck[cardnum]->EnergyConsume(2, this))
		damage(13);
		target->State_Vulnerable += 1;
		target->State_Weak += 1;
	}break;
	case 1058:
	{
		if(Deck[cardnum]->EnergyConsume(2, this))
		damage(13);
		target->State_Vulnerable += 2;
		target->State_Weak += 2;
	}break;
	case 1005:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		Block += (5 + Dexterity);
		int i;
		for (i = 1; i < HandPoint; i++)
		{
			if (Hand[i] < 1000)
				Hand[i] += 1000;
		}
	}break;
	case 10:
	{
		Strength += 2;
		StrengthUpTemp += 2;
	}break;
	case 1010:
	{
		Strength += 4;
		StrengthUpTemp += 4;
	}break;
	case 11:
	{
		usecard(DrawPile[DrawPoint], target, n);
		DrawPile[DrawPoint] = 0;
		DrawPoint -= 1;
	}break;
	case 1011:
	{
		usecard(DrawPile[DrawPoint], target, n);
		DrawPile[DrawPoint] = 0;
		DrawPoint -= 1;
	}break;
	case 18:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		srand((unsigned int)(time(NULL)));
		int t = random(n);
		int i;
		for (i = 0; i < 3; i++)
			(target + t)->EnemyBlock -= int((3 + Strength) * WeakCoefficient * target->Vulnerable);
	}break;
	case 1018:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		srand((unsigned int)(time(NULL)));
		int t = random(n);
		int i;
		for (i = 0; i < 4; i++)
			(target + t)->EnemyBlock -= int((3 + Strength) * WeakCoefficient * target->Vulnerable);
	}break;
	case 19:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		int i;
		for (i = 0; i < n; i++)
		{
			(target + i)->EnemyBlock -= int((4 + Strength) * WeakCoefficient * target->Vulnerable);
			(target + i)->State_Vulnerable += 1;
		}
	}break;
	case 1019:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		int i;
		for (i = 0; i < n; i++)
		{
			(target + i)->EnemyBlock -= int((7 + Strength) * WeakCoefficient * target->Vulnerable);
			(target + i)->State_Vulnerable += 1;
		}
	}break;
	case 20:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		Block += 7;
		srand((unsigned int)(time(NULL)));
		int i = random(HandPoint);
		Hand[i] = Hand[i + 1];
		for (i = i + 1; i < HandPoint - 1; i++)
			Hand[i] = Hand[i + 1];
		HandPoint -= 1;
	}break;
	case 24:
	{
		draw(3);
		CanDraw = 0;
	}
	case 1024:
	{
		draw(4);
		CanDraw = 0;
	}
	case 26:
	{
		HP -= 3;
		Energy += 1;
	}break;
	case 1026:
	{
		HP -= 3;
		Energy += 2;
	}break;
	case 28:
	{
		if(Deck[cardnum]->EnergyConsume(2, this))
		damage(20);
	}break;
	case 1028:
	{
		if(Deck[cardnum]->EnergyConsume(2, this))
		damage(28);
	}break;
	case 32:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		damage(5);
		if (target->State_Vulnerable > 0)
		{
			Energy += 1;
			draw(1);
		}
	}break;
	case 1032:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		damage(8);
		if (target->State_Vulnerable > 0)
		{
			Energy += 1;
			draw(1);
		}
	}break;
	case 34:
	{
		if(Deck[cardnum]->EnergyConsume(2, this))
		Block *= 2;
	}break;
	case 1034:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		Block *= 2;
	}break;
	case 38:
	{
		if(Deck[cardnum]->EnergyConsume(2, this))
		Block += (12 + Dexterity);
		FlameBarrier = 4;
	}break;
	case 1038:
	{
		if(Deck[cardnum]->EnergyConsume(2, this))
		Block += (16 + Dexterity);
		FlameBarrier = 6;
	}break;
	case 40:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		HP -= 3;
		damage(14);
	}break;
	case 1040:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		HP -= 2;
		damage(18);
	}break;
	case 42:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		Strength += 2;
	}break;
	case 1042:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		Strength += 3;
	}break;
	case 61:
	{
		Vulnerable += 3;
		Berserk += 1;
	}break;
	case 1061:
	{
		Vulnerable += 2;
		Berserk += 1;
	}break;
	case 62:
	{
		if(Deck[cardnum]->EnergyConsume(3, this))
		damage(32);
	}break;
	case 1062:
	{
		if(Deck[cardnum]->EnergyConsume(3, this))
		damage(42);
	}break;
	case 65:
	{
		if(Deck[cardnum]->EnergyConsume(3, this))
		StrengthUp += 2;
	}break;
	case 1065:
	{
		if(Deck[cardnum]->EnergyConsume(3, this))
		StrengthUp += 3;
	}break;
	case 70:
	{
		if(Deck[cardnum]->EnergyConsume(2, this))
		int i;
		for (i = 0; i < n; i++)
		{
			(target + i)->EnemyBlock -= 21;
		}
		DiscardPile[DiscardPoint] = 129;
		DiscardPoint++;
	}break;
	case 1070:
	{
		if(Deck[cardnum]->EnergyConsume(2, this))
		int i;
		for (i = 0; i < n; i++)
		{
			(target + i)->EnemyBlock -= 28;
		}
		DiscardPile[DiscardPoint] = 129;
		DiscardPoint++;
	}break;
	case 72:
	{
		if(Deck[cardnum]->EnergyConsume(2, this))
		Juggernaut = 5;
	}break;
	case 1072:
	{
		if(Deck[cardnum]->EnergyConsume(2, this))
		Juggernaut = 7;
	}break;
	case 77:
	{
		damage(7);
		HP += 2;
	}break;
	case 1077:
	{
		damage(8);
		HP += 3;
	}break;
	case 8:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		int i;
		for (i = 0; i < n; i++)
		{
			(target + i)->EnemyBlock -= int((8 + Strength) * WeakCoefficient * target->Vulnerable);
		}
	}break;
	case 1008:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		int i;
		for (i = 0; i < n; i++)
		{
			(target + i)->EnemyBlock -= int((8 + Strength) * WeakCoefficient * target->Vulnerable);
		}
	}break;
	case 29:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		Combust = 5;
	}break;
	case 1029:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		Combust = 7;
	}break;
	case 35:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		Evolve = 1;
	}break;
	case 1035:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		Evolve = 2;
	}break;
	case 44:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		Metallicize = 3;
	}break;
	case 1044:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		Metallicize = 4;
	}break;
	case 45:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		Hand[HandPoint] = 131;
		Hand[HandPoint + 1] = 131;
		HandPoint += 2;
		Block += 15;
	}break;
	case 1045:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		Hand[HandPoint] = 131;
		Hand[HandPoint + 1] = 131;
		HandPoint += 2;
		Block += 20;
	}break;
	case 47:
	{
		Rage = 3;
	}break;
	case 1047:
	{
		Rage = 5;
	}break;
	case 48:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		damage(8 + RampageTime * 5);
		RampageTime += 1;
	}break;
	case 1048:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		damage(8 + RampageTime * 8);
		RampageTime += 1;
	}break;
	case 49:
	{
		damage(7);
		addToDrawPile(130);
	}break;
	case 1049:
	{
		damage(10);
		addToDrawPile(130);
	}break;
	case 50:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		Rupture = 1;
	}break;
	case 1050:
	{
		Rupture = 1;
	}break;
	case 57:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		int i;
		for (i = 0; i < n; i++)
		{
			if ((target + i)->intend == 0)
			{
				Strength += 3;
			}
		}
	}break;
	case 1057:
	{
		if(Deck[cardnum]->EnergyConsume(1, this))
		int i;
		for (i = 0; i < n; i++)
		{
			if ((target + i)->intend == 0)
			{
				Strength += 4;
			}
		}
	}break;
	case 59:
	{
		int i, j;
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < Energy; j++)
			{
				(target + i)->EnemyBlock -= int((5 + Strength) * WeakCoefficient * target->Vulnerable);
			}
		}
		Energy = 0;
	}break;
	case 1059:
	{
		int i, j;
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < Energy; j++)
			{
				(target + i)->EnemyBlock -= int((8 + Strength) * WeakCoefficient * target->Vulnerable);
			}
		}
		Energy = 0;
	}break;
	case 60:
	{
		if(Deck[cardnum]->EnergyConsume(3, this))
		Barricade = 1;
	}break;
	case 1060:
	{
		if(Deck[cardnum]->EnergyConsume(2, this))
		Barricade = 1;
	}break;
	case 63:
	{
		Brutality = 1;
	}break;
	}
}*/

void StateVariables::brutality(void)
{
	HP -= 1;
	draw(1);
}