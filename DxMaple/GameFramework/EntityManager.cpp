#include "stdafx.h"
#include "EntityManager.h"
#include "CollisionDetection.h"
#include "SceneManager.h"
IMPLEMENT_SINGLETON(EntityManager)
EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
	for (auto& entityList : entities_)
		entityList.second.clear();
}

void EntityManager::update()
{

	lock_guard<mutex> lock(entityLock_);

	for (auto& insertEntity : entitiesInserted_)
	{
		entities_[insertEntity.first].emplace_back(insertEntity.second);
	}
	entitiesInserted_.clear();

	for (auto& entityList : entities_)
	{
		for (auto& entity : entityList.second)
		{
			entity->update();
			if (entity->hasComponent<BoxCollider>())
				entitiesForCollision_.emplace_back(entity);
		}
	}

	if (entitiesForCollision_.size() >= 2)
	{
		for (auto& firstIter = entitiesForCollision_.begin(); firstIter != entitiesForCollision_.end() - 1; ++firstIter)
		{
			for (auto& secondIter = firstIter + 1; secondIter != entitiesForCollision_.end(); ++secondIter)
			{
				CollisionDetection::BoxColliderDetection(&*(*firstIter), &*(*secondIter));
			}
		}
		entitiesForCollision_.clear();
	}


}

void EntityManager::lateUpdate()
{
	lock_guard<mutex> lock(entityLock_);

	for (auto& entityList : entities_)
		for (auto& entity : entityList.second)
			entity->lateUpdate();
}

void EntityManager::render()
{
	lock_guard<mutex> lock(entityLock_);
	lock_guard<mutex> releaseLock(releaseLock_);

	for (auto& entityList : entities_)
	{
		for (auto& entity : entityList.second)
		{
			if (entity->hasComponent<Transform>())
				entitiesForRenderSorting_.emplace_back(entity);
		}
	}

	if (entitiesForRenderSorting_.empty())
		return;
		
	
	
	sort(entitiesForRenderSorting_.begin(), entitiesForRenderSorting_.end(),
		[](const shared_ptr<Entity>& firstEntity, const shared_ptr<Entity>& secondEntity) {
		Transform& firstTransform = firstEntity->getComponent<Transform>();
		Transform& secondTransform = secondEntity->getComponent<Transform>();

		if (firstTransform.position_.z > secondTransform.position_.z)
			return true;
		else
			return false;
	});

	/*sort(entitiesForRenderSorting_.begin(), entitiesForRenderSorting_.end(),
		[](const shared_ptr<Entity>& firstEntity, const shared_ptr<Entity>& secondEntity) {

		if (!firstEntity->hasComponent<AtlasAnimation>() || !secondEntity->hasComponent<AtlasAnimation>())
			return false;


		AtlasAnimation& firstAnim = firstEntity->getComponent<AtlasAnimation>();
		AtlasAnimation& secondAnim = secondEntity->getComponent<AtlasAnimation>();


		if (firstAnim.isZRender > secondAnim.isZRender)
			return true;
		else
			return false;
	});*/


	for (auto& entity : entitiesForRenderSorting_)
	{
		entity->render();
	}
	entitiesForRenderSorting_.clear();
	//entitiesForRenderSorting_.shrink_to_fit();
}

void EntityManager::releaseAll(ObjectPool<Entity>* entityPool)
{
	lock_guard<mutex> lock(releaseLock_);

	entitiesForCollision_.clear();
	entitiesForRenderSorting_.clear();

	for (auto& entityList : entities_)
	{
		for (auto& iter = entityList.second.begin(); iter != entityList.second.end();++iter)
		{
			if (nullptr != entityPool)
			{
				entityPool->release(*iter); //실 객체는 오브젝트풀로 보내고
			}
		}
		entityList.second.clear(); //얘넨 링크 끊음 (sp라서 링크끊었는데 count 0  되면 소멸)

	}

}

