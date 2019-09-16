#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>


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


void kruskal(int N, int M, std::vector<std::pair<int, std::pair<int, int>>> & edgelist)
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
			int u = edge.second.first, v = edge.second.second;
			if (u < v)
				std::cout << u << " " << v << "\n";
			else
				std::cout << v << " " << u << "\n";

			cost+=edge.first;

			uf.set_union(edge.second.first, edge.second.second);
		}
	}

}


int main()
{
	int n, m;

	int t = 1;
	while(std::cin >> n >> m)
	{
		if (n == 0) break;

		std::cout << "Teste " << t++ << "\n";

		std::vector<std::pair<int, std::pair<int, int>>> edgelist(m);

		for (int i = 0; i < m; i++)
		{
			int u, v, w; std::cin >> u >> v >> w;
			edgelist[i] = {w, {u, v}};

		}

		kruskal(n, m, edgelist);
		std::cout << "\n";
	}
}
