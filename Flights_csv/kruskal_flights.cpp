#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

std::map<std::string, int> dict;
std::map<int, std::string> access;

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


int kruskal(int N, int M, std::vector<std::pair<int, std::pair<int, int>>> & edgelist)
{
	int cost = 0;
	UnionFind uf(N);

	// {weight, {u, v}} 
	std::pair<int, std::pair<int, int>> edge;

	//std::sort(edgelist.begin(), edgelist.end());

	for (int i = 0; i < M; i++)
	{
		edge = edgelist[i];

		if (not uf.is_in_same_set(edge.second.first, edge.second.second))
		{
			cost+=edge.first;

			std::cout << "Adicionando rota de " << access[edge.second.first] << " a " << access[edge.second.second] << " com comprimento " << edge.first << "km\n";
			uf.set_union(edge.second.first, edge.second.second);
		}
	}

	return cost;
}

int main()
{
	std::ifstream csv_file("flights.csv");
	std::set<std::pair<int, std::pair<int, int>>> list;


	int idx = 1;
	while (not csv_file.eof())
	{
		std::string origin, dest, dist;

		std::getline(csv_file, origin, ',');
		std::getline(csv_file, dest, ',');
		std::getline(csv_file, dist);
		
		int aux;
		try{
			aux = std::stoi(dist);
			if (dict[origin] == 0) {
				dict[origin] = idx;
				access[idx++] = origin;
			}
			if (dict[dest] == 0)
			{
				dict[dest] = idx;
				access[idx++] = dest;
			}
			list.insert({aux, {dict[origin], dict[dest]}});
		}catch(std::invalid_argument)
		{
		}

	}

	std::vector<std::pair<int, std::pair<int, int>>> edgelist(list.begin(), list.end());

	int answer = kruskal(idx-1, edgelist.size(), edgelist);

	std::cout << "Menor distancia para percorrer todos os aeroportos: " << answer << "km\n";
}
