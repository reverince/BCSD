#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <time.h>
using namespace std;

enum MENU { NONE, MAP, SHOP, INVENTORY, EXIT };
enum MAP_TYPE { MAP_NONE, MAP_EASY, MAP_NORMAL, MAP_HARD, MAP_BACK };
enum JOB { JOB_NONE, JOB_KNIGHT, JOB_ARCHER, JOB_WIZARD, JOB_END };
enum BATTLE { BATTLE_NONE, BATTLE_ATTACK, BATTLE_BACK };
enum ITEM_TYPE { ITEM_NONE, ITEM_WEAPON, ITEM_ARMOR, ITEM_BACK };
enum SHOP_MENU { SHOP_NONE, SHOP_WEAPON, SHOP_ARMOR, SHOP_BACK };

const int NAME_SIZE = 32;
const int DESC_SIZE = 256;
const int INVENTORY_SIZE = 20;
const int SHOP_WEAPON_SIZE = 3;
const int SHOP_ARMOR_SIZE = 3;

struct Item {
	char name[NAME_SIZE];
	ITEM_TYPE type;
	char typeName[NAME_SIZE];
	char desc[DESC_SIZE];
	int min, max, buyPrice, sellPrice;
};

struct Inventory {
	int gold;
	Item items[INVENTORY_SIZE];
	int cntItem;
};

struct Player {
	char name[NAME_SIZE];
	JOB job;
	char jobName[NAME_SIZE];
	int attackMin, attackMax;
	int armorMin, armorMax;
	int hp, hpMax, mp, mpMax;
	int level, exp;
	Inventory inventory;
};

struct Monster {
	char name[NAME_SIZE];
	int attackMin, attackMax;
	int armorMin, armorMax;
	int hp, hpMax, mp, mpMax;
	int level, exp;
	int goldMin, goldMax;
};

