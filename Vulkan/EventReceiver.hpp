class EventReceiver {
	Gwen::Controls::Canvas* m_Canvas;
	int m_MouseX = 0;
	int m_MouseY = 0;

	static void char_callback(GLFWwindow* window, unsigned int codepoint)
	{
		EventReceiver* Rcvr = static_cast<EventReceiver*>(glfwGetWindowUserPointer(window));
		Gwen::UnicodeChar chr = (Gwen::UnicodeChar) codepoint;
		Rcvr->m_Canvas->InputCharacter(chr);
	}

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		EventReceiver* Rcvr = static_cast<EventReceiver*>(glfwGetWindowUserPointer(window));
		bool bDown = false;
		if (action == GLFW_PRESS || GLFW_REPEAT) {
			bDown = true;
		} else if(action == GLFW_RELEASE) {
			bDown = false;
		}
		int iKey = -1;
		if (key == GLFW_KEY_LEFT_SHIFT || GLFW_KEY_RIGHT_SHIFT) { iKey = Gwen::Key::Shift; }
		else if (key == GLFW_KEY_ENTER) { iKey = Gwen::Key::Return; }
		else if (key == GLFW_KEY_BACKSPACE) {
			iKey = Gwen::Key::Backspace;
		}
		else if (key == GLFW_KEY_DELETE) { iKey = Gwen::Key::Delete; }
		else if (key == GLFW_KEY_LEFT) { iKey = Gwen::Key::Left; }
		else if (key == GLFW_KEY_RIGHT) { iKey = Gwen::Key::Right; }
		else if (key == GLFW_KEY_TAB) { iKey = Gwen::Key::Tab; }
		else if (key == GLFW_KEY_SPACE) { iKey = Gwen::Key::Space; }
		else if (key == GLFW_KEY_HOME) { iKey = Gwen::Key::Home; }
		else if (key == GLFW_KEY_END) { iKey = Gwen::Key::End; }
		else if (key == GLFW_KEY_LEFT_CONTROL || GLFW_KEY_RIGHT_CONTROL) { iKey = Gwen::Key::Control; }
		else if (key == GLFW_KEY_SPACE) { iKey = Gwen::Key::Space; }
		else if (key == GLFW_KEY_UP) { iKey = Gwen::Key::Up; }
		else if (key == GLFW_KEY_DOWN) { iKey = Gwen::Key::Down; }
		if (iKey != -1) {
			printf("key %i %i\n", key, bDown);
			Rcvr->m_Canvas->InputKey(iKey, false);
			Rcvr->m_Canvas->InputKey(iKey, true);
			Rcvr->m_Canvas->InputKey(iKey, false);
		}
		/*Event NewEvent;
		NewEvent.Action = EventTypes::Keyboard;
		static_cast<EventReceiver*>(glfwGetWindowUserPointer(window))->OnEvent(NewEvent);*/
	}

	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		EventReceiver* Rcvr = static_cast<EventReceiver*>(glfwGetWindowUserPointer(window));
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
			Rcvr->m_Canvas->InputMouseButton(0, true);
		}
		else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
			Rcvr->m_Canvas->InputMouseButton(0, false);
		}
		else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
			Rcvr->m_Canvas->InputMouseButton(1, true);
		}
		else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
			Rcvr->m_Canvas->InputMouseButton(1, false);
		}
		Event NewEvent;
		NewEvent.Type = EventTypes::Mouse;
		if (action == GLFW_PRESS) {
			NewEvent.Action = EventActions::Press;
		}
		else if (action == GLFW_RELEASE) {
			NewEvent.Action = EventActions::Release;
		}
		else if (action == GLFW_REPEAT) {
			NewEvent.Action = EventActions::Repeat;
		}
		Rcvr->OnEvent(NewEvent);
	}

	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		EventReceiver* Rcvr = static_cast<EventReceiver*>(glfwGetWindowUserPointer(window));
		int x = xpos;
		int y = ypos;
		int dx = x - Rcvr->m_MouseX;
		int dy = y - Rcvr->m_MouseY;
		Rcvr->m_MouseX = x;
		Rcvr->m_MouseY = y;
		Rcvr->m_Canvas->InputMouseMoved(x, y, dx, dy);
	}

protected:
	enum EventTypes {
		Keyboard = 1,
		Mouse = 2
	};

	enum EventActions {
		Press = 1,
		Release = 2,
		Repeat = 3
	};

	struct Event {
		EventTypes Type;
		EventActions Action;
		//	Other Event Related Values
	};

public:
	virtual void OnEvent(Event& NewEvent) = 0;

	void SetGWEN(Gwen::Controls::Canvas* Canvas) {
		m_Canvas = Canvas;
	}

	friend class VulkanDriver;
};

class CustomEventReceiver : public EventReceiver {
	VulkanDriver* _Driver;
public:
	CustomEventReceiver(VulkanDriver* Driver) : _Driver(Driver) {

	}

	void OnEvent(Event& NewEvent) {
		if (NewEvent.Type == EventTypes::Keyboard) {
#ifdef _DEBUG
			printf("Keyboard\n");
#endif
			const std::vector<Vertex> vertices2 = {
			{{-0.7f, -0.7f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
			{{0.7f, -0.7f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
			{{0.7f, 0.7f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
			{{-0.7f, 0.7f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}
			};

			const std::vector<uint16_t> indices = {
			0, 1, 2, 2, 3, 0
			};
			//_Driver->_SceneGraph->createSkinnedMeshSceneNode(vertices2, indices);
		}
		else if (NewEvent.Type == EventTypes::Mouse) {
#ifdef _DEBUG
			printf("Mouse ");
#endif
			if (NewEvent.Action == EventActions::Press) {
#ifdef _DEBUG
				printf("Press\n");
#endif
				const std::vector<Vertex> vertices = {
					{{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
					{{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
					{{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
					{{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}
				};

				const std::vector<uint16_t> indices = {
					0, 1, 2, 2, 3, 0,
					4, 5, 6, 6, 7, 4
				};
				_Driver->_SceneGraph->createTriangleMeshSceneNode(vertices, indices);
			}
			else if (NewEvent.Action = EventActions::Release) {
#ifdef _DEBUG
				printf("Release\n");
#endif
			}
			else if (NewEvent.Action = EventActions::Repeat) {
#ifdef _DEBUG
				printf("Repeat\n");
#endif
			}
		}
	}
};