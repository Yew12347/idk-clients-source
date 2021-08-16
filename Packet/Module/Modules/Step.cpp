#include "Step.h"

Step::Step() : IModule(0, Category::MOVEMENT, "Increases your step height") {
	registerBoolSetting("Reverse", &reverse, reverse);
	registerFloatSetting("Height", &height, height, 1.f, 2.f);
}

Step::~Step() {
}

const char* Step::getModuleName() {
	return ("Step");
}

void Step::onTick(C_GameMode* gm) {
	gm->player->stepHeight = height;
	if (reverse) {
		if (gm->player->onGround && !gm->player->isInWater() && !gm->player->isInLava()) {
			gm->player->velocity.y = -1;
		}
	}
}

void Step::onDisable() {
	if (g_Data.getLocalPlayer() != nullptr)
		g_Data.getLocalPlayer()->stepHeight = 0.5625f;
}
