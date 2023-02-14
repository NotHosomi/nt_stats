#include "Team.h"

int Team::totalKills() const
{
	int count = 0;
	for (auto p : roster)
	{
		count += p->kills;
	}
	return count;
}

int Team::totalDeaths() const
{
	int count = 0;
	for (auto p : roster)
	{
		count += p->deaths;
	}
	return count;
}

int Team::totalSui() const
{
	int count = 0;
	for (auto p : roster)
	{
		count += p->suicides;
	}
	return count;
}

int Team::totalCaps() const
{
	int count = 0;
	for (auto p : roster)
	{
		count += p->ghost_caps;
	}
	return count;
}

int Team::totalAssists() const
{
	int count = 0;
	for (auto p : roster)
	{
		count += p->assists;
	}
	return count;
}

int Team::totalTK() const
{
	int count = 0;
	for (auto p : roster)
	{
		count += p->TKs;
	}
	return count;
}

int Team::totalTKed() const
{
	int count = 0;
	for (auto p : roster)
	{
		count += p->TKed;
	}
	return count;
}

std::string Team::csv() const
{
	char* buffer = new char[50];
	sprintf_s(buffer, 50, "%d,%d,%d,%d,%d,%d,%d,%d,", totalKills(), totalDeaths(), totalSui(), totalCaps(), totalAssists(), totalTK(), totalTKed(),maps);
	return buffer;
}
