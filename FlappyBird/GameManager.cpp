#include "GameManager.h"

USING_NS_CC;

GameManager::GameManager(void)
{
	m_best = 0;
}


GameManager::~GameManager(void)
{
}

bool GameManager::init(){
	bool bRet = false;
	do{

		size = CCDirector::sharedDirector()->getVisibleSize();
		m_bg1 = CCSprite::create("BackGround1.png");
		m_bg1->setPosition(ccp(size.width/2,size.height/2));
		this->addChild(m_bg1,0);

		m_bg2 = CCSprite::create("BackGround1.png");
		m_bg2->setPosition(ccp(size.width+size.width/2, size.height/2));
		this->addChild(m_bg2,0);

		m_player = CCSprite::create("Player2.png");
		m_player->setPosition(ccp(100,size.height/2));
		this->addChild(m_player,3);
		this->setTouchEnabled(true);

		m_pillar1 = CCSprite::create("Pillar.png");
		m_pillar1->setPosition(ccp(size.width+75,543));
		this->addChild(m_pillar1,1);

		m_blank1 = CCSprite::create("Blank.png");
		m_blank1->setPosition(ccp(size.width+75,(rand()%8*50+326.0)));
		this->addChild(m_blank1,2);


		m_pillar2 = CCSprite::create("Pillar.png");
		m_pillar2->setPosition(ccp(size.width+425,543));
		this->addChild(m_pillar2,1);

		m_blank2 = CCSprite::create("Blank.png");
		m_blank2->setPosition(ccp(size.width+425,(rand()%8*50+326.0)));
		this->addChild(m_blank2,2);


		m_pillar3 = CCSprite::create("Pillar.png");
		m_pillar3->setPosition(ccp(size.width+775,543));
		this->addChild(m_pillar3,1);

		m_blank3 = CCSprite::create("Blank.png");
		m_blank3->setPosition(ccp(size.width+775,(rand()%8*50+326.0)));
		this->addChild(m_blank3,2);

		m_scorelabel = CCLabelTTF::create("0","Arial",60);
		m_scorelabel->setPosition(ccp(size.width/2,800));
		m_scorelabel->setColor(ccc3(0,0,0));
		this->addChild(m_scorelabel,3);

		m_lose = CCLabelTTF::create("You Lose!!","Arial",80);
		m_lose->setPosition(ccp(size.width/2,size.height/2+50));
		m_lose->setColor(ccc3(0,0,0));
		this->addChild(m_lose,3);
		m_lose->setVisible(false);

		m_bestlabel = CCLabelTTF::create("Best: 0","Arial",30);
		m_bestlabel->setPosition(ccp(70,900));
		m_bestlabel->setColor(ccc3(0,0,0));
		this->addChild(m_bestlabel,3);

		setBest();

		m_pillarmark = 1;
	    m_score = 0;
		overflag = false;

		this->schedule(schedule_selector(GameManager::update));
		this->schedule(schedule_selector(GameManager::BackGroundMove));
		bRet = true;
	}while(0);

	return bRet;
}


void GameManager::update(float dt){
	CCPoint temp = m_player->getPosition();
	CCSize playersize = m_player->getContentSize();
	if((temp.y-3)>146){
		temp.y -= 3;
	}
	m_player ->setPosition(temp);
	CheckLose();
}

void GameManager::ccTouchesBegan(CCSet* pTouches,CCEvent* pEvent){
	if(!overflag){
	Jump();
	}
}

void GameManager::ccTouchesMoved(CCSet* pTouches,CCEvent* pEvent){
}

void GameManager::ccTouchesEnded(CCSet* pTouches,CCEvent* pEvent){
}

void GameManager::Jump(){
	CCPoint temp = m_player->getPosition();
	CCSize playersize = m_player->getContentSize();
	if((temp.y+20)<(size.height-playersize.height/2)){
		temp.y += 70;
	}
	m_player ->setPosition(temp);

}


