#include "Disabler.h"

#include "../../../Utils/Target.h"
#include "../ModuleManager.h"

Disabler::Disabler() : IModule(0, Category::EXPLOIT, "Disables AntiCheats") {
	registerEnumSetting("Mode", &this->mode, 0);
	mode.addEntry("Nethergames", 0);
	mode.addEntry("Mineville", 1);
#ifdef _DEBUG
	mode.addEntry("Hive", 2);
#endif
}

Disabler::~Disabler() {
}

const char* Disabler::getModuleName() {
	return "Disabler";
}

void Disabler::onEnable() {
	if (mode.getSelectedValue() == 3)
		counter = 1;
}

void Disabler::onTick(C_GameMode* gm) {
	auto speed = moduleMgr->getModule<Speed>();
	auto d = moduleMgr->getModule<Disabler>();
	//if (g_Data.canUseMoveKeys()) {
	if (mode.getSelectedValue() == 0 && !gm->player->onGround) {
		C_MovePlayerPacket pNether(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&pNether);
	}
	if (mode.getSelectedValue() == 1 && !gm->player->onGround) {
		C_MovePlayerPacket Mineville(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&Mineville);
	}
	//}
#ifdef _DEBUG
	if (mode.getSelectedValue() == 2) {
		auto player = g_Data.getLocalPlayer();
		if (counter == 6) {
			counter = 1;
		} else {
			counter++;
		}
		if (gm->player->damageTime >= 1 && counter == 4) {
			speed->setEnabled(true);
		} else {
			speed->setEnabled(false);
			if (player->damageTime >= 1 && counter == 6) {
				setEnabled(false);
				if (player->damageTime > 1)
					d->setEnabled(false);
			}
		}
	}
#endif
}

void Disabler::onSendPacket(C_Packet* packet) {
	//if (g_Data.canUseMoveKeys()) {
	if (packet->isInstanceOf<C_MovePlayerPacket>()) {
		auto player = g_Data.getLocalPlayer();
		if (mode.getSelectedValue() == 1 && !player->onGround) {
			C_MovePlayerPacket* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
			movePacket->onGround = true;
		}
	}
	if (packet->isInstanceOf<C_MovePlayerPacket>()) {
		auto player = g_Data.getLocalPlayer();
		if (mode.getSelectedValue() == 1 && !player->onGround) {
			C_MovePlayerPacket* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
			if (g_Data.canUseMoveKeys()) {
				movePacket->onGround = true;
			}
		}
	}
	//}
}