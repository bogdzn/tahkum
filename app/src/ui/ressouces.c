
#include "exec.h"
#include "parser.h"
#include "ui.h"
#include "utils.h"
#include <GLFW/glfw3.h>

static void error_callback(int error, const char *desc)
{
    __log(ERROR, "GLFW failed with %i -- %s.\n", error, desc);
}

int init_ctx(ctx_t *ctx, int ac, char **av)
{
    int major, minor, revision;

    glfwSetErrorCallback(error_callback);
    glfwGetVersion(&major, &minor, &revision);
    __log(INFO, "Running a with GLFW %i.%i.%i\n", major, minor, revision);
    __log(INFO, "Compiled with GLFW %i.%i.%i\n", GLFW_VERSION_MAJOR,
    GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);
    ctx->user_settings = initial_setup(ac, av);
    ctx->ryzectl = create_default_socket(ctx->user_settings);
    // todo initiate video socket and turn stream on
    if (!glfwInit()) {
        ctx->window = NULL;
        __log(ERROR, "Could not initiate GLFW.\n");
        return 1;
    } else ctx->window = glfwCreateWindow(1280, 768, "tahkum", NULL, NULL);
    ctx->user_settings = send_startup_commands(ctx->ryzectl,
    ctx->user_settings);
    // todo set key callback
    // todo create buffer for video stream
    return 0;
}

void destroy_ctx(ctx_t context)
{
    //todo close video socket
    close_socket(context.ryzectl, context.user_settings);
    __log(WARNING, "Closing window...\n");
    glfwDestroyWindow(context.window);
    glfwTerminate();
}
