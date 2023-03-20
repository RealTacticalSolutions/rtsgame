class Scene {

private:
	

public:
	Scene() {};

	std::vector<GameObject> gameObjects;

	void addObject();
	void removeObject();

	std::unique_ptr<renderer> renderer;
};