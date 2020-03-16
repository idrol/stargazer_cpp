#include "CAPITransformComponent.h"
#include "../Engine/Entity/Component/TransformComponent.h"
#include <glm/glm.hpp>

MonoArray *getTransformComponentPosition(CComponent component) {
    TransformComponent *transform = reinterpret_cast<TransformComponent*>(component);
    glm::vec3 position = transform->getPosition();
    MonoArray *array = mono_array_new(mono_domain_get(), mono_get_single_class(), 3);
    mono_array_set(array, float, 0, position.x);
    mono_array_set(array, float, 1, position.y);
    mono_array_set(array, float, 2, position.z);
    return array;
}
