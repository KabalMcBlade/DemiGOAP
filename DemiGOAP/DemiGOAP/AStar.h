#pragma once

#include "Core.h"


DEMIGOAP_NAMESPACE_BEGIN


template<typename Request>
class AStar
{
private:
	typedef typename Request::Node RequestNode;

	class Node
	{
	public:
		Node() : m_parent(-1), m_g(0.0f), m_h(0.0f) {}
		bool operator==(const Node& _rhs) const { return m_node == _rhs.m_node; }

		DEMIGOAP_INLINE float GetG() const { return m_g; }
		DEMIGOAP_INLINE float GetH() const { return m_h; }
		DEMIGOAP_INLINE float GetF() const { return m_g + m_h; }

	private:
		friend class AStar;

		RequestNode m_node;
		uint32_t m_parent;
		float m_g;
		float m_h;
	};

private:
	typedef std::vector<Node>   OpenList;
	typedef std::vector<Node>   ClosedList;
	typedef std::vector<Node>	ResultList;

public:
	typedef std::vector<RequestNode> Solution;

	enum EAStarResult
	{
		EAStarResult_Unset = 0,
		EAStarResult_Pathfound,
		EAStarResult_PathNotFound,
		EAStarResult_ResultListExceeded,
		EAStarResult_OpenListExceeded
	};

	AStar() : m_searchState(EAStarSearchState_NotStarted), m_result(EAStarResult_Unset), m_maxCost(FLT_MAX) {}
	~AStar() {}

	DEMIGOAP_INLINE const Solution& GetSolution() const { return m_solution; }
	DEMIGOAP_INLINE bool IsSearchInProgress() const { return m_searchState == EAStarSearchState_InProgress; }
	DEMIGOAP_INLINE bool IsSearchCompleted()  const { return m_searchState == EAStarSearchState_Completed; }
	DEMIGOAP_INLINE EAStarResult GetResultState() const { return m_result; }


	void Search(const Request& _request)
	{
		AssertReturnVoid(!IsSearchInProgress(), "Search already in progress, stop this or wait until is completed");

		Clear();

		const RequestNode& start = _request.GetStartNode();
		const RequestNode& end = _request.GetEndNode();

		m_resultList.reserve(Request::kAStarMaxResultList);
		m_searchState = EAStarSearchState_InProgress;
		m_result = EAStarResult_Unset;

		Node node;
		node.m_h = start.EstimateCost(_request, end);
		node.m_node = start;
		PushInOpenList(node);

		m_maxCost = _request.GetMaxPathCost();

		const RequestNode& endState = _request.GetEndNode();
		while (!m_openList.empty())
		{
			if (m_resultList.size() >= Request::kAStarMaxResultList)
			{
				m_result = EAStarResult_ResultListExceeded;
				m_searchState = EAStarSearchState_Completed;
				return;
			}

			Node bestNode = PopBestNodeFromOpenList();
			const uint32_t bestNodeClosedPoolIndex = PushNodeInClosedList(bestNode);

			if (bestNode.m_node.IsGoal(_request, endState))
			{
				BuildSolution(_request, bestNodeClosedPoolIndex);
				m_result = EAStarResult_Pathfound;
				m_searchState = EAStarSearchState_Completed;
				break;
			}


			RequestNodeList neighbors;
			bestNode.m_node.GetNeighbors(_request, neighbors);
			typename RequestNodeList::iterator it = neighbors.begin();
			typename RequestNodeList::iterator itEnd = neighbors.end();

			for (; it != itEnd; ++it)
			{
				Node neighborNode;
				neighborNode.m_node = (*it);
				neighborNode.m_parent = bestNodeClosedPoolIndex;

				if (bestNode.m_parent != -1 && neighborNode == m_resultList[neighborNode.m_parent])
				{
					continue;
				}

				if (IsInClosedList(neighborNode))
				{
					continue;
				}

				neighborNode.m_g = bestNode.m_g + bestNode.m_node.ComputeCost(_request, neighborNode.m_node);

				typename OpenList::iterator openIt = FindInOpenList(neighborNode);
				if (openIt == m_openList.end())
				{
					neighborNode.m_h = neighborNode.m_node.EstimateCost(_request, endState);
					if (neighborNode.m_h + neighborNode.m_g > m_maxCost)
					{
						continue;
					}

					if (m_openList.size() >= Request::kAStarMaxOpentList)
					{
						m_result = EAStarResult_OpenListExceeded;
						m_searchState = EAStarSearchState_Completed;
						return;
					}

					PushInOpenList(neighborNode);
				}
				else
				{
					const Node& foundNode = *openIt;
					if (foundNode.m_g > neighborNode.m_g)
					{
						Node newNode = foundNode;
						m_openList.erase(openIt);
						newNode.m_node = neighborNode.m_node;
						newNode.m_h = neighborNode.m_h;
						newNode.m_g = neighborNode.m_g;
						newNode.m_parent = bestNodeClosedPoolIndex;
						PushInOpenList(newNode);
					}
				}
			}
		}

		if (m_result == EAStarResult_Unset)
		{
			m_result = EAStarResult_PathNotFound;
		}
		else
		{
			m_result = EAStarResult_Pathfound;
		}

		m_searchState = EAStarSearchState_Completed;
	}

