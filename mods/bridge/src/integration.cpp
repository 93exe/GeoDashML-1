#include <Geode/Geode.hpp>
#include "bridge.hpp"
#include "integration.hpp"
#include "input_buffer/Engine.hpp"

using namespace geode::prelude;

namespace integration {
    void onBridgeDetached() {
        buf::g_engine.onReset();
        buf::g_engine.resetMarks();
    }
}

class $modify(IntegrationPlayLayer, PlayLayer) {
    static void onModify(auto& self) {
        (void)self.setHookPriority("PlayLayer::playEndAnimationToPos", -2147483647);
    }

    void playEndAnimationToPos(cocos2d::CCPoint position) {
        if (gdml::isBridgeAttached()) {
            m_levelEndAnimationStarted = true;
            if (m_player1) m_player1->m_isLocked = true;
            if (m_player2) m_player2->m_isLocked = true;
            return;
        }
        if (buf::g_engine.isSimulating()) return;
        PlayLayer::playEndAnimationToPos(position);
    }
};
