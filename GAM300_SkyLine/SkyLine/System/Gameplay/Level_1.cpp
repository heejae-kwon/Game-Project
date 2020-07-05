#include "Level_1.hpp"
#include "Level_temp.hpp"
#include "ObjectManager.hpp"
#include "Actor.hpp"
#include <iostream>
#include <iomanip>
#include <GraphicsCore.hpp>
#include <Input.hpp>
#include <Engine.hpp>
#include "Rigidbody.hpp"
#include <PhysicsCore.hpp>

//Actor * Battleship;
//Actor * Island;
//Actor * Cloud1;
//Actor * Cloud2;

Level::Level_1::Level_1(std::string stageFileName_)
{
  //GraphicsCore * GC = GraphicsCore::instance();
 // Camera *camera = GC->getCameraManager()->getCamera();
	mSound = AudioCore::instance()->CreateSound("./Assets/Sound/OceanBGM.ogg");
	mSound1 = AudioCore::instance()->CreateSound("./Assets/Sound/ShipSound.ogg");
	mSound2 = AudioCore::instance()->CreateSound("./Assets/Sound/PlaneInterior.ogg");

	GraphicsCore * GC = GraphicsCore::instance();
	m_obj = ObjectManager::instance();
//	m_obj->Reset();

	actor = m_obj->CreateActor("Player");
	actor->addComponent<Component::Transform>();
	Component::Transform * atc = actor->getComponent<Component::Transform>();
	atc->setScale(glm::vec3(.8f,.8f,.8f));
  //atc->setScale(glm::vec3(0.1f, 0.1f, 0.1f));
	//atc->setScale(glm::vec3(100.0f, 100.0f, 100.0f));
	atc->translate(glm::vec3(0.0f,100.0f, 500.0f));
	actor->addComponent<Component::PlayerController>();
	actor->addComponent<Component::Renderable>();
	actor->saveActor = true;

  // Player's Rigidbody
  Component::Rigidbody *rb = actor->addComponent<Component::Rigidbody>();
  rb->setCollisionShape(CollisionShape::BOX);
  rb->setMass(1.0f);
  PhysicsCore::instance()->getPhysics()->addRigidbody(*rb);
  

  // Player's renderable
	ModelManager * MM = GC->getModelManager();
	RenderableManager* RM = GC->getRenderableManager();
	Component::Renderable * M = actor->getComponent<Component::Renderable>();
	M->setModel(MM->getModel("PlayerPlane"));
	RM->addRenderable(*M);
	

  // Battleship
	Battleship = m_obj->CreateActor("Battleship");
	Battleship->addComponent<Component::Transform>();
	Battleship->addComponent<Component::Renderable>();
	Component::Transform * btt = Battleship->getComponent<Component::Transform>();

	btt->translate(glm::vec3(80.0f,-7.0f,00.0f));

	// =====Island============
	Island = m_obj->CreateActor("BasicIsland");
	Island->addComponent<Component::Transform>();
	Island->addComponent<Component::Renderable>();
	Component::Renderable * iM = Island->getComponent<Component::Renderable>();
	iM->setModel(MM->getModel("BasicIsland"));
	RM->addRenderable(*iM);
	Component::Transform * iT = Island->getComponent<Component::Transform>();
	iT->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
	iT->translate(glm::vec3(0.0f, -7.0f, 0.0f));

	///////////

	Island1 = m_obj->CreateActor("BasicIsland1");
	Island1->addComponent<Component::Transform>();
	Island1->addComponent<Component::Renderable>();
	Component::Renderable * iM1 = Island1->getComponent<Component::Renderable>();
	iM1->setModel(MM->getModel("BasicIsland"));
	RM->addRenderable(*iM1);
	Component::Transform * iT1 = Island1->getComponent<Component::Transform>();
	iT1->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
	iT1->translate(glm::vec3(100.0f, -7.0f, 0.0f));
	///////////
	Island2 = m_obj->CreateActor("BasicIsland2");
	Island2->addComponent<Component::Transform>();
	Island2->addComponent<Component::Renderable>();
	Component::Renderable * iM2 = Island2->getComponent<Component::Renderable>();
	iM2->setModel(MM->getModel("BasicIsland"));
	RM->addRenderable(*iM2);
	Component::Transform * iT2 = Island2->getComponent<Component::Transform>();
	iT2->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
	iT2->translate(glm::vec3(-100.0f, -7.0f, 0.0f));
	///////////
	//Island3 = m_obj->CreateActor("BasicIsland3");
	//Island3->addComponent<Component::Transform>();
	//Island3->addComponent<Renderable>();
	//Renderable * iM3 = Island3->getComponent<Renderable>();
	//iM3->setModel(MM->getModel("BasicIsland"));
	//RM->addRenderable(std::shared_ptr<Renderable>(iM2));
	//Component::Transform * iT2 = Island2->getComponent<Component::Transform>();
	//iT2->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
	//iT2->translate(glm::vec3(-100.0f, -7.0f, 0.0f));
	///////////
	///////////

	//btt->setScale(glm::vec3(0.001f, 0.001f, 0.001f));
	Component::Renderable * bM = Battleship->getComponent<Component::Renderable>();
	bM->setModel(MM->getModel("Battleship"));
	RM->addRenderable(*bM);

	//Missile = m_obj->CreateActor("Missile");
	//Missile->addComponent<Component::Transform>();
	//Missile->addComponent<Component::Chasing>();
	//Missile->getComponent<Component::Chasing>()->SetTarget(actor);
	//Missile->addComponent<Renderable>();
	//Component::Transform * Mis = Missile->getComponent<Component::Transform>();
	//Mis->translate(glm::vec3(0.0f, -7.0f, 0.0f));
	////btt->setScale(glm::vec3(0.001f, 0.001f, 0.001f));
	//Renderable * mis_model = Missile->getComponent<Renderable>();
	//mis_model->setModel(MM->getModel("Cylinder"));
	//RM->addRenderable(*mis_model);

	//glm::vec3 mis_pos = Mis->getPosition();

  //actor->getComponent<Component::Transform>()->setScale(glm::vec3(0.001f, .001f, .001f));

	//M->setModel(MM->getModel("Battleship"));
	//actor->getComponent<Renderable>()->setModel(MM->getModel("PlayerPlane"));

	playerMissle = m_obj->CreateActor("playerMissile");
	playerMissle->addComponent<Component::Transform>();
	playerMissle->addComponent<Component::Chasing>();
	playerMissle->addComponent<Component::Bullet>();
	playerMissle->getComponent<Component::Bullet>()->setPlayer(actor);
	playerMissle->addComponent<Component::Renderable>();
	Component::Transform * pmTransform = playerMissle->getComponent<Component::Transform>();
	pmTransform = atc;
	Component::Renderable * pmModel = playerMissle->getComponent<Component::Renderable>();
	pmModel->setModel(MM->getModel("Cylinder"));
	RM->addRenderable(*pmModel);

	BattleshipMissile = m_obj->CreateActor("battleshipMissile");
	BattleshipMissile->addComponent<Component::Transform>();
	//BattleshipMissile->addComponent<Component::Chasing>();
	//BattleshipMissile->getComponent<Component::Chasing>()->SetTarget(actor);
	BattleshipMissile->addComponent<Component::MissileExplode>();
	BattleshipMissile->getComponent<Component::MissileExplode>()->SetTarget(actor);
	BattleshipMissile->getComponent<Component::MissileExplode>()->SetShooter(Battleship);
	BattleshipMissile->addComponent<Component::Renderable>();
	Component::Renderable * bmModel = BattleshipMissile->getComponent<Component::Renderable>();
	bmModel->setModel(MM->getModel("Cylinder"));
	RM->addRenderable(*bmModel);


  // == Test Cloud=====
  TextureManager* TM = GC->getTextureManager();

  Cloud1 = m_obj->CreateActor("Cloud1");
  Cloud1->addComponent<Component::Transform>();
  Cloud1->addComponent<Component::Renderable>();
  Component::Transform * cloud1Transform = Cloud1->getComponent<Component::Transform>();
  cloud1Transform->translate(glm::vec3(0.0f, 100.0f, 250.0f));
  Component::Renderable* cloudRenderable = Cloud1->getComponent<Component::Renderable>();
  cloudRenderable->setModel(MM->getModel("Square"));
  cloudRenderable->setTexture(TM->getTexture("cloud"));
  RM->addRenderable(*cloudRenderable);
  
  BattleshipMissile->getComponent<Component::MissileExplode>()->SetCloud(Cloud1);

	/// =======BATTLESHIP=====
	//Battleship = m_obj->CreateActor("Battleship");
	//Battleship->addComponent<Component::Transform>();
	//Battleship->addComponent<Renderable>();
	//Component::Transform * btt = Battleship->getComponent<Component::Transform>();
	//btt->translate(glm::vec3(0.0f,-7.0f,0.0f));
	////btt->setScale(glm::vec3(0.001f, 0.001f, 0.001f));
	//Renderable * bM = Battleship->getComponent<Renderable>();
	//bM->setModel(MM->getModel("Battleship"));
	//RM->addRenderable(std::shared_ptr<Renderable>(bM));


	//Component::Transform * bT = Battleship->getComponent<Component::Transform>();
	//glm::vec3 BattleshipPos = glm::vec3(0.0f, -30.0f, -80.0f);

	//bM->scale_ = glm::vec3(1.0f, 1.0f, 1.0f);
	//bM->rotate_ = bT->getOrientation();
	//bM->translate_ = BattleshipPos;


	//// =====Island============
	//Island = m_obj->CreateActor("BasicIsland");
	//Island->addComponent<Component::Transform>();
	//Island->addComponent<Renderable>();
	//Renderable * iM = Island->getComponent<Renderable>();
	//iM->setModel(MM->getModel("Island"));
	//Component::Transform * iT = Island->getComponent<Component::Transform>();
	//glm::vec3 IslandPos = glm::vec3(100.0f, -30.0f, -180.0f);

	//iM->scale_ = glm::vec3(4.0f, 4.0f, 4.0f);
	//iM->rotate_ = iT->getOrientation();
	//iM->translate_ = IslandPos;
}

