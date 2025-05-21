#include "Model.h"
#include "func.h"
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
 
const glm::mat4 WorldMatrix = glm::mat4(1.0f);


int WinWidth;
int WinHeight;

glm::vec3 CamPosition;


int main() {

    GLFWwindow* window = InitAll(1024, 768, false);
    if (window == nullptr)
    {
        EndAll();
        return -1;
    }

    double start_time = glfwGetTime();

    // ���� �������� - �����, ����, �������, ���, ����, ����, ����2.

    //������� ��� �������� ��������� ������
    std::vector< glm::vec3 > temp_vertices;
    std::vector< glm::vec2 > temp_textures;
    std::vector< glm::vec3 > temp_normals;
    std::vector< glm::vec3 > temp_colors;
    std::vector< GLuint > temp_indices;
    size_t size;

    /////////////////////////////    �������� �����
    // �����
    // ����� ������� �����
    glm::vec3 boatPosition(0.0f, 0.0f, 0.0f);
    //�������� ��������� �� �����
    loadOBJ("Objects\\boat.obj", temp_vertices, temp_textures, temp_normals);
    size = temp_vertices.size();
    //�������� ������
    Model boat(window,1);
    //�������� ������ ������
    boat.load_coords(temp_vertices.data(), size);
    boat.load_normals(temp_normals.data(), temp_normals.size());
    boat.load_texcoord(temp_textures.data(), temp_textures.size());
    boat.setMaterial(glm::vec3(0.9f, 0.9f, 0.9f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.9f, 0.9f, 0.9f), 128 * 0.5);
    boat.load_shaders("matvs.glsl", "matfs.glsl");


    // ����
    glm::vec3 points[] = {
           { -0.5f,  0.5f, 0.0f},
           { -0.5f, -0.5f, 0.0f},
           {0.5f, -0.5f, 0.0f},
           {0.5f,  0.5f, 0.0f}
    };
    glm::vec2 textcoords[] = {
           {0.0f, 0.0f},
           {0.0f, 1.0f},
           {1.0f, 1.0f},
           {1.0f, 0.0f}
    };

    GLuint indices[] = { 0, 1, 3, 1, 2, 3 };

    glm::vec3 sea1Position(0.0f, 0.0f, 0.0f);
    // ������� ������ ��������������
    Model rectangle(window, 2);
    rectangle.load_coords(points, 4);
    rectangle.load_texcoord(textcoords, 4);
    rectangle.load_indices(indices, 6);
    // ��������� ������� � ��������
    rectangle.load_shaders("texvs.glsl", "texfs.glsl");
    rectangle.load_texture("Texture\\wave.jpg", "");


    // ���� 2
    glm::vec3 sea2Position(0.0f, 0.0f, 0.0f);
    sea2Position = { -1000, 0, 0 };
    // ������� ������ ��������������
    Model rectangle2(window, 2);
    rectangle2.load_coords(points, 4);
    rectangle2.load_texcoord(textcoords, 4);
    rectangle2.load_indices(indices, 6);
    // ��������� ������� � ��������
    rectangle2.load_shaders("texvs.glsl", "texfs.glsl");
    rectangle2.load_texture("Texture\\wave.jpg", "");


    // ����
    glm::vec3 tigerPosition(0.0f, 0.0f, 0.0f);
    //�������� ��������� �� �����
    loadOBJ("Objects\\tiger.obj", temp_vertices, temp_textures, temp_normals);
    size = temp_vertices.size();
    Model tiger(window,2);
    tiger.load_coords(temp_vertices.data(), size);
    tiger.load_normals(temp_normals.data(), temp_normals.size());
    tiger.load_texcoord(temp_textures.data(), temp_textures.size());
    tiger.load_shaders("texvs.glsl", "texfs.glsl");
    tiger.setMaterial(glm::vec3(0), glm::vec3(0), glm::vec3(0), 32);
    tiger.load_texture("Texture\\wool.jpg", "");

    // �������
    glm::vec3 manPosition(0.0f, 0.0f, 0.0f);
    //�������� ��������� �� �����
    loadOBJ("Objects\\man.obj", temp_vertices, temp_textures, temp_normals);
    size = temp_vertices.size();
    Model man(window, 2);
    man.load_coords(temp_vertices.data(), size);
    man.load_normals(temp_normals.data(), temp_normals.size());
    man.load_texcoord(temp_textures.data(), temp_textures.size());
    man.load_shaders("texvs.glsl", "texfs.glsl");
    man.setMaterial(glm::vec3(0), glm::vec3(0), glm::vec3(0), 32);
    man.load_texture("Texture\\cloth.jpg", "");

    // ���
    glm::vec3 whalePosition(0.0f, 0.0f, 0.0f);
    whalePosition = { -400.0, -1.0, 4.0 };
    //�������� ��������� �� �����
    loadOBJ("Objects\\whale.obj", temp_vertices, temp_textures, temp_normals);
    size = temp_vertices.size();
    Model whale(window, 2);
    whale.load_coords(temp_vertices.data(), size);
    whale.load_normals(temp_normals.data(), temp_normals.size());
    whale.load_texcoord(temp_textures.data(), temp_textures.size());
    whale.load_shaders("texvs.glsl", "texfs.glsl");
    whale.setMaterial(glm::vec3(0), glm::vec3(0), glm::vec3(0), 32);
    whale.load_texture("Texture\\leather.jpg", "");

    // ����
    genSphere(temp_indices, temp_vertices, temp_textures, temp_normals, 5, 50, 50);
    size = temp_vertices.size();
    Model sphere(window, 2);
    sphere.load_coords(temp_vertices.data(), size);
    sphere.load_normals(temp_normals.data(), temp_normals.size());
    sphere.load_texcoord(temp_textures.data(), temp_textures.size());
    sphere.load_indices(temp_indices.data(), temp_indices.size());
    sphere.setMaterial(glm::vec3(0), glm::vec3(0), glm::vec3(0), 128);
    sphere.load_shaders("texvs.glsl", "texfs.glsl");
    sphere.load_texture("Texture\\stars.jpg", "");

    // ����
    glm::vec3 moonPosition(0.0f, 0.0f, 0.0f);
    genSphere(temp_indices, temp_vertices, temp_textures, temp_normals, 5, 50, 50);
    size = temp_vertices.size();
    Model moon(window, 2);
    moon.load_coords(temp_vertices.data(), size);
    moon.load_normals(temp_normals.data(), temp_normals.size());
    moon.load_texcoord(temp_textures.data(), temp_textures.size());
    moon.load_indices(temp_indices.data(), temp_indices.size());
    moon.setMaterial(glm::vec3(0), glm::vec3(0), glm::vec3(0), 128);
    moon.load_shaders("texvs.glsl", "texfs.glsl");
    moon.load_texture("Texture\\moon.jpg", "");

    ////////////////////////////////////////   ���������  �����    /////////////////////
    LightsInfo Lights;

    Lights.numPLights = 3;

    glm::vec3 lightPos = { 1,1,0 };
    glm::vec3 la = { 0.2f, 0.2f, 0.2f };
    glm::vec3 ld = { 0.5f, 0.5f, 0.5f };
    glm::vec3 ls = { 1,1,1 };

    DirLight lSource;
    lSource.ambient = la;
    lSource.diffuse = ld;
    lSource.specular = ls;
    lSource.direction = glm::vec3(0, -1, 0);

    Lights.dirLight = lSource;

    // ������
    PointLight P;

    // ����� 2
    P.ambient = glm::vec3(1.0f, 1.0f, 1.0f);
    P.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
    P.specular = glm::vec3(1, 1, 1);
    P.position = whalePosition;
    P.constant = 1;
    P.linear = 0.01;
    P.quadratic = 0.001;
    Lights.pointLights.push_back(P);
    // ����� 1 ����
    P.ambient = glm::vec3(1.0f, 1.0f, 1.0f);
    P.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
    P.specular = glm::vec3(1, 1, 1);
    P.position = { -200, 200, -50 };
    P.constant = 1;
    P.linear = 0.01;
    P.quadratic = 0.00001;
    Lights.pointLights.push_back(P);

    //�������
    P.ambient = glm::vec3(0.0f, 0.1f, 0.1f);
    P.diffuse = glm::vec3(0.0f, 0.8f, 0.8f);
    P.specular = glm::vec3(1, 1, 1);
    P.position = glm::vec3(-1, -10, 0);
    P.constant = 1;
    P.linear = 0.01;
    P.quadratic = 0.000000001;
    Lights.pointLights.push_back(P);



    //������ �������� ������
    glm::mat4 MMatr = WorldMatrix;
    glm::mat4 VMatr = WorldMatrix;
    glm::mat4 PMatr = WorldMatrix;

    //������� ������������� ����� ������ ����� ��, ������ � �� ���� �����
    PMatr = glm::perspective(
        glm::radians(67.0f), // ���� ������
        (float)WinWidth / WinHeight,       // ����������� ������
        0.01f,              // ������� ��������� ���������
        10000.0f             // ������� ��������� ���������
    );

    //���� ����
    glClearColor(0.678f, 0.847f, 0.902f, 1.0f);

    //� ��� ��� ���� � 3d ����� �� ������ ��� ����� ������� (���������� ������ ���)
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);



    glm::vec3 Position = { 9.23859,2.28816, 0.707238 };
    glm::vec3 Orientation = { -0.997465, -0.00681765, -0.070843 };
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 cameraMatrix = glm::mat4(1.0f);

    // ������������� ������ ������ ��� ������ ������ ����� ������� ����.
    bool firstClick = true;

    // ������������� �������� ������ � �� ����������������, ����� ������.
    float speed = 0.4f;
    float sensitivity = 100.0f;

    float speed_2 = 2.0f; // �������� �������� ������� �� ��� X (������� � �������)
    float deltaTime = 0.0f; // �����, ��������� � ����������� �����
    float lastFrame = 0.0f; // ����� ���������� �����

    float speed3 = 4.0f;// �������� �������� ����
    int flag = 0;

    float rotation = 0;

    while (!glfwWindowShouldClose(window)) {

        double elapsed = glfwGetTime() - start_time;
        glViewport(0, 0, WinWidth, WinHeight);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // �����
        float rotation = 15.0f * sin(elapsed); // ���� �������� �� -30 �� +30 ��������
        float rotation2 = 5.0f * sin(elapsed); // ���� �������� �� -30 �� +30 ��������

        //����� ������
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // �������� ���� ������
        sea1Position.x += speed_2 * deltaTime; // ������� ������ �� X
        sea2Position.x += speed_2 * deltaTime; // ������� ������ �� X 
        
        if (sea1Position.x >= 1000) {
            sea1Position.x = -1000;

        }
        if (sea2Position.x >= 1000) {
            sea2Position.x = -1000;
        }
        

        // ���
        //flag = 0; ��������� ������� ���� 1
        //flag = 1; ��� ���� ���� 1
        //flag = 2; ��� ������������ � ������� 2
        //flag = 3; ��� ����������� �� ������� 2
        //flag = 4; ��� ���������� � ������� 2
        //flag = 5; ��� ������������ � ������� 3
        //flag = 6; ��� ����������� �� ������� 3
        //flag = 7; ��� ���������� � ������� 3

        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        {
            flag = 1;
        }
        
        if (flag == 1) {
            whalePosition.y += -speed3 * deltaTime;

            if (whalePosition.y < -20) {
                flag = 2;
            }
        }

        //����������� � ������� 2
        if (flag == 2) {
            whalePosition.x += 30 * speed3 * deltaTime;

            if (whalePosition.x > -200) {
                flag = 3;
            }
        }

        // ����������� �� ����������� 2
        if (flag == 3) {
            whalePosition.y += speed3 * deltaTime;
            
            if (whalePosition.y > -1) {
                flag = 4;
            }
        }

        // ���������� � ����������� 2
        if (flag == 4) {
            whalePosition.y += 0.8 * -speed3 * deltaTime;

            if (whalePosition.y < -10) {
                flag = 5;
            }
        }

        //����������� � ������� 3
        if (flag == 5) {
            whalePosition.x += 20 * speed3 * deltaTime;

            if (whalePosition.x > -10) {
                flag = 6;
            }
        }

        // ����������� �� ����������� 3
        if (flag == 6) {
            whalePosition.y += speed3 * deltaTime;

            if (whalePosition.y > -10) {
                whalePosition.y += 0.5 * speed3 * deltaTime;
            }

            if (whalePosition.y > -1) {
                flag = 7;
            }
        }

        // ���������� � ����������� 3
        if (flag == 7) {
            whalePosition.y += 0.7 * -speed3 * deltaTime;

            if (whalePosition.y < -20) {
                flag = 0;
                whalePosition = { -400.0, -1.0, 4.0 };
            }
        }
       
        // ���������� ������� ����
        VMatr = WorldMatrix;
        VMatr = glm::lookAt(Position, Position + Orientation, Up);

        // ����
        MMatr = WorldMatrix;
        MMatr = glm::translate(MMatr, glm::vec3(0.0, 0.0, 0.0));
        MMatr = glm::rotate(MMatr, 0.0f, glm::vec3(1.0, 0.0, 0.0));
        MMatr = glm::rotate(MMatr, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
        MMatr = glm::scale(MMatr, glm::vec3(100, 100, 100));
        sphere.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);

        // ����
        MMatr = WorldMatrix;
        moonPosition = { -400, 200, -50 };
        MMatr = glm::translate(MMatr, moonPosition);
        MMatr = glm::rotate(MMatr, 0.0f, glm::vec3(1.0, 0.0, 0.0));
        MMatr = glm::rotate(MMatr, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
        MMatr = glm::scale(MMatr, glm::vec3(3, 3, 3));
        moon.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);


        // ����
        MMatr = WorldMatrix;
        MMatr = glm::translate(glm::mat4(1.0f), sea1Position);
        MMatr = glm::rotate(MMatr, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
        MMatr = glm::scale(MMatr, glm::vec3(1000.0, 1000.0, 0.0));
        rectangle.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);

        // ���� 2
        MMatr = WorldMatrix;
        MMatr = glm::translate(glm::mat4(1.0f), sea2Position);
        MMatr = glm::rotate(MMatr, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
        MMatr = glm::scale(MMatr, glm::vec3(1000.0, 1000.0, 0.0));
        rectangle2.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);


        // �����
        MMatr = WorldMatrix;
       
        MMatr = glm::translate(glm::mat4(1.0f), boatPosition);
        //����� ��������
        MMatr = glm::rotate(MMatr, glm::radians(rotation), glm::vec3(0.0, 0.0, 1.0));
        MMatr = glm::rotate(MMatr, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
        MMatr = glm::rotate(MMatr, glm::radians(-90.0f), glm::vec3(0.0, 0.0, 1.0));
        MMatr = glm::scale(MMatr, glm::vec3(0.01, 0.01, 0.01));
        boat.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);

        // ����
        MMatr = WorldMatrix;
        tigerPosition = { 0, 0.6, 1.5 };
        MMatr = glm::translate(MMatr, tigerPosition);
        //���� ��������
        MMatr = glm::rotate(MMatr, glm::radians(rotation2), glm::vec3(0.0, 0.0, 1.0));
        MMatr = glm::rotate(MMatr, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
        MMatr = glm::scale(MMatr, glm::vec3(0.06, 0.06, 0.06));
        tiger.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);

        // �������
        MMatr = WorldMatrix;
        manPosition = { 0.3, 0.4, -2 };
        MMatr = glm::translate(MMatr, manPosition);
        //������� ��������
        MMatr = glm::rotate(MMatr, glm::radians(rotation2), glm::vec3(0.0, 0.0, 1.0));
        MMatr = glm::rotate(MMatr, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
        MMatr = glm::scale(MMatr, glm::vec3(0.35, 0.35, 0.35));
        man.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);

        // ���
        MMatr = WorldMatrix;
        MMatr = glm::translate(MMatr, whalePosition);
        MMatr = glm::rotate(MMatr, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
        MMatr = glm::rotate(MMatr, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.0));

        //������ ������� ����
        if (flag == 0 || flag == 1) {
            MMatr = glm::rotate(MMatr, glm::radians(-90.0f), glm::vec3(0.0, 1.0, 0.0));
        }

        //������ ������� ����
        

        //������ ������� ����
        if (flag == 6 || flag == 7) {
            MMatr = glm::rotate(MMatr, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
        }

        MMatr = glm::scale(MMatr, glm::vec3(0.05, 0.05, 0.05));
        whale.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);


        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        {
            Position = { 9.23859,2.28816, 0.707238 };
            Orientation = { -0.997465, -0.00681765, -0.070843 };
        }


        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            Position += speed * Orientation;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            Position += speed * -glm::normalize(glm::cross(Orientation, Up));
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            Position += speed * -Orientation;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            Position += speed * glm::normalize(glm::cross(Orientation, Up));
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
        {
            Position += speed * -Up;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        {
            Position += speed * Up;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            speed = 0.4f;
        }
        else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
        {
            speed = 0.1f;
        }


        // Handles mouse inputs
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            // Hides mouse cursor
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

            // Prevents camera from jumping on the first click
            if (firstClick)
            {
                glfwSetCursorPos(window, (WinWidth / 2), (WinHeight / 2));
                firstClick = false;
            }

            // Stores the coordinates of the cursor
            double mouseX;
            double mouseY;
            // Fetches the coordinates of the cursor
            glfwGetCursorPos(window, &mouseX, &mouseY);

            // Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
            // and then "transforms" them into degrees 
            float rotX = sensitivity * (float)(mouseY - (WinHeight / 2)) / WinHeight;
            float rotY = sensitivity * (float)(mouseX - (WinWidth / 2)) / WinWidth;

            // Calculates upcoming vertical change in the Orientation
            glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

            // Decides whether or not the next vertical Orientation is legal or not
            if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
            {
                Orientation = newOrientation;
            }

            // Rotates the Orientation left and right
            Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

            // Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
            glfwSetCursorPos(window, (WinWidth / 2), (WinHeight / 2));
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
        {
            // Unhides cursor since camera is not looking around anymore
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            // Makes sure the next time the camera looks around it doesn't jump
            firstClick = true;
        }

        glfwPollEvents();
        glfwSwapBuffers(window);
        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(window, 1);

        }
    }
    return 0;
}
    