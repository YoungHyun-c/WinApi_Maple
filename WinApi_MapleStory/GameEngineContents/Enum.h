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
};