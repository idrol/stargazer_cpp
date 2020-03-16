#include "LevelFormatter.h"
#include "EntityFormatter.h"
#include "../../../Engine/Level/Level.h"
#include "../../../Engine/Entity/EntityManager.h"
#include "../../../Engine/Entity/Entity.h"
#include "../../../Engine/Scripting/Level/LevelScript.h"
#include "../../../Engine/Scripting/Level/LevelScriptInstance.h"
#include "../../../Engine/Scripting/ScriptingEngine.h"
#include "../../../ResourceManager/ResourceManager.h"

nlohmann::json LevelFormatter::serialize(Level *level) {
    EntityFormatter *entityFormatter = new EntityFormatter();
    nlohmann::json entites = {};
    for(auto & entry: level->getEntityManager()->getEntites()) {
        nlohmann::json entityJson = entityFormatter->serialize(entry.second);
        if(!entityJson.empty()) {
            entites.push_back(entityJson);
        }
    }

    nlohmann::json levelData = {
            {"name", level->getName()},
            {"entites", entites},
            {"script", level->getScriptInstance()->getScript()->getLocalScriptPath()}
    };
    delete entityFormatter;
    return levelData;
}

void LevelFormatter::deserialize(nlohmann::json levelData, Level *level) {
    LevelScript *levelScript = new LevelScript(levelData["script"].get<std::string>(), ResourceManager::getInstance().resolvePath(levelData["script"].get<std::string>()));
    ScriptingEngine::getInstance().registerScript(levelScript);
    auto *scriptInstance = levelScript->createInstance(level);
    level->setScriptInstance(scriptInstance);
    nlohmann::json entitesJson = levelData["entites"];
    if(!entitesJson.empty()) {
        auto *entityFormatter = new EntityFormatter();
        for(auto & entity: entitesJson) {
            entityFormatter->deserialize(entity, level->getEntityManager());
        }
        delete entityFormatter;
    }
}
