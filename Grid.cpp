#include "Grid.h"

#include "Components/Gate.h"
#include "Components/SWITCH.h"
#include "Components/LED.h"
#include "Components/Connection.h"

Grid::Grid(int r_X, int r_Y): Nodes(r_X, std::vector<Node> (r_Y))
{
    SizeX = r_X;
    SizeY = r_Y;
    Reset();
}

void Grid::Reset()
{
    for (int i = 0; i < SizeX; i++)
        for (int j = 0; j < SizeY; j++)
		{
			Nodes[i][j].State = Node::NOTHING;
			Nodes[i][j].pComp = NULL;
			Nodes[i][j].pPin = NULL;
			Nodes[i][j].Visited = false;
			Nodes[i][j].BelongToGate = false;
		}
}

std::vector< std::pair<int,int> > Grid::FindPath(std::pair<int,int> Point1, std::pair<int,int> Point2)
{
	std::queue< std::pair<int,int> > NodesQueue;
	bool Found = false;
	int TempArrayX[4] = { 0,0,1,-1 }, TempArrayY[4] = { 1,-1,0,0 };
	int TempY, TempX, CurrentX, CurrentY;
	NodesQueue.push(std::pair<int,int> (Point1.first, Point1.second));
	Nodes[Point1.first][Point1.second].Visited = true;
	while (!NodesQueue.empty() && !Found)
	{
		CurrentX = NodesQueue.front().first;
		CurrentY = NodesQueue.front().second;
		for (int z = 0; z < 4; z++)
		{
			TempX = TempArrayX[z] + CurrentX;
			TempY = TempArrayY[z] + CurrentY;
			if (TempX < SizeX && TempX > 0 && TempY < SizeY  && TempY > 0 && !(Nodes[TempX][TempY].Visited) && Nodes[TempX][TempY].State != Node::GATE && Nodes[TempX][TempY].State != Node::CONNECTIONFULL&& Nodes[TempX][TempY].State != Node::CORNER)
			{
				if (Nodes[TempX][TempY].State == Node::PINPOINT)
				{
					if (TempX == Point2.first && TempY == Point2.second)
					{
						Found = true;
						Nodes[TempX][TempY].ParentX = CurrentX;
						Nodes[TempX][TempY].ParentY = CurrentY;
						break;
					}
					else
					{
						continue;
					}
				}
				if ((TempY == CurrentY && Nodes[TempX][TempY].State != Node::HORIZONTAL) || (TempX == CurrentX && Nodes[TempX][TempY].State != Node::VERTICAL))
				{
					Nodes[TempX][TempY].ParentX = CurrentX;
					Nodes[TempX][TempY].ParentY = CurrentY;
					Nodes[TempX][TempY].Visited = true;
					NodesQueue.push(std::pair<int,int> (TempX, TempY));
				}
			}
		}
		if (!NodesQueue.empty())
			NodesQueue.pop();
	}
	if (!Found)
        throw "Cannot find a path";
    return CreateThePath(Point1, Point2);
}

bool Grid::IsValidCenter(std::pair<int,int> Center) const
{
    if (-6+Center.first <= 0 || -6+Center.second <= 0 || 6+Center.first >= SizeX || 6+Center.second >= SizeY)
        return false;
	for (int i = -6; i <= 6; i++)
		for (int j = -6; j <= 6; j++)
			if (Nodes[i + Center.first][j + Center.second].State != Node::NOTHING)
				return false;
	return true;
}

