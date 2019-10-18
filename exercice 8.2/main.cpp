#include <iostream>
#include <vector>
#include "dragon.h"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

int main() {

	std::ifstream i("cochons.json");
	json jpigs;
	i >> jpigs;
	i.close();

	std::ifstream b("dragon.json");
	json jdragon;
	b >> jdragon;
	b.close();
	
	
	
	Dragon dragon = Dragon(jdragon["health"], jdragon["attack"]);
	std::vector<Pig> pigs;

	const auto nbPig = 10;
	
	pigs.reserve(nbPig);
	for(auto i = 0; i < nbPig; i++)
	{
		pigs.emplace_back(Pig(jpigs["health"], jpigs["attack"]));
	}

	bool finish = false;
	while(!finish)
	{
		//Dragon attack
		for (auto& pig : pigs)
		{
			if(pig.IsAlive())
			{
				dragon.Attack(pig);
				break; //Dragon attack once
			}
		}
		
		//Pigs attack
		for (auto& pig : pigs)
		{
			pig.Attack(dragon);
		}

		//print Dragon
		dragon.Print();

		//print Pigs
		for (auto& pig : pigs)
		{
			pig.Print();
		}

		std::cout << "=======================\n";

		//Victory conditions
		if(!dragon.IsAlive())
		{
			finish = true;
		}

		bool allPigsDead = true;
		for (auto& pig : pigs)
		{
			if(pig.IsAlive())
			{
				allPigsDead = false;
				break;
			}
		}
		if(allPigsDead)
		{
			finish = true;
		}
	}
	system("pause");
	return 0;

}