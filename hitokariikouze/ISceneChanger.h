#pragma once
typedef enum {
	eScene_Title,
	eScene_GamePlay,
	eScene_Ending,

	eScene_None,
}eScene;

class ISceneChanger
{
public:

	virtual ~ISceneChanger();
	virtual void ChangeScene(eScene NextScene) = 0;
private:

};