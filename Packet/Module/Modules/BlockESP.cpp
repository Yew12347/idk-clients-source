#include "../../DrawUtils.h"
#include "BlockESP.h"

BlockESP::BlockESP() : IModule(0, Category::VISUAL, "Outlines Blocks") {
	registerBoolSetting("Spawners", &spawner, spawner);
	registerBoolSetting("Diamond", &dOre, dOre);
	registerBoolSetting("Emerald", &eOre, eOre);
	registerBoolSetting("Redstone", &rOre, rOre);
	registerBoolSetting("Gold", &gOre, gOre);
	registerBoolSetting("Iron", &iOre, iOre);
	registerBoolSetting("Coal", &cOre, cOre);
	registerIntSetting("Range", &range, range, 1, 15);
	registerFloatSetting("Width", &width, width, 0.3, 1);
}

BlockESP::~BlockESP() {
}

const char* BlockESP::getModuleName() {
	return ("BlockESP");
}

void BlockESP::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	if (g_Data.canUseMoveKeys() && g_Data.getLocalPlayer() != nullptr) {
		auto player = g_Data.getLocalPlayer();
		vec3_t* pos = player->getPos();
		for (int x = (int)pos->x - range; x < pos->x + range; x++) {
			for (int z = (int)pos->z - range; z < pos->z + range; z++) {
				for (int y = (int)pos->y - range; y < pos->y + range; y++) {
					vec3_t blockPos = vec3_t(x, y, z);
					int id = (int)player->region->getBlock(blockPos)->toLegacy()->blockId;
					bool spRender = false;
					bool dRender = false;
					bool eRender = false;
					bool rRender = false;
					bool gRender = false;
					bool iRender = false;
					bool cRender = false;

					if (id == 52 && spawner) spRender = true;  // Spawner
					if (id == 56 && dOre) dRender = true;   // Diamond
					if (id == 129 && eOre) eRender = true;  // Emerald
					if (id == 73 && rOre) rRender = true;   // Redstone
					if (id == 74 && rOre) rRender = true;   // Redstone
					if (id == 14 && gOre) gRender = true;   // Gold
					if (id == 15 && iOre) iRender = true;   // Iron
					if (id == 16 && cOre) cRender = true;   // Coal

					if (spRender) {
						DrawUtils::setColor(0.03, 0.13, 0.61, 1);
						DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), width);
					} else if (dRender) {
						DrawUtils::setColor(0.2, 0.9, 1, 1);
						DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), width);
					} else if (eRender) {
						DrawUtils::setColor(0, 0.7, 0, 1);
						DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), width);
					} else if (rRender) {
						DrawUtils::setColor(0.8, 0, 0, 1);
						DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), width);
					} else if (gRender) {
						DrawUtils::setColor(1, 0.7, 0, 1);
						DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), width);
					} else if (iRender) {
						DrawUtils::setColor(1, 0.9, 0.8, 1);
						DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), width);
					} else if (cRender) {
						DrawUtils::setColor(0.3, 0.3, 0.3, 1);
						DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), width);
					}
				}
			}
		}
	}
}