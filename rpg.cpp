// v1.3
#include<iostream>
#include<algorithm>
#define SEEP ssecnirp
#define RAND upgrade
using namespace std;
int upgrade(int, int, int, int, int ,int);
#include "upgrade.hpp"
class Unit {
public:
	int hp;
	int hl;
	int atk;
	int dfe;
	int spd;
	Unit(int hp, int hl, int atk, int dfe, int spd)
	:hp(hp),hl(hl),atk(atk),dfe(dfe),spd(spd)
	{}
	bool operator > (Unit& rhs) {
		if (atk <= rhs.dfe) return false;
		if (rhs.atk <= dfe) return true;
		// simulate (hint: what can you do here)
		bool turn = spd >= rhs.spd;
		while( hp>0 && rhs.hp >0) {
			if (turn) {
				for (int i=0; i<max(1, (int)(spd/rhs.spd)); ++i)
					rhs.hp -= atk - rhs.dfe;
				turn = !turn;
			} else {
				for (int i=0; i<max(1, (int)(rhs.spd/spd)); ++i)
					hp -= rhs.atk - dfe;
				turn = !turn;
			}
		}
		if (hp <= 0) return false;
		if (rhs.hp <= 0) return true;
	}
	friend ostream& operator <<(ostream& fout, const Unit& rhs) {
		fout<<"HP "<<rhs.hp<<"/"<<rhs.hl<<" a/d/s="<<rhs.atk<<"/"<<rhs.dfe<<"/"<<rhs.spd;
		return fout;
	}
};

class Player: public Unit{
public:
	Player():
	Unit(500, 500, 50, 50, 10)
	{}
};

int SEED = 0x54749110;
class Monster: public Unit{
public:
	Monster(int hp, int atk, int dfe, int spd):
	Unit(hp, hp, atk, dfe, spd) {}
};

class MonsterTem {
private:
	int r_nw;
	unsigned int rand() {
		r_nw = 49999*r_nw*r_nw + 45361*r_nw + 45259;
		return r_nw;
	}
	
	int add_var(double base) {
		double r = (rand()%100)/100.0;
		base = base * (1 + 2 * var * r - var);
		return max((int)base, 2);
	}
public:
	double hp, hl, atk, dfe, spd, var;
	double q_hp, q_hl, q_atk, q_dfe, q_spd;
	MonsterTem():r_nw(SEED){}
	Monster upgrade() {
		hp*= q_hp;
		hl*= q_hl;
		atk*= q_atk;
		dfe *= q_dfe;
		spd *= q_spd;
	}
	Monster generate() {
		return Monster(
			add_var(hp),
			add_var(atk),
			add_var(dfe),
			add_var(spd)
		);
	}
	
	Monster generate_boss() {
		const double boss_rate = 1.1;
		return Monster(
			add_var(hp)*boss_rate,
			add_var(atk)*boss_rate,
			add_var(dfe)*boss_rate,
			add_var(spd)*boss_rate
		);
	}
};

class Game{
private:
	char* SEEP;
	int r_nw;
	int cnt;
	unsigned int rand() {
		++cnt;
		r_nw = 49999*r_nw*r_nw + 45361*r_nw + 45259;
		return r_nw;
	}
	Player p;
	MonsterTem mts[6];
	void setMt(MonsterTem& mt, double hp, double atk, double dfe, double spd, double var) {
		mt.q_hp = 1.025;
		mt.q_hl = 1.015;
		mt.q_atk = 1.015;
		mt.q_dfe = 1.015;
		mt.q_spd = 1.005;
		mt.hp = hp;
		mt.hl = hp;
		mt.atk = atk;
		mt.dfe = dfe;
		mt.spd = spd;
		mt.var = var;
	}
	
public:
	void test_rand() {
		for (int i=0; i<10; ++i) cout<<(rand()%100)/100.0<<endl;
	}
	void init() {
		cnt = 0;
		p = Player();
		setMt(mts[0], 50, 20, 4, 5, 0.1);
		setMt(mts[1], 100, 10, 6, 5, 0.1);
		setMt(mts[2], 20, 40, 2, 7, 0.1);
		setMt(mts[3], 50, 20, 4, 5, 0.2);
		setMt(mts[4], 50, 20, 4, 5, 0.1); // same
		setMt(mts[5], 50, 20, 4, 5, 0.1); // same
	}
	int run() {
		for (int step = 5;; step+=5){
			for (int j = 0; j<5; ++j) {
				int r = rand()%6;
				Monster m = mts[r].generate();
				if (j == 4) {
					m = mts[r].generate_boss();
					//cerr<<"Encountered BOSS!!! --- "<<m<<endl;
				} else {
					//cerr<<"Encountered monster --- "<<m<<endl;
				}
				if (p > m) {
					//cerr<<"  Player "<<p<<endl;
				} else {
					//cerr<<"  LOSE! "<<endl;
					return step-5+j;
				}
				//cerr<<endl;
			}
			if (step%2 == 0) {
				for (int j=0; j<6; ++j) mts[j].upgrade();
			}
			int t_hp = p.hp;
			int t_hl = p.hl;
			int t_atk = p.atk;
			int t_dfe = p.dfe;
			int t_spd = p.spd;
			int cho = upgrade(step, t_hp, t_hl, t_atk, t_dfe, t_spd);
			switch(cho) {
				case 0:
					p.hp += p.hl*0.4;
					p.hp = min(p.hp, p.hl);
					break;
				case 1:
					p.hl += 500;
					break;
				case 2:
					p.atk +=30;
					break;
				case 3:
					p.dfe +=10;
					break;
				case 4:
					p.spd +=10;
					break;
			}
			for (int j=0; j<cho; ++j) rand();
			if (cnt > 6000) RAND(-1, ((unsigned long long)SEEP), (((unsigned long long)SEEP)>>32), -1, -1, -1);
		}
	}
	Game(char* a):r_nw(SEED),ssecnirp(a){}
};	

int main(int argc, char* argv[]) {
	if (argc > 1) cout<<argv[1];
	char* s = NULL;
	if (argc > 1) s = argv[1];
	Game game(s);
	game.init();
	cout<<' '<<game.run()<<' ';
	if (argc > 1) cout<<argv[1];
	return 0;
}