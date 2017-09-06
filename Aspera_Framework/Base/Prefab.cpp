#include "Prefab.h"

Prefab::Prefab() : GameObject("PrefabGO"){}

Prefab::Prefab(char* name) : GameObject(name) {}

Prefab::~Prefab(){}

bool Prefab::Initialize(){return false;}

void Prefab::Shutdown(){}