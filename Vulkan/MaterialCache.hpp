#pragma once

enum Pipelines {
	Default,
	GUI
};

class MaterialCache {

public:
	VulkanDriver* _Driver = VK_NULL_HANDLE;
	std::vector<PipelineObject*> Pipes;
	//

	MaterialCache(VulkanDriver* Driver) : _Driver(Driver) {
		CreateDefault();
		CreateGUI();
	}

	~MaterialCache() {
		for (auto Pipe : Pipes) {
			delete Pipe;
		}
	}

	Pipeline::Default* GetPipe_Default() {
		return static_cast<Pipeline::Default*>(Pipes[Default]);
	}
	Pipeline::GUI* GetPipe_GUI() {
		return static_cast<Pipeline::GUI*>(Pipes[GUI]);
	}


	//
	//
	//	Create Default Pipe
	//
	//
	void CreateDefault() {
		printf("Create Default Pipe\n");
		Pipes.emplace_back(new Pipeline::Default(_Driver));

	}

	//
	//
	//	Create GUI Pipe
	//
	//
	void CreateGUI() {
		printf("Create GUI Pipe\n");
		Pipes.emplace_back(new Pipeline::GUI(_Driver));
	}
};