int main() {
	srand((unsigned int)time(0));
	int ipt;

	// 플레이어 정보 설정
	Player player = { };
	cout << "이름: ";
	cin.getline(player.name, NAME_SIZE - 1);
	player.level = 1;
	player.exp = 0;
	player.inventory.gold = 10000;
	while (true) {
		cout << "1. 기사 / 2. 궁수 / 3. 마법사\n";
		cout << "직업을 선택하세요: ";
		cin >> ipt;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		if (ipt > JOB_NONE && ipt < JOB_END) {
			player.job = (JOB)ipt;
			switch (player.job) {
			case JOB_KNIGHT:
				strcpy_s(player.jobName, "기사");
				player.attackMin = 5;
				player.attackMax = 10;
				player.armorMin = 15;
				player.armorMax = 20;
				player.hpMax = player.hp = 500;
				player.mpMax = player.mp = 100;
				break;
			case JOB_ARCHER:
				strcpy_s(player.jobName, "궁수");
				player.attackMin = 10;
				player.attackMax = 15;
				player.armorMin = 10;
				player.armorMax = 15;
				player.hpMax = player.hp = 400;
				player.mpMax = player.mp = 200;
				break;
			case JOB_WIZARD:
				strcpy_s(player.jobName, "마법사");
				player.attackMin = 15;
				player.attackMax = 20;
				player.armorMin = 5;
				player.armorMax = 10;
				player.hpMax = player.hp = 300;
				player.mpMax = player.mp = 300;
				break;
			}
			break;
		}
	}

	// 몬스터 정보 설정
	Monster monsters[MAP_BACK - 1] = { };

	// 고블린
	strcpy_s(monsters[0].name, "고블린");
	monsters[0].attackMin = 20;
	monsters[0].attackMax = 30;
	monsters[0].armorMin = 2;
	monsters[0].armorMax = 5;
	monsters[0].hpMax = monsters[0].hp = 100;
	monsters[0].mpMax = monsters[0].mp = 10;
	monsters[0].level = 1;
	monsters[0].exp = 1000;
	monsters[0].goldMin = 500;
	monsters[0].goldMax = 1500;
	// 트롤
	strcpy_s(monsters[1].name, "트롤");
	monsters[1].attackMin = 80;
	monsters[1].attackMax = 130;
	monsters[1].armorMin = 60;
	monsters[1].armorMax = 90;
	monsters[1].hpMax = monsters[1].hp = 2000;
	monsters[1].mpMax = monsters[1].mp = 100;
	monsters[1].level = 5;
	monsters[1].exp = 7000;
	monsters[1].goldMin = 6000;
	monsters[1].goldMax = 8000;
	// 드래곤
	strcpy_s(monsters[2].name, "드래곤");
	monsters[2].attackMin = 250;
	monsters[2].attackMax = 500;
	monsters[2].armorMin = 200;
	monsters[2].armorMax = 400;
	monsters[2].hpMax = monsters[2].hp = 30000;
	monsters[2].mpMax = monsters[2].mp = 20000;
	monsters[2].level = 10;
	monsters[2].exp = 30000;
	monsters[2].goldMin = 20000;
	monsters[2].goldMax = 50000;

	// 상점 판매 아이템 목록
	Item shopWeapons[SHOP_WEAPON_SIZE] = { };
	Item shopArmors[SHOP_ARMOR_SIZE] = { };

	while (true) {
		system("cls");
		cout << "=====< 메뉴 >=====\n";
		cout << "1. 맵 / 2. 상점 / 3. 가방 / 4. 종료\n";
		cout << "메뉴를 선택하세요: ";
		cin >> ipt;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}

		if (ipt == EXIT) exit(0);
		switch (ipt) {
		case MAP:
			while (true) {
				system("cls");
				cout << "=====< 맵 >=====\n";
				cout << "1. 쉬움 / 2. 보통 / 3. 어려움 / 4. 취소\n";
				cout << "맵을 선택하세요: ";
				cin >> ipt;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}

				if (ipt == MAP_BACK) break;
				Monster monster = monsters[ipt - 1];
				switch (ipt) {
				case MAP_EASY:
					cout << "=====< 쉬움 >=====\n";
					break;
				case MAP_NORMAL:
					cout << "=====< 보통 >=====\n";
					break;
				case MAP_HARD:
					cout << "=====< 어려움 >=====\n";
					break;
				}

				while (true) {
					system("cls");
					// 플레이어 정보 출력
					cout << "이름: " << player.name << "\t직업: " << player.jobName << '\n';
					cout << "레벨: " << player.level << "\t경험치: " << player.exp << '\n';
					cout << "공격력: " << player.attackMin << " ~ " << player.attackMax << '\t';
					cout << "방어력: " << player.armorMin << " ~ " << player.armorMax << '\n';
					cout << "체력: " << player.hp << " / " << player.hpMax << '\t';
					cout << "마나: " << player.mp << " / " << player.mpMax << '\n';
					cout << "골드: " << player.inventory.gold << "\n";

					// 몬스터 정보 출력
					cout << "=====< Monster >=====\n";
					cout << "이름: " << monster.name << "\t레벨: " << monster.level << '\n';
					cout << "공격력: " << monster.attackMin << " ~ " << monster.attackMax << '\t';
					cout << "방어력: " << monster.armorMin << " ~ " << monster.armorMax << '\n';
					cout << "체력: " << monster.hp << " / " << monster.hpMax << '\t';
					cout << "마나: " << monster.mp << " / " << monster.mpMax << '\n';

					cout << "1. 공격 / 2. 도망\n";
					cout << "메뉴를 선택하세요: ";
					cin >> ipt;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}
					if (ipt == BATTLE_BACK) break;
					switch (ipt) {
					case BATTLE_ATTACK:
						int attack = player.attackMin + rand() % (player.attackMax - player.attackMin + 1);
						int armor = monster.armorMin + rand() % (monster.armorMax - monster.armorMin + 1);
						int damage = attack - armor;

						damage = (damage < 1) ? 1 : damage;  // 최소 1 데미지
						monster.hp -= damage;
						cout << player.name << "(이)가 " << monster.name << "에게 " << damage << "피해를 입혔습니다.\n";

						if (monster.hp <= 0) {
							cout << monster.name << "(이)가 죽었습니다.\n";
							player.exp += monster.exp;
							int gold = monster.goldMin + rand() % (monster.goldMax - monster.goldMin + 1);
							player.inventory.gold += gold;
							cout << monster.exp << " 경험치를 획득했습니다.\n";
							cout << gold << " 골드를 획득했습니다.\n";

							monster.hp = monster.hpMax;
							monster.mp = monster.mpMax;
							break;
						}

						// 몬스터 턴
						attack = monster.attackMin + rand() % (monster.attackMax - monster.attackMin + 1);
						armor = player.armorMin + rand() % (player.armorMax - player.armorMin + 1);
						damage = attack - armor;

						damage = (damage < 1) ? 1 : damage;  // 최소 1 데미지
						player.hp -= damage;
						cout << monster.name << "(이)가 " << player.name << "에게 " << damage << "피해를 입혔습니다.\n";

						if (player.hp <= 0) {
							cout << player.name << "(이)가 죽었습니다.\n";
							int exp = (int)(player.exp * 0.1f);
							int gold = (int)(player.inventory.gold * 0.1f);
							player.exp -= exp;
							player.inventory.gold -= gold;
							cout << exp << " 경험치를 잃었습니다.\n";
							cout << gold << " 골드를 잃었습니다.\n";

							player.hp = player.hpMax;
							player.mp = player.mpMax;
						}

						break;
					}

					system("pause");
				}  // end of while (true)
			}
			break;

		case SHOP:
			while (true) {
				system("cls");
				cout << "=====< 상점 >=====\n";
				cout << "1. 무기 / 2. 방어구 / 3. 취소\n";
				cout << "메뉴를 선택하세요: ";
				cin >> ipt;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}

				if (ipt == SHOP_BACK) break;
				switch (ipt) {
				case SHOP_WEAPON:
					cout << "=====< 무기 상점 >=====\n";
					break;
				case SHOP_ARMOR:
					break;
				}
			}
			break;

		case INVENTORY:
			break;

		default:
			cout << "잘못 입력했습니다.\n";
			break;
		}
	}
	return 0;
}