void Grid::AddGate(Gate* pGate)
{
	std::pair<int, int> Center = pGate->GetCenter();

	for (int i = -3; i <= 3; i++)
		for (int j = -2; j <= 2; j++)
		{
			Nodes[i + Center.first][j + Center.second].State = Node::GATE;
			Nodes[i + Center.first][j + Center.second].pComp = pGate;
		}

	Nodes[Center.first + 4][Center.second].State = Node::PINPOINT;

	Nodes[Center.first + 4][Center.second].pPin = pGate->GetOutputPin();
	Nodes[Center.first + 4][Center.second].pComp = pGate;
	std::vector<InputPin>& temp = pGate->GetInputPins();

	if (temp.size() == 2)
	{
		Nodes[Center.first - 4][Center.second].State = Node::PINPOINT;
		Nodes[Center.first - 4][Center.second + 1].State = Node::PINPOINT;
		Nodes[Center.first - 4][Center.second - 1].State = Node::PINPOINT;

		Nodes[Center.first - 4][Center.second - 1].pPin = &(temp[0]);
		Nodes[Center.first - 4][Center.second - 1].pComp = pGate;
		Nodes[Center.first - 4][Center.second + 1].pPin = &(temp[1]);
		Nodes[Center.first - 4][Center.second + 1].pComp = pGate;
	}
	else if (temp.size() == 3)
    {
        Nodes[Center.first - 4][Center.second].State = Node::PINPOINT;
        Nodes[Center.first - 4][Center.second + 1].State = Node::PINPOINT;
        Nodes[Center.first - 4][Center.second - 1].State = Node::PINPOINT;

        Nodes[Center.first - 4][Center.second - 1].pPin = &(temp[0]);
        Nodes[Center.first - 4][Center.second - 1].pComp = pGate;
        Nodes[Center.first - 4][Center.second].pPin = &(temp[1]);
        Nodes[Center.first - 4][Center.second].pComp = pGate;
        Nodes[Center.first - 4][Center.second + 1].pPin = &(temp[2]);
        Nodes[Center.first - 4][Center.second + 1].pComp = pGate;
    }
    else
    {
        Nodes[Center.first - 4][Center.second].State = Node::PINPOINT;

        Nodes[Center.first - 4][Center.second].pPin = &(temp[0]);
        Nodes[Center.first - 4][Center.second].pComp = pGate;
    }

	for (int i = -6; i <= 6; i++)
		for (int j = -6; j <= 6; j++)
		{
			Nodes[i + Center.first][j + Center.second].BelongToGate = true;
			if (Nodes[i + Center.first][j + Center.second].State == Node::NOTHING)
				Nodes[i + Center.first][j + Center.second].State = Node::NOCONNECTION;
		}
}

void Grid::AddSWITCH(SWITCH* pSWITCH)
{
	std::pair<int, int> Center = pSWITCH->GetCenter();

	for (int i = -3; i <= 3; i++)
		for (int j = -2; j <= 2; j++)
		{
			Nodes[i + Center.first][j + Center.second].State = Node::GATE;
			Nodes[i + Center.first][j + Center.second].pComp = pSWITCH;
		}

	Nodes[Center.first + 4][Center.second].State = Node::PINPOINT;
	Nodes[Center.first + 4][Center.second].pPin = pSWITCH ->GetOutputPin();
	Nodes[Center.first + 4][Center.second].pComp = pSWITCH;

	for (int i = -6; i <= 6; i++)
		for (int j = -6; j <= 6; j++)
		{
			Nodes[i + Center.first][j + Center.second].BelongToGate = true;
			if (Nodes[i + Center.first][j + Center.second].State == Node::NOTHING)
				Nodes[i + Center.first][j + Center.second].State = Node::NOCONNECTION;
		}
}

void Grid::AddLED(LED* pLED)

{
	std::pair<int, int> Center = pLED->GetCenter();

	for (int i = -3; i <= 3; i++)
		for (int j = -2; j <= 2; j++)
		{
			Nodes[i + Center.first][j + Center.second].State = Node::GATE;
			Nodes[i + Center.first][j + Center.second].pComp = pLED;
		}

	Nodes[Center.first - 4][Center.second].State = Node::PINPOINT;
	Nodes[Center.first - 4][Center.second].pPin = pLED->GetInputPin();
	Nodes[Center.first - 4][Center.second].pComp = pLED;

	for (int i = -6; i <= 6; i++)
		for (int j = -6; j <= 6; j++)
		{
			Nodes[i + Center.first][j + Center.second].BelongToGate = true;
			if (Nodes[i + Center.first][j + Center.second].State == Node::NOTHING)
				Nodes[i + Center.first][j + Center.second].State = Node::NOCONNECTION;
		}
}

