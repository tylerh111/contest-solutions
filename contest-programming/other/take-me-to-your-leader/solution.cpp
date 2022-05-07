#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#include <unordered_map>
#include <unordered_set>

//using namespace std;

std::string leader(int n);


int main() {
	
	


	int n;
	std::cin >> n;
	std::string solution = leader(n);
	std::cout << solution;

	return 0;
}


std::string leader(int n) {

	std::unordered_map<std::string, std::string> map;
	std::unordered_map<std::string, int> mapOccur;

	int *nameCounter = new int[n];
	
	for (int i = 0; i < n; i++) {
		std::string name, boss;
		std::cin >> name;
		std::cin >> boss;
		
		map[name] = boss;
		map.emplace(boss, "");
	}

	int maxOccurences = 0;
	//std::string* currBoss = new std::string("");
	std::string currBoss = "";

	//WORK ON THIS!!!!!
	for (auto s : map) {
		//std::string *nextString = new std::string(s.first);
		std::string nextString = s.first;
		int count = 0;

		while (!map[nextString].empty()) {
			if (mapOccur.emplace(nextString, 0).second) count++;
			nextString = map[nextString];
			//count++;
		}

		mapOccur[nextString] += count;

		if (nextString == currBoss)
			maxOccurences += count;
		else if (mapOccur[nextString] > maxOccurences) {
			maxOccurences = mapOccur[nextString];
			currBoss = nextString;
		}
		else if (mapOccur[nextString] == maxOccurences && nextString < currBoss)
			currBoss = nextString;
	}

	
	delete nameCounter;

	return currBoss;
}


