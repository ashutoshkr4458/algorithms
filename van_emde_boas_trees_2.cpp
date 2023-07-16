//Code for van emde boas trees - insertion, find, min and max queries 
#include <bits/stdc++.h>
using namespace std;

class Van_Emde_Boas {

public:
	int universe_size;
	int minimum;
	int maximum;
	Van_Emde_Boas* summary;
	vector<Van_Emde_Boas*> clusters;

	int high(int x)
	{
		int div = ceil(sqrt(universe_size));
		return x / div;
	}

  int low(int x)
	{
		int mod = ceil(sqrt(universe_size));
		return x % mod;
	}

	int generate_index(int x, int y)
	{
		int ru = ceil(sqrt(universe_size));
		return x * ru + y;
	}

	// Constructor
	Van_Emde_Boas(int size)
	{
		universe_size = size;
		minimum = -1;
		maximum = -1;

    if (size <= 2) {
			summary = nullptr;
			clusters = vector<Van_Emde_Boas*>(0, nullptr);
		}
		else {
			int no_clusters = ceil(sqrt(size));
      
			summary = new Van_Emde_Boas(no_clusters);

			clusters = vector<Van_Emde_Boas*>(no_clusters, nullptr);

			for (int i = 0; i < no_clusters; i++) {
				clusters[i] = new Van_Emde_Boas(ceil(sqrt(size)));
			}
		}
	}
};


int VEB_minimum(Van_Emde_Boas* helper)
{
	return (helper->minimum == -1 ? -1 : helper->minimum);
}

int VEB_maximum(Van_Emde_Boas* helper)
{
	return (helper->maximum == -1 ? -1 : helper->maximum);
}

// Function to insert a key in the tree
void insert(Van_Emde_Boas* helper, int key)
{

	if (helper->minimum == -1) {
		helper->minimum = key;
		helper->maximum = key;
	}
	else {
		if (key < helper->minimum) {

			swap(helper->minimum, key);
		}

    if (helper->universe_size > 2) {


			if (VEB_minimum(helper->clusters[helper->high(key)]) == -1) {
				insert(helper->summary, helper->high(key));
        
				helper->clusters[helper->high(key)]->minimum = helper->low(key);
				helper->clusters[helper->high(key)]->maximum = helper->low(key);
			}
			else {
				insert(helper->clusters[helper->high(key)], helper->low(key));
			}
		}

		if (key > helper->maximum) {
			helper->maximum = key;
		}
	}
}

bool isMember(Van_Emde_Boas* helper, int key)
{

	if (helper->universe_size < key) {
		return false;
	}

	if (helper->minimum == key || helper->maximum == key) {
		return true;
	}
	else {

	
		if (helper->universe_size == 2) {
			return false;
		}
		else {

			return isMember(helper->clusters[helper->high(key)],
							helper->low(key));
		}
	}
}

// Driver code
int main()
{
	Van_Emde_Boas* veb = new Van_Emde_Boas(8);

	insert(veb, 2);
	insert(veb, 3);
	insert(veb, 6);

	cout << boolalpha;

	cout << isMember(veb, 3) << endl;

	cout << isMember(veb, 4) << endl;

	cout << VEB_maximum(veb) << endl;

	cout << VEB_minimum(veb) << endl;
}