void EntityManager::releaseEntity(Entity::ENTITYTYPE entityType, ObjectPool<Entity>* entityPool)
{
	if (entities_[entityType].empty())
		return;

	lock_guard<mutex> lock(releaseLock_);

	entitiesForCollision_.clear();
	entitiesForRenderSorting_.clear();

	for (auto& iter = entities_[entityType].begin(); iter != entities_[entityType].end();++iter)
	{
		
		if (nullptr != entityPool)
		{
			entityPool->release(*iter);
		}
	}
	entities_[entityType].clear();
}

void EntityManager::refresh(ObjectPool<Entity>* entityPool)
{
	lock_guard<mutex> lock(entityLock_);

	for (auto& entityList : entities_)
	{
		entityList.second.erase(remove_if(entityList.second.begin(), entityList.second.end(),
			[&](shared_ptr<Entity> entity)
			{
				bool isActive = entity->isActive();
				if (!isActive)
				{
					entity->eraseAllComponents();
					if (nullptr != entityPool)
						entityPool->release(move(entity));//스마트포인터소육권이전 //근데 참조형은 l벨류만 받아야되서 move빼야하는거아님?  템플릿이라 오류못잡는거고
					return true;
				}
				else
					return false;

			}), entityList.second.end());
		
	}

}


HRESULT EntityManager::insertEntity(shared_ptr<Entity>& insertEntity)
{
	//lock_guard<mutex> lock(entityLock_);

	/*Entity::ENTITYTYPE type = insertEntity->getType();
	auto& find_iter = entities_.find(type);
	if (find_iter == entities_.end())
		entities_.emplace(type, vector<shared_ptr<Entity>>());*/
	entitiesInserted_.emplace_back(make_pair(insertEntity->getType(), insertEntity));
	//entities_[type].emplace_back(insertEntity);

	return S_OK;
}

Entity* EntityManager::findEntity(int userIDN, int entityNumber, Entity::ENTITYTYPE entityType)
{
	//lock_guard<mutex> lock(entityLock_);

	for (auto& entityList : entities_)
	{
		for (auto& entity : entityList.second)
		{
			int findUserIDN, findEntityNumber;
			Entity::ENTITYTYPE findEntityType;
			entity->getEntityNetworkInfo(findUserIDN, findEntityNumber, findEntityType);

			if (userIDN == findUserIDN && entityNumber == findEntityNumber && entityType == findEntityType)
				return entity.get();
		}
	}
	return nullptr;
}

shared_ptr<Entity> EntityManager::findEntitySharedPtr(int userIDN, int entityNumber, Entity::ENTITYTYPE entityType)
{
	for (auto& entityList : entities_)
	{
		for (auto& entity : entityList.second)
		{
			int findUserIDN, findEntityNumber;
			Entity::ENTITYTYPE findEntityType;
			entity->getEntityNetworkInfo(findUserIDN, findEntityNumber, findEntityType);

			if (userIDN == findUserIDN && entityNumber == findEntityNumber && entityType == findEntityType)
				return entity;
		}
	}
	return shared_ptr<Entity>(nullptr);
}

shared_ptr<Entity> EntityManager::findEntityWithPointer(Entity* findEntity)
{
	for (auto& entityList : entities_)
	{
		for (auto& entity : entityList.second)
		{

			if (entity.get()== findEntity)
				return entity;
		}
	}
	return shared_ptr<Entity>(nullptr);
}

void EntityManager::eraseEntity(int userIDN, int entityNumber, Entity::ENTITYTYPE entityType)
{
	for (auto& iter = entities_[entityType].begin();iter != entities_[entityType].end();++iter)
	{
		int findUserIDN, findEntityNumber;
		Entity::ENTITYTYPE findEntityType;
		(*iter)->getEntityNetworkInfo(findUserIDN, findEntityNumber, findEntityType);
		if (userIDN == findUserIDN && entityNumber == findEntityNumber && entityType == findEntityType)
		{
			(*iter)->setActive(false);
			break;
		}
	}
}

void EntityManager::getColliderEntities(vector<shared_ptr<Entity>>& entities)
{
	//처음엔 비어있어야됨
	if (!entities.empty())
		return;

	for (auto& entityList : entities_)
	{
		for (auto& entity : entityList.second)
		{
			if (entity->hasComponent<BoxCollider>())
				entities.emplace_back(entity);
		}
	}
}

