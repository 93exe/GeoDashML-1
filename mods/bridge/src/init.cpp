#include <Geode/Geode.hpp>
#include "bridge.hpp"
#include "input_buffer/Config.hpp"
#include "input_buffer/OpenUiSetting.hpp"

using namespace geode::prelude;

$on_mod(Loaded) {
    auto result = Mod::get()->registerCustomSettingType(
        "open-ui",
        [](std::string key, std::string modID, matjson::Value const& json) {
            return buf::OpenUiSetting::parse(key, modID, json);
        });
    if (!result) {
        log::error("Could not register the settings window button: {}", result.unwrapErr());
    }
    buf::loadConfig();
    gdml::startBridgeServer();
}
