#pragma once
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Obj.h"

class LayerManager
{
private:
	std::list<std::pair<std::string, std::unique_ptr<Obj>>> objectList;

public:
	LayerManager() = default;

	void addObj(const std::string& key, std::unique_ptr<Obj> obj) {
		objectList.emplace_back(key, std::move(obj));
	}

	void clearObj() {
		objectList.clear();
	}

	void updateAll(const sf::Vector2f& mousePos)
	{
		bool updated = false;
		for (auto it = objectList.rbegin(); it != objectList.rend(); ++it) {
			if (!updated && it->second->update(mousePos))
				updated = true;
			else
				it->second->reset();
		}
	}


	void renderAll(sf::RenderTarget& target) {
		auto it = objectList.begin();
		for (; it != objectList.end(); it++) {
			it->second->render(target);
		}
	}

	void pushObjToFront(const std::string& key) {
		for (auto it = objectList.begin(); it != objectList.end(); ++it) {
			if (it->first == key) {
				auto pair = std::move(*it);
				objectList.erase(it);
				objectList.push_back(std::move(pair));
				return;
			}
		}
	}

	void pushObjToBack(const std::string& key) {
		for (auto it = objectList.begin(); it != objectList.end(); ++it) {
			if (it->first == key) {
				objectList.splice(objectList.begin(), objectList, it);
				return;
			}
		}
	}

	void renderOneObj(sf::RenderTarget& target, const std::string& key) {
		for (auto& pair : objectList) {
			if (pair.first == key) {
				pair.second->render(target);
				return;
			}
		}
	}

	bool isPointerOverUI(const sf::Vector2f& mousePos) {
		for (auto& pair : objectList) {
			if (pair.second->isMouseOver(mousePos)) return true;
		}
		return false;
	}

	void resetAll()
	{
		for (auto& pair : objectList) 
			pair.second->reset();
	}
};