void Grid::AddConnection(Connection* pConnection)
{
	std::vector< std::pair<int, int> > Path = pConnection->GetPath();
	int TempX, TempY, Count = 1;
	TempX = Path.front().first;
	TempY = Path.front().second;
	do
	{

		while ((TempX != Path.back().first || TempY != Path.back().second) && TempX == Path[Count].first)
		{
			if (Nodes[TempX][TempY].State == Node::NOTHING || Nodes[TempX][TempY].State == Node::NOCONNECTION)
			{
				Nodes[TempX][TempY].pComp = pConnection;
				Nodes[TempX][TempY].State = Node::VERTICAL;
			}
			if (Nodes[TempX][TempY].State == Node::HORIZONTAL)
			{
				Nodes[TempX][TempY].pComp = NULL;
				Nodes[TempX][TempY].State = Node::CONNECTIONFULL;
			}

			(TempY > Path[Count].second) ? TempY-- : TempY++;

			if (TempY == Path[Count].second)
			{
				if (Nodes[TempX][TempY].State != Node::PINPOINT)
				{
					Nodes[TempX][TempY].pComp = pConnection;
					Nodes[TempX][TempY].State = Node::CORNER;
				}
				Count++;
			}

		}

		while ((TempX != Path.back().first || TempY != Path.back().second) && TempX != Path[Count].first)
		{
			if (Nodes[TempX][TempY].State == Node::NOTHING || Nodes[TempX][TempY].State == Grid::Node::NOCONNECTION)
			{
				Nodes[TempX][TempY].pComp = pConnection;
				Nodes[TempX][TempY].State = Node::HORIZONTAL;
			}
			if (Nodes[TempX][TempY].State == Node::VERTICAL)
			{
				Nodes[TempX][TempY].pComp = NULL;
				Nodes[TempX][TempY].State = Node::CONNECTIONFULL;
			}

			(TempX > Path[Count].first) ? TempX-- : TempX++;

			if (TempX == Path[Count].first)
			{
				if (Nodes[TempX][TempY].State != Node::PINPOINT)
				{
					Nodes[TempX][TempY].pComp = pConnection;
					Nodes[TempX][TempY].State = Node::CORNER;
				}
				Count++;
			}
		}

	} while (TempX != Path.back().first || TempY != Path.back().second);
}

void Grid::RemoveGate(Gate* pGate)
{
	std::pair<int, int> Center = pGate->GetCenter();

	if(pGate != Nodes[Center.first][Center.second].pComp)
        throw "Component mismatch";

	std::vector<InputPin>& temp = pGate->GetInputPins();
	if (pGate->GetOutputPin() != Nodes[Center.first + 4][Center.second].pPin)
		throw "Pin mismatch";
	if (temp.size() == 2)
    {
        if (Nodes[Center.first - 4][Center.second - 1].pPin != &(temp[0]) || Nodes[Center.first - 4][Center.second + 1].pPin != &(temp[1]))
			throw "Pin mismatch";
    }
	else if (temp.size() == 3)
    {
        if (Nodes[Center.first - 4][Center.second - 1].pPin != &(temp[0]) || Nodes[Center.first - 4][Center.second].pPin != &(temp[1]) || Nodes[Center.first - 4][Center.second + 1].pPin != &(temp[2]))
            throw "Pin mismatch";
    }
    else
    {
        if (Nodes[Center.first - 4][Center.second].pPin != &(temp[0]))
            throw "Pin mismatch";
    }

	for (int i = -6; i <= 6; i++)
		for (int j = -6; j <= 6; j++)
		{
			Nodes[i + Center.first][j + Center.second].BelongToGate = false;
			if (Nodes[i + Center.first][j + Center.second].State == Node::GATE || Nodes[i + Center.first][j + Center.second].State == Node::NOCONNECTION || Nodes[i + Center.first][j + Center.second].State == Node::PINPOINT)
			{
				Nodes[i + Center.first][j + Center.second].State = Node::NOTHING;
				Nodes[i + Center.first][j + Center.second].pComp = NULL;
				Nodes[i + Center.first][j + Center.second].pPin = NULL;
			}
		}
}

