#pragma once
#include <map>
#include "Dijkstra.h"
#include "Barricade.h"
#include "PathNode.h"

class PathFinder :
	public Dijkstra
{
public:
	PathFinder();
	virtual ~PathFinder();

	virtual void Initialize(char* dataFile = nullptr) override;
	void Destroy();

	void Render();

	bool CheckBarricadeCollision(const D3DXVECTOR3& start, const D3DXVECTOR3& end);
	int FindNearestPathNode(const D3DXVECTOR3& position);
	void PathOptimize(std::list<int>& path, const D3DXVECTOR3& start, const D3DXVECTOR3& end);

	inline const D3DXVECTOR3& GetPathNodePosition(int index){ return path[index]->GetPosition(); }

protected:
	std::vector<PathNode*> path;
	std::vector<Barricade*> barricades;

	bool drawEdgeLine = true;
	std::vector<FVF_PositionColor> edgeLine;

	static const int PATH_NODE_COUNT = 8;
	static const int BARRICADE_COUNT = 3;

	UINT lineCount = 0;
};

