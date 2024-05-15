#pragma once

template<class Key,class Value>
class vector_table
{
	size_t size;
	vector<pair<Key,Value>> v;

public:

	void add(pair<Key, Value> x)
	{
		int l = 0,r=size;
		int id=-1;
		while (l <= r)
		{
			int m = (l + r) / 2;
			if (v[m] < x.first) l = m + 1;
			else
			{
				if (v[m] == x.first) { id = m; break; }
				r = m - 1;
			}
		}

		if (id == -1) ++size, v.emplace_back(x), sort(v.begin(), v.end());
	}

	void erase(pair<Key, Value> x)
	{
		int l = 0, r = size;
		int id = -1;
		while (l <= r)
		{
			int m = (l + r) / 2;
			if (v[m] < x.first) l = m + 1;
			else
			{
				if (v[m] == x.first) { id = m; break; }
				r = m - 1;
			}
		}

		if (id == -1) return;

		--size;
		v.erase(x);
	}

	bool find(Key x)
	{
		int l = 0, r = size;
		int id = -1;
		while (l <= r)
		{
			int m = (l + r) / 2;
			if (v[m] < x.first) l = m + 1;
			else
			{
				if (v[m] == x.first) { id = m; break; }
				r = m - 1;
			}
		}

		if (id == -1) return 0;
		else return 1;
	}

};