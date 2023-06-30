#pragma once


enum class RenderOrder
{
	BackGround,
	Monster,
	Play,
	PlayUI,
	PlayerHPMPBar,
	InvenIcon,
	MouseUI,
	Fade,
};

enum class CollisionOrder
{
	Map,
	GardenPotal,
	BossPotal,
	BossSummon,
	Potal,
	PlayerBody,
	PlayerAttack,
	MonsterBody,
	InvenIcon,
	MouseObject,
	MouseObjectPlay,
	StartIcon,
	QuestIcon,
};

enum class UpdateOrder
{
	Player,
	Monster,
	Potal,
};