#include "Scene.h"

/*
Sets this scene within the visualisation
@param visualisation The visualisation that is hosting the scene.
*/
Scene::Scene(Visualisation &visualisation)
    : visualisation(visualisation)
{
    this->visualisation.setScene(this);
}
/*
Calls the destructor
*/
void Scene::kill(){
}
/*
Registers an entity, so the scene can manage it's modelview and projection matrices and reloads
*/
void Scene::registerEntity(std::shared_ptr<Entity> ent)
{
    if (ent.get())
    {
        //Store value for later
        entities.push_back(ent);
        //Setup matrices
        ent->setModelViewMatPtr(this->visualisation.getCamera());
        ent->setProjectionMatPtr(&this->visualisation);
    }
    else
        fprintf(stderr, "Can't register a null entity!\n");
}
/*
Reloads all registered entities, then calls reload on the subclassed scene
*/
void Scene::_reload()
{
    printf("Reloading Shaders.\n");
    for (std::vector<std::shared_ptr<Entity>>::iterator i = entities.begin(); i != entities.end(); i++)
    {
        (*i)->reload();
    }
    reload();
}