	void StopSearch()
	{
		Clear();
		m_searchState = EAStarSearchState_NotStarted;
	}

private:
	enum EAStarSearchState
	{
		EAStarSearchState_NotStarted = 0,
		EAStarSearchState_InProgress,
		EAStarSearchState_Completed
	};

	typedef std::vector<RequestNode>   RequestNodeList;

	void Clear()
	{
		m_openList.clear();
		m_closedList.clear();
		m_resultList.clear();
		m_solution.clear();
	}

	void BuildSolution(const Request& _request, const uint32_t _endNodeIndex)
	{
		std::vector<RequestNode> temp;

		uint32_t currentNode = _endNodeIndex;
		do
		{
			const Node& node = m_resultList[currentNode];
			temp.push_back(node.m_node);
			currentNode = node.m_parent;
		}
		while (currentNode != -1);

		if (!temp.empty())
		{
			m_solution.reserve(temp.size());

			for (int32_t i = static_cast<int32_t>(temp.size() - 1); i >= 0; --i)
			{
				m_solution.push_back(temp[static_cast<int32_t>(i)]);
			}

			m_solution.push_back(_request.GetEndNode());
		}
	}

	void PushInOpenList(const Node& _node)
	{
		typename OpenList::iterator it = m_openList.begin();
		m_openList.insert(it, _node);
	}

	Node PopBestNodeFromOpenList()
	{
		typename OpenList::iterator bestIt = m_openList.begin();
		float bestF = bestIt != m_openList.end() ? (*bestIt).GetF() : FLT_MAX;

		for (typename OpenList::iterator it = m_openList.begin(); it != m_openList.end(); ++it)
		{
			float currentF = (*it).GetF();
			if (currentF < bestF)
			{
				bestIt = it;
				bestF = currentF;
			}
		}

		Node bestNode = (*bestIt);

		m_openList.erase(bestIt);

		return bestNode;
	}

	typename OpenList::iterator FindInOpenList(const Node& _node)
	{
		std::vector<RequestNode> openListRequestNode;
		openListRequestNode.reserve(m_openList.size());

		for (const auto& value : m_openList)
		{
			openListRequestNode.push_back(value.m_node);
		}

		int32_t index = _node.m_node.FindIndexInOpenList(openListRequestNode);
		if (index > -1)
		{
			return m_openList.begin() + index;
		}
		else
		{
			return m_openList.end();
		}
	}

	uint32_t PushNodeInClosedList(Node& _node)
	{
		m_resultList.push_back(_node);

		typename OpenList::iterator it = m_closedList.begin();
		m_closedList.insert(it, _node);

		return static_cast<uint32_t>(m_resultList.size() - 1);
	}

	bool IsInClosedList(const Node& _node)
	{
		std::vector<RequestNode> closeListRequestNode;
		closeListRequestNode.reserve(m_closedList.size());

		for (const auto& value : m_closedList)
		{
			closeListRequestNode.push_back(value.m_node);
		}

		return _node.m_node.IsInClosedList(closeListRequestNode);
	}

private:
	EAStarSearchState m_searchState;
	EAStarResult m_result;

	OpenList m_openList;
	ClosedList m_closedList;
	ResultList m_resultList;

	Solution m_solution;
	float m_maxCost;
};

DEMIGOAP_NAMESPACE_END