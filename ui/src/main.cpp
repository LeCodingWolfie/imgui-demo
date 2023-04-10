/* #include "../vendor/glfw/include/GLFW/glfw3.h"
#include "../vendor/imgui/backends/imgui_impl_glfw.h"
#include "../vendor/imgui/backends/imgui_impl_opengl3.h"
#include "../vendor/imgui/imgui.h" */

#include "GLFW/glfw3.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

#include <GLES2/gl2.h>
#include <stdio.h>

int windowHeight = 1280;
int windowWidth = 720;

bool showDemoWindow = true;

// Prints the information of an GLFW error every time it is thrown
void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main()
{
	glfwSetErrorCallback(glfw_error_callback);

	// Checks if GLFW can be initialized
	if (!glfwInit()) {
		printf("Cannot init.");
		return 1;
	}

	// Specifies the window's OpenGL and Shading Language versions
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	// Instantiates a 720p GLFW window
	GLFWwindow* window = glfwCreateWindow(windowHeight, windowWidth, "GLFW/OpenGL3", NULL, NULL);
	if (window == NULL) {
		printf("Cannot create window.");
		return 1;
	}

	// Adds the OpenGL "canvas" (known as context) to the window
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enables VSync

	// Initializes ImGui
	ImGui::CreateContext();

	// Accesses the ImGui's main configuration and I/O [1]
	ImGuiIO& io = ImGui::GetIO();

	// Sets ImGui dark theme
	ImGui::StyleColorsDark();

	// Initializes ImGui GLFW (platform) and GL3 (renderer) backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// Loops as long as the application is not closed
	while (!glfwWindowShouldClose(window)) {
		// Processes all events, such as mouse input
		glfwPollEvents();

		// Starts an ImGui frame through the backends, which can be drawn into
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Clears the framebuffer with color, which avoids flickering [2]
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draws a window on the frame
		ImGui::ShowDemoWindow(&showDemoWindow);

		// Renders ImGui's drawn input with OpenGL
		ImGui::Render(); // Finishes the frame
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window); // "Swaps buffers" (i.e. displays the drawn frame) [3]
	}

	// If in close, stops the backends, cleans up the canvas, and destroys the window
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