void Grid::RemoveSWITCH(SWITCH* pSWITCH)
{
	std::pair<int, int> Center = pSWITCH->GetCenter();

	if(pSWITCH != Nodes[Center.first][Center.second].pComp)
        throw "Component mismatch";

	if (pSWITCH->GetOutputPin() != Nodes[Center.first + 4][Center.second].pPin)
		throw "Pin mismatch";

	for (int i = -6; i <= 6; i++)
		for (int j = -6; j <= 6; j++)
		{
			Nodes[i + Center.first][j + Center.second].BelongToGate = false;
			if (Nodes[i + Center.first][j + Center.second].State == Node::GATE || Nodes[i + Center.first][j + Center.second].State == Node::NOCONNECTION || Nodes[i + Center.first][j + Center.second].State == Node::PINPOINT)
			{
				Nodes[i + Center.first][j + Center.second].State = Node::NOTHING;
				Nodes[i + Center.first][j + Center.second].pComp = NULL;
				Nodes[i + Center.first][j + Center.second].pPin = NULL;
			}
		}
}

void Grid::RemoveLED(LED* pLED)
{
	std::pair<int, int> Center = pLED->GetCenter();

	if(pLED != Nodes[Center.first][Center.second].pComp)
        throw "Component mismatch";

	if (pLED->GetInputPin() != Nodes[Center.first - 4][Center.second].pPin)
		throw "Pin mismatch";

	for (int i = -6; i <= 6; i++)
		for (int j = -6; j <= 6; j++)
		{
			Nodes[i + Center.first][j + Center.second].BelongToGate = false;
			if (Nodes[i + Center.first][j + Center.second].State == Node::GATE || Nodes[i + Center.first][j + Center.second].State == Node::NOCONNECTION || Nodes[i + Center.first][j + Center.second].State == Node::PINPOINT)
			{
				Nodes[i + Center.first][j + Center.second].State = Node::NOTHING;
				Nodes[i + Center.first][j + Center.second].pComp = NULL;
				Nodes[i + Center.first][j + Center.second].pPin = NULL;
			}
		}
}

