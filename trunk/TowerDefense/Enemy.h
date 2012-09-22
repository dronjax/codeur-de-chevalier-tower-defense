#ifndef __ENEMY__
#define __ENEMY__

class Enemy
{
	private:
		int Speed;
		int aSpeed;
		int Health;
		int aHealth;
		int x;
		int y;
		int Price;
		int Income;
		int Reward;
		char * Name;
		char * Element;
	public:
		Enemy();
		Enemy(char*);
		~Enemy();
		Enemy(const Enemy&);
		Enemy& operator = (const Enemy&);
		
		int getSpeed();
		int getaSpeed();
		int getHealth();
		int getaHealth();
		int getx();
		int gety();
		int getPrice();
		int getIncome();
		int getReward();
		char * getName();
		char * getElement();
		
		void setSpeed(int);
		void setaSpeed(int);
		void setHealth(int);
		void setaHealth(int);
		void setx(int);
		void sety(int);
		void setPrice(int);
		void setIncome(int);
		void setReward(int);
		void setName(char*);
		void setElement(char*);
		
		Enemy Upgrade (char*);
};

#endif