#include "pch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "base_script.h"

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

class I : public BaseScript
{
public:
    I(DataManager &dataManager) : dataManager(dataManager) { onCreate(); }
    ~I() { onDelete(); }
    void onCreate() override
    {
        ImGui::SetCurrentContext(dataManager.get<ImGuiContext*>("context"));
    }
    void onDelete() override
    {
           
    }
    void onUpdate(float deltaTime) override
    {
        ImGui::Begin("hi");

        ImGui::Text("You can add or remove stuff at runtinme");
        ImGui::Text("It will recompile and relink automatically");

        ImGui::End();
    }

private:
    DataManager &dataManager;
    GLFWwindow *second_window;
};

extern "C" BaseScript* create_(DataManager &dataManager)
{
    return new I(dataManager);
}
extern "C" void remove_(BaseScript* script)
{
    delete (I*)script;
}
