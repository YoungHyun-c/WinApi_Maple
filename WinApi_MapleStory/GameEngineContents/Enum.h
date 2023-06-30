#pragma once


enum class RenderOrder
{
	BackGround,
	Monster,
	Play,
	PlayUI,
	InvenIcon,
	MouseUI,
	Fade,
};

enum class CollisionOrder
{
	Map,
	GardenPotal,
	BossPotal,
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