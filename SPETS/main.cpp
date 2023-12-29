#include "GameLayer.h"

int main()
{
	auto& app = wv::cApplication::getInstance();

	app.pushLayer( new GameLayer() );
	app.run();

	return 0;
}
