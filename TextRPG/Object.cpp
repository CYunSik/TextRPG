#include "Object.h"

void CObject::TakeDamage(int _damage)
{
	mHP -= _damage;

	if (mHP <= 0)
	{
		mHP = 0;
	}
}
