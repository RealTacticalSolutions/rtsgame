#pragma once

class BluePrint {


private:
	

public:
	BluePrint(RenderObject& renderObject) : renderObject(renderObject)
	{};

	RenderObject& renderObject;
	Mesh mesh;
	char* texture;
};