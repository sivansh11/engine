#include "pch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "base_script.h"
#include "module_loader.h"

add_option("-pthread")

add_include_dir("../core/include")
add_include_dir("../external/glad/include")
add_include_dir("../external/glfw/include")
add_include_dir("../external/imgui/imgui")
add_include_dir("../external/imgui/imgui/backends")

add_link_library_path("core")
add_link_libraries("core")

add_link_library_path("external/glad")
add_link_library_path("external/glfw/src")
add_link_library_path("external/imgui")
add_link_libraries("glad")
add_link_libraries("imgui")
add_link_libraries("glfw3")
add_link_libraries("stdc++fs")

class Window : public BaseScript
{
public:
    Window(DataManager &dataManager) 
        : dataManager(dataManager)
    { onCreate(); }
    ~Window() { onDelete(); }
    void onCreate() override
    {
        assert(glfwInit() && "Couldnt init glfw");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(600, 600, "name", NULL, NULL);

        assert(window && "Couldnt create window");

        glfwMakeContextCurrent(window);

        dataManager.allocate<GLFWwindow*>("window") = window;

        gladLoadGL();

        IMGUI_CHECKVERSION();
        ImGuiContext *context = ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 460");

        dataManager.allocate<ImGuiContext*>("context") = context;

        imguiModule = new DynamicModule("../script/src/imgui_script.cpp", "../script/out/imgui_script.so", dataManager);
    }
    void onDelete() override
    {
        delete imguiModule;
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext(); 

        glfwDestroyWindow(window);
        glfwTerminate();
    }
    void onUpdate(float deltaTime) override
    {
        glfwPollEvents();

        glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        imguiModule->onUpdate(deltaTime);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);

        if (glfwWindowShouldClose(window)) 
        {
            // dataManager.dispatcher->post<AppShouldClose>();
            dataManager.get<Dispatcher>("dispatcher").post<AppShouldClose>();
        }

        glfwSwapBuffers(window);
    }

private:
    DataManager &dataManager;
    GLFWwindow* window;
    DynamicModule *imguiModule;
};

extern "C" BaseScript* create_(DataManager &dataManager)
{
    return new Window(dataManager);
}
extern "C" void remove_(BaseScript* script)
{
    delete (Window*)script;
}
