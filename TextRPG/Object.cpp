#include "Object.h"

void CObject::TakeDamage(int _damage)
{
	mHP -= _damage;

	if (mHP <= 0)
	{
		mHP = 0;
	}
}

bool CObject::IsDead(string _name, int _hp)
{
	if (_hp <= 0)
	{
		COUTN(_name << "이(가) 죽었습니다!");
		return false;
	}
	else
	{
		return true;
	}
}