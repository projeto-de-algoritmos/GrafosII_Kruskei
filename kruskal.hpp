#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

std::vector<std::pair<int, std::pair<int, int>>> edgelist;

class UnionFind
{
private:
	std::vector<int> parent, rank;
public:
	UnionFind(int N)
	{
		rank.assign(N+1, 0);
		parent.assign(N+1, 0);

		for (int i = 0; i <= N; i++)
			parent[i] = i;
	}

	int find(int index)
	{
		while (index != parent[index])
			index = parent[index];

		return index;
	}

	bool is_in_same_set(int x, int y)
	{
		return find(x) == find(y);
	}

	void set_union(int x, int y)
	{
		if (is_in_same_set(x, y))
			return;

		int a = find(x);
		int b = find(y);

		if (rank[a] > rank[b])
			parent[b] = a;
		else
		{
			parent[a] = b;
			if (rank[a] == rank[b])
				rank[b]++;
		}
	}
};


int kruskal(int N, int M)
{
	int cost = 0;
	UnionFind uf(N);

	// {weight, {u, v}} 
	std::pair<int, std::pair<int, int>> edge;

	std::sort(edgelist.begin(), edgelist.end());

	for (int i = 0; i < M; i++)
	{
		edge = edgelist[i];

		if (not uf.is_in_same_set(edge.second.first, edge.second.second))
		{
			cost+=edge.first;

			uf.set_union(edge.second.first, edge.second.second);
		}
	}

	return cost;
}

