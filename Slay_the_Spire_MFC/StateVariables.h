#pragma once
#include "stdafx.h"

class Enemy;
class Cards;

class StateVariables
{
public:
	StateVariables(void);
	~StateVariables(void);
	int HP;//����ֵ
	int HPMax;//����ֵ����
	int Energy;//����ֵ
	int EnergyMax;//����ֵ����
	int Block;//����
	int Strength;//����
	int StrengthUpTemp;//���غ����ӵ�����
	int Dexterity;//����
	int DexterityUpTemp;//���غ����ӵ�����
	int Gold;//���
	int Hand[10];//����
	Cards* GameDeck[300];//��Ϸ�ƿ�
	int GameDeckPoint;//��Ϸ�ƿ�����
	Cards* Deck[100];//����ƿ�
	int DeckPoint;//����ƿ�����
	int* DeckPtr;//����ƿ�����ָ��
	int DrawNum;
	int DrawPile[100];//���ƶ�����
	int DiscardPile[100];
	int DrawPoint;//���ƶ�����
	int* DrawPtr;//���ƶ�����ָ��
	int DiscardPoint;//���ƶ�����
	int* DiscardPtr;//	���ƶ�����ָ��
	int HandPoint;//������
	int* HandPtr;//������ָ��
	int StrengthUp;//ÿ�غ���������
	int Vulnerable;//����
	int Weak;//����
	int Berserk;//�»غϿ�ʼ���Energy
	int Frail;//���Ƽ�
	int CanDraw;//�Ƿ�ɼ�������
	int FlameBarrier;//��������Ч��
	int Juggernaut;//�Ʋ��ɵ�Ч��
	int Combust;//CombustЧ��
	int Metallicize;//������Ч��
	int RampageTime;//Rampageʹ�ô���
	int Barricade;//BarricadeЧ��
	int Brutality;//BrutalityЧ��
	int EnemyNum;//��������

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
	int EnemyHP;//����Ѫ��
	int EnemyBlock;//���ﻤ��
	int Damage1;//���﹥������1�˺�
	int AttackTimes1;//���﹥������1����
	int Damage2;//���﹥������2�˺�
	int AttackTimes2;//���﹥������2����
	int Damage3;//���﹥������3�˺�
	int AttackTimes3;//���﹥������3����

	int State_Weak;//����
	int State_Vulnerable;//����
	int State_Poison;//�ж�
	int State_Ritual;//��ʽ���غϽ����ӹ�
	int strength;//���������������˺�
	int intend;//�´�ִ������

	void debuffWeak(int n, StateVariables* player);//��n������
	void debuffMucus(int n, StateVariables* player);//��ճҺ��
	void debuffVulnerable(int n, StateVariables* player);//��n������
	void buffRitual();//��ʽЧ��
	void buffStrengthUp(unsigned int n);//��n����
	void buffFrail(int n, StateVariables* player);//��n���Ƽ�
};

class Cards
{
public:
	Cards(int cardnum, int EnergyCost);
	~Cards(void);
	unsigned int CardsNum;//���Ʊ��
	unsigned int EnergyCost;//����
	int EnergyConsume(int x, StateVariables* player);
	void Damage(int damage, StateVariables* player, Enemy* target, int n);
	void Defence(int block, StateVariables* player, Enemy* target);
};