#ifndef VISIBLE_H
#define VISIBLE_H

class CVisible
{
public:
					CVisible();
	virtual			~CVisible();
	virtual void	Draw() const = 0;
};

#endif
