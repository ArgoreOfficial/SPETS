#pragma once

#include <Wyvern/Core/iSceneObject.h>

class cImportingWindow : public wv::iSceneObject
{
public:
	cImportingWindow();
	~cImportingWindow();

	void drawUI() override;

};