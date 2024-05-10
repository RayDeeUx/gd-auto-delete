#include <Geode/modify/LevelInfoLayer.hpp>

using namespace geode::prelude;

bool save = false;

class $modify(lil, LevelInfoLayer) {
	bool init(GJGameLevel* p0, bool p1) {
		if (!LevelInfoLayer::init(p0, p1)) {return false;}

		auto menu = CCMenu::create();

		menu->setID("toggler-menu"_spr);
		menu->setPosition(-62, -15);
		menu->setScale(0.47);

		auto deleteToggledButton = CCMenuItemSpriteExtra::create(
			ButtonSprite::create("Do save"),
			this,
			menu_selector(lil::onToggleSaved)
		);

		deleteToggledButton->setID("delete-toggled"_spr);
		deleteToggledButton->setPosition(0,0);
		
		auto saveToggledButton = CCMenuItemSpriteExtra::create(
			ButtonSprite::create("Do delete"),
			this,
			menu_selector(lil::onToggleSaved)
		);

		saveToggledButton->setID("save-toggled"_spr);
		saveToggledButton->setPosition(0,0);

		menu->addChild(saveToggledButton);
		menu->addChild(deleteToggledButton);

		this->addChild(menu);

		saveToggled();

		return true;
	}

	void onBack(cocos2d::CCObject* sender) {
		LevelInfoLayer::onBack(sender);
		if (!save) GameLevelManager::get()->deleteLevel(this->m_level);
	}

	void saveToggled() {
		CCMenuItemSpriteExtra* saveToggledButton = static_cast<CCMenuItemSpriteExtra*>(this->getChildByID("toggler-menu"_spr)->getChildByID("save-toggled"_spr));
		CCMenuItemSpriteExtra* deleteToggledButton = static_cast<CCMenuItemSpriteExtra*>(this->getChildByID("toggler-menu"_spr)->getChildByID("delete-toggled"_spr));
		saveToggledButton->setVisible(save); 
		deleteToggledButton->setVisible(!save);
	}

	void onToggleSaved(CCObject*sender) {
		save = !save;
		saveToggled();
	}
};