#pragma once


enum class RenderOrder
{
	BackGround,
	Play,
	PlayUI,
	InvenIcon,
	MouseUI,
	Fade,
};

enum class CollisionOrder
{
	Map,
	Potal,
	PlayerBody,
	MonsterBody,
	InvenIcon,
	MouseObject,
	StartIcon,
	QuestIcon,
};

enum class UpdateOrder
{
	Player,
	Monster,
};