#include<iostream>

#include<list>
#include<queue>


//north = 0, east = 1, south = 2, west = 3
inline short checker(long* arr, long ndx, int len, short dir, long lookup) {
	switch (dir) {
	case 0: 
		if (arr[ndx - len] == -1) return 2;
		if (arr[ndx - len] > lookup + 1 || arr[ndx - len] == 0) {
			arr[ndx - len] = lookup + 1;
			return 1;
		}
		break;
	case 1: 
		if (arr[ndx + 1] == -1) return 2;
		if (arr[ndx + 1] > lookup + 1 || arr[ndx + 1] == 0) {
			arr[ndx + 1] = lookup + 1;
			return 1;
		}
		break;
	case 2: 
		if (arr[ndx + len] == -1) return 2;
		if (arr[ndx + len] > lookup + 1 || arr[ndx + len] == 0) {
			arr[ndx + len] = lookup + 1;
			return 1;
		}
		break;
	case 3:	
		if (arr[ndx - 1] == -1) return 2;
		if (arr[ndx - 1] > lookup + 1 || arr[ndx - 1] == 0) {
			arr[ndx - 1] = lookup + 1;
			return 1;
		}
		break;
	default: return 0;
	}
	return 0;
}




inline int codeInput(char in) {
	switch (in) {
	case '*': return 0;
	case 'k': return -1;
	case 'o': return -2;
	default: std::exit(100);
	}
}

//Water is your new best friend
long waterBFS(long* arr, std::queue<long, std::list<long>>* q, long lookup, int w, int l) {

	//stops if there is no path to end
	while (!q->empty()) {

		long qSize = q->size();
		for (long i = 0; i < qSize; i++) {
			
			long nextNdx = q->front();
			q->pop();

			int y = nextNdx / l; // y pos on board
			int x = nextNdx % l; // x pos on board
			
			//check above
			if (y != 0) {
				switch (checker(arr, nextNdx, l, 0, lookup)) {
				case 0: break;
				case 1: q->push(nextNdx - l); break;
				case 2: return lookup + 1; break;
				default: std::exit(100); 
				}
			}
			//check right
			if (x != l - 1) {
				switch (checker(arr, nextNdx, l, 1, lookup)) {
				case 0: break;
				case 1: q->push(nextNdx + 1); break;
				case 2: return lookup + 1; break;
				default: std::exit(100);
				}
			}
			//check below
			if (y!= w - 1) {
				switch (checker(arr, nextNdx, l, 2, lookup)) {
				case 0: break;
				case 1: q->push(nextNdx + l); break;
				case 2: return lookup + 1; break;
				default: std::exit(100);
				}
			}
			//check left
			if (x != 0) {
				switch (checker(arr, nextNdx, l, 3, lookup)) {
				case 0: break;
				case 1: q->push(nextNdx - 1); break;
				case 2: return lookup + 1; break;
				default: std::exit(100);
				}
			}
		}
		lookup++;
	}
	return -5;
}


int main() {

	//input
	int w, l;
	std::cin >> w;
	std::cin >> l;

	//board
	long boardSize = w * l;
	long* arr = new long[boardSize];

	//indices to be checked
	std::queue<long, std::list<long>> q;

	//fills board
	//also fills the queue around the w's
	for (long i = 0; i < boardSize; i++) {
		char input;
		std::cin >> input;

		int y = i / l; // y pos on board
		int x = i % l; // x pos on board

		//initializing queue
		if (input == 'w') {
			arr[i] = -3;
			q.push(i);
		}
		else arr[i] = codeInput(input);
	}
	
	//forming solution
	int output = waterBFS(arr, &q, 0, w, l);
	if (output == -5) std::cout << ":-p";
	else std::cout << output;

	delete[] arr;

	return 0;
}



