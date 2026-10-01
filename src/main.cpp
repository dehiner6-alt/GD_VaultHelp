#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp>
#include <Geode/modify/SecretLayer.hpp>
#include <Geode/modify/SecretLayer2.hpp>
#include <Geode/modify/SecretLayer3.hpp>

using namespace geode::prelude;

// --- CLASE DEL POPUP UNIFICADA ---
class VaultPopup : public Popup<std::string> {
protected:
    bool setup(std::string vaultName) override {
        // Título centrado arriba
        auto title = CCLabelBMFont::create((vaultName + " Helper").c_str(), "goldFont.fnt");
        title->setPosition(m_size.width / 2, m_size.height - 20.f);
        title->setScale(0.6f);
        m_mainLayer->addChild(title);

        // Códigos reales para cada bóveda
        std::vector<std::string> codes;
        if (vaultName == "The Vault") {
            codes = {"Lenny", "Blockbite", "Spooky", "Neverending", "Mule", "Ahead", "Gandalfpotter", "Sparky", "Robotop", "Finalboss"};
        } 
        else if (vaultName == "Vault of Secrets") {
            codes = {"Octocube", "Brainpower", "Seven", "Thechickenisonfire", "The Challenge", "Gimmiethecolor", "Cod3breaker", "Glubfub", "TheChickenisReady", "D4shg30me7ry"};
        } 
        else if (vaultName == "Chamber of Time") {
            codes = {"Volcano", "River", "Silence", "Darkness", "Hunger", "Givemehelper", "Backontrack"};
        }

        // Listar los códigos con un botón de "Copiar :D" al lado
        float startY = m_size.height - 50.f;
        for (const auto& code : codes) {
            auto label = CCLabelBMFont::create(code.c_str(), "chatFont.fnt");
            label->setAnchorPoint({0.f, 0.5f});
            label->setPosition(25.f, startY);
            label->setScale(0.5f);
            m_mainLayer->addChild(label);

            auto btnSprite = ButtonSprite::create("Copy", "goldFont.fnt", "GJ_button_01.png");
            btnSprite->setScale(0.45f);

            auto copyBtn = CCMenuItemSpriteExtra::create(
                btnSprite,
                this,
                menu_selector(VaultPopup::onCopyCode)
            );
            copyBtn->setUserObject(CCString::create(code));

            auto menu = CCMenu::create();
            menu->addChild(copyBtn);
            menu->setPosition(m_size.width - 45.f, startY);
            m_mainLayer->addChild(menu);

            startY -= 26.f; 
        }

        return true;
    }

    void onCopyCode(CCObject* sender) {
        if (auto btn = typeinfo_cast<CCMenuItemSpriteExtra*>(sender)) {
            if (auto strObj = typeinfo_cast<CCString*>(btn->getUserObject())) {
                std::string code = strObj->getCString();
                
                // Copiar al portapapeles y mostrar notificación
                geode::utils::clipboard::write(code);
                Notification::create("Copied to clipboard!", NotificationIcon::Success)->show();
            }
        }
    }

public:
    static VaultPopup* create(std::string vaultName) {
        auto ret = new VaultPopup();
        if (ret && ret->initAnchored(300.f, 220.f, vaultName)) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
};

// --- 1. THE VAULT (Bóveda Principal) ---
class $modify(MySecretLayer, SecretLayer) {
    bool init() {
        if (!SecretLayer::init()) return false;

        auto btn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("Vault Helper", "goldFont.fnt", "GJ_button_01.png"),
            this,
            menu_selector(MySecretLayer::onOpenHelper)
        );
        btn->setScale(0.6f);

        auto menu = CCMenu::create();
        menu->addChild(btn);
        
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        menu->setPosition(winSize.width - 65.f, winSize.height - 25.f);
        this->addChild(menu);

        return true;
    }

    void onOpenHelper(CCObject*) {
        VaultPopup::create("The Vault")->show();
    }
};

// --- 2. VAULT OF SECRETS (Bóveda de los Secretos) ---
class $modify(MySecretLayer2, SecretLayer2) {
    bool init() {
        if (!SecretLayer2::init()) return false;

        auto btn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("Secrets Helper", "goldFont.fnt", "GJ_button_01.png"),
            this,
            menu_selector(MySecretLayer2::onOpenHelper)
        );
        btn->setScale(0.6f);

        auto menu = CCMenu::create();
        menu->addChild(btn);
        
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        menu->setPosition(winSize.width - 70.f, winSize.height - 25.f);
        this->addChild(menu);

        return true;
    }

    void onOpenHelper(CCObject*) {
        VaultPopup::create("Vault of Secrets")->show();
    }
};

// --- 3. CHAMBER OF TIME (Cámara del Tiempo) ---
class $modify(MySecretLayer3, SecretLayer3) {
    bool init() {
        if (!SecretLayer3::init()) return false;

        auto btn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("Chamber Helper", "goldFont.fnt", "GJ_button_01.png"),
            this,
            menu_selector(MySecretLayer3::onOpenHelper)
        );
        btn->setScale(0.6f);

        auto menu = CCMenu::create();
        menu->addChild(btn);
        
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        menu->setPosition(winSize.width - 70.f, winSize.height - 25.f);
        this->addChild(menu);

        return true;
    }

    void onOpenHelper(CCObject*) {
        VaultPopup::create("Chamber of Time")->show();
    }
};
