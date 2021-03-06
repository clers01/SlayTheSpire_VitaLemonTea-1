#pragma once
#include "stdafx.h"

class Enemy;
class Cards;

class StateVariables
{
public:
	StateVariables(void);
	~StateVariables(void);
	int HP;//生命值
	int HPMax;//生命值上限
	int Energy;//法力值
	int EnergyMax;//法力值上限
	int Block;//护盾
	int Strength;//力量
	int StrengthUpTemp;//单回合增加的力量
	int Dexterity;//敏捷
	int DexterityUpTemp;//单回合增加的敏捷
	int Gold;//金币
	int Hand[10];//手牌
	Cards* GameDeck[300];//游戏牌库
	int GameDeckPoint;//游戏牌库牌数
	Cards* Deck[100];//玩家牌库
	int DeckPoint;//玩家牌库牌数
	int* DeckPtr;//玩家牌库牌数指针
	int DrawNum;
	int DrawPile[100];//抽牌堆数组
	int DiscardPile[100];
	int DrawPoint;//抽牌堆牌数
	int* DrawPtr;//抽牌堆牌数指针
	int DiscardPoint;//弃牌堆牌数
	int* DiscardPtr;//	弃牌堆牌数指针
	int HandPoint;//手牌数
	int* HandPtr;//手牌数指针
	int StrengthUp;//每回合增加力量
	int Vulnerable;//易伤
	int Weak;//虚弱
	int Berserk;//下回合开始获得Energy
	int Frail;//脆弱
	int CanDraw;//是否可继续摸牌
	int FlameBarrier;//火焰屏障效果
	int Juggernaut;//势不可挡效果
	int Combust;//Combust效果
	int Metallicize;//金属化效果
	int RampageTime;//Rampage使用次数
	int Barricade;//Barricade效果
	int Brutality;//Brutality效果
	int Evolve;//进化效果
	int EnemyNum;//怪物数量

	void draw(int drawnum);
	void usecard(int cardnum, Enemy* target, int n, Cards* GameDeck[], StateVariables* player);
	void addTo(int cardnum, int Pile[], int* pilePoint);
	void randomDamage(int damage, Enemy* target, int n);
	void combust(Enemy* target, int EnemyNum);
	void metallicize(Enemy* target, int EnemyNum);
	void Dexup(int DexupVal, Enemy* target, int EnemyNum);
	void brutality(void);
};

class Enemy
{
public:
	Enemy(int hp, unsigned int damage1, unsigned int attackTimes1 = 1, unsigned int damage2 = 0, unsigned int attackTimes2 = 0, unsigned int damage3 = 0, unsigned int attackTimes3 = 0);
	~Enemy(void);
	int EnemyHP;//怪物血量
	int EnemyBlock;//怪物护盾
	int Damage1;//怪物攻击方案1伤害
	int AttackTimes1;//怪物攻击方案1次数
	int Damage2;//怪物攻击方案2伤害
	int AttackTimes2;//怪物攻击方案2次数
	int Damage3;//怪物攻击方案3伤害
	int AttackTimes3;//怪物攻击方案3次数

	int State_Weak;//虚弱
	int State_Vulnerable;//易伤
	int State_Poison;//中毒
	int State_Ritual;//仪式：回合结束加攻
	int strength;//力量，攻击附加伤害
	int intend;//下次执行命令

	void debuffWeak(int n, StateVariables* player);//上n层虚弱
	void debuffMucus(int n, StateVariables* player);//给粘液牌
	void debuffVulnerable(int n, StateVariables* player);//上n层易伤
	void buffRitual();//仪式效果
	void buffStrengthUp(unsigned int n);//加n力量
	void buffFrail(int n, StateVariables* player);//上n层破甲
};

class Cards
{
public:
	Cards(int cardnum, int EnergyCost);
	~Cards(void);
	unsigned int CardsNum;//卡牌编号
	unsigned int EnergyCost;//费用
	int EnergyConsume(int x, StateVariables* player);
	void Damage(int damage, StateVariables* player, Enemy* target, int n);
	void Defence(int block, StateVariables* player, Enemy* target);
};