void Grid::RemoveConnection(Connection* pConnection)
{
	std::vector<std::pair<int, int> >Path = pConnection->GetPath();

	int TempY, TempX, Count = 1;
	TempX = Path.front().first;
	TempY = Path.front().second;
	do
	{
		while ((TempX != Path.back().first || TempY != Path.back().second) && TempX == Path[Count].first)
		{
			if (Nodes[TempX][TempY].State == Node::CONNECTIONFULL)
			{
				Nodes[TempX][TempY].State = Node::HORIZONTAL;
				if (Nodes[TempX + 1][TempY].pComp == NULL || Nodes[TempX - 1][TempY].pComp == NULL)
					Nodes[TempX][TempY].pComp = Nodes[TempX][TempY + 1].pComp;
				else
					Nodes[TempX][TempY].pComp = Nodes[TempX + 1][TempY].pComp;
			}

			if (Nodes[TempX][TempY].State == Node::VERTICAL || Nodes[TempX][TempY].State == Node::CORNER)
			{
				Nodes[TempX][TempY].State = (Nodes[TempX][TempY].BelongToGate) ? Node::NOCONNECTION : Node::NOTHING;
				Nodes[TempX][TempY].pComp = NULL;
			}

			(TempY > Path[Count].second) ? TempY-- : TempY++;

			if (TempY == Path[Count].second)
				Count++;
		}

		while ((TempX != Path.back().first || TempY != Path.back().second) && TempX != Path[Count].first)
		{
			if (Nodes[TempX][TempY].State == Node::CONNECTIONFULL)
			{
				Nodes[TempX][TempY].State = Node::VERTICAL;
				if (Nodes[TempX + 1][TempY].pComp == NULL || Nodes[TempX - 1][TempY].pComp == NULL)
					Nodes[TempX][TempY].pComp = Nodes[TempX][TempY + 1].pComp;
				else
					Nodes[TempX][TempY].pComp = Nodes[TempX + 1][TempY].pComp;
			}

			if (Nodes[TempX][TempY].State == Node::HORIZONTAL || Nodes[TempX][TempY].State == Node::CORNER)
			{
				Nodes[TempX][TempY].State = (Nodes[TempX][TempY].BelongToGate) ? Node::NOCONNECTION : Node::NOTHING;
				Nodes[TempX][TempY].pComp = NULL;
			}

			(TempX > Path[Count].first) ? TempX-- : TempX++;

			if (TempX == Path[Count].first)
				Count++;
		}

	} while (TempX != Path.back().first || TempY != Path.back().second);
}

Component* Grid::GetComponentAt(std::pair<int, int> Point)
{
    if (Point.first < 0 || Point.first >= SizeX || Point.second < 0 || Point.second >= SizeY)
        return NULL;
    return Nodes[Point.first][Point.second].pComp;
}

Pin* Grid::GetPinAt(std::pair<int, int> Point)
{
    if (Point.first < 0 || Point.first >= SizeX || Point.second < 0 || Point.second >= SizeY)
        return NULL;
    return Nodes[Point.first][Point.second].pPin;
}

std::vector< std::pair<int, int> > Grid::CreateThePath(std::pair<int, int> Point1, std::pair<int, int> Point2)
{
	std::vector< std::pair<int, int> >Path;
	Path.push_back(std::make_pair(Point2.first, Point2.second));
	int CurrentX = Point2.first, CurrentY = Point2.second, TempY, TempX;
	TempX = CurrentX;
	TempY = CurrentY;
	CurrentX = Nodes[TempX][TempY].ParentX;
	CurrentY = Nodes[TempX][TempY].ParentY;
	do
	{
		while ((TempX != Point1.first || TempY != Point1.second) && TempX == CurrentX)
		{
			TempX = CurrentX;
			TempY = CurrentY;
			CurrentX = Nodes[TempX][TempY].ParentX;
			CurrentY = Nodes[TempX][TempY].ParentY;
			if (TempX != CurrentX)
			{
				Path.push_back(std::make_pair(TempX, TempY));
			}
		}
		while ((TempX != Point1.first || TempY != Point1.second) && TempX != CurrentX)
		{
			TempX = CurrentX;
			TempY = CurrentY;
			CurrentX = Nodes[TempX][TempY].ParentX;
			CurrentY = Nodes[TempX][TempY].ParentY;
			if (TempX == CurrentX)
			{
				Path.push_back(std::make_pair(TempX, TempY));
			}
		}

	} while (TempX != Point1.first || TempY != Point1.second);
	if (!(Point1.first == Path.back().first && Point1.second == Path.back().second))
	{
		Path.push_back(std::make_pair(Point1.first, Point1.second));
	}
	ClearParent();
	return Path;
}

void Grid::ClearParent()
{
	for (int i = 0; i < SizeX; i++)
	{
		for (int j = 0; j < SizeY; j++)
		{
			Nodes[i][j].ParentX = 0;
			Nodes[i][j].ParentY = 0;
			Nodes[i][j].Visited = false;
		}
	}
}
