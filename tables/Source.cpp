#include<iostream>
#include<string>
#include "Hash.h"
#include "AVLtree.h";
#include "vector_table.h"
#include "list_table.h"

using namespace std;

size_t f1(string x, size_t mod)
{
	size_t id = 0;
	for (auto i : x)id += i, id %= mod;
	
	return id;
}

size_t f2(string x, size_t mod)
{
	int x0 = 13;
	size_t id = 0;
	int last = 1;
	for (auto i : x)id += i * last, id %= mod, last *= x0;

	return id;
}

int main()
{
    AVL_tree<int, int> t;
    int array[] = { 100,55,50,45,47,70,80,78,77,79,82,81,83,150,140,
                     135,142,143,180,170,165,160,175,173,200,190,195,500,1000,1500,2000,3000,4000,5000,6000,7000,8000,9000 };

    pair<int, int> array1[38];
    for (int i = 0; i < 38; i++)  array1[i] = make_pair(array[i], i);

    for (int i = 0; i < 38; i++)
    {
        t.insert(array1[i]);
    }
    std::cout << "insertion done" << std::endl;
    t.display();


    t.erase(make_pair(45, 0));
    t.erase({ 47,0 });
    t.erase({ 50 ,0 });
    t.erase({ 55 ,0 });
    t.erase({ 70,0 });
    t.erase({ 77,0 });
    t.erase({ 78,0 });
    t.erase({ 79,0 });
    t.erase({ 80,0 });
    t.erase({ 81,0 });
    t.erase({ 82,0 });
    t.erase({ 83,0 });
    t.erase({ 100,0 });
    t.erase({ 135,0 });

    t.erase({ 140 ,0});
    t.display();
   
}
