#ifndef _FIRA_PENALTY_H_
#define _FIRA_PENALTY_H_

#include <strategy.h>

class Fira_penalty:public Strategist
{
public:
	Fira_penalty();
	~Fira_penalty();
private:

    int debug_print;

protected:
    virtual void ThreadMotion();
    virtual int GetImageResult();
};

#endif // _FIRA_PENALTY_H_
