#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/binding/GameLevelManager.hpp>

bool save = false;

class $modify(lil, LevelInfoLayer) {
	bool init(GJGameLevel* p0, bool p1) {
		if (!LevelInfoLayer::init(p0, p1)) {return false;}

		auto menu = CCMenu::create();

		menu->setID("bingy3.dosave-toggler-menu");
		menu->setPosition(10, 22.5);
		menu->setScale(0.7);

		auto deleteToggledButton = CCMenuItemSpriteExtra::create(
			ButtonSprite::create("Do save"),
			this,
			menu_selector(lil::onToggleSaved)
		);

		deleteToggledButton->setID("bingy3.delete-toggled");
		deleteToggledButton->setPosition(0,0);
		
		auto saveToggledButton = CCMenuItemSpriteExtra::create(
			ButtonSprite::create("Do delete"),
			this,
			menu_selector(lil::onToggleSaved)
		);

		saveToggledButton->setID("bingy3.save-toggled");
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
		CCMenuItemSpriteExtra* saveToggledButton = static_cast<CCMenuItemSpriteExtra*>(this->getChildByID("bingy3.dosave-toggler-menu")->getChildByID("bingy3.save-toggled"));
		CCMenuItemSpriteExtra* deleteToggledButton = static_cast<CCMenuItemSpriteExtra*>(this->getChildByID("bingy3.dosave-toggler-menu")->getChildByID("bingy3.delete-toggled"));
		saveToggledButton->setVisible(save); 
		deleteToggledButton->setVisible(!save);
	}

	void onToggleSaved(CCObject*sender) {
		save = !save;
		saveToggled();
	}
};