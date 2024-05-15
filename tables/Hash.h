#pragma once

#include<stack>
#include<vector>
using namespace std;

vector<int> prime;

void find_prime()
{
	vector<bool> primer(1e6 + 1, 1);
	primer[0] = 0;
	primer[1] = 0;
	for (long i = 0; i < 1e6 + 1; ++i)
	{
		if (primer[i])
		{
			prime.push_back(i);
			if (i * 1ll * i <= 1e6 + 1) for (long j = i * i; j < 1e6 + 1; j += i) primer[j] = false;
		}
	}
}

template<class Key, class Value, size_t f(string x, size_t mod)>
class Hash_table
{
	size_t size;
	Value* values;
	Key* keys;
	bool* pos;

public:

	Hash_table() { size = 13; values = new Value[size]; keys = new Key[size]; pos = new bool[size]; for (size_t i = 0; i < size; ++i) pos[size] = 0; }

	void re_Hash()
	{
		stack<pair<Key, Value>> st;
		for (size_t i = 0; i < size; ++i) st.push(mp(keys[i], values[i]));

		delete[] values;
		delete[] keys;
		delete[] pos;

		size_t new_size = upper_bound(prime.begin(), prime.end(), size) - prime.begin();
		if (new_size == size) throw "errror";
		else
		{
			size = new_size;
			values = new Value[size]; keys = new Key[size]; pos = new bool[size]; for (size_t i = 0; i < size; ++i) pos[size] = 0;
			while (!st.empty())
			{
				pair<Key, Value> x = st.top();
				st.pop();

				this[x.first] = x.second;
			}
		}

	}

	Value& operator[] (Key key)
	{
		size_t id = f(key, size);
		size_t start = id;
		bool find = true;
		while (pos[id] != 0 && keys[id] != key)
		{
			++id;
			id %= size;
			if (id == start) { re_Hash(); find = false; break; }
		}
		if (!find) for (size_t i = 0; i < size; ++i) if (!pos[i]) { id = i; break; }

		if (pos[id] == 0) pos[id] = 1, keys[id] = key;
		return values[id];
	}

	void erase(Key key)
	{
		size_t id = f(key, size);
		size_t start = id;
		bool find = true;

		while (pos[id] != 0 && keys[id] != key)
		{
			++id;
			id %= size;
			if (id == start) { find = false; break; }
		}

		if (!find) return;

		pos[id] = 0;
	}

	bool find(Key key)
	{
		size_t id = f(key, size);
		size_t start = id;
		bool find = true;

		while (pos[id] != 0 && keys[id] != key)
		{
			++id;
			id %= size;
			if (id == start) { find = false; break; }
		}

		return find && pos[id];
	}

	~Hash_table() { delete[] values; delete[] keys; delete[] pos; }
};