#pragma once


enum class RenderOrder
{
	BackGround,
	Play,
	PlayUI,
};

enum class CollisionOrder
{
	Map,
	Potal,
	PlayerBody,
	MonsterBody,
	InvenIcon,
	MouseObject,
};

enum class UpdateOrder
{
	Player,
	Monster,
};