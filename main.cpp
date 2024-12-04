#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_opengl3.h"
#include "Imgui/imgui_impl_glfw.h"

//include imgui before glad and glfw and include glad before glfw
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>






int main() {
	//GLFW window creating and setting up

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GL_TRUE);


	//with floating it puts your window on top of everything (you can't click through it with this
	//glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);


	GLFWwindow* window = glfwCreateWindow(1920, 1080, "Cool OpenGL window! ", NULL, NULL);

	if (!window) {

		std::cout << "Fail! Window could't get created! \n";
		glfwDestroyWindow(0);
		return 0;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, 1920, 1080);


	//IMGUI initialization
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");


	bool active = true;



	//main loop
	while (!glfwWindowShouldClose(window)) {


		//clear the color buffer
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();


		//What should ImGui draw (Render) (always after OpenGL rendering)
		ImGui::Begin("heyyy");

		ImGui::Text("Hey, this is nice and easy!");


		ImGui::Checkbox("ESP", &active);
		if (ImGui::Button("!!Close!!")) {

			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();


			glfwDestroyWindow(window);

			glfwTerminate();


			return 0;

		}


		ImDrawList* draw_list = ImGui::GetForegroundDrawList();

		ImVec2 p1 = ImVec2(1000, 900);
		ImVec2 p2 = ImVec2(1200, 1000);

		draw_list->AddLine(p1, p2, IM_COL32(255, 0, 0, 255), 10.0f);

		ImGui::End();




		//prepare ImGUi draw data for render

		ImGui::Render();

		//Render the draw data with opengl

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//swap buffer

		glfwSwapBuffers(window);

		//handle events

		glfwPollEvents();



	}

	//shutdown in order everything 

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();


	glfwDestroyWindow(window);

	glfwTerminate();


	return 0;
}