void GameManager::BackGroundMove(float dt){
	CCPoint bg1 = m_bg1->getPosition();
	CCPoint bg2 = m_bg2->getPosition();
	CCPoint p1 = m_pillar1->getPosition();
	CCPoint p2 = m_pillar2->getPosition();
	CCPoint p3 = m_pillar3->getPosition();
	CCPoint b1 = m_blank1->getPosition();
	CCPoint b2 = m_blank2->getPosition();
	CCPoint b3 = m_blank3->getPosition();

	if(bg1.x<-size.width/2){
		bg1.x += size.width*2;
	}
	if(bg2.x<-size.width/2){
		bg2.x += size.width*2;
	}
	if(p1.x<-75){
		p1.x += 1050;
		b1.y =(float)(rand()%8*50+326);
		b1.x = p1.x;
		m_pillarmark = 2;
		m_score++;
		setScore();
	}
	if(p2.x<-75){
		p2.x += 1050;
		b2.y = (float)(rand()%8*50+326);
		b2.x = p2.x;
		m_pillarmark = 3;
		m_score++;
		setScore();
	}
	if(p3.x<-75){
		p3.x += 1050;
		b3.y =(float)(rand()%8*50+326);
		b3.x = p3.x;
		m_pillarmark = 1;
		m_score++;
		setScore();
	}

	bg1.x -=2;
	bg2.x -=2;
	p1.x -=2;
	p2.x -=2;
	p3.x -=2;
	b1.x -=2;
	b2.x -=2;
	b3.x -=2;

	m_bg1->setPosition(bg1);
	m_bg2->setPosition(bg2);
	m_pillar1->setPosition(p1);
	m_pillar2->setPosition(p2);
	m_pillar3->setPosition(p3);
	m_blank1->setPosition(b1);
	m_blank2->setPosition(b2);
	m_blank3->setPosition(b3);
}

bool GameManager::CheckLose(){
	bool temp;    
	CCRect uppillar;
	CCRect dwpillar;
	CCRect player = CCRectMake(m_player->getPosition().x - 45,m_player->getPosition().y - 40,90,80);
	CCPoint upLD;
	CCPoint upRU;
	CCPoint dwLD;
	CCPoint dwRU;
	switch (m_pillarmark)
	{
	case 1:
		upLD = ccp(m_blank1->getPosition().x-75,m_blank1->getPosition().y+95);
		upRU = ccp(upLD.x+150,960);
		dwLD = ccp(m_blank1->getPosition().x - 75,126);
		dwRU = ccp(upRU.x,m_blank1->getPosition().y - 95);
		break;
	case 2:
		upLD = ccp(m_blank2->getPosition().x-75,m_blank2->getPosition().y+95);
		upRU = ccp(upLD.x+150,960);
		dwLD = ccp(m_blank2->getPosition().x - 75,126);
		dwRU = ccp(upRU.x,m_blank2->getPosition().y - 95);
		break;
	case 3:
		upLD = ccp(m_blank3->getPosition().x-75,m_blank3->getPosition().y+95);
		upRU = ccp(upLD.x+150,960);
		dwLD = ccp(m_blank3->getPosition().x - 75,126);
		dwRU = ccp(upRU.x,m_blank3->getPosition().y - 95);
		break;
	}

	uppillar = CCRectMake(upLD.x,upLD.y,(upRU.x-upLD.x),(upRU.y-upLD.y));
	dwpillar = CCRectMake(dwLD.x,dwLD.y,(dwRU.x-dwLD.x),(dwRU.y-dwLD.y));
	if(uppillar.intersectsRect(player)||dwpillar.intersectsRect(player)||m_player->getPositionY()<156){
		CCLOG("YOU LOSE!!!");
		this->unscheduleAllSelectors();
		overflag = true;
		if(m_score>m_best){
			m_best = m_score;
			setBest();
		}
		EndScene();
	}
	return false;
}

void GameManager::EndScene(){
	m_lose->setVisible(true);
	CCMenuItemImage *restartItem = CCMenuItemImage::create("RePlay.png","RePlay.png",this, menu_selector(GameManager::rePlay));
	restartItem->setPosition( ccp(size.width/2, size.height/2-150));
	CCMenu *menu = CCMenu::create(restartItem, NULL);
	menu->setPosition(CCPointZero);
	this->addChild(menu,4);
}

void GameManager::setScore(){
	char score_buffer [10];
	sprintf(score_buffer,"%i",m_score);
	m_scorelabel -> setString(score_buffer);
}

void GameManager::setBest(){
	char score_buffer [15];
	sprintf(score_buffer,"Best: %i",m_best);
	m_bestlabel -> setString(score_buffer);
}

void GameManager::rePlay(CCObject* pSender){
	this->removeAllChildren();
	this->init();
}


