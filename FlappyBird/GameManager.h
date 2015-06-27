 #ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include "cocos2d.h"
#include "d:\cocos2d-x-2.1.4\projects\FlappyBird\proj.win32\Pillar.h"
USING_NS_CC;

class GameManager : public CCLayer
{
public:
	GameManager(void);
	~GameManager(void);
	virtual bool init();
	virtual void update(float dt);
	CREATE_FUNC(GameManager);
	virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* pEvent);
	virtual void ccTouchesMoved(CCSet* pTouches, CCEvent* pEvent);
	virtual void ccTouchesEnded(CCSet* pTouches, CCEvent* pEvent);

	void BackGroundMove(float dt);
	void Jump();
	bool CheckLose();
	void EndScene();
	void setScore();
	void setBest();
	void rePlay(CCObject* pSender);
public:
	CCSprite* m_player;
	CCSize size;
	CCSprite* m_bg1;
	CCSprite* m_bg2;
	CCSprite* m_pillar1;
	CCSprite* m_pillar2;
	CCSprite* m_pillar3;	
	CCSprite* m_blank1;
	CCSprite* m_blank2;
	CCSprite* m_blank3;
	CCLabelTTF* m_scorelabel;
	CCLabelTTF* m_lose;
	CCLabelTTF* m_bestlabel;
	bool overflag;
	int m_pillarmark;
	int m_score;
	int m_best;
};

#endif