Level::Level_1::~Level_1()
{
		//This should be exist to GameLevel
		m_obj->Reset();
}

void Level::Level_1::Update(float dt)
{
	GraphicsCore * GC  = GraphicsCore::instance();
	Camera *camera = GC->getCameraManager()->getCamera();
	

    Component::Transform * playerTransform = actor->getComponent<Component::Transform>();

  /*
  // Make offset respect orientation. !!!This is a very important step!!!
	float xOffset = 0.0f;
	float yOffset = 4.0f;
	float zOffset = 30.0f;
  glm::vec3 offset = camera->Orientation_ * glm::vec3(xOffset, yOffset, zOffset);

  glm::vec3 cameraNewPosition = playerTransform->getPosition() + offset;
  camera->goTo(cameraNewPosition);

  //glm::mix()

  //camera->goTo(glm::vec3(0.0f, 100.0f, 500.0f));

  camera->Orientation_ = playerTransform->getOrientation();
  */
   time += dt;

  /*glm::vec3 Cam3 = glm::vec3((1 + sin(3 * PI / 45 * time))*sin(PI / 4 * (1 + sin(2 * PI / 35 * time)))*cos(PI*(1.5f + sin(2 * PI / 35 * time))),
	 0,
	  (2 + sin(2 * PI / 35 * time))*sin(PI / 4 * (2 + sin(2 * PI / 35 * time)))*sin(PI*(1 + sin(2 * PI / 45 * time))));

  Component::Transform* battleShipTransform = Battleship->getComponent<Component::Transform>();
  battleShipTransform->translate(Cam3 * 0.01f);*/




  float bbspeed = 0.025f;
  Component::Transform * bbt = Battleship->getComponent<Component::Transform>();
  bbt->translate(bbt->getFront() * bbspeed);

  float angle = 0.250f;
  //float angle = 1.f;
  bbt->rotate(dt*angle,glm::vec3(0.0f,1.0f,0.0f));

  float shipSound = 0.5f;
  //AudioCore::instance()->Play(*mSound, 0.5f);
  AudioCore::instance()->Play(*mSound1, shipSound);
 // AudioCore::instance()->Play(*mSound2, 1.0f);
 
  shipSound = (1/distance(bbt->getPosition(), playerTransform->getPosition()))*100.f;

  //cloud
  Component::Transform * cloud1Transform = Cloud1->getComponent<Component::Transform>();
  cloud1Transform->RotateTowards(camera->Orientation_,180.0f);


	//////////////////////////////////////////
	//glm::vec3 m_newPos = misTransform->getPosition();
	//glm::vec3 p_newPos = playerTransform->getPosition();

	//glm::vec3 P_rel = p_newPos - m_newPos;
	
	//misTransform->translate(P_rel*0.0012f);
	
	
	//camera->parent(playerTransform->getOrientation(), playerTransform->getPosition(), glm::vec3(xOffset,yOffset,zOffset));
 

	//std::cout <<
	//	"player pos: "
	//	<< std::setprecision(4) << playerPosition.x <<
	//	" " << std::setprecision(4) << playerPosition.y <<
	//	" " << std::setprecision(4) << playerPosition.z;


	//std::cout <<
	//	" camera pos: "
	//	    << std::setprecision(4) << camera->Position_.x <<
	//	" " << std::setprecision(4) << camera->Position_.y <<
	//	" " << std::setprecision(4) << camera->Position_.z << std::endl;

	//std::setprecision(4);
	//std::cout << "PLAYER: " <<
	//	"Front: [" << PlayerTransform->getFront().x << " " << PlayerTransform->getFront().y << " " << PlayerTransform->getFront().z << "] "
	//	"Right: [" << PlayerTransform->getRight().x << " " << PlayerTransform->getRight().y << " " << PlayerTransform->getRight().z << "] "
	//	"Up: [" << PlayerTransform->getUP().x << " " << PlayerTransform->getUP().y << " " << PlayerTransform->getUP().z << "] " << "		";




/*

	std::setprecision(4);
	std::cout << "PLAYER: " <<
		"Front: [" << camera.Front_.x << " " << camera.Front_.y << " " << camera.Front_.z << "] "
		"Right: [" << camera.Right_.x << " " << camera.Right_.y << " " << camera.Right_.z << "] "
		"Up: [" << camera.Up_.x << " " << camera.Up_.y << " " << camera.Up_.z << "] " << std::endl;
*/
	//==============battleship=================

	//Component::Transform * BattleshipTransform = Battleship->getComponent<Component::Transform>();
	//PlayerTransform->lookAt(glm::vec3(1.0f, 0.0f, 0.0f));
	//Renderable *  BattleshipRenderable = Battleship->getComponent<Renderable>();

	//glm::vec3 BBosition = Battleship->getComponent<Component::Transform>()->getPosition();
	////glm::vec3 BattleshipPos = glm::vec3(0.0f, -30.0f, -80.0f);
	//BattleshipTransform->translate(glm::vec3(0.0f, 0.0f, 80.0f));

	//BattleshipRenderable->scale_ = glm::vec3(1.0f, 1.0f, 1.0f);
	//BattleshipRenderable->rotate_ = BattleshipTransform->getOrientation();
	//BattleshipRenderable->translate_ = BattleshipTransform->getPosition();


/*
	std::cout << type <<
		"    , The position of parentPos is (" << playerPosition.x << ", " << playerPosition.y << ", " << playerPosition.z << ")" << std::endl;

*/
	
		if (Input::Keyboard::instance()->IsTriggered(Key_SCANCODE_X)) {
				Engine::instance()->PushActiveLevel(new Level::Level_temp(std::string("Level_temp")));
				return;
		}
	if (Input::Keyboard::instance()->IsTriggered(Key_SCANCODE_Z)) {
				Engine::instance()->GotoNextLevel(new Level::Level_temp(std::string("Level_temp")));
				return;
		}
	
